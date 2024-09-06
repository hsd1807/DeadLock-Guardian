void bankers_algorithm(SystemState *state) {
    int process = -1; // Initialize the process index
    int count = 0; // Count of processes that have completed

    do {
        int print = 0; // Variable to determine whether to print system state
        printf("\nPress any key to print System State or 0 to continue without printing the System State : ");
        scanf("%d", &print); // Get user input
        if (print) {
            print_system_state(state); // Print the current system state if requested
        }

        process = -1; // Reset the process index
        for (int i = 0; i < state->process_count; i++) {
            if (!state->completed[i]) { // Check if the process is not completed
                process = i;
                for (int j = 0; j < state->resource_count; j++) {
                    // Check if resources are sufficient for the process
                    if (state->available.resources[j] < state->processes[i].rem_need[j]) {
                        process = -1; // If not sufficient, set process to -1
                        break;
                    }
                }
            }

            if (process != -1) break; // Break out of the loop if a valid process is found
        }

        if (process != -1) {
            printf("Process %d runs to the completion \n", process);
            state->safe[count] = process; // Record the process as part of the safe sequence
            count++;
            // Update the available resources and reset the process's resource allocations
            for (int j = 0; j < state->resource_count; j++) {
                state->available.resources[j] += state->processes[process].allocated[j];
                state->processes[process].allocated[j] = 0;
                state->processes[process].max_need[j] = 0;
                state->processes[process].rem_need[j] = 0;
            }
            state->completed[process] = 1; // Mark the process as completed
            printf("New Availability of Resource: ");
            for (int j = 0; j < state->resource_count; j++) {
                printf("%d ", state->available.resources[j]); // Print the new resource availability
            }
            printf("\n"); // Print newline
        }
    } while (count != state->process_count && process != -1); // Continue until all processes are completed or no process can proceed

    if (count == state->process_count) {
        // If all processes are completed, print the safe state sequence
        printf("\nSystem is in SAFE STATE\n");
        printf("\nSAFE STATE SEQUENCE : < ");

        for (int i = 0; i < state->process_count; i++) {
            printf("%d ", state->safe[i]); // Print the safe sequence
        }
        printf(">\n");
    }
    else {
        // If not all processes are completed, the system is in an unsafe state
        state->is_safe = 0;
        printf("System is in UNSAFE STATE. DEADLOCK may occur.\n");
    }
}
