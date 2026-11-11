#include <minibox.hxx>

int
main(int argc, char *argv[]) {
    char *_basename = basename(argv[0]);
	if (strcmp(_basename, BINARY_NAME) == 0)
	{
		if (argc == 1)
		{
			usage();
		}
		
		else if (argc == 2 && (strcmp(argv[1], "--help") == 0))
		{
			usage();
		}
		
		else if (argc == 2 && (strcmp(argv[1], "--version") == 0))
		{
			version();
		}
		
		else
		{
			applets_call(argc, argv);
		}
	}
	else
	{
		applets_as_main(argc, argv);
	}
}

void
usage() {
        std::cout << "Usage:\n"
BINARY_NAME " --version\n"
BINARY_NAME " --help\n"
BINARY_NAME " --list\n"
BINARY_NAME " command [[arguments]...]\n\n"
"MiniBox is tool which can be used as an alternative for Busybox\n"
"and Toybox." << std::endl << std::endl <<
"MiniBox Source Code <https://github.com/ayuzzh/MiniBox>\n"
"Email Us for bugs <kmayushkm@gmail.com>\n";
        exit(SUCC_CODE);
}

void
version() {
        std::cout << MINIBOX_NAME << " " << MINIBOX_VERSION << std::endl;
        exit(SUCC_CODE);
}
