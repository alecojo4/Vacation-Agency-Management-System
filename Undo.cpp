//
// Created by Ale on 5/2/2023.
//

#include "Undo.h"

void UndoAdauga::undo() {
    this->repo.remove(this->oferta);
}


void UndoSterge::undo() {
    this->repo.add(this->oferta);
}


void UndoModifica::undo() {
    this->repo.update(this->oferta);
}