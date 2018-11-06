#include <iostream>
#include <string>

#include "driver.hpp"

int main (int argc, char *argv[]) {
    Driver drv;
    std::string file = "-";

    if (argc > 1) {
        file = argv[1];
    }

    drv.parse(file);
}
