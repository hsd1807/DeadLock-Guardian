#include <stdio.h>

typedef struct {
	int count;
	int *resources;
} ResourceList;

typedef struct {
	int id;
	int *max_need;
	int *allocated;
	int *need;
} Process;

typedef struct {
	int process_count;
	Process *processes;
	ResourceList available;
	ResourceList total;
} SystemState;

void welcome_user();

int main() {
	SystemState state;

	welcome_user();

	while (true) {
		break;
	}
	return 0;
}

void welcome_user() {
	printf("Welcome to DeadLock Guardian : A Banker's Algorithm Simulator\n");
	printf("This program simulates resource allocation and deadlock detection\n");
	printf("\n");
}
