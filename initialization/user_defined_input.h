void user_defined_input(SystemState *state) {
	int processes, resources;
	
	printf("Processes: ");
	scanf("%d", &processes);

	if (processes > MAX_PROCESSES) {
		printf("Number of Processes normalized to 10, to maintain symmetry of matrices\n");
		printf("(You can change this limit by changing the value of MAX_PROCESSES macro.)\n");
		processes = 10;
	}
	else if (processes < 0) {
		printf("INVALID Input, Processes have to be non-negative!\n");
		user_defined_input(state);
		return;
	}
	state->process_count = processes;
	state->processes = (Process *) malloc(processes * sizeof(Process));
	state->completed = (int *) malloc(processes * sizeof(int));
	state->safe = (int *) malloc(processes * sizeof(int));
	
	for (int i = 0; i < processes; i++) {
		state->completed[i] = 0;
	}

	printf("Resources : ");
	scanf("%d", &resources);

	if (resources > MAX_RESOURCES) {
	        printf("Number of Resources normalized to 26, to maintain symmetry of matrices\n");
		printf("(You can change this limit by changing the value of MAX_RESOURCES macro.)\n");
		resources = 26;
	}
	else if (resources < 0) {
		printf("INVALID Input, Resources have to be non-negative!\n");
		user_defined_input(state);
		return;
	}
	state->resource_count = resources;
	state->total.count = resources;
	state->total.resources = (int *) malloc(resources * sizeof(int));
	state->available.count = resources;
	state->available.resources = (int *) malloc(resources * sizeof(int));

	printf("Available Resources (");
	for (int i = 0; i < resources; i++) {
		printf("%c", 'A' + i);
		if (i < resources - 1) printf (", ");
	}
	printf("): ");
	for (int i = 0; i < resources; i++) {
		scanf("%d", &state->total.resources[i]);
		state->available.resources[i] = state->total.resources[i];
	}

	printf("\nMAX NEED\n");
	printf("Process | ");
	for (int i = 0; i < resources; i++) {
		printf("%c|", 'A' + i);
	}
	printf("\n");

	for (int i = 0; i < processes; i++) {
		state->processes[i].id = i;
		state->processes[i].max_need = (int *) malloc(resources * sizeof(int));
		state->processes[i].allocated = (int *) malloc(resources * sizeof(int));
		state->processes[i].rem_need = (int *) malloc(resources * sizeof(int));

		printf("P%d      : ", i);
		for (int j = 0; j < resources; j++) {
			scanf("%d", &state->processes[i].max_need[j]);
		}
	}

	printf("\nALLOCATED\n");
	printf("Process | ");
	for (int i = 0; i < resources; i++) {
		printf("%c|", 'A' + i);
	}
	printf("\n");

	for (int i = 0; i < processes; i++) {
		printf("P%d      : ", i);
		for (int j = 0; j < resources; j++) {
			scanf("%d", &state->processes[i].allocated[j]);
			state->processes[i].rem_need[j] = state->processes[i].max_need[j] - state->processes[i].allocated[j];
			state->available.resources[j] -= state->processes[i].allocated[j];
		}
	}
}
