bool initialize_system(SystemState *state) {
    // Array of function pointers to different input methods
    void (*input_functions[])(SystemState *) = {user_defined_input, random_input, input_from_file};
    int choice;

    // Prompt user to choose an input method for system initialization
    printf("\nHow would you like to give input for system initialization:\n");
    printf("\n");
    printf("1. User-defined Input\n");
    printf("2. Random Input\n");
    printf("3. Input from file\n");
    printf("\n");
    printf("Enter your choice 1, 2, 3 or 0 to exit : ");
    scanf("%d", &choice);

    // Validate the user's choice
    if (choice < 0 || choice > 3) {
        // Handle invalid choice by defaulting to user-defined input
        printf("Invalid choice\n");
        printf("Defaulting to user-defined input.\n");
        printf("Enter 1 to Continue, -1 to go back or 0 to exit : ");
        scanf("%d", &choice);

        if (choice == -1) {
            // Recursive call to re-prompt the user
            return initialize_system(state);
        }
        else if (!choice) {
            // Exit if user chooses to exit
            return 0;
        }
        else {
            // Set choice to 1 if the user chooses to continue
            choice = 1;
        }
    }
    else if (!choice) {
        // Exit if the user chooses 0
        return 0;
    }

    // Call the appropriate input function based on the user's choice
    input_functions[choice - 1](state);

    // Set the system state to safe initially
    state->is_safe = 1;
    return 1;
}
