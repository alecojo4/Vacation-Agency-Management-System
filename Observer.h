//
// Created by Ale on 5/26/2023.
//
#pragma once
#ifndef LABQTFINAL_OBSERVER_H
#define LABQTFINAL_OBSERVER_H
#include <vector>
#include <algorithm>

class Observer {
public:
    virtual void update()=0;///updateaza observerul, in cazul nostru, lista de oferte
};
class Observable{
private:
    std::vector<Observer*> observers;///vectorul de observeri, in cazul nostru, lista de oferte
public:
    void addObserver(Observer* obs){///adauga un observer
        observers.push_back(obs);
    }
    void removeObserver(Observer* obs){///sterge un observer
        observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
    }
protected:
    void notify(){///notifica toti observerii
        for(auto &observer:observers)
            observer->update();///updateaza fiecare observer
    }
};


#endif //LABQTFINAL_OBSERVER_H
