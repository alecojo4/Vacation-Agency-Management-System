//
// Created by Ale on 5/2/2023.
//

#include "OfertaRepo.h"

OfertaRepo::~OfertaRepo() {
    this->oferte.clear();
}

void OfertaRepo::add(const Oferta &oferta) {
    if (this->find(oferta) != -1)
        throw RepositoryException("Oferta deja exista!");
    this->oferte.push_back(oferta);
}

void OfertaRepo::remove(const Oferta &oferta) {
    int index = this->find(oferta);
    if (index == -1)
        throw RepositoryException("Oferta nu exista!");
    this->oferte.erase(this->oferte.begin() + index);
}

void OfertaRepo::update(const Oferta &oferta) {
    int index = this->find(oferta);
    if (index == -1)
        throw RepositoryException("Oferta nu exista!");
    this->oferte[index] = oferta;
}

const vector<Oferta> &OfertaRepo::getAll() const {
    return this->oferte;
}

int OfertaRepo::size() const {
    return this->oferte.size();
}

const Oferta &OfertaRepo::getOferta(int index) const {
    return this->oferte[index];
}

int OfertaRepo::find(const Oferta &oferta) const {
    for (int i = 0; i < this->oferte.size(); i++) {
        if (this->oferte[i] == oferta)
            return i;
    }
    return -1;
}