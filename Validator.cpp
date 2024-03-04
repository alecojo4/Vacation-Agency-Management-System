//
// Created by Ale on 5/2/2023.
//

#include "Validator.h"
#pragma once

void Validator::validateOferta(const Oferta &oferta) {
    string errors;
    if (oferta.getDenumire().empty()) {
        errors += "Denumire cannot be empty!\n";
    }
    if (oferta.getDestinatie().empty()) {
        errors += "Destinatie cannot be empty!\n";
    }
    if (oferta.getPret() < 0) {
        errors += "Pret cannot be negative!\n";
    }
    if (oferta.getTip().empty()) {
        errors += "Tip cannot be empty!\n";
    }
    if (!errors.empty()) {
        throw ValidationException(errors);
    }
}