#include <minibox.hxx>

void applets_call(int argc, char *argv[])
{
	int _argc = argc - 1;
	char** _argv = new char*[_argc];

	for (int i = 0; i < _argc; i++)
	{
		_argv[i] = argv[i+1];
	}

	if (1 == 2)
	{ /*This will never execute*/
	}

#if ECHO_BUILD == ON
	else if (strcmp(argv[1], "echo") == 0)
	{
		echo_main(_argc, _argv);
	}
#endif

#if TRUE_BUILD == ON
	else if (strcmp(argv[1], "true") == 0)
	{
		true_main();
	}
#endif

#if FALSE_BUILD == ON
	else if (strcmp(argv[1], "false") == 0)
	{
		false_main();
	}
#endif

#if CLEAR_BUILD == ON
	else if (strcmp(argv[1], "clear") == 0)
	{
		clear_main(_argc, _argv);
	}
#endif

#if RESET_BUILD == ON
	else if (strcmp(argv[1], "reset") == 0)
	{
		reset_main(_argc, _argv);
	}
#endif

	else
	{
		std::cout << argv[1] << ": " << CMD_NOT_FOUND << std::endl;
		exit(ERR_CODE);
	}

	delete[] _argv;
}

void
applets_as_main(int argc, char *argv[]) {
	char* _basename = basename(argv[0]);
	if (1 == 2)
	{ /*This will never execute*/
	}

#if ECHO_BUILD == ON
	else if (strcmp(_basename, "echo") == 0)
	{
		echo_main(argc, argv);
	}
#endif

#if TRUE_BUILD == ON
	else if (strcmp(_basename, "true") == 0)
	{
		true_main();
	}
#endif

#if FALSE_BUILD == ON
	else if (strcmp(_basename, "false") == 0)
	{
		false_main();
	}
#endif

#if CLEAR_BUILD == ON
	else if (strcmp(_basename, "clear") == 0)
	{
		clear_main(argc, argv);
	}
#endif

#if CLEAR_BUILD == ON
	else if (strcmp(_basename, "reset") == 0)
	{
		reset_main(argc, argv);
	}
#endif

	else
	{
		std::cout << argv[0] << ": " << CMD_NOT_FOUND << std::endl;
		exit(ERR_CODE);
	}
}
