#ifndef APPLETS
#define APLLETS

#include <config.h>

int echo_main(int argc, char* argv[]);
int true_main();
int false_main();
int clear_main(int argc, char *argv[]);
int reset_main(int argc, char *argv[]);

void applets_call(int argc, char* argv[]);
void applets_as_main(int argc, char* argv[]);
void usage();
void version();

#endif	/*APPLETS*/
