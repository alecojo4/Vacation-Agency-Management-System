//
// Created by Ale on 5/16/2023.
//

#include "WatchListGUI.h"

void WatchListGUI::initGUI() {
    auto mainLayout = new QHBoxLayout{this};

    setLayout(mainLayout);
    table->setColumnCount(4);
    mainLayout->addWidget(table);

    auto formLayout = new QFormLayout{};
    formLayout->addRow("Denumire", txtDenumire);
    formLayout->addRow("Destinatie", txtDestinatie);
    formLayout->addRow("Pret", txtPret);
    formLayout->addRow("Tip", txtTip);
    formLayout->addRow("Filename", txtFilename);
    mainLayout->addLayout(formLayout);

    auto buttonsLayout = new QVBoxLayout{};

    buttonsLayout->addWidget(btnAddToWatchlist);
    buttonsLayout->addWidget(btnDeleteFromWatchlist);
    buttonsLayout->addWidget(btnSaveToFile);
    mainLayout->addLayout(buttonsLayout);
}
void WatchListGUI::initConnect() {
    QObject::connect(btnAddToWatchlist, &QPushButton::clicked, [&]() {
        try {
            service.addToWatchlist(txtDenumire->text().toStdString(), txtDestinatie->text().toStdString(),
                                   stoi(txtPret->text().toStdString()), txtTip->text().toStdString());
            loadData();
        }
        catch (exception &e) {
            QMessageBox::critical(this, "Error", e.what());
        }
    });
    QObject::connect(btnDeleteFromWatchlist, &QPushButton::clicked, [&]() {
        try {
            service.deleteFromWatchlist(txtDenumire->text().toStdString());
            loadData();
        }
        catch (exception &e) {
            QMessageBox::critical(this, "Error", e.what());
        }
    });
    QObject::connect(btnSaveToFile, &QPushButton::clicked, [&]() {
        try {
            string savedFileName = "../Watchlists/"+txtFilename->text().toStdString()+".csv";
            service.saveWatchlistToFile(savedFileName);
        }
        catch (exception &e) {
            QMessageBox::critical(this, "Error", e.what());
        }
    });
    QObject::connect(table, &QTableWidget::itemSelectionChanged, [&]() {
        if (table->selectedItems().isEmpty()) {
            txtDenumire->setText("");
            txtDestinatie->setText("");
            txtPret->setText("");
            txtTip->setText("");
            return;
        }

        auto selectedRow = table->selectedItems().at(0)->row();
        auto denumire = table->item(selectedRow, 0)->text();
        auto destinatie = table->item(selectedRow, 1)->text();
        auto pret = table->item(selectedRow, 2)->text();
        auto tip = table->item(selectedRow, 3)->text();

        txtDenumire->setText(denumire);
        txtDestinatie->setText(destinatie);
        txtPret->setText(pret);
        txtTip->setText(tip);
    });
}

void WatchListGUI::loadData() {
    vector<Oferta> watchList = service.getWatchlist();
    table->clear();
    table->setRowCount(0);
    for (const auto& oferta : watchList) {
        auto row = table->rowCount();
        table->insertRow(row);

        auto *denumire = new QTableWidgetItem(QString::fromStdString(oferta.getDenumire()));
        auto *destinatie = new QTableWidgetItem(QString::fromStdString(oferta.getDestinatie()));
        auto *pret = new QTableWidgetItem(QString::fromStdString(to_string(oferta.getPret())));
        auto *tip = new QTableWidgetItem(QString::fromStdString(oferta.getTip()));

        table->setItem(row, 0, denumire);
        table->setItem(row, 1, destinatie);
        table->setItem(row, 2, pret);
        table->setItem(row, 3, tip);


    }
}