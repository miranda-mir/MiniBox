#include <minibox.hxx>

int
yes_main(int argc, char *argv[]) {
    std::string msg = "y";
    if(!(argc <= 1)) {
        msg = argv[1];
    }
    while(1) {
        std::cout << msg << std::endl;
    }
}
