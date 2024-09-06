bool simulation_mode(SystemState *state) {
    // Array of function pointers for different simulation algorithms
    void (*algorithms[])(SystemState *) = {bankers_algorithm, user_defined_algorithm};

    // Prompt the user to choose a simulation mode
    printf("Choose Simulation Mode :\n");
    printf("1. Banker's Algorithm Simulation\n");
    printf("2. User-guided Simulation\n");
    printf("Enter your choice 1 or 2 :");

    int mode;
    scanf("%d", &mode); // Read user choice

    // Validate user input
    if (mode < 1 || mode > 2) {
        printf("INVALID Choice\n");
        printf("Defaulting to Banker's Algorithm Simulation\n");

        // Prompt user to either continue with default choice, go back, or exit
        printf("Enter 1 to continue, -1 to go back or 0 to exit :");
        scanf("%d", &mode);

        if (mode == -1) return simulation_mode(state); // Recursively call function to allow user to choose again
        else if (!mode) return 0; // Exit if user enters 0
        else mode = 1; // Default to Banker's Algorithm if user enters any other value
    }

    // Call the selected simulation algorithm
    algorithms[mode - 1](state);

    return 1; // Return 1 to indicate successful execution
}
