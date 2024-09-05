void print_system_state(SystemState *state) {
printf("\n-------------------------------------------------------------------------------------------\n");

	printf("\nCurrent System State:\n");

	printf("\nTotal Resources:\n");
	for (int i = 0; i < state->resource_count; i++) {
		printf("%c: %d ", 'A' + i, state->total.resources[i]);
	}

	printf("\n\nAvailable Resources: \n");
	for (int i = 0; i < state->resource_count; i++) {
		printf("%c: %d ", 'A' + i, state->available.resources[i]);
	}

	printf("\n\nAllocation Matrix:\n");
	printf("Process | ");
	for (int i = 0; i < state->resource_count; i++) {
		printf("%c ", 'A' + i);
	}
	printf("\n");
	for (int i = 0; i < state->resource_count; i++) {
		printf("P%d      | ", i);
		for (int j = 0; j < state->resource_count; j++) {
			printf("%d ", state->processes[i].allocated[j]);
		}
		printf("\n");
	}

	printf("\nMax Need Matrix:\n");
	printf("Process | ");
	for (int i = 0; i < state->resource_count; i++) {
		printf("%c ", 'A' + i);
	}
	printf("\n");
	for (int i = 0; i < state->resource_count; i++) {
		printf("P%d      | ", i);
		for (int j = 0; j < state->resource_count; j++) {
			printf("%d ", state->processes[i].max_need[j]);
		}
		printf("\n");
	}

	printf("\nRemaining Need Matrix:\n");
	printf("Process | ");
	for (int i = 0; i < state->resource_count; i++) {
		printf("%c ", 'A' + i);
	}
	printf("\n");
	for (int i = 0; i < state->process_count; i++) {
		printf("P%d      | ", i);
		for (int j = 0; j < state->resource_count; j++) {
			printf("%d ", state->processes[i].rem_need[j]);
		}
		printf("\n");
	}
	printf("\n-------------------------------------------------------------------------------------------\n");
}
