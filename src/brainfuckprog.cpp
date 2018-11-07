#include "driver.hpp"
#include "brainfuckprog.hpp"
#include "brainfuckmem.hpp"

namespace bf {

    namespace pnode {

        /********
         * Base *
         ********/

        Base::Base(Driver &drv, Memory &mem) 
        : memory {mem}
        , driver {drv}
        , next {nullptr}
        , isReady {false}
        , outputStream {std::cout}
        {

        }

        /*******
         * Add *
         *******/

        Add::Add(Driver &drv, Memory &mem)
        : Base(drv, mem) 
        {
            isReady = true;
        };

        void Add::execute() {
            memory.increment_current();
            driver.program_pointer = this->next;
        }

        /************
         * Subtract *
         ************/

        Subtract::Subtract(Driver &drv, Memory &mem)
        : Base(drv, mem) 
        {
            isReady = true;
        };

        void Subtract::execute() {
            memory.decrement_current();
            driver.program_pointer = this->next;
        }

        /*********
         * Right *
         *********/

        Right::Right(Driver &drv, Memory &mem)
        : Base(drv, mem) 
        {
            isReady = true;
        };

        void Right::execute() {
            memory.move_right();
            driver.program_pointer = this->next;
        }

        /********
         * Left *
         ********/

        Left::Left(Driver &drv, Memory &mem)
        : Base(drv, mem) 
        {
            isReady = true;
        };

        void Left::execute() {
            memory.move_left();
            driver.program_pointer = this->next;
        }

        /**********
         * Output *
         **********/

        Output::Output(Driver &drv, Memory &mem)
        : Base(drv, mem) 
        {
            isReady = true;
        };

        void Output::execute() {
            outputStream << memory.get_current_value();
            driver.program_pointer = this->next;
        }

        /*********
         * Input *
         *********/

        Input::Input(Driver &drv, Memory &mem)
        : Base(drv, mem) 
        {
            isReady = true;
        };

        void Input::execute() {
            char input = fgetc(stdin);
            memory.set_current_value(input);
            driver.program_pointer = this->next;
        }

        /************
         * OpenLoop *
         ************/

        OpenLoop::OpenLoop(Driver &drv, Memory &mem)
        : Base(drv, mem)
        , loop_link {nullptr}
        {
            isReady = false;
        };

        void OpenLoop::execute() {
            if (!isReady) {
                std::cerr << "left bracket wasn't ready!\n";
                throw "left bracket wasn't ready!";
            }

            if (loop_link == nullptr) {
                std::cerr << "Can't jump forward to a null pointer!";
                throw "Can't jump forward to a null pointer!";
            }

            char current_val = memory.get_current_value();

            if (current_val == 0x00) {
                driver.program_pointer = loop_link;
            } else {
                driver.program_pointer = this->next;
            }
        }

        void OpenLoop::link(CloseLoop* cl) {
            loop_link = cl;
            isReady = true;
        }

        /*************
         * CloseLoop *
         *************/

        CloseLoop::CloseLoop(Driver &drv, Memory &mem)
        : Base(drv, mem)
        , loop_link {nullptr}
        {
            isReady = true;
        };

        void CloseLoop::execute() {
            if (loop_link == nullptr) {
                std::cerr << "Can't jump back to a null pointer!\n";
                throw "Can't jump back to a null pointer!";
            }

            char current_val = memory.get_current_value();

            if (current_val != 0x00) {
                driver.program_pointer = loop_link;
            } else {
                driver.program_pointer = this->next;
            }
        }

        void CloseLoop::link(OpenLoop* ol) {
            loop_link = ol;
        }

    } // pnode

} // bf