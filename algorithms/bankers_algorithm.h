void bankers_algorithm(SystemState *state) {
	int process = -1;
	int count = 0;
	do {
		int print = 0;
		printf("\nPress any key to print System State or 0 to continue without printing the System State : ");
		scanf("%d", &print);
		if (print) {
			print_system_state(state);
		}
		process = -1;
		for (int i = 0; i < state->process_count; i++) {
			if (!state->completed[i]) {
				process = i;
				for (int j = 0; j < state->resource_count; j++) {
					if (state->available.resources[j] < state->processes[i].rem_need[j]) {
						process = -1;
						break;
					}
				}
			}

			if (process != -1) break;
		}

		if (process != -1) {
			printf("Process %d runs to the completion \n", process);
			state->safe[count] = process;
			count++;
			for (int j = 0; j < state->resource_count; j++) {
				state->available.resources[j] += state->processes[process].allocated[j];
				state->processes[process].allocated[j] = 0;
				state->processes[process].max_need[j] = 0;
				state->processes[process].rem_need[j] = 0;
			}
			state->completed[process] = 1;
			printf("New Availabiltiy of Resource : ");
			for (int j = 0; j < state->resource_count; j++) {
				printf("%d ", state->available.resources[j]);
			}
		}
	} while (count != state->process_count && process != -1);

	if (count == state->process_count) {
		printf("\nSystem is in SAFE STATE\n");
		printf("\nSAFE STATE SEQUENCE : < ");

		for (int i = 0; i < state->process_count; i++) {
			printf("%d ", state->safe[i]);
		}
		printf(">\n");
	}
	else {
	        state->is_safe = 0;
		printf("System is in UNSAFE STATE. DEADLOCK may occur.\n");
	}
}
