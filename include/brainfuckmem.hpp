#pragma once

#include <memory>
#include <iostream>

namespace bf {

    class MemoryCell {
        friend class Memory;
        public:
            MemoryCell();
            ~MemoryCell();

            void increment();
            void decrement();

        private:
            MemoryCell *cell_right;
            MemoryCell *cell_left;
            unsigned char value;
    };

    class Memory {
        public:
            Memory();
            ~Memory();

            void set_current_value(unsigned char val);
            unsigned char get_current_value();

            void move_right();
            void move_left();
            void increment_current();
            void decrement_current();

            void report(std::ostream& out = std::cout);

        private:
            MemoryCell *cell_current;

            int position;
            unsigned int usage;
    };  

}