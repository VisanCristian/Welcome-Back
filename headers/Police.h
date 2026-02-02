#ifndef OOP_POLICE_H
#define OOP_POLICE_H

#include "Killer.h"

class Police : public Killer {

public:
    Police();
    ~Police();

    Option spawn() override;
};



#endif
