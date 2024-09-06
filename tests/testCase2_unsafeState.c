#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define endl printf("\n");

#include "../structures/process.h"
#include "../structures/resourceList.h"
#include "../structures/systemState.h"
#include "../utilities/print_system_state.h"
#include "../algorithms/bankers_algorithm.h"

void input_from_file(SystemState *state) {
	char filename[100] = "testCase2_unsafeState.txt";

	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		printf("File can't be found!\n");
		input_from_file(state);
		return;
	}

	fscanf(file, "%d %d", &state->process_count, &state->resource_count);
	

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

void test_bankers_algorithm() {
    SystemState state;
    state.is_safe = 1;
    
    input_from_file(&state);

    bankers_algorithm(&state);

    assert(state.is_safe == 0);
    printf("Test 2 (UNSAFE STATE) passed!\n");

}


int main() {
	test_bankers_algorithm();
	return 0;
}
