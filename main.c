#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 26

#define endl printf("\n")

#include "structures/process.h"
#include "structures/resourceList.h"
#include "structures/systemState.h"

void welcome_user();

bool initialize_system(SystemState *state);

bool simulation_mode(SystemState *state);

void bankers_algorithm(SystemState *state);

void user_defined_algorithm(SystemState *state);

void validate_and_sanitize_input(SystemState *state);

void print_system_state(SystemState *state);

void print_file_format_instructions();

void input_from_file(SystemState *state);

void user_defined_input(SystemState *state);

void random_input(SystemState *state);

void calculate_remaining_need(SystemState *state);

void calculate_available_resources(SystemState *state);

void validate_and_sanitize_input(SystemState *state);

void print_system_state(SystemState *state);

void generate_report(SystemState *state, clock_t start_time, clock_t end_time);

void cleanup_system(SystemState *state);

#include "initialization/initialize_system.h"
#include "initialization/user_defined_input.h"
#include "initialization/print_file_format_instructions.h"
#include "initialization/input_from_file.h"
#include "initialization/random_input.h"

#include "utilities/print_system_state.h"

#include "algorithms/simulation_mode.h"
#include "algorithms/bankers_algorithm.h"
#include "algorithms/user_defined_algorithm.h"

#include "finalization/generate_report.h"
#include "finalization/cleanup_system.h"

int main() {
	SystemState state;
	clock_t start_time, end_time;

	welcome_user();

	while (true) {
		if (initialize_system(&state)) {
			start_time = clock();
			validate_and_sanitize_input(&state);

			print_system_state(&state);

			printf("\nSystem State after getting validated and sanitized\n\n");

			
			bool exit = false;
			
			if (!simulation_mode(&state)) {
				exit = true;
			}
			end_time = clock();

			generate_report(&state, start_time, end_time);

			cleanup_system(&state);

			if (exit) break;

			printf("\nDo you want to run another simulation? (1/0):  ");
			int choice;
			scanf("%d", &choice);
			if (!choice) break;
		}
		else {
			break;
		}
	}
	return 0;
}

void welcome_user() {
	printf("Welcome to DeadLock Guardian : A Banker's Algorithm Simulator\n");
	printf("This program simulates resource allocation and deadlock detection\n");
	printf("\n");
}

void calculate_remaining_need(SystemState *state) {
	for (int i = 0; i < state->process_count; i++) {
		for (int j = 0;j < state->resource_count; j++) {
			state->processes[i].rem_need[j] = state->processes[i].max_need[j] - state->processes[i].allocated[j];
		}
	}
}

void calculate_available_resources(SystemState *state) {
	for (int j = 0; j < state->resource_count; j++) {
		int allocated_sum = 0;
		for (int i = 0; i < state->process_count; i++) {
			allocated_sum += state->processes[i].allocated[j];
		}
		state->available.resources[j] = state->total.resources[j] - allocated_sum;
	}
}

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
