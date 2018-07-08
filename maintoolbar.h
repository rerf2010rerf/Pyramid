#ifndef MAINTOOLBAR_H
#define MAINTOOLBAR_H

#include <QToolBar>
#include <QComboBox>
#include <QLabel>

#include "pyramid.h"

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
    void update(const Pyramid &pyramid);

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
    void updateForPyramid(const Pyramid &pyramid);
    virtual ~MainToolbar() {}

signals:
    void layerChanged(int index);

private:
    LayerComboBox *layerBox;
    ImageSizeLabel *imageSizeLabel;

private slots:
    void layerComboBoxChanged(int index);

};

#endif // MAINTOOLBAR_H
