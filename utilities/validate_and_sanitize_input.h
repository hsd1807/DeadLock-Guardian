void validate_and_sanitize_input(SystemState *state) {
	for (int i = 0; i < state->process_count; i++) {
		for (int j = 0; j < state->resource_count; j++) {
			if (state->processes[i].max_need[j] < 0) {
				state->processes[i].max_need[j] = 0;
			}
			if (state->processes[i].allocated[j] < 0) {
				state->processes[i].allocated[j] = 0;
			}

			if (state->processes[i].allocated[j] > state->processes[i].max_need[j]) {
			state->processes[i].allocated[j] = state->processes[i].max_need[j];
			}


			state->processes[i].rem_need[j] = state->processes[i].max_need[j] - state->processes[i].allocated[j];
		}
	}
	calculate_remaining_need(state);
	calculate_available_resources(state);

	for (int j = 0; j < state->resource_count; j++) {
	    if (state->available.resources[j] < 0) {
	        state->available.resources[j] = 0;
		}
	}
}
