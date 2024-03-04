//
// Created by Ale on 5/2/2023.
//

#ifndef LABORATOR8_9OOP_UI_H
#define LABORATOR8_9OOP_UI_H
#pragma once

#include "Service.h"

class UI {
private:
    Service& service;
public:
    UI() = default;
    explicit UI(Service& service) : service{service} {};
    void run();
    void printMenu();
    void addOferta();
    void removeOferta();
    void updateOferta();
    void printAllOferte();
    void printOferteByDenumire();
    void printOferteByPret();
    void printSortedOferteByDenumire();
    void printSortedOferteByDestinatie();
    void printSortedOferteByPret();
    void printSortedOferteByTip();
    void addToWatchlist();
    void deleteFromWatchlist();
    void generateWatchlist();
    void saveWatchlistToFile();
    void printWatchlist();
    void undo();

};
#endif //LABORATOR8_9OOP_UI_H
