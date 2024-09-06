void calculate_available_resources(SystemState *state) {
	for (int j = 0; j < state->resource_count; j++) {
		int allocated_sum = 0;
		for (int i = 0; i < state->process_count; i++) {
			allocated_sum += state->processes[i].allocated[j];
		}
		state->available.resources[j] = state->total.resources[j] - allocated_sum;
	}
}
