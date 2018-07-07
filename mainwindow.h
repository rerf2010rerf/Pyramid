#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QScrollArea>

#include "imagesizelabel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

private slots:
    void openFile();

private:
    QImage image;

    ImageSizeLabel *imageSizeLabel;
    QLabel *imageLabel;
    QScrollArea *scrollArea;


    void initializeMenu();
    void initializeToolBar();
};

#endif // MAINWINDOW_H
