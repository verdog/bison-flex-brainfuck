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
    std::cout << "Destroyed a cell.\n";
}

unsigned char BFMC::get_value() {
    return value;
}

void BFMC::set_value(unsigned char val) {
    value = val;
}

/********************
 * Brainfuck memory *
 ********************/

BrainFuckMemory::BrainFuckMemory() 
: cell_current (new BrainFuckMemoryCell)
, position {0}
{

}

unsigned char BrainFuckMemory::get_current_value() {
    return cell_current->get_value();
}

void BrainFuckMemory::set_current_value(unsigned char val) {
    cell_current->set_value(val);
}

void BrainFuckMemory::move_right() {
    if (cell_current->cell_right == nullptr) {
        cell_current->cell_right = std::shared_ptr<BrainFuckMemoryCell>(new BrainFuckMemoryCell);
        cell_current->cell_right->cell_left = cell_current;
        usage++;
    }

    cell_current = cell_current->cell_right;

    position++;
}

void BrainFuckMemory::move_left() {
    if (cell_current->cell_left == nullptr) {
        cell_current->cell_left = std::shared_ptr<BrainFuckMemoryCell>(new BrainFuckMemoryCell);
        cell_current->cell_left->cell_right = cell_current;
        usage++;
    }

    cell_current = cell_current->cell_left;

    position--;
}

void BrainFuckMemory::report(std::ostream& out) {
    out << "Position: " << position << std::endl;
    out << "Value: " << get_current_value() << std::endl;
    out << "Total memory usage: " << usage << std::endl;
}