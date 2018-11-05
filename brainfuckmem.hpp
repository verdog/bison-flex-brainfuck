#include <memory>

class BrainFuckMemoryCell {
    friend class BrainFuckMemory;
    public:
        BrainFuckMemoryCell();
        ~BrainFuckMemoryCell();

        unsigned char get_value();
        void set_value(unsigned char val);

    private:
        std::shared_ptr<BrainFuckMemoryCell> cell_right;
        std::shared_ptr<BrainFuckMemoryCell> cell_left;
        unsigned char value;
};

class BrainFuckMemory {
    public:
        BrainFuckMemory();

        unsigned char get_current_value();
        void set_current_value(unsigned char val);

        void move_right();
        void move_left();

        void report(std::ostream& out);

    private:
        std::shared_ptr<BrainFuckMemoryCell> cell_current;

        int position;
        unsigned int usage;
};