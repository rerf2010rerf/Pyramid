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
    mainToolbar->setVisible(false);
    connect(mainToolbar, QOverload<int>::of(&MainToolbar::layerChanged), this, &MainWindow::changeLayer);
    connect(mainToolbar, QOverload<const ImageItem &>::of(&MainToolbar::imageChanged), this, &MainWindow::changeImage);
    connect(mainToolbar, QOverload<double>::of(&MainToolbar::pyramidStepChanged), this, &MainWindow::changeStep);

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
        ImageItem image = imagesManager.openNewImage(fileName);
        mainToolbar->addNewImageItem(image);
        mainToolbar->updateForPyramid(imagesManager.changeActivePyramid(image));
        changeLayer(Pyramid::originImageLayer);
        mainToolbar->setVisible(true);
    } catch (PyramidException) {
        QMessageBox::information(this, "error", "Error image loading");
        return;
    }
}

void MainWindow::changeLayer(int layerId) {
    const QImage &layer = imagesManager.getActivePyramid().getLayer(layerId);
    imageLabel->setPixmap(QPixmap::fromImage(layer).scaled(imagesManager.getActivePyramid().getOriginSize()));
    imageLabel->adjustSize();

}

void MainWindow::changeImage(const ImageItem &imageItem)
{
    mainToolbar->updateForPyramid(imagesManager.changeActivePyramid(imageItem));
    changeLayer(Pyramid::originImageLayer);
}

void MainWindow::changeStep(double newStep)
{
    mainToolbar->updateForPyramid(imagesManager.changeActivePyramidStep(newStep));
    changeLayer(Pyramid::originImageLayer);
}



