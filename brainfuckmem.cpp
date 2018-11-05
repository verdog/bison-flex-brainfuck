#include <iostream>

#include "brainfuckmem.hpp"

/*************************
 * Brainfuck memory cell *
 *************************/

using BFMC = BrainFuckMemoryCell;

BFMC::BrainFuckMemoryCell() 
: cell_right {nullptr}
, cell_left {nullptr}
, value {0x00}
{

}

BFMC::~BrainFuckMemoryCell() {
    if (cell_right != nullptr) {
        delete cell_right;
    }

    // std::cout << "Destroyed a cell.\n";
}

/********************
 * Brainfuck memory *
 ********************/

BrainFuckMemory::BrainFuckMemory() 
: cell_current (new BrainFuckMemoryCell)
, position {0}
, usage {1}
{

}

BrainFuckMemory::~BrainFuckMemory() {
    // cell delete from left to right.
    // start at leftmost cell.
    while (cell_current->cell_left != nullptr) {
        cell_current = cell_current->cell_left;
    }

    delete cell_current;
}

unsigned char BrainFuckMemory::get_current_value() {
    return cell_current->value;
}

void BrainFuckMemory::set_current_value(unsigned char val) {
    cell_current->value = val;
}

void BFMC::increment() {
    value++;
}

void BFMC::decrement() {
    value--;
}

void BrainFuckMemory::move_right() {
    if (cell_current->cell_right == nullptr) {
        cell_current->cell_right = new BrainFuckMemoryCell;
        cell_current->cell_right->cell_left = cell_current;
        usage++;
    }

    cell_current = cell_current->cell_right;

    position++;
}

void BrainFuckMemory::move_left() {
    if (cell_current->cell_left == nullptr) {
        cell_current->cell_left = new BrainFuckMemoryCell;
        cell_current->cell_left->cell_right = cell_current;
        usage++;
    }

    cell_current = cell_current->cell_left;

    position--;
}

void BrainFuckMemory::increment_current() {
    (*cell_current).increment();
}

void BrainFuckMemory::decrement_current() {
    (*cell_current).decrement();
}

void BrainFuckMemory::report(std::ostream& out) {
    out << "Position: " << position << std::endl;
    out << "Value: " << (unsigned int)get_current_value() << std::endl;
    out << "Total memory usage: " << usage << std::endl;
}