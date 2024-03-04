//
// Created by Ale on 5/2/2023.
//

#ifndef LABORATOR8_9OOP_OFERTAREPO_H
#define LABORATOR8_9OOP_OFERTAREPO_H
#pragma once

#include "Oferta.h"
#include "Exceptions.h"
#include "AbsRepo.h"
#include <vector>

using namespace std;

class OfertaRepo: public AbsRepo {

public:
    OfertaRepo() = default;

     ~OfertaRepo() override;

     void add(const Oferta &oferta) override;

     void remove(const Oferta &oferta) override;

     void update(const Oferta &oferta) override;

     const vector<Oferta> &getAll() const override;

     int size() const override;

     const Oferta &getOferta(int index) const override;

     int find(const Oferta &oferta) const override;


};
#endif //LABORATOR8_9OOP_OFERTAREPO_H
