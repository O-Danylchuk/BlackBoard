#include "CLI.h"

void CLI::run() {
    std::cout << "Available methods:\ndraw -> draws blackboard to the console\nlist -> shows all added shapes and their parameters\nshapes -> shows all supported figures with needed params\nadd -> adds cpecified figure to the blackboard\nundo -> remofe last added figure\nclear -> remove all figures from the board\nsave <file path> -> state of blackboard is saved to file with cpecivied location\nload -> load state of blackboard to file\n\n" << std::endl;
}