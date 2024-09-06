void user_defined_input(SystemState *state) {
    int processes, resources;
    
    // Prompt user to input the number of processes
    printf("Processes: ");
    scanf("%d", &processes);

    // Validate and normalize the number of processes
    if (processes > MAX_PROCESSES) {
        printf("Number of Processes normalized to 10, to maintain symmetry of matrices\n");
        printf("(You can change this limit by changing the value of MAX_PROCESSES macro.)\n");
        processes = 10;
    }
    else if (processes < 0) {
        printf("INVALID Input, Processes have to be non-negative!\n");
        user_defined_input(state); // Recursive call to re-prompt the user
        return;
    }
    
    // Set process count and allocate memory for process-related arrays
    state->process_count = processes;
    state->processes = (Process *) malloc(processes * sizeof(Process));
    state->completed = (int *) malloc(processes * sizeof(int));
    state->safe = (int *) malloc(processes * sizeof(int));
    
    // Initialize the completed array to 0
    for (int i = 0; i < processes; i++) {
        state->completed[i] = 0;
    }

    // Prompt user to input the number of resources
    printf("Resources : ");
    scanf("%d", &resources);

    // Validate and normalize the number of resources
    if (resources > MAX_RESOURCES) {
        printf("Number of Resources normalized to 26, to maintain symmetry of matrices\n");
        printf("(You can change this limit by changing the value of MAX_RESOURCES macro.)\n");
        resources = 26;
    }
    else if (resources < 0) {
        printf("INVALID Input, Resources have to be non-negative!\n");
        user_defined_input(state); // Recursive call to re-prompt the user
        return;
    }

    // Set resource count and allocate memory for resource-related arrays
    state->resource_count = resources;
    state->total.count = resources;
    state->total.resources = (int *) malloc(resources * sizeof(int));
    state->available.count = resources;
    state->available.resources = (int *) malloc(resources * sizeof(int));

    // Prompt user to input the available resources
    printf("Available Resources (");
    for (int i = 0; i < resources; i++) {
        printf("%c", 'A' + i); // Print resource labels (e.g., A, B, C, ...)
        if (i < resources - 1) printf(", ");
    }
    printf("): ");
    for (int i = 0; i < resources; i++) {
        scanf("%d", &state->total.resources[i]); // Read available resources
        state->available.resources[i] = state->total.resources[i]; // Initialize available resources
    }

    // Prompt user to input the maximum need of each process
    printf("\nMAX NEED\n");
    printf("Process | ");
    for (int i = 0; i < resources; i++) {
        printf("%c|", 'A' + i); // Print resource labels
    }
    printf("\n");

    for (int i = 0; i < processes; i++) {
        state->processes[i].id = i;
        state->processes[i].max_need = (int *) malloc(resources * sizeof(int));
        state->processes[i].allocated = (int *) malloc(resources * sizeof(int));
        state->processes[i].rem_need = (int *) malloc(resources * sizeof(int));

        printf("P%d      : ", i);
        for (int j = 0; j < resources; j++) {
            scanf("%d", &state->processes[i].max_need[j]); // Read max need for each resource
        }
    }

    // Prompt user to input the allocated resources for each process
    printf("\nALLOCATED\n");
    printf("Process | ");
    for (int i = 0; i < resources; i++) {
        printf("%c|", 'A' + i); // Print resource labels
    }
    printf("\n");

    for (int i = 0; i < processes; i++) {
        printf("P%d      : ", i);
        for (int j = 0; j < resources; j++) {
            scanf("%d", &state->processes[i].allocated[j]); // Read allocated resources
            state->processes[i].rem_need[j] = state->processes[i].max_need[j] - state->processes[i].allocated[j]; // Calculate remaining need
            state->available.resources[j] -= state->processes[i].allocated[j]; // Update available resources
        }
    }
}
