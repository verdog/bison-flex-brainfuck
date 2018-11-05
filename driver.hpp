#ifndef DRIVER_HH
#define DRIVER_HH
#include <string>
#include <map>
#include "parser.hpp"
#include "brainfuckmem.hpp"

// Give Flex the prototype of yylex we want ...
# define YY_DECL \
  yy::parser::symbol_type yylex (Driver& drv)
// ... and declare it for the parser's sake.
YY_DECL;

class Driver {
    public:
        Driver ();

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

        void do_right(); // process a ">". return 0 on success.
        void do_left(); // process a "<". return 0 on success.
        void do_plus(); // process a "+". return 0 on success.
        void do_minus(); // process a "-". return 0 on success.
        void do_output(); // process a ".". return 0 on success.
        void do_replace(); // process a ",". return 0 on success.
        void do_openbracket(); // process a "[". return 0 on success.
        void do_closebracket(); // process a "]". return 0 on success.

        BrainFuckMemory memory;
};
#endif // ! DRIVER_HH
