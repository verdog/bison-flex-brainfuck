#ifndef DRIVER_HH
#define DRIVER_HH
#include <string>
#include <map>
#include "parser.hpp"
#include "brainfuckmem.hpp"
#include "brainfuckprog.hpp"

// Give Flex the prototype of yylex we want ...
# define YY_DECL \
  yy::parser::symbol_type yylex (Driver& drv)
// ... and declare it for the parser's sake.
YY_DECL;

class Driver {
    public:
        Driver();

        // Run the parser on file F.  Return 0 on success.
        int parse (const std::string& f);

        // The name of the file being parsed.
        std::string file;

        // Handling the scanner.
        void scan_begin ();
        void scan_end ();

        // Whether to generate scanner debug traces.
        bool trace_scanning;
        // Whether to generate parser debug traces.
        bool trace_parsing;

        bf::Memory memory;
        bf::pnode::Base *program_pointer;
        bf::pnode::Base *last_node;

        std::vector<bf::pnode::OpenLoop*> loop_stack;

        void add_symbol(bf::pnode::Base* node);
        void run();
};
#endif // ! DRIVER_HH
