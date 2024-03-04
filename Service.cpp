//
// Created by Ale on 5/2/2023.
//

#include "Service.h"

#include <algorithm>
#include <chrono>
#include <map>

Service::Service( AbsRepo *repo, const Validator &validator) {
    this->repo = repo;
    this->validator = validator;
}

void Service::addOferta(const string &denumire, const string &destinatie, int pret, const string &tip) {
    Oferta oferta(denumire, destinatie, pret, tip);
    this->validator.validateOferta(oferta);
    this->repo->add(oferta);
    UndoAdauga* undoAdauga = new UndoAdauga(reinterpret_cast<OfertaRepoFile &>(this->repo), oferta);
    //unique_ptr este construit cu obiectul undoAdauga ca argument, astfel încât noul obiect adăugat la vector va fi un pointer unic la obiectul undoAdauga.
    // Acesta este modul în care se asigură că obiectul este eliberat automat din memorie atunci când pointerul unic este distrus,
    // fără a fi necesară apelarea explicită a funcției delete.

    this->undoActions.push_back(unique_ptr<ActiuneUndo>(undoAdauga));
}
//Fucntion to remove an element from the repository
void Service::removeOferta(const string &denumire, const string &destinatie, int pret, const string &tip) {
    Oferta oferta(denumire, destinatie, pret, tip);
    this->repo->remove(oferta);
    UndoSterge* undoSterge = new UndoSterge(reinterpret_cast<OfertaRepoFile &>(this->repo), oferta);
    this->undoActions.push_back(unique_ptr<ActiuneUndo>(undoSterge));
}

void Service::updateOferta(const string &denumire, const string &destinatie, int pret, const string &tip) {
    Oferta oferta(denumire, destinatie, pret, tip);
    int index = this->repo->find(oferta);
    Oferta oldOferta;
    if (index != -1) {
        oldOferta = this->repo->getOferta(index);
    }
    this->validator.validateOferta(oferta);
    this->repo->update(oferta);
    UndoModifica* undoModifica = new UndoModifica(reinterpret_cast<OfertaRepoFile &>(this->repo), oldOferta);
    this->undoActions.push_back(unique_ptr<ActiuneUndo>(undoModifica));
}

const vector<Oferta> &Service::getAll() const {
    return this->repo->getAll();
}

int Service::size() const {
    return this->repo->size();
}

const Oferta &Service::getOferta(int index) const {
    return this->repo->getOferta(index);
}

int Service::find(const string & denumire) const {
    Oferta oferta(denumire, "", 0, "");
    return this->repo->find(oferta);
}

vector<Oferta> Service::getOferteByDenumire(const string& denumire) {
    vector<Oferta> oferte = repo->getAll();
    vector<Oferta> oferteByDenumire;
    copy_if(oferte.begin(), oferte.end(), back_inserter(oferteByDenumire), [denumire](const Oferta&  oferta) {
        return oferta.getDenumire() == denumire;
    });
    return oferteByDenumire;
}

vector<Oferta> Service::getOferteByPret(int pret) {
    vector<Oferta> oferte = repo->getAll();
    vector<Oferta> oferteByPret;
    copy_if(oferte.begin(), oferte.end(), back_inserter(oferteByPret), [pret](const Oferta&  oferta) {
        return oferta.getPret() == pret;
    });
    return oferteByPret;
}

vector<Oferta> Service::sortOferteByDenumire(bool ascending) {
    vector<Oferta> oferte = repo->getAll();
    if (ascending) {
        sort(oferte.begin(), oferte.end(), [](const Oferta&  oferta1, const Oferta&  oferta2) {
            return oferta1.getDenumire() < oferta2.getDenumire();
        });
    } else {
        sort(oferte.begin(), oferte.end(), [](const Oferta&  oferta1, const Oferta&  oferta2) {
            return oferta1.getDenumire() > oferta2.getDenumire();
        });
    }
    return oferte;
}

vector<Oferta> Service::sortOferteByDestinatie(bool ascending) {
    vector<Oferta> oferte = repo->getAll();
    if (ascending) {
        sort(oferte.begin(), oferte.end(), [](const Oferta&  oferta1, const Oferta&  oferta2) {
            return oferta1.getDestinatie() < oferta2.getDestinatie();
        });
    } else {
        sort(oferte.begin(), oferte.end(), [](const Oferta& oferta1, const Oferta&  oferta2) {
            return oferta1.getDestinatie() > oferta2.getDestinatie();
        });
    }
    return oferte;
}

vector<Oferta> Service::sortOferteByPret(bool ascending) {
    vector<Oferta> oferte = repo->getAll();
    if (ascending) {
        sort(oferte.begin(), oferte.end(), [](const Oferta&  oferta1, const Oferta&  oferta2) {
            return oferta1.getPret() < oferta2.getPret();
        });
    } else {
        sort(oferte.begin(), oferte.end(), [](const Oferta&  oferta1, const Oferta&  oferta2) {
            return oferta1.getPret() > oferta2.getPret();
        });
    }
    return oferte;
}

vector<Oferta> Service::sortOferteByTip(bool ascending) {
    vector<Oferta> oferte = repo->getAll();
    if (ascending) {
        sort(oferte.begin(), oferte.end(), [](const Oferta&  oferta1, const Oferta&  oferta2) {
            return oferta1.getTip() < oferta2.getTip();
        });
    } else {
        sort(oferte.begin(), oferte.end(), [](const Oferta&  oferta1, const Oferta&  oferta2) {
            return oferta1.getTip() > oferta2.getTip();
        });
    }
    return oferte;
}

void Service::addToWatchlist(const string& denumire, const string& destinatie, int pret, const string& tip) {
    Oferta oferta(denumire, destinatie, pret, tip);
    validator.validateOferta(oferta);
    watchlist.add(oferta);
}

void Service::deleteFromWatchlist(const string& denumire) {
    Oferta oferta =  Oferta(denumire, "", 0, "");
    watchlist.remove(oferta);
}

vector<Oferta> Service::getWatchlist() {
    return watchlist.getAll();
}

void Service::generateWatchlist(int numberOfOferte) {
    //Generate numberOfMovies random titles, genre, year and mainActor and add them to the watchlist

    auto seed = chrono::steady_clock::now().time_since_epoch().count();
    srand(seed);

    for (int i = 0; i < numberOfOferte; i++) {
        //Generate random titles using seed
        string denumire;
        int denumireLength = rand() % 20 + 1;
        for (int j = 0; j < denumireLength; j++) {
            denumire += (char) (rand() % 26 + 97);
        }

        //Generate random genre
        string destinatie;
        int destinatieLength = rand() % 20 + 1;
        for (int j = 0; j < destinatieLength; j++) {
            destinatie += (char) (rand() % 26 + 97);
        }

        //Generate random year
        int pret = rand() % 200 + 1900;

        //Generate random mainActor
        string tip;
        int tipLength = rand() % 20 + 1;
        for (int j = 0; j < tipLength; j++) {
            tip += (char) (rand() % 26 + 97);
        }

        Oferta oferta(denumire, destinatie, pret, tip);
        watchlist.add(oferta);
    }

}

void Service::saveWatchlistToFile(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }
    vector<Oferta> oferte = watchlist.getAll();
    for (const Oferta& oferta : oferte) {
        file << oferta.getDenumire() << "," << oferta.getDestinatie() << "," << oferta.getPret() << "," << oferta.getTip()<< endl;
    }
    file.close();
}

void Service::doUndo() {
    if (undoActions.empty()) {
        throw std::runtime_error("No more undos");
    }
    undoActions.back()->undo();
    undoActions.pop_back();
}

//unordered_map<string,vector<Oferta>> Service::getRaports() {
//    //un map de tip <TIP, OFERTA>
//    unordered_map<string,vector<Oferta>> raports;
//
//    //parcurg toate ofertele din repo
//    for(auto item : repo->getAll()){
//        //verifica daca pentru o oferta din repo oferta.getTip() apare undeva in map ca si cheie
//        if (raports.find(item.getTip()) == raports.end()){//daca nu apare
//            vector<Oferta>temp;//fac un vector cu oferte
//            temp.push_back(item);//adaug oferta in vector
//            auto pereche = pair<string,vector<Oferta>>(item.getTip(),temp);//creez o pereche de tip <tipul gasit, vectorul de mai sus cu oferta>
//            raports.insert(pereche);//am pus-o in map
//        }//daca cheia exista
//        else{
//            raports[item.getTip()].push_back(item);//adaug oferta in vectorul corespunzato cheii tipului gaist
//        }
//    }
//    return raports;
//}


map<string,vector<Oferta>>Service::getOferteByTip(string tip){
    map<string,vector<Oferta>> oferteByTip;
    if(tip=="Denumire"){
        vector <Oferta> oferte = repo->getAll();
        std::copy_if(oferte.begin(),oferte.end(),oferte.begin(),[tip](const Oferta& oferta){
            return oferta.getTip()==tip;
        });
        for(const auto& item : oferte){
            oferteByTip[item.getDenumire()].push_back(item);
        }
    }
    if(tip=="Destinatie"){
        vector <Oferta> oferte = repo->getAll();
        std::copy_if(oferte.begin(),oferte.end(),oferte.begin(),[tip](const Oferta& oferta){
            return oferta.getTip()==tip;
        });
        for(const auto& item : oferte){
            oferteByTip[item.getDestinatie()].push_back(item);
        }
    }
    if(tip=="Pret"){
        vector <Oferta> oferte = repo->getAll();
        std::copy_if(oferte.begin(),oferte.end(),oferte.begin(),[tip](const Oferta& oferta){
            return oferta.getTip()==tip;
        });
        for(const auto& item : oferte){
            oferteByTip[to_string(item.getPret())].push_back(item);
        }
    }
    if(tip=="Tip"){
        vector <Oferta> oferte = repo->getAll();
        std::copy_if(oferte.begin(),oferte.end(),oferte.begin(),[tip](const Oferta& oferta){
            return oferta.getTip()==tip;
        });
        for(const auto& item : oferte){
            oferteByTip[item.getTip()].push_back(item);
        }
    }
}
