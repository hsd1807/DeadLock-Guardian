void generate_report(SystemState *state, clock_t start_time, clock_t end_time) {
    // Calculate the CPU time used for the simulation
    double cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    // Print the report header and simulation time
    printf("\n=== DeadLock Guardian Report ===\n");
    printf("Simulation Completed in %.6f seconds\n", cpu_time_used);

    // Estimate and print memory usage
    printf("Memory Usage: Approximately %lu bytes\n", 
        sizeof(SystemState) + 
        state->process_count * (sizeof(Process) + 3 * state->resource_count * sizeof(int)) + 
        2 * state->resource_count * sizeof(int));

    // Print the final system state
    printf("\nFinal System State:\n");
    print_system_state(state);

    // Print the safe sequence or indicate if the system is unsafe
    printf("Safe Sequence: ");
    if (state->is_safe) {
        for (int i = 0; i < state->process_count; i++) {
            printf("P%d ", state->safe[i]); // Print the safe sequence
        }
        printf("\n");
    }
    else {
        printf("System is in UNSAFE State. DEADLOCK may occur\n");
    }

    // Ask the user if they want to save the report to a file
    printf("\nDo you want to save highlights of this report to a file? (y/n): ");
    char choice;
    scanf(" %c", &choice); // Read user choice

    if (choice == 'y' || choice == 'Y') {
        // Open the file for writing
        FILE *fp = fopen("algorithm_report.txt", "w");
        if (fp == NULL) {
            printf("Error opening file for writing.\n");
            return; // Exit if file cannot be opened
        }

        // Write the report to the file
        fprintf(fp, "=== DeadLock Guardian Report ===\n\n");
        fprintf(fp, "Simulation completed in %.6f seconds\n", cpu_time_used);
        fprintf(fp, "Memory Usage: approximately %lu bytes\n\n", 
            sizeof(SystemState) + 
            state->process_count * (sizeof(Process) + 3 * state->resource_count * sizeof(int)) + 
            2 * state->resource_count * sizeof(int));

        fprintf(fp, "Final System State: ");

        if (state->is_safe) {
            fprintf(fp, "System is in SAFE State.\n");
            fprintf(fp, "Safe Sequence: ");
            for (int i = 0; i < state->process_count; i++) {
                fprintf(fp, "P%d ", state->safe[i]); // Write the safe sequence to the file
            }
            fprintf(fp, "\n");
        }
        else {
            fprintf(fp, "System is in UNSAFE State. DEADLOCK may occur\n");
        }

        fclose(fp); // Close the file
        printf("Report saved to algorithm_report.txt\n");
    }
}
