//
// Created by Ale on 5/2/2023.
//

#ifndef LABORATOR8_9OOP_OFERTAREPOFILE_H
#define LABORATOR8_9OOP_OFERTAREPOFILE_H
#pragma once

#include <fstream>
#include "OfertaRepo.h"

class OfertaRepoFile : public AbsRepo {
private:
    string filename;
    void loadFromFile();
    void writeToFile();
public:
    OfertaRepoFile();
    void add(const Oferta &oferta) override;
    void remove(const Oferta &oferta) override;
    void update(const Oferta &Oferta) override;
    explicit OfertaRepoFile(const string &filename);
    ~OfertaRepoFile() override;
    const vector<Oferta> &getAll() const override;
    int size() const override;
    const Oferta &getOferta(int index) const override;
    int find(const Oferta &oferta) const override;
};
#endif //LABORATOR8_9OOP_OFERTAREPOFILE_H
