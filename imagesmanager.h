#ifndef IMAGESMANAGER_H
#define IMAGESMANAGER_H

#include <QVector>
#include <QtMath>

#include "pyramid.h"

class ImageItem {
public:
    ImageItem();
    ImageItem(const QString &fileName, const QSize &imageSize, int index);

    QString getFileName() const;
    QSize getImageSize() const;
    int getIndex() const;

private:
    const QString fileName;
    const QSize imageSize;
    const int index;
};
Q_DECLARE_METATYPE(ImageItem)

class ImagesManager
{
public:
    ImageItem openNewImage(const QString &fileName);
    Pyramid &changeActivePyramid(const ImageItem &imageItem);
    Pyramid &getActivePyramid();


private:
    QVector<Pyramid> pyramides;
    int activePyramid = 0;
};

#endif // IMAGESMANAGER_H
