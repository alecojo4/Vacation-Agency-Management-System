//
// Created by Ale on 5/2/2023.
//

#ifndef LABORATOR8_9OOP_TESTS_H
#define LABORATOR8_9OOP_TESTS_H
#pragma once

#include "Oferta.h"
#include "OfertaRepo.h"
#include "Validator.h"
#include "OfertaRepoFile.h"
#include <cassert>

class Tests {
public:
    void testAll();

private:
    void testOferta();

    void testRepo();

    void testRepoFile();

    void testService();

    void testIO();

    void testUndo();
};
#endif //LABORATOR8_9OOP_TESTS_H
