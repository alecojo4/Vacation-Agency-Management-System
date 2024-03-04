//
// Created by Ale on 5/2/2023.
//

#include "OfertaRepoFile.h"
#include <sstream>

void OfertaRepoFile::loadFromFile() {
    ifstream fin(this->filename);
    if (!fin.is_open()) {
        throw RepositoryException("File could not be opened!");
    }
    //Clear the vector
    this->oferte.clear();
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        //Se citesc liniile din fișier și se tokenizează fiecare linie într-un vector de string-uri separate prin virgulă.
        // Variabila "line" conține linia curentă din fișier, iar variabila "ss" este un obiect de tip "stringstream" care permite citirea și manipularea string-urilor.
        // În cadrul buclei interne, fiecare linie este împărțită într-un vector de token-uri separate prin virgulă.
        vector<string> tokens;
        string token;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        if (tokens.size() != 4) {
            continue;
        }
        string denumire = tokens[0];
        string destinatie = tokens[1];
        int pret = stoi(tokens[2]);
        string tip = tokens[3];
        Oferta oferta(denumire, destinatie, pret, tip);
        this->oferte.push_back(oferta);
    }
}

OfertaRepoFile::OfertaRepoFile(const string &filename) {
    this->filename = filename;
    this->loadFromFile();
}

void OfertaRepoFile::writeToFile() {
    ofstream fout(this->filename);
    if (!fout.is_open()) {
        throw RepositoryException("File could not be opened!");
    }
    for (const auto &oferta : this->oferte) {
        fout << oferta << "\n";
    }
}

void OfertaRepoFile::add(const Oferta &oferta) {
    this->loadFromFile();
    if (this->find(oferta) != -1)
        throw RepositoryException("Oferta deja exista!");
    this->oferte.push_back(oferta);
    this->writeToFile();
    this->loadFromFile();
}

void OfertaRepoFile::remove(const Oferta &oferta) {
    this->loadFromFile();
    int index = this->find(oferta);
    if (index == -1)
        throw RepositoryException("Oferta nu exista!");
    this->oferte.erase(this->oferte.begin() + index);
    this->writeToFile();
    this->loadFromFile();
}

void OfertaRepoFile::update(const Oferta &oferta) {
    this->loadFromFile();
    int index = this->find(oferta);
    if (index == -1)
        throw RepositoryException("Oferta nu exista!");
    this->oferte[index] = oferta;
    this->writeToFile();
    this->loadFromFile();
}

OfertaRepoFile::~OfertaRepoFile() {
//    this->writeToFile();
//    this->movies.clear();
}

const vector<Oferta> &OfertaRepoFile::getAll() const {
    return this->oferte;
}

int OfertaRepoFile::size() const {
    return this->oferte.size();
}

const Oferta &OfertaRepoFile::getOferta(int index) const {
    return this->oferte[index];
}

int OfertaRepoFile::find(const Oferta &oferta) const {
    for (int i = 0; i < this->oferte.size(); i++) {
        if (this->oferte[i] == oferta)
            return i;
    }
    return -1;
}

OfertaRepoFile::OfertaRepoFile() {
    this->filename = "";
}