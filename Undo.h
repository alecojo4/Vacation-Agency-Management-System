//
// Created by Ale on 5/2/2023.
//

#ifndef LABORATOR8_9OOP_UNDO_H
#define LABORATOR8_9OOP_UNDO_H
#pragma once

#include "OfertaRepoFile.h"


class ActiuneUndo {
public :
    //Funcțiile virtuale sunt utilizate pentru a permite polimorfismul în cadrul clasei și a-i permite să fie derivată.

    virtual void undo() = 0;
    //clasa "ActiuneUndo" definește o interfață comună pentru alte clase care doresc să implementeze undo/redo.

    //destructorul este declarat și el ca virtual, ceea ce înseamnă că, atunci când se apelează funcția "delete" pentru un obiect al unei clase derivate
    // Se va apela mai întâi destructorul clasei derivate și apoi destructorul clasei de bază.
    virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
private:
    Oferta oferta;
    OfertaRepoFile& repo;
public:
    //Construcția ": repo{repo}, oferta{oferta} {}" reprezintă lista de inițializare a membrilor clasei.
    // Aceasta este o modalitate mai eficientă de a inițializa membrii unei clase decât folosindu-se constructori în corpul clasei.
    //În cazul de față, se inițializează referința "repo" cu obiectul primit ca argument și obiectul "oferta" cu obiectul primit ca al doilea argument.
    UndoAdauga(OfertaRepoFile& repo, const Oferta& oferta) :  repo{repo}, oferta{oferta} {};
    // {} corpul constructorului ( care este gol )

    //Metoda "undo()" este definită ca fiind "override", ceea ce înseamnă că suprascrie funcția virtuală pură "undo()"
    void undo() override;
};

class UndoSterge : public ActiuneUndo {
private:
    Oferta oferta;
    OfertaRepoFile& repo;
public:
    UndoSterge(OfertaRepoFile& repo, const Oferta& oferta) :  repo{repo}, oferta{oferta} {};
    void undo() override;
};

class UndoModifica : public ActiuneUndo {
private:
    Oferta oferta;
    OfertaRepoFile& repo;
public:
    UndoModifica(OfertaRepoFile& repo, const Oferta& oferta) :  repo{repo}, oferta{oferta} {};
    void undo() override;
};
#endif //LABORATOR8_9OOP_UNDO_H
