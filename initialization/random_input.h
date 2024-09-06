void random_input(SystemState *state) {
    // Seed the random number generator with the current time
    srand(time(NULL));

    // Prompt user to input the number of processes
    printf("Enter the number of Processes : ");
    scanf("%d", &state->process_count);

    // Prompt user to input the number of resources
    printf("Enter the number of Resources : ");
    scanf("%d", &state->resource_count);

    // Validate and normalize the number of processes
    if (state->process_count > MAX_PROCESSES) {
        printf("Number of Processes normalized to 10, to maintain symmetry of matrices\n");
        printf("(You can change this limit by changing the value of MAX_PROCESSES macro.)\n");
        state->process_count = 10;
    }
    else if (state->process_count < 0) {
        printf("INVALID Input, Processes have to be non-negative!\n");
        random_input(state); // Recursive call to re-prompt the user
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
        random_input(state); // Recursive call to re-prompt the user
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

    // Generate random values for total resources and initialize available resources
    for (int i = 0; i < state->resource_count; i++) {
        state->total.resources[i] = rand() % 100; // Random value between 0 and 99
        state->available.resources[i] = state->total.resources[i]; // Initialize available resources
    }

    // Generate random values for processes' resource needs and allocations
    for (int i = 0; i < state->process_count; i++) {
        state->processes[i].id = i;
        state->processes[i].max_need = (int *) malloc(state->resource_count * sizeof(int));
        state->processes[i].allocated = (int *) malloc(state->resource_count * sizeof(int));
        state->processes[i].rem_need = (int *) malloc(state->resource_count * sizeof(int));

        for (int j = 0; j < state->resource_count; j++) {
            // Random maximum need up to 50% of total resources
            state->processes[i].max_need[j] = rand() % (int)(state->total.resources[j] * 0.5 + 1);
            // Randomly allocate resources up to the maximum need
            state->processes[i].allocated[j] = rand() % (state->processes[i].max_need[j] + 1);
            // Calculate remaining need
            state->processes[i].rem_need[j] = state->processes[i].max_need[j] - state->processes[i].allocated[j];
            // Update available resources
            state->available.resources[j] -= state->processes[i].allocated[j];
        }
    }

    // Notify the user that the random system state has been generated
    printf("Random System State generated successfully.\n");
}
