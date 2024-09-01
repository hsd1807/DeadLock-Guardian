bool simulation_mode(SystemState *state) {
                        void (*algorithms[])(SystemState *) = {bankers_algorithm, user_defined_algorithm};
			printf("Choose Simulation Mode :\n");
			printf("1. Banker's Algorithm Simulation\n");
			printf("2. User-guided Simulation\n");
			printf("Enter your choice 1 or 2 :");
			
			int mode;
			scanf("%d", &mode);

			if (mode < 1 || mode > 2) {
				printf("INVALID Choice\n");
				printf("Defaulting to Banker's Algorithm Simulation\n");
				printf("Enter 1 to continue, -1 to go back or 0 to exit :");
				scanf("%d", &mode);
				if (mode == -1) return simulation_mode(state);
				else if (!mode) return 0;
				else mode = 1;
			}

			algorithms[mode - 1](state);

			return 1;
}
