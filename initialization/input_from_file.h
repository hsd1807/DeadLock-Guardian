void input_from_file(SystemState *state) {
	char filename[100];

	print_file_format_instructions();

	printf("Enter the name of the input file: ");
	scanf("%s", filename);

	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		printf("File can't be found!\n");
		input_from_file(state);
		return;
	}

	fscanf(file, "%d %d", &state->process_count, &state->resource_count);
	
	if (state->process_count > MAX_PROCESSES) {
		printf("Number of Processes normalized to 10, to maintain symmetry of matrices\n");
		printf("(You can change this limit by changing the value of MAX_PROCESSES macro.)\n");
		 state->process_count = 10;
	}
	else if (state->processes < 0) {
		printf("INVALID Input, Processes have to be non-negative!\n");
		input_from_file(state);
		return;
	}
	
	if (state->resource_count > MAX_RESOURCES) {
	        printf("Number of Resources normalized to 26, to maintain symmetry of matrices\n");
		printf("(You can change this limit by changing the value of MAX_RESOURCES macro.)\n");
		state->resource_count = 26;
	}
	else if (state->resource_count < 0) {
		printf("INVALID Input, Resources have to be non-negative!\n");
		input_from_file(state);
		return;
	}

	state->processes = (Process *) malloc(state->process_count * sizeof(Process));
	state->completed = (int *) malloc(state->process_count * sizeof(int));
	state->safe = (int *) malloc(state->process_count * sizeof(int));
	state->total.count = state->resource_count;
	state->total.resources = (int *) malloc(state->resource_count * sizeof(int));
	state->available.count = state->resource_count;
	state->available.resources = (int *) malloc(state->resource_count * sizeof(int));

	for (int i = 0; i < state->resource_count; i++) {
		fscanf(file, "%d", &state->total.resources[i]);
		state->available.resources[i] = state->total.resources[i];
	}

	for (int i = 0; i < state->process_count; i++) {
		state->processes[i].id = i;
		state->processes[i].max_need = (int *) malloc(state->resource_count * sizeof(int));
		state->processes[i].allocated = (int *) malloc(state->resource_count * sizeof(int));
		state->processes[i].rem_need = (int *) malloc(state->resource_count * sizeof(int));

	for (int j = 0; j < state->resource_count; j++) {
		fscanf(file, "%d", &state->processes[i].max_need[j]);
	}

	for (int j = 0; j < state->resource_count; j++) {
		fscanf(file, "%d", &state->processes[i].allocated[j]);
		state->processes[i].rem_need[j] = state->processes[i].max_need[j] - state->processes[i].allocated[j];
		state->available.resources[j] -= state->processes[i].allocated[j];
		}
	}
	
	fclose(file);
	printf("System State loaded from File successfully.\n");
}
