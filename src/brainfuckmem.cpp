#include <iostream>

#include "brainfuckmem.hpp"

namespace bf {

    /*************************
     * Brainfuck memory cell *
     *************************/

    MemoryCell::MemoryCell() 
    : cell_right {nullptr}
    , cell_left {nullptr}
    , value {0x00}
    {

    }

    MemoryCell::~MemoryCell() {
        if (cell_right != nullptr) {
            delete cell_right;
        }

        // std::cout << "Destroyed a cell.\n";
    }

    /********************
     * Brainfuck memory *
     ********************/

    Memory::Memory() 
    : cell_current (new MemoryCell)
    , position {0}
    , usage {1}
    {

    }

    Memory::~Memory() {
        // cell delete from left to right.
        // start at leftmost cell.
        while (cell_current->cell_left != nullptr) {
            cell_current = cell_current->cell_left;
        }

        delete cell_current;
    }

    unsigned char Memory::get_current_value() {
        return cell_current->value;
    }

    void Memory::set_current_value(unsigned char val) {
        cell_current->value = val;
    }

    void MemoryCell::increment() {
        value++;
    }

    void MemoryCell::decrement() {
        value--;
    }

    void Memory::move_right() {
        if (cell_current->cell_right == nullptr) {
            cell_current->cell_right = new MemoryCell;
            cell_current->cell_right->cell_left = cell_current;
            usage++;
        }

        cell_current = cell_current->cell_right;

        position++;
    }

    void Memory::move_left() {
        if (cell_current->cell_left == nullptr) {
            cell_current->cell_left = new MemoryCell;
            cell_current->cell_left->cell_right = cell_current;
            usage++;
        }

        cell_current = cell_current->cell_left;

        position--;
    }

    void Memory::increment_current() {
        (*cell_current).increment();
    }

    void Memory::decrement_current() {
        (*cell_current).decrement();
    }

    void Memory::report(std::ostream& out) {
        out << "Position: " << position << std::endl;
        out << "Value: " << (unsigned int)get_current_value() << std::endl;
        out << "Total memory usage: " << usage << std::endl;
    }

}