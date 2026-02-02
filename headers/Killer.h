#ifndef OOP_KILLER_H
#define OOP_KILLER_H

enum class Option {
    Hide,
    ChangeConnection,
    Turn
};

class Killer {
private:
    const int duration;
public:
    Killer();
    virtual ~Killer();
    virtual Option spawn() = 0;
};




#endif
