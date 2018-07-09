#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>

#include "imagesmanager.h"
#include "maintoolbar.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private slots:
    void openFile();
    void changeLayer(int layerId);
    void changeImage(const ImageItem &imageItem);

private:
    ImagesManager imagesManager;

    MainToolbar *mainToolbar;
    QLabel *imageLabel;
    QScrollArea *scrollArea;

    const static double windowSizeCoeff;

    void initializeMenu();
    void initializeToolBar();

};

#endif // MAINWINDOW_H
