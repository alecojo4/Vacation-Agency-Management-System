//
// Created by Ale on 5/2/2023.
//

#ifndef LABORATOR8_9OOP_SERVICE_H
#define LABORATOR8_9OOP_SERVICE_H
#pragma once
#include <map>
#include "OfertaRepoFile.h"
#include "Validator.h"
#include "AbsRepo.h"
#include "Undo.h"
#include <memory>
class Service {
private:
    AbsRepo *repo;
    OfertaRepo watchlist = OfertaRepo();
    Validator validator;
    vector<unique_ptr<ActiuneUndo>> undoActions;
public:
    Service() = default;
    Service(AbsRepo *repo, const Validator &validator);
    void addOferta(const string &denumire, const string &destinatie, int pret, const string &tip);
    void removeOferta(const string &denumire, const string &destinatie, int pret, const string &tip);
    void updateOferta(const string &denumire, const string &destinatie, int pret, const string &tip);
    const vector<Oferta> &getAll() const;
    int size() const;
    const Oferta &getOferta(int index) const;
    int find(const string & denumire) const;

    void doUndo();

    vector<Oferta> getOferteByDenumire(const string& denumire);
    vector<Oferta> getOferteByPret(int pret);
    vector<Oferta> sortOferteByDenumire(bool ascending);
    vector<Oferta> sortOferteByDestinatie(bool ascending);
    vector<Oferta> sortOferteByPret(bool ascending);
    vector<Oferta> sortOferteByTip(bool ascending);

    void addToWatchlist(const string &denumire, const string &destinatie, int pret, const string &tip);
    void deleteFromWatchlist(const string& denumire);
    vector<Oferta> getWatchlist();
    void generateWatchlist(int numberOfOferte);

    void saveWatchlistToFile(const string& filename);
    map<string, vector<Oferta>> getOferteByTip( string tip);

};
#endif //LABORATOR8_9OOP_SERVICE_H
