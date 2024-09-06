#include "file_system.hpp"

int main(int argc, char** argv){
    srand(time(NULL));
    file_system os;
    os.menu();
    return 0;
}