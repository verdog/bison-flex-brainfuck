#include <iostream>
#include <string>

#include "driver.hh"

int main (int argc, char *argv[]) {
    driver drv;
    std::string file = "-";

    if (argc > 1) {
        file = argv[1];
    }

    drv.parse(file);
}
