typedef struct {
	int process_count;
	Process *processes;
	int resource_count;
	ResourceList available;
	ResourceList total;
	int *completed;
	int *safe;
	int is_safe;
} SystemState;
