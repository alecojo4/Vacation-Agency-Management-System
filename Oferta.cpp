//
// Created by Ale on 5/2/2023.
//

#include "Oferta.h"
#include <vector>
#include <sstream>

Oferta::Oferta(const Oferta &oferta) {
    this->denumire = oferta.denumire;
    this->destinatie = oferta.destinatie;
    this->pret = oferta.pret;
    this->tip = oferta.tip;
}

Oferta &Oferta::operator=(const Oferta &oferta) {
    if (this != &oferta) {
        this->denumire = oferta.denumire;
        this->destinatie = oferta.destinatie;
        this->pret = oferta.pret;
        this->tip = oferta.tip;
    }
    return *this;
}

string Oferta::getDenumire() const {
    return this->denumire;
}

void Oferta::setDenumire(const string &ofertaDenumire) {
    this->denumire = ofertaDenumire;
}

string Oferta::getDestinatie() const {
    return this->destinatie;
}

void Oferta::setDestinatie(const string &destinatie) {
    this->destinatie = destinatie;
}

int Oferta::getPret() const {
    return this->pret;
}

void Oferta::setPret(int ofertaPret) {
    this->pret = ofertaPret;
}

string Oferta::getTip() const {
    return this->tip;
}

void Oferta::setTip(const string &ofertaTip) {
    this->tip = ofertaTip;
}

bool Oferta::operator==(const Oferta &rhs) const {
    return this->denumire == rhs.denumire;
}

Oferta::Oferta(Oferta &&oferta) noexcept {
    this->denumire = oferta.denumire;
    this->destinatie = oferta.destinatie;
    this->pret = oferta.pret;
    this->tip = oferta.tip;
}

Oferta &Oferta::operator=(Oferta &&oferta) noexcept {
    if (this != &oferta) {
        this->denumire = oferta.denumire;
        this->destinatie = oferta.destinatie;
        this->pret = oferta.pret;
        this->tip = oferta.tip;
    }
    return *this;
}

bool Oferta::operator!=(const Oferta &rhs) const {
    return !(rhs == *this);
}

string Oferta::toString() {
    return "Oferta : " + this->denumire + " " + this->destinatie + " " + to_string(this->pret) + " " + this->tip;
}

ostream &operator<<(ostream &os, const Oferta &oferta) {
    os << oferta.denumire << "," << oferta.destinatie << "," << oferta.pret << "," << oferta.tip;
    return os;
}

istream &operator>>(istream &is, Oferta &oferta) {
    string line;
    getline(is, line);

    vector<string> tokens;
    stringstream ss(line);
    string token;
    while (getline(ss, token, ',')) {
        tokens.push_back(token);
    }

    if (tokens.size() != 4) {
        return is;
    }

    oferta.denumire = tokens[0];
    oferta.destinatie = tokens[1];
    oferta.pret = stoi(tokens[2]);
    oferta.tip = tokens[3];

    return is;
}

Oferta::Oferta(const string &denumire, const string &destinatie, int pret, const string &tip) {
    this->denumire = denumire;
    this->destinatie = destinatie;
    this->pret = pret;
    this->tip = tip;
}