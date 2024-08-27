bool initialize_system(SystemState *state) {
	void (*input_functions[])(SystemState *) = {user_defined_input, random_input, input_from_file};
	int choice;
	printf("\nHow would you like to give input for system intialization:\n");
	printf("\n");
	printf("1. User-defined Input\n");
	printf("2. Random Input\n");
	printf("3. Input from file\n");
	printf("\n");
	printf("Enter your choice 1, 2, 3 or 0 to exit : ");
	scanf("%d", &choice);
	if (choice < 0 || choice > 3) {
		printf("Invalid choice\n");
		printf("Defaulting to user-defined input.\n");
		printf("Enter 1 to Continue, -1 to go back or 0 to exit : ");
		scanf("%d", &choice);
		if (choice == -1) return initialize_system(state);
		else if (!choice) return 0;
		else choice = 1;	
	}
	else if (!choice) return 0;

	input_functions[choice - 1](state);
	return 1;
}
