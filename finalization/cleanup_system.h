void cleanup_system(SystemState *state) {
    // Iterate over all processes to free allocated memory
    for (int i = 0; i < state->process_count; i++) {
        free(state->processes[i].max_need);    // Free memory allocated for max_need array of each process
        free(state->processes[i].allocated);   // Free memory allocated for allocated array of each process
        free(state->processes[i].rem_need);    // Free memory allocated for rem_need array of each process
    }
    
    // Free memory allocated for process array itself
    free(state->processes);
    
    // Free memory allocated for total resources array
    free(state->total.resources);
    
    // Free memory allocated for available resources array
    free(state->available.resources);
}
