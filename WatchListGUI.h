//
// Created by Ale on 5/16/2023.
//

#ifndef LABQTFINAL_WATCHLISTGUI_H
#define LABQTFINAL_WATCHLISTGUI_H

#pragma once
#include "Service.h"
#include "Observer.h"

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

#include <random>
#include <chrono>
#include <cstdlib>
#include <fstream>

using std::vector;
using std::string;
using std::ostream;
using std::sort;

class WatchListGUI : public Observable {
private:
    OfertaRepo& repo;///referinta la repo
    vector <Oferta> watchList;///lista de oferte
public:
    WatchListGUI(OfertaRepo& repo):repo{repo}{};
    void distributie_random(int numar) {

        if (repo.getAll().size() < numar) {
            throw ("Nu exista destule discipline de adaugat in contract!");
        }

        int nr_oferte_adaugate = 0;

        for (auto& elem : repo.getAll()) {
            if (find_oferta_in_WatchList(elem.getDenumire())) {
                numar_discipline_adaugate += 1;
            }
        }

        if (numar > repo.getAll().size() - nr_oferte_adaugate) {
            throw ("Nu exista suficiente discipline neadaugate in acest contract!");
        }

        std::mt19937 mt{ std::random_device{}() };
        std::uniform_int_distribution<> dist(0, repo.getAll().size() - 1);
        int rndNr;

        int cnt = 0;
        while (cnt < numar) {
            rndNr = dist(mt);
            Oferta dis = repo.get(rndNr);
            if (!find_disciplina_in_contract(dis.getId())) {
                cnt++;
                repo.store_disciplina_contract(dis);
            }
        }
        notify();
    }

};
#endif //LABQTFINAL_WATCHLISTGUI_H
