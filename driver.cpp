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
