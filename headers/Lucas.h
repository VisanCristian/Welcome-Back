#ifndef OOP_LUCAS_H
#define OOP_LUCAS_H

#include "Killer.h"

class Lucas : public Killer {

public:
    Lucas();
    ~Lucas();

    Option spawn() override;
};



#endif
