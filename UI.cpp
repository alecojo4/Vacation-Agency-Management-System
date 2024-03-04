//
// Created by Ale on 5/2/2023.
//

#include "UI.h"

void UI::printMenu() {
    cout << "1. Add oferta" << endl;
    cout << "2. Remove oferta" << endl;
    cout << "3. Update oferta" << endl;
    cout << "4. Print all oferte" << endl;
    cout << "5. Print oferte by denumire" << endl;
    cout << "6. Print oferte by destinatie" << endl;
    cout << "7. Print sorted oferte by denumire" << endl;
    cout << "8. Print sorted oferte by destinatie" << endl;
    cout << "9. Print sorted oferte by pret" << endl;
    cout << "10. Print sorted oferte by tip" << endl;
    cout << "11. Add oferta to watchlist" << endl;
    cout << "12. Delete oferta from watchlist" << endl;
    cout << "13. Generate watchlist" << endl;
    cout << "14. Save watchlist to file" << endl;
    cout << "15. Print watchlist" << endl;
    cout << "16. Undo" << endl;
    cout << "0. Exit" << endl;
}

void UI::addOferta() {
    string denumire, destinatie, tip;
    int pret;
    cout << "Enter denumire: ";
    cin >> denumire;
    cout << "Enter destinatie: ";
    cin >> destinatie;
    cout << "Enter pret: ";
    cin >> pret;
    cout << "Enter tip: ";
    cin >> tip;
    try {
        this->service.addOferta(denumire, destinatie, pret, tip);
    }
    catch (const ValidationException &exception) {
        cout << exception << endl;
    }
    catch (const RepositoryException &exception) {
        cout << exception << endl;
    }
}

void UI::removeOferta() {
    string denumire, destinatie, tip;
    int pret;
    cout << "Enter denumire: ";
    cin >> denumire;
    cout << "Enter destinatie: ";
    cin >> destinatie;
    cout << "Enter pret: ";
    cin >> pret;
    cout << "Enter tip: ";
    cin >> tip;
    try {
        this->service.removeOferta(denumire, destinatie, pret, tip);
    }
    catch (const ValidationException &exception) {
        cout << exception << endl;
    }
    catch (const RepositoryException &exception) {
        cout << exception << endl;
    }
}

void UI::updateOferta() {
    string denumire, destinatie, tip;
    int pret;
    cout << "Enter denumire: ";
    cin >> denumire;
    cout << "Enter destinatie: ";
    cin >> destinatie;
    cout << "Enter pret: ";
    cin >> pret;
    cout << "Enter tip: ";
    cin >> tip;
    try {
        this->service.updateOferta(denumire, destinatie, pret, tip);
    }
    catch (const ValidationException &exception) {
        cout << exception << endl;
    }
    catch (const RepositoryException &exception) {
        cout << exception << endl;
    }
}

void UI::printAllOferte() {
    vector<Oferta> oferte = this->service.getAll();
    for (const Oferta& oferta : oferte) {
        cout << oferta << endl;
    }
}

void UI::printOferteByDenumire() {
    string denumire;
    cout << "Enter denumire: ";
    cin >> denumire;
    vector<Oferta> oferte = this->service.getOferteByDenumire(denumire);
    for (const Oferta& oferta : oferte) {
        cout << oferta << endl;
    }
}

void UI::printOferteByPret() {
    int pret;
    cout << "Enter pret: ";
    cin >> pret;
    vector<Oferta> oferte = this->service.getOferteByPret(pret);
    for (const Oferta& oferta : oferte) {
        cout << oferta << endl;
    }
}

void UI::printSortedOferteByDenumire() {
    bool ascending;
    cout << "Ascending? (1/0): ";
    cin >> ascending;
    vector<Oferta> oferte = this->service.sortOferteByDenumire(ascending);
    for (const Oferta& oferta : oferte) {
        cout << oferta << endl;
    }
}

void UI::printSortedOferteByDestinatie() {
    bool ascending;
    cout << "Ascending? (1/0): ";
    cin >> ascending;
    vector<Oferta> oferte = this->service.sortOferteByDestinatie(ascending);
    for (const Oferta& oferta : oferte) {
        cout << oferta << endl;
    }
}

void UI::printSortedOferteByPret(){
    bool ascending;
    cout << "Ascending? (1/0): ";
    cin >> ascending;
    vector<Oferta> oferte = this->service.sortOferteByPret(ascending);
    for (const Oferta& oferta : oferte) {
        cout << oferta << endl;
    }
}

void UI::printSortedOferteByTip() {
    bool ascending;
    cout << "Ascending? (1/0): ";
    cin >> ascending;
    vector<Oferta> oferte = this->service.sortOferteByTip(ascending);
    for (const Oferta& oferta : oferte) {
        cout << oferta << endl;
    }
}

void UI::addToWatchlist() {
    string title, genre, mainActor;
    int year;
    cout << "Enter title: ";
    cin >> title;
    cout << "Enter genre: ";
    cin >> genre;
    cout << "Enter year: ";
    cin >> year;
    cout << "Enter main actor: ";
    cin >> mainActor;
    try {
        this->service.addToWatchlist(title, genre, year, mainActor);
    }
    catch (const RepositoryException &exception) {
        cout << exception << endl;
    }
}

void UI::deleteFromWatchlist() {
    string denumire;
    cout << "Enter denumire: ";
    cin >> denumire;
    try {
        this->service.deleteFromWatchlist(denumire);
    }
    catch (const RepositoryException &exception) {
        cout << exception << endl;
    }
}

void UI::generateWatchlist() {
    int numberOfOferte;
    cout << "Enter number of oferte: ";
    cin >> numberOfOferte;
    try {
        this->service.generateWatchlist(numberOfOferte);
    }
    catch (const RepositoryException &exception) {
        cout << exception << endl;
    }
}

void UI::saveWatchlistToFile() {
    string filename;
    cout << "Enter filename: ";
    cin >> filename;
    try {
        this->service.saveWatchlistToFile(filename);
    }
    catch (const RepositoryException &exception) {
        cout << exception << endl;
    }
}

void UI::printWatchlist() {
    vector<Oferta> oferte = this->service.getWatchlist();
    for (const Oferta& oferta : oferte) {
        cout << oferta << endl;
    }
}

void UI::undo() {
    try {
        this->service.doUndo();
    }
    catch (const RepositoryException &exception) {
        cout << exception << endl;
    }
}

void UI::run() {
    while (true) {
        this->printMenu();
        int command;
        cout << "Enter command: ";
        cin >> command;
        switch (command) {
            case 0:
                return;
            case 1:
                this->addOferta();
                break;
            case 2:
                this->removeOferta();
                break;
            case 3:
                this->updateOferta();
                break;
            case 4:
                this->printAllOferte();
                break;
            case 5:
                this->printOferteByDenumire();
                break;
            case 6:
                this->printOferteByPret();
                break;
            case 7:
                this->printSortedOferteByDenumire();
                break;
            case 8:
                this->printSortedOferteByDestinatie();
                break;
            case 9:
                this->printSortedOferteByPret();
                break;
            case 10:
                this->printSortedOferteByTip();
                break;
            case 11:
                this->addToWatchlist();
                break;
            case 12:
                this->deleteFromWatchlist();
                break;
            case 13:
                this->generateWatchlist();
                break;
            case 14:
                this->saveWatchlistToFile();
                break;
            case 15:
                this->printWatchlist();
                break;
            case 16:
                this->undo();
                break;
            default:
                cout << "Invalid command!" << endl;
                break;
        }
    }
}