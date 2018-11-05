#include <memory>

class BrainFuckMemoryCell {
    friend class BrainFuckMemory;
    public:
        BrainFuckMemoryCell();
        ~BrainFuckMemoryCell();

        void increment();
        void decrement();

    private:
        std::shared_ptr<BrainFuckMemoryCell> cell_right;
        std::shared_ptr<BrainFuckMemoryCell> cell_left;
        unsigned char value;
};

class BrainFuckMemory {
    public:
        BrainFuckMemory();

        void set_current_value(unsigned char val);
        unsigned char get_current_value();

        void move_right();
        void move_left();
        void increment_current();
        void decrement_current();

        void report(std::ostream& out);

    private:
        std::shared_ptr<BrainFuckMemoryCell> cell_current;

        int position;
        unsigned int usage;
};