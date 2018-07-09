#ifndef MAINTOOLBAR_H
#define MAINTOOLBAR_H

#include <QToolBar>
#include <QComboBox>
#include <QLabel>
#include <QDoubleSpinBox>

#include "pyramid.h"
#include "imagesmanager.h"

class FileListModel : public QAbstractListModel {
public:
    FileListModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    int addImage(const ImageItem &imageItem);

private:
    QVector<QVariant> items;
};

class FileComboBox : public QComboBox {
    Q_OBJECT

public:
    FileComboBox();
    void addImageFile(const ImageItem &imageItem);

signals:
    void fileChanged(const ImageItem &imageItem);

private slots:
    void qComboBoxActivate(int id);

private:
    FileListModel *model;
};

class ImageSizeLabel : public QLabel
{
    Q_OBJECT

public:
    void setImageSize(const QSize &size);
};


class LayerComboBox : public QComboBox
{
    Q_OBJECT

public:
    LayerComboBox();
    void update(Pyramid &pyramid);

signals:
    void layerChanged(int index);

private slots:
    void qComboBoxActivate(int id);
};

class MainToolbar : public QToolBar
{
    Q_OBJECT

public:
    MainToolbar();
    void updateForPyramid(Pyramid &pyramid);
    void addNewImageItem(const ImageItem &imageItem);

signals:
    void layerChanged(int index);
    void imageChanged(const ImageItem &imageItem);
    void pyramidStepChanged(double newStep);

private:
    FileComboBox *imageBox;
    LayerComboBox *layerBox;
    ImageSizeLabel *imageSizeLabel;
    QDoubleSpinBox *stepSpinBox;

private slots:
    void layerComboBoxChanged(int index);
    void imageComboBoxChanged(const ImageItem &imageItem);
    void updateStepClicked();

};

#endif // MAINTOOLBAR_H
