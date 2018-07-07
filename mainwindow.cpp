#include <QtWidgets>

#include "mainwindow.h"


MainWindow::MainWindow() :
    scrollArea(new QScrollArea()),
    imageLabel(new QLabel()),
    imageSizeLabel(new ImageSizeLabel())
{
    setWindowTitle("Pyramid");

    scrollArea->setWidget(imageLabel);
    setCentralWidget(scrollArea);

    initializeMenu();
    initializeToolBar();

    resize(QGuiApplication::primaryScreen()->availableSize() * 1 / 2);
}

void MainWindow::initializeMenu() {
    QMenu *fileMenu = menuBar()->addMenu("File");
    fileMenu->addAction("Open", this, &MainWindow::openFile);

}

void MainWindow::initializeToolBar() {
    QToolBar *mainToolBar = addToolBar("mainToolBar");
    mainToolBar->addWidget(imageSizeLabel);
}

void MainWindow::openFile() {
    const QString fileName = QFileDialog::getOpenFileName(this,
                                                          "Choose file",
                                                          QString(),
                                                          "Images (*.png *.jpg *.jpeg);;All files (*.*");
    if (fileName.isNull()) {
        return;
    }
    const QImage newImage(fileName);
    if (newImage.isNull()) {
        QMessageBox::information(this, "error", "Error image loading");
    } else {
        image = newImage;
        imageLabel->setPixmap(QPixmap::fromImage(image));
        imageLabel->adjustSize();
        imageSizeLabel->setImageSize(image.width(), image.height());
    }

}
