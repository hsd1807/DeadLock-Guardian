void print_file_format_instructions() {
	printf("\nFile Format Instructions: \n");
	printf("1. First line : <number of processes> <number of resource types>\n");
	printf("2. Second line : <total resources for each type>\n");
	printf("3. Following lines : <max need> <allocated> for each process\n");
	printf("Example:\n");
	printf("3 4\n");
	printf("10 5 7 8\n");
	printf("7 5 3 1 0 1 0 2\n");
	printf("3 2 2 2 1 0 0 1\n");
	printf("9 0 2 2 1 0 2 0\n");
	printf("\n");
}
