
#include <QtWidgets/QApplication>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <vector>
#include <string>

#include "AbsRepo.h"
#include "Tests.h"
#include "Service.h"
#include "OfertaGUI.h"

using std::vector;
using std::string;


int main(int argc, char* argv[])
{

    srand((unsigned)time(0));
    Tests tests;
//    tests.testAll();

    AbsRepo* repo = new OfertaRepoFile("../Persistence/oferte.csv");
    AbsRepo* repo1 = new OfertaRepo();
    Validator validator;
    Service service{repo, validator};
    QApplication a(argc, argv);
//    UI ui = UI(service);
//    ui.run();

    OfertaGUI2 gui{ service };
    gui.show();

    return a.exec();
}
//#include <iostream>
//#include "Tests.h"
//#include "UI.h"
//
//
//using namespace std;
//
//int main() {
//
//    Tests tests;
//    tests.testAll();
//
//    AbsRepo* repo = new OfertaRepoFile("../Persistence/oferte.csv");
//    AbsRepo* repo1 = new OfertaRepo();
//    Validator validator;
//    Service service(repo, validator);
//
//    UI ui = UI(service);
//    ui.run();
//
//    delete repo;
//    delete repo1;
//    return 0;
//}