#ifndef OOP_KILLER_H
#define OOP_KILLER_H

enum class Option {
    Hide,
    ChangeConnection,
    Turn
};

class Killer {
private:
public:
    Killer();
    virtual ~Killer();
    virtual Option spawn() = 0;
};




#endif
