void cleanup_system(SystemState *state) {
	for (int i = 0; i < state->process_count; i++) {
		free(state->processes[i].max_need);
		free(state->processes[i].allocated);
		free(state->processes[i].rem_need);
	}
	free(state->processes);
	free(state->total.resources);
	free(state->available.resources);
}
