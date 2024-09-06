void print_system_state(SystemState *state) {
    // Print a separator line for clarity
    printf("\n-------------------------------------------------------------------------------------------\n");

    // Display the header for the current system state
    printf("\nCurrent System State:\n");

    // Print the total resources available in the system
    printf("\nTotal Resources:\n");
    for (int i = 0; i < state->resource_count; i++) {
        printf("%c: %d ", 'A' + i, state->total.resources[i]);
    }

    // Print available resources currently not allocated
    printf("\n\nAvailable Resources: \n");
    for (int i = 0; i < state->resource_count; i++) {
        printf("%c: %d ", 'A' + i, state->available.resources[i]);
    }

    // Print the Allocation Matrix
    printf("\n\nAllocation Matrix:\n");
    printf("Process | ");
    for (int i = 0; i < state->resource_count; i++) {
        printf("%c ", 'A' + i); // Print resource labels
    }
    printf("\n");
    // Print allocation for each process
    for (int i = 0; i < state->process_count; i++) {
        printf("P%d      | ", i); // Print process ID
        for (int j = 0; j < state->resource_count; j++) {
            printf("%d ", state->processes[i].allocated[j]); // Print allocated resources
        }
        printf("\n");
    }

    // Print the Max Need Matrix
    printf("\nMax Need Matrix:\n");
    printf("Process | ");
    for (int i = 0; i < state->resource_count; i++) {
        printf("%c ", 'A' + i); // Print resource labels
    }
    printf("\n");
    // Print max need for each process
    for (int i = 0; i < state->process_count; i++) {
        printf("P%d      | ", i); // Print process ID
        for (int j = 0; j < state->resource_count; j++) {
            printf("%d ", state->processes[i].max_need[j]); // Print maximum need
        }
        printf("\n");
    }

    // Print the Remaining Need Matrix
    printf("\nRemaining Need Matrix:\n");
    printf("Process | ");
    for (int i = 0; i < state->resource_count; i++) {
        printf("%c ", 'A' + i); // Print resource labels
    }
    printf("\n");
    // Print remaining need for each process
    for (int i = 0; i < state->process_count; i++) {
        printf("P%d      | ", i); // Print process ID
        for (int j = 0; j < state->resource_count; j++) {
            printf("%d ", state->processes[i].rem_need[j]); // Print remaining need
        }
        printf("\n");
    }

    // Print a separator line for clarity
    printf("\n-------------------------------------------------------------------------------------------\n");
}
