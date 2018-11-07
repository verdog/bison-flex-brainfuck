#pragma once

#include <iostream>

class Driver;

namespace bf {

    class Memory;

    namespace pnode {

        class Base {
            public:
                Base(Driver &drv, Memory &mem);

                virtual void execute() = 0;

                Base *next;
                Memory &memory;
                Driver &driver;
                bool isReady;
                std::ostream& outputStream;
        };

        class Add : public Base {
            public:
                Add(Driver &drv, Memory &mem);

                void execute();
        };

        class Subtract : public Base {
            public:
                Subtract(Driver &drv, Memory &mem);

                void execute();
        };

        class Right : public Base {
            public:
                Right(Driver &drv, Memory &mem);

                void execute();
        };

        class Left : public Base {
            public:
                Left(Driver &drv, Memory &mem);

                void execute();
        };

        class Output : public Base {
            public:
                Output(Driver &drv, Memory &mem);

                void execute();
        };

        class Input : public Base {
            public:
                Input(Driver &drv, Memory &mem);

                void execute();
        };

        class CloseLoop;

        class OpenLoop : public Base {
            public:
                OpenLoop(Driver &drv, Memory &mem);

                void execute();
                void link(CloseLoop* cl);

                CloseLoop *loop_link;
        };

        class CloseLoop : public Base {
            public:
                CloseLoop(Driver &drv, Memory &mem);

                void execute();
                void link(OpenLoop* ol);

                OpenLoop *loop_link;
        };

    }

}