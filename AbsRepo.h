//
// Created by Ale on 5/4/2023.
//

#ifndef LABORATOR8_9OOP_ABSREPO_H
#define LABORATOR8_9OOP_ABSREPO_H
#include "Oferta.h"
#include <vector>

class AbsRepo {
protected:
    vector<Oferta> oferte;
public:
    virtual ~AbsRepo() = default;

    virtual void add(const Oferta &oferta) = 0;

    virtual void remove(const Oferta &oferta) = 0;

    virtual void update(const Oferta &oferta) = 0;

    virtual const vector<Oferta> &getAll() const = 0;

    virtual int size() const = 0;

    virtual const Oferta &getOferta(int index) const = 0 ;

    virtual int find(const Oferta &oferta) const = 0 ;

};


#endif //LABORATOR8_9OOP_ABSREPO_H
