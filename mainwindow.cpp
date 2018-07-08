#include <QtWidgets>

#include "mainwindow.h"

const double MainWindow::windowSizeCoeff = 0.5;

MainWindow::MainWindow() :
    mainToolbar(new MainToolbar()),
    imageLabel(new QLabel()),
    scrollArea(new QScrollArea())
{
    setWindowTitle("Pyramid");

    scrollArea->setWidget(imageLabel);
    setCentralWidget(scrollArea);

    initializeMenu();
    addToolBar(mainToolbar);
    connect(mainToolbar, QOverload<int>::of(&MainToolbar::layerChanged), this, &MainWindow::changeLayer);

    resize(QGuiApplication::primaryScreen()->availableSize() * windowSizeCoeff);
}

void MainWindow::initializeMenu() {
    QMenu *fileMenu = menuBar()->addMenu("File");
    fileMenu->addAction("Open", this, &MainWindow::openFile);
}


void MainWindow::openFile() {
    const QString fileName = QFileDialog::getOpenFileName(this,
                                                          "Choose file",
                                                          QString(),
                                                          "Images (*.png *.jpg *.jpeg);;All files (*.*)");

    if (fileName.isNull()) {
        return;
    }
    try {
        pyramid.openImage(fileName);
    } catch (PyramidException) {
        QMessageBox::information(this, "error", "Error image loading");
        return;
    }

    mainToolbar->updateForPyramid(pyramid);
    changeLayer(Pyramid::originImageLayer);
}

void MainWindow::changeLayer(int layerId) {
    const QImage &layer = pyramid.getLayer(layerId);
    imageLabel->setPixmap(QPixmap::fromImage(layer).scaled(pyramid.getOriginSize()));
    imageLabel->adjustSize();

}

