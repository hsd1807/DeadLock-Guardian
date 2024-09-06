void calculate_remaining_need(SystemState *state) {
	for (int i = 0; i < state->process_count; i++) {
		for (int j = 0;j < state->resource_count; j++) {
			state->processes[i].rem_need[j] = state->processes[i].max_need[j] - state->processes[i].allocated[j];
		}
	}
}
