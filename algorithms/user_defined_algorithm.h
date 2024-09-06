void user_defined_algorithm(SystemState *state) {
    int process = -1; // Initialize the process index
    int count = 0; // Count of processes that have completed

    do {
        int print = 0; // Variable to determine whether to print system state
        printf("\nPress any key to print System State or 0 to continue without printing the System State : ");
        scanf("%d", &print); // Get user input
        if (print) {
            print_system_state(state); // Print the current system state if requested
        }
        
        // Prompt user to enter the Process ID to execute
        printf("\nEnter the Process ID to execute:");
        scanf("%d", &process); // Read user input for process ID

        // Validate the process ID
        if (process < 0 || process >= state->process_count) {
            printf("INVALID Process ID, Enter Process ID from 0 to %d", state->process_count - 1);
            continue; // Re-prompt the user if the process ID is invalid
        }

        // Check if the process has already been completed
        if (!state->completed[process]) {
            // Check if resources are sufficient for the selected process
            for (int j = 0; j < state->resource_count; j++) {
                if (state->available.resources[j] < state->processes[process].rem_need[j]) {
                    process = -1; // Mark process as invalid if resources are insufficient
                    break;
                }
            }
        }
        else {
            printf("Process has already been completed\n");
            continue; // Skip to the next iteration if the process is already completed
        }

        // Execute the process if it is valid
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
            printf("\n"); // Print newline (assuming 'endl' is meant to be '\n')
        }
    } while (count != state->process_count && process != -1); // Continue until all processes are completed or no valid process is selected

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
