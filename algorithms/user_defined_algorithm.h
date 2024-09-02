void user_defined_algorithm(SystemState *state) {
	int process = -1;
	int count = 0;
	do {
		int print = 0;
		printf("\nPress any key to print System State or 0 to continue without printing the System State : ");
		scanf("%d", &print);
		if (print) {
			print_system_state(state);
		}
		
		printf("\nEnter the Process ID to execute:");
		scanf("%d", &process);
		if (process < 0 || process > state->process_count) {
			//Validate Function
		}
		if (!state->completed[process]) {
			for (int j = 0; j < state->resource_count; j++) {
				if (state->available.resources[j] < state->processes[process].rem_need[j]) {
					process = -1;
					break;
				}
			}
		}
		else {
			printf("Process has already been completed\n");
			continue;
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
