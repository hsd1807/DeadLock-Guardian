void input_from_file(SystemState *state) {
    char filename[100];

    // Print instructions for file format
    print_file_format_instructions();

    // Prompt user to input the name of the file containing system state
    printf("Enter the name of the input file: ");
    scanf("%s", filename);

    // Open the file for reading
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        // Error handling if file cannot be opened
        printf("File can't be found!\n");
        input_from_file(state); // Recursive call to re-prompt the user
        return;
    }

    // Read the number of processes and resources from the file
    fscanf(file, "%d %d", &state->process_count, &state->resource_count);
    
    // Validate and normalize the number of processes
    if (state->process_count > MAX_PROCESSES) {
        printf("Number of Processes normalized to 10, to maintain symmetry of matrices\n");
        printf("(You can change this limit by changing the value of MAX_PROCESSES macro.)\n");
        state->process_count = 10;
    }
    else if (state->process_count < 0) {
        printf("INVALID Input, Processes have to be non-negative!\n");
        input_from_file(state); // Recursive call to re-prompt the user
        return;
    }

    // Validate and normalize the number of resources
    if (state->resource_count > MAX_RESOURCES) {
        printf("Number of Resources normalized to 26, to maintain symmetry of matrices\n");
        printf("(You can change this limit by changing the value of MAX_RESOURCES macro.)\n");
        state->resource_count = 26;
    }
    else if (state->resource_count < 0) {
        printf("INVALID Input, Resources have to be non-negative!\n");
        input_from_file(state); // Recursive call to re-prompt the user
        return;
    }

    // Allocate memory for processes and resource arrays
    state->processes = (Process *) malloc(state->process_count * sizeof(Process));
    state->completed = (int *) malloc(state->process_count * sizeof(int));
    state->safe = (int *) malloc(state->process_count * sizeof(int));
    state->total.count = state->resource_count;
    state->total.resources = (int *) malloc(state->resource_count * sizeof(int));
    state->available.count = state->resource_count;
    state->available.resources = (int *) malloc(state->resource_count * sizeof(int));

    // Read the total resources from the file and initialize available resources
    for (int i = 0; i < state->resource_count; i++) {
        fscanf(file, "%d", &state->total.resources[i]);
        state->available.resources[i] = state->total.resources[i];
    }

    // Read the maximum needs and allocated resources for each process from the file
    for (int i = 0; i < state->process_count; i++) {
        state->processes[i].id = i;
        state->processes[i].max_need = (int *) malloc(state->resource_count * sizeof(int));
        state->processes[i].allocated = (int *) malloc(state->resource_count * sizeof(int));
        state->processes[i].rem_need = (int *) malloc(state->resource_count * sizeof(int));

        // Read maximum need for each resource for the current process
        for (int j = 0; j < state->resource_count; j++) {
            fscanf(file, "%d", &state->processes[i].max_need[j]);
        }

        // Read allocated resources for each resource for the current process
        for (int j = 0; j < state->resource_count; j++) {
            fscanf(file, "%d", &state->processes[i].allocated[j]);
            // Calculate remaining need and update available resources
            state->processes[i].rem_need[j] = state->processes[i].max_need[j] - state->processes[i].allocated[j];
            state->available.resources[j] -= state->processes[i].allocated[j];
        }
    }

    // Close the file and notify the user that the system state has been loaded successfully
    fclose(file);
    printf("System State loaded from File successfully.\n");
}
