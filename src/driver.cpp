#include "driver.hpp"
#include "parser.hpp"

Driver::Driver()
: trace_parsing (false)
, trace_scanning (false)
, program_pointer {nullptr}
, last_node {nullptr}
{
    //
}

int Driver::parse(const std::string &f) {
    file = f;
    scan_begin(); // defined in .ll file
    yy::parser parser(*this);
    parser.set_debug_level(trace_parsing);
    int res = parser();
    scan_end(); // defined in .ll file
    return res;
}

void Driver::add_symbol(bf::pnode::Base *node) {
    if (last_node == nullptr) {
        // starting a new list
        program_pointer = node;
        last_node = node;
    } else {
        // adding to the end of the list
        last_node->next = node;
        last_node = node;

        if (program_pointer == nullptr) {
            program_pointer = node;
        }
    }

    if (auto open_loop = dynamic_cast<bf::pnode::OpenLoop*>(node)) {
        // node is an open loop. add it to the stack.
        loop_stack.push_back(open_loop);
    } else if (auto close_loop = dynamic_cast<bf::pnode::CloseLoop*>(node)) {
        // node is an close loop. 
        // link it to the top open loop and pop the open loop off the stack.
        if (loop_stack.empty()) {
            std::cout << "Used a closing bracket before opening one!\n";
            throw "Used a closing bracket before opening one!";
        }

        auto open_loop = loop_stack.back();

        close_loop->link(open_loop);
        open_loop->link(close_loop);

        loop_stack.pop_back();
    }
}

void Driver::run() {
    while (program_pointer != nullptr && program_pointer->isReady) {
        program_pointer->execute();
        // memory.report();
    }
}