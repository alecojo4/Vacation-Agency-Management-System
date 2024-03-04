//
// Created by Ale on 5/2/2023.
//

#include "Tests.h"
#include "Service.h"
#include <fstream>

void Tests::testAll() {
    testOferta();
    //testIO();
    testRepo();
    testRepoFile();
    testService();
//    testUndo();
}

void Tests::testOferta() {
    Validator validator;
    Oferta *oferta1 = new Oferta("1", "1", 1, "1");
    Oferta *oferta2 = new Oferta(*oferta1);
    Oferta *oferta3 = new Oferta();
    *oferta3 = *oferta1;
    assert(*oferta1 == *oferta2);

    assert(oferta1->getDenumire() == "1");
    assert(oferta1->getDestinatie() == "1");
    assert(oferta1->getPret() == 1);
    assert(oferta1->getTip() == "1");

    validator.validateOferta(*oferta1);

    string s = oferta1->toString();

    oferta1->setDenumire("");
    oferta1->setDestinatie("");
    oferta1->setPret(-24);
    oferta1->setTip("");
    assert(*oferta1 != *oferta3);
    try {
        validator.validateOferta(*oferta1);
    }
    catch (ValidationException &exception) {
        assert(true);
    }

    Oferta cm1 = std::move(*oferta1);
    assert(cm1.getDenumire().empty());
    auto *cm2 = new Oferta(std::move(*oferta3));
    assert(cm2->getDenumire() == "1");


    auto cm3 = new Oferta();
    *cm3 = std::move(*cm2);

    assert(cm3->getDenumire() == "1");


    delete oferta1;
    delete oferta2;
    delete oferta3;
    delete cm3;
    delete cm2;
}

//void Tests::testIO() {
//    Oferta *oferta = new Oferta("1", "1", 1, "1");
//    Oferta *oferta2 = new Oferta();
//
//    Oferta aux;
//    ofstream fout("out");
//    ifstream fin("in");
//
//    fout << *oferta;
//    fin >> *oferta2;
//    fin >> aux;
//    assert(oferta2->getDenumire() == "1");
//
//
//    delete oferta;
//    delete oferta2;
//    fin.close();
//    fout.close();
//}

void Tests::testRepo() {
    OfertaRepo repo;
    Oferta oferta1 = Oferta("1", "1", 1, "1");
    Oferta oferta2 = Oferta("2", "2", 2, "2");
    Oferta oferta3 = Oferta("1", "3", 3, "3");
    repo.add(oferta1);
    try {
        repo.add(oferta1);
    }
    catch (RepositoryException &exception) {
        assert(true);
    }
    try {
        repo.remove(oferta2);

    }
    catch (RepositoryException &exception) {
        assert(true);
    }
    try {
        repo.update(oferta2);
    }
    catch (RepositoryException &exception) {
        assert(true);
    }
    repo.add(oferta2);
    repo.remove(oferta2);
    repo.update(oferta3);
    assert(repo.getAll().size() == 1);
    assert(repo.size() == 1);

    Oferta m = repo.getOferta(0);

}

void Tests::testRepoFile() {
    OfertaRepoFile repo = OfertaRepoFile("../IORepoTests/test");
    Oferta oferta1 = Oferta("1", "1", 1, "1");
    Oferta oferta2 = Oferta("2", "2", 2, "2");
    Oferta oferta3 = Oferta("1", "3", 3, "3");
    repo.add(oferta1);
    try {
        repo.add(oferta1);
    }
    catch (RepositoryException &exception) {
        assert(true);
    }
    try {
        repo.remove(oferta2);
    }
    catch (RepositoryException &exception) {
        assert(true);
    }
    try {
        repo.update(oferta2);
    }
    catch (RepositoryException &exception) {
        assert(true);
    }
    repo.add(oferta2);
    repo.remove(oferta2);
    repo.update(oferta3);
    assert(repo.getAll().size() == 1);
    assert(repo.size() == 1);

    Oferta m = repo.getOferta(0);
    repo.remove(oferta3);

}

void Tests::testService() {
    AbsRepo *repo = new OfertaRepoFile("../IORepoTests/testService");
    Validator validator;
    Service service = Service(repo, validator);

    service.addOferta("1", "1", 1, "1");
    try {
        service.addOferta("1", "1", 1, "1");
    }
    catch (RepositoryException &exception) {
        assert(true);
    }
    try {
        service.addOferta("", "", -1, "");
    }
    catch (ValidationException &exception) {
        assert(true);
    }
    try {
        service.removeOferta("2", "2", 2, "2");
    }
    catch (RepositoryException &exception) {
        assert(true);
    }
    try {
        service.updateOferta("2", "2", 2, "2");
    }
    catch (RepositoryException &exception) {
        assert(true);
    }
    try {
        service.updateOferta("1", "", -1, "");
    }
    catch (ValidationException &exception) {
        assert(true);
    }
    service.updateOferta("1", "3", 3, "3");
    assert(service.getAll().size() == 1);
    assert(service.getOferta(0).getDenumire() == "1");
    assert(service.size() == 1);
    assert(service.find("1") == 0);
    service.removeOferta("1",  "2", 2, "2");

    service.addOferta("1", "1", 1, "1");
    service.addOferta("3", "3", 3, "3");
    service.addOferta("2", "2", 2, "2");


    assert(service.getOferteByDenumire("1").size() == 1);
    assert(service.getOferteByPret(2).size() == 1);
    assert(service.sortOferteByDenumire(true)[0].getDenumire() == "1");
    assert(service.sortOferteByPret(true)[0].getPret() == 1);
    assert(service.sortOferteByDestinatie(true)[0].getDestinatie() == "1");
    assert(service.sortOferteByTip(true)[0].getTip() == "1");
    assert(service.sortOferteByDenumire(false)[0].getDenumire() == "3");
    assert(service.sortOferteByPret(false)[0].getPret() == 3);
    assert(service.sortOferteByDestinatie(false)[0].getDestinatie() == "3");
    assert(service.sortOferteByTip(false)[0].getTip() == "3");

    service.addToWatchlist("1", "1", 1, "1");
    try {
        service.addToWatchlist("1", "1", 1, "1");
    }
    catch (RepositoryException &exception) {
        assert(true);
    }
    try {
        service.addToWatchlist("", "", -1, "");
    }
    catch (ValidationException &exception) {
        assert(true);
    }
    try {
        service.deleteFromWatchlist("2");
    }
    catch (RepositoryException &exception) {
        assert(true);
    }

    assert(service.getWatchlist().size() == 1);

    service.generateWatchlist(2);

    assert(service.getWatchlist().size() == 3);

    service.saveWatchlistToFile("testWatchlist");


    service.removeOferta("3", "2", 2, "2");
    service.removeOferta("2", "2", 2, "2");
    service.removeOferta("1", "2", 2, "2");

    delete repo;
}

void Tests::testUndo() {
    AbsRepo *repo = new OfertaRepoFile("../IORepoTests/testUndo");
    Validator validator;
    Service service = Service(repo, validator);
    try {
        service.doUndo();
        assert(false);
    }
    catch (runtime_error &exception) {
        assert(true);
    }

    service.addOferta("1", "1", 1, "1");
    service.addOferta("2", "2", 2, "2");
    service.doUndo();

    service.addOferta("2", "2", 2, "2");
    service.removeOferta("2", "2", 2, "2");
    assert(service.getAll().size() == 1);
    service.doUndo();
    assert(service.getAll().size() == 2);

    service.updateOferta("2", "3", 3, "3");
    assert(service.getOferta(1).getDestinatie() == "3");
    service.doUndo();
    assert(service.getOferta(1).getDestinatie() == "2");

    service.doUndo();
    service.doUndo();
}