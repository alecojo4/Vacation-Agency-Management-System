//
// Created by Ale on 5/8/2023.
//
#include <QtWidgets/qwidget.h>
#include <qdebug.h>
#include <qmessagebox.h>
#include <qradiobutton.h>
#include <qbuttongroup.h>
#include <QRegularExpression>
#include "Service.h"
#include <vector>
#include <string>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include "Exceptions.h"
#include "Observer.h"
#include <qpainter.h>
using std::vector;
using std::string;

class OfertaGUI : public QWidget {
private:
    vector <Oferta> oferte;
    QPushButton* btnExit = new QPushButton{"&Exit"};
public:
    OfertaGUI(vector<Oferta> oferta){
        oferte=oferta;
        initOfertaGUI();
        initConnect();
    }
    void initOfertaGUI(){
        QVBoxLayout* mainLayout=new QVBoxLayout{};
        setLayout(mainLayout);
        QListWidget* list=new QListWidget{};
        for(const auto& oferta:oferte){
            QListWidgetItem* item=new QListWidgetItem{QString::fromStdString(oferta.getDenumire())+" "+QString::fromStdString(oferta.getDestinatie())+" "+QString::fromStdString(oferta.getTip())+" "+QString::number(oferta.getPret())};
            list->addItem(item);
        }
        mainLayout->addWidget(list);
        mainLayout->addWidget(btnExit);
    }
    void initConnect(){
        QObject::connect(btnExit, &QPushButton::clicked, [&]() {
            qDebug()<<"Exit";
        QMessageBox::information(this,"Info","Aplicatia a fost deschisa cu succes!");
        QWidget::close();
        });
    }
};
class OfertaGUI2 : public QWidget {
public:
    friend class OfertaGUI;
    OfertaGUI2(Service&s):service{s} {
        initGUI();
        loadData(service.getAll());
        initConnect();
        addButton(service.getAll());

    }
    void addOferta() {
        auto denumire = txtDenumire->text().toStdString();
        auto destinatie = txtDestinatie->text().toStdString();
        auto tip = txtTip->text().toStdString();
        auto pret = txtPret->text().toInt();
        try {
        //cout<<"add oferta"<<denumire<<destinatie<<pret<<tip<<endl;
            service.addOferta(denumire, destinatie, pret, tip);
            loadData(service.getAll());
        }
        catch (ValidationException &ex) {
            QMessageBox::warning(this, "Warning", QString::fromStdString("Oferta introdusa invalida!"));
        }

        catch (RepositoryException &ex) {
            QMessageBox::warning(this, "Warning", QString::fromStdString("Oferta existenta!"));
        }
        addButton(service.getAll());
    }

    void removeOferta(){
        auto denumire = txtDenumire->text().toStdString();
        auto destinatie = txtDestinatie->text().toStdString();
        auto tip = txtTip->text().toStdString();
        auto pret = txtPret->text().toInt();
       try {
            service.removeOferta(denumire, destinatie, pret, tip);
            loadData(service.getAll());
        }
        catch (ValidationException &ex) {
            QMessageBox::warning(this, "Warning", QString::fromStdString("Oferta introdusa invalida!"));
        }
        catch (RepositoryException &ex) {
            QMessageBox::warning(this, "Warning", QString::fromStdString("Oferta inexistenta!"));
        }
        addButton(service.getAll());
    }

    void updateOferta(){
        auto denumire = txtDenumire->text().toStdString();
        auto destinatie = txtDestinatie->text().toStdString();
        auto tip = txtTip->text().toStdString();
        auto pret = txtPret->text().toInt();
        try {
            service.updateOferta(denumire, destinatie, pret, tip);
            loadData(service.getAll());
        }
        catch (ValidationException &ex) {
            QMessageBox::warning(this, "Warning", QString::fromStdString("Oferta introdusa invalida!"));
        }
        catch (RepositoryException &ex) {
            QMessageBox::warning(this, "Warning", QString::fromStdString("Oferta inexistenta!"));
        }
        addButton(service.getAll());
    }

    void sortOferteByDenumire() {
        vector<Oferta> oferte;
        if (radioDescresc->isChecked()) {
            oferte = service.sortOferteByDenumire(true);
        }
        else {
            oferte = service.sortOferteByDenumire(false);
        }
        loadData(oferte);
    }
    void sortOferteByDestinatie(){
        vector<Oferta> oferte;
        if (radioDescresc->isChecked()) {
            oferte = service.sortOferteByDestinatie(true);
        }
        else {
            oferte = service.sortOferteByDestinatie(false);
        }
        loadData(oferte);
    }
    void sortOferteByPret(){
        vector<Oferta> oferte;
        if (radioDescresc->isChecked()) {
            oferte = service.sortOferteByPret(true);
        }
        else {
            oferte = service.sortOferteByPret(false);
        }
        loadData(oferte);
    }
    void sortOferteByTip(){
        vector<Oferta> oferte;
        if (radioDescresc->isChecked()) {
            oferte = service.sortOferteByTip(true);
        }
        else {
            oferte = service.sortOferteByTip(false);
        }
        loadData(oferte);
    }

    void undo(){
        try {
            service.doUndo();
            vector<Oferta> oferte = service.getAll();
            loadData(service.getAll());
        }
        catch (RepositoryException &ex) {
            QMessageBox::warning(this, "Warning", QString::fromStdString("Nu se mai poate face undo!"));
        }
    }


private:
    Service& service;
    QTableWidget* table = new QTableWidget(0,4);
    QPushButton* btnExit = new QPushButton{"&Exit"};
    QPushButton* btnAdd = new QPushButton{"&Add"};
    QPushButton* btnRemove = new QPushButton{"&Remove"};
    QPushButton* btnUpdate = new QPushButton{"&Update"};
    QPushButton* btnSortDenumire = new QPushButton{"&Sort by Denumire"};
    QPushButton* btnSortDestinatie = new QPushButton{"&Sort by Destinatie"};
    QPushButton* btnSortPret = new QPushButton{"&Sort by Pret"};
    QPushButton* btnSortTip = new QPushButton{"&Sort by Tip"};
    QPushButton* btnUndo = new QPushButton{"&Undo"};
    QPushButton* btnRefresh = new QPushButton{"&Refresh"};
    QPushButton* btnWatchList = new QPushButton{"&WatchList"};
//    QPushButton* btnAddCos= new QPushButton{"&Add to Cos"};
//    QPushButton* btnRemoveCos= new QPushButton{"&Remove from Cos"};
//    QPushButton* btnUpdateCos= new QPushButton{"&Update Cos"};
//    QPushButton* btnAddRandCos=

    QLineEdit* txtDenumire = new QLineEdit{};
    QLineEdit* txtDestinatie = new QLineEdit{};
    QLineEdit* txtPret = new QLineEdit{};
    QLineEdit* txtTip = new QLineEdit{};

    QGridLayout* grid = new QGridLayout{};
    QRadioButton* radioCresc = new QRadioButton{"Crescator"};
    QRadioButton* radioDescresc = new QRadioButton{"Descrescator"};

    QRegularExpression rx{ "[0-9]+\\s+[0-9]+" };
    QValidator* validator = new QRegularExpressionValidator(rx, this);

    void initConnect(){
        QObject::connect(btnExit, &QPushButton::clicked, [&]() {
            qDebug()<<"Exit";
        QMessageBox::information(this,"Info","Aplicatia a fost deschisa cu succes!");
        QWidget::close();
        });
        QObject::connect(btnAdd, &QPushButton::clicked, this, &OfertaGUI2::addOferta);
        QObject::connect(btnRemove, &QPushButton::clicked, this, &OfertaGUI2::removeOferta);
        QObject::connect(btnUpdate, &QPushButton::clicked, this, &OfertaGUI2::updateOferta);
        QObject::connect(btnSortDenumire, &QPushButton::clicked, this, &OfertaGUI2::sortOferteByDenumire);
        QObject::connect(btnSortDestinatie, &QPushButton::clicked, this, &OfertaGUI2::sortOferteByDestinatie);
        QObject::connect(btnSortPret, &QPushButton::clicked, this, &OfertaGUI2::sortOferteByPret);
        QObject::connect(btnSortTip, &QPushButton::clicked, this, &OfertaGUI2::sortOferteByTip);
        QObject::connect(btnUndo, &QPushButton::clicked, this, &OfertaGUI2::undo);
        //QObject::connect(btnWatchList, &QPushButton::clicked, this, &OfertaGUI2::watchList);
        QObject::connect(btnRefresh,&QPushButton::clicked,[&](){
            txtDenumire->setText("");
            txtDestinatie->setText("");
            txtPret->setText("");
            txtTip->setText("");
        });
        QObject::connect(btnRefresh, &QPushButton::pressed, [&]() {
            QPalette pal = btnRefresh->palette();
            btnRefresh->setFlat(true);
            pal.setColor(QPalette::Button, QColor(Qt::green));
            btnRefresh->setAutoFillBackground(true);
            btnRefresh->setPalette(pal);
            btnRefresh->update();
        });
        QObject::connect(btnRefresh, &QPushButton::released, [&]() {
            QPalette pal = btnRefresh->palette();
            btnRefresh->setFlat(true);
            pal.setColor(QPalette::Button, QColor(Qt::white));
            btnRefresh->setAutoFillBackground(true);
            btnRefresh->setPalette(pal);
            btnRefresh->update();
        });

        //fct noua
        QObject::connect(table,&QTableWidget::itemSelectionChanged,[&](){
            if(table->selectedItems().isEmpty()){
                txtDenumire->setText("");
                txtDestinatie->setText("");
                txtPret->setText("");
                txtTip->setText("");
            }
            else{
                txtDenumire->setText(table->selectedItems().at(0)->text());
                txtDestinatie->setText(table->selectedItems().at(1)->text());
                txtPret->setText(table->selectedItems().at(2)->text());
                txtTip->setText(table->selectedItems().at(3)->text());
            }
        });

    }
    void loadData(const vector<Oferta>& oferte) {
        table->clear();///stergem tot
        table->setRowCount(0);///setam numarul de linii
        table->setColumnCount(4);///setam numarul de coloane
        table->setHorizontalHeaderItem(0, new QTableWidgetItem("Denumire"));
        table->setHorizontalHeaderItem(1, new QTableWidgetItem("Destinatie"));
        table->setHorizontalHeaderItem(2, new QTableWidgetItem("Pret"));
        table->setHorizontalHeaderItem(3, new QTableWidgetItem("Tip"));
        for (const auto &oferta : oferte) {
            int row = table->rowCount();
            table->insertRow(row);
            table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(oferta.getDenumire())));
            table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(oferta.getDestinatie())));
            table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(to_string(oferta.getPret()))));
            table->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(oferta.getTip())));
        }
    }
    void addButton(const std::vector<Oferta>& oferte) {

        map <string, vector<Oferta>> denumiri_oferte;
        //Empty the button layout
        QLayoutItem* item;
        while ((item = grid->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }


        for(const auto& oferta : oferte) {
            denumiri_oferte[oferta.getDenumire()].push_back(oferta);
        }
        for(const auto& denumire : denumiri_oferte) {
            auto btn = new QPushButton{QString::fromStdString(denumire.first)};
            grid->addWidget(btn);
            QObject::connect(btn, &QPushButton::clicked, [this, denumire, oferte]() {
                int nr_oferte = std::count_if(oferte.begin(), oferte.end(),
                                              [denumire](const Oferta& o)   {
                                                    return o.getDenumire() == denumire.first;
                                              });

                QMessageBox::information(nullptr, "Numar oferte", "Numarul de oferte pentru " + QString::fromStdString(denumire.first) + " este " + QString::number(nr_oferte));
            });
        }
    }


    void initGUI() {
        QVBoxLayout *mainLayout = new QVBoxLayout{};
        QWidget::setLayout(mainLayout);

        QHBoxLayout *ly1 = new QHBoxLayout{};

        QVBoxLayout *stgLy = new QVBoxLayout{};
        table->setSelectionBehavior(QAbstractItemView::SelectRows);
        stgLy->addWidget(table);

        QVBoxLayout *drLy = new QVBoxLayout{};
        QHBoxLayout *josLy = new QHBoxLayout{};

        vector<QPushButton*> btns;

        auto formLy = new QFormLayout{};
        formLy->addRow("Denumire", txtDenumire);
        formLy->addRow("Destinatie", txtDestinatie);
        formLy->addRow("Pret", txtPret);
        formLy->addRow("Tip", txtTip);
        txtDenumire->setPlaceholderText("Introduceti denumirea");
        txtDestinatie->setPlaceholderText("Introduceti destinatia");
        txtPret->setPlaceholderText("Introduceti pretul");
        txtPret->setValidator(validator);
        txtTip->setPlaceholderText("Introduceti tipul");
        drLy->addLayout(formLy);

        auto lyBtn = new QHBoxLayout{};
        auto lyBtn2 = new QHBoxLayout{};
        auto lyBtn3 = new QHBoxLayout{};
        lyBtn->addWidget(btnAdd);
        lyBtn->addWidget(btnRemove);
        lyBtn->addWidget(btnUpdate);
        drLy->addLayout(lyBtn);

        auto hBtn = new QHBoxLayout{};
        hBtn->addWidget(btnUndo);
        hBtn->addWidget(btnRefresh);

        drLy->addLayout(hBtn);

        lyBtn2->addWidget(btnSortDenumire);
        lyBtn2->addWidget(btnSortDestinatie);
        lyBtn2->addWidget(btnSortPret);
        lyBtn2->addWidget(btnSortTip);

        stgLy->addLayout(lyBtn2);

        grid->addWidget(radioCresc, 0, 0);
        grid->addWidget(radioDescresc, 0, 1);
        stgLy->addLayout(grid);

        josLy->addWidget(btnExit);

        ly1->addLayout(stgLy);
        ly1->addLayout(drLy);

        mainLayout->addLayout(ly1);
        mainLayout->addWidget(btnExit);
        btnExit->setStyleSheet("background-color: red; color: white;");
        btnExit->setFont(QFont("Times", 14, QFont::Bold));

        // setarea culorilor si fontului pentru butonul btnAdd
        btnAdd->setStyleSheet("background-color: blue; color: white;");
        btnAdd->setFont(QFont("Arial", 12));

        // setarea culorilor si fontului pentru butonul btnRemove
        btnRemove->setStyleSheet("background-color: blue; color: white;");
        btnRemove->setFont(QFont("Arial",12));

        btnUpdate->setStyleSheet("background-color: blue; color: white;");
        btnUpdate->setFont(QFont("Arial",12));

        btnSortDenumire->setStyleSheet("background-color: pink; color: purple;");
        btnSortDestinatie->setStyleSheet("background-color: pink; color: purple;");
        btnSortPret->setStyleSheet("background-color: pink; color: purple;");
        btnSortTip->setStyleSheet("background-color: pink; color: purple;");

        btnRefresh->setStyleSheet("background-color: blue; color: black;");
        btnUndo->setStyleSheet("background-color: blue; color: black;");

        QFont font{"Verdana", 11, QFont::Bold}; // Crearea unui font cu familia "Verdana", dimensiunea 11 și stilul Bold
        txtDenumire->setFont(font); // Setarea noului font pentru caseta txtDenumire
        txtDestinatie->setFont(font); // Setarea noului font pentru caseta txtDestinatie
        txtPret->setFont(font); // Setarea noului font pentru caseta txtPret
        txtTip->setFont(font); // Setarea noului font pentru caseta txtTip

        QFont font2("Arial", 10, QFont::Bold); //crearea unui obiect font
        radioCresc->setFont(font2); //setarea fontului pentru butonul radio
        radioDescresc->setFont(font2);


    }


};