#include "driver.hpp"
#include "parser.hpp"

Driver::Driver()
: trace_parsing (false)
, trace_scanning (false)
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

int Driver::do_right() {
    memory.move_right();
    return 0;
}

int Driver::do_left() {
    memory.move_left();
    return 0;
}

int Driver::do_plus() {
    memory.increment_current();
    return 0;
}

int Driver::do_minus() {
    memory.decrement_current();
    return 0;
}

int Driver::do_output() {
    std::cout << memory.get_current_value();
    return 0;
}

int Driver::do_replace() {
    unsigned char new_value = fgetc(stdin);
    memory.set_current_value(new_value);
    return 0;
}

int Driver::do_openbracket() {
    return 0;
}

int Driver::do_closebracket() {
    return 0;
}
