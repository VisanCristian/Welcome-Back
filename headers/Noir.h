#ifndef OOP_NOIR_H
#define OOP_NOIR_H

#include "Killer.h"

class Noir : public Killer {
    
public:
    Noir();
    ~Noir() override;

    Option spawn() override;
};



#endif
