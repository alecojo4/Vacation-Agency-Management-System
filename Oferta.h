//
// Created by Ale on 5/2/2023.
//

#ifndef LABORATOR8_9OOP_OFERTA_H
#define LABORATOR8_9OOP_OFERTA_H
#pragma once

#include    <string>
#include <iostream>

using namespace std;

class Oferta {
private :
    string denumire;
    string destinatie;
    int pret;
    string tip;

public:
    Oferta() = default;

    Oferta(const string &denumire, const string &destinatie, int pret, const string &tip);

    Oferta(const Oferta &oferta);

    Oferta &operator=(const Oferta &oferta);

    //Rule of 5
    ~Oferta() = default;

    Oferta(Oferta &&oferta) noexcept;

    Oferta &operator=(Oferta &&oferta) noexcept;

    string getDenumire() const;

    void setDenumire(const string &ofertaTitle);

    string getDestinatie() const;

    void setDestinatie(const string &destinatie);

    int getPret() const;

    void setPret(int ofertaPret);

    string getTip() const;

    void setTip(const string &ofertaTip);

    bool operator==(const Oferta &rhs) const;

    bool operator!=(const Oferta &rhs) const;

    string toString();

    friend ostream &operator<<(ostream &os, const Oferta &oferta);

    friend istream &operator>>(istream &is, Oferta &oferta);
};
#endif //LABORATOR8_9OOP_OFERTA_H
