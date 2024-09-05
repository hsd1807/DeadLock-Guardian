void generate_report(SystemState *state, clock_t start_time, clock_t end_time) {
	double cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

	printf("\n=== DeadLock Guardian Report ===\n");
	printf("Simulation Completed in %.2f seconds\n", cpu_time_used);
	printf("Memory Usage: Approximately %lu bytes\n", sizeof(SystemState) + state->process_count * (sizeof(Process) + 3 * state->resource_count * sizeof(int)) + 2 * state->resource_count * sizeof(int));
	printf("\nFinal System State:\n");
	print_system_state(state);

	printf("Safe Sequence: ");
	if (state->is_safe) {
		for (int i = 0; i < state->process_count; i++) {
			printf("P%d ", state->safe[i]);
		}
		printf("\n");
	}
	else {
		printf("System is in UNSAFE State. DEADLOCK may occur\n");
	}

	printf("\nDo you want to save this report to a file? (y/n): ");
	char choice;
	scanf("%c", &choice);

	if (choice == 'y' || choice == 'Y') {
		FILE *fp = fopen("algorithm_report.txt", "w");
		if (fp == NULL) {
			printf("Error opening file for writing.\n");
			return;
		}

		fprintf(fp, "=== DeadLock Guardian Report ===\n");
		fprintf(fp, "Simulation completed in %.2f seconds\n", cpu_time_used);
		fprintf(fp, "Memory Usage: approximately %lu bytes\n\n", sizeof(SystemState) + state->process_count * (sizeof(Process) + 3 * state->resource_count * sizeof(int)) + 2 * state->resource_count * sizeof(int));

		fprintf(fp, "Final System State:\n");

		fprintf(fp, "Safe Sequence: ");
		if (state->is_safe) {
			for (int i = 0; i < state->process_count; i++) {
				fprintf(fp, "P%d ", state->safe[i]);
			}
			fprintf(fp, "\n");
		}
		else {
			fprintf(fp, "System is in UNSAFE State. DEADLOCK may occur\n");
		}

		fclose(fp);
		printf("Report saved to algorithm_report.txt\n");
	}
}
