#include <QtWidgets/qlabel.h>
#include <QtWidgets/qscrollarea.h>
#include <iostream>
#include "Display.h"

Display::Display(int width, int height):width(width),height(height)
{

}

Display::Display(): Display(1280,720)
{

}

void Display::setupLayout()
{

    QDir projectDir(".");
    projectDir.cdUp();
    projectDir.cdUp();

    std::cout << projectDir.path().toStdString() << std::endl;
    std::cout << projectDir.filePath("src/awesome.png").toStdString() << std::endl;
    QImageReader imageReader(projectDir.filePath("src/awesome.png"));
    const QImage image = imageReader.read();
    if(image.isNull())
        std::cout << "IT'S NO USE: "<< imageReader.errorString().toStdString() << std::endl;
    QLabel* panel = new QLabel(this);
    panel->setBaseSize(200,200);
    panel->setPixmap(QPixmap::fromImage(image));
    panel->adjustSize();

    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(panel);
    setCentralWidget(scrollArea);
}
