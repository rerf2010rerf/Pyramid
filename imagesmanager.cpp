#include "imagesmanager.h"

ImagesManager::ImagesManager()
{

}

ImageItem ImagesManager::openNewImage(const QString &fileName)
{
    Pyramid newPyramid;
    try {
        newPyramid.openImage(fileName);
    } catch(...) {
        throw;
    }
    pyramides.append(newPyramid);
    return ImageItem(fileName, newPyramid.getOriginSize(), pyramides.size() - 1);
}

const Pyramid &ImagesManager::changeActivePyramid(const ImageItem &imageItem)
{
    activePyramid = imageItem.getIndex();
    return pyramides.at(activePyramid);
}

const Pyramid &ImagesManager::getActivePyramid()
{
    return pyramides.at(activePyramid);
}

ImageItem::ImageItem() : ImageItem(QString(""), QSize(), -1) {}

ImageItem::ImageItem(const QString &fileName, const QSize &imageSize, int index) :
    fileName(fileName),
    imageSize(imageSize),
    index(index) {}

QString ImageItem::getFileName() const
{
    return fileName;
}

QSize ImageItem::getImageSize() const
{
    return imageSize;
}

int ImageItem::getIndex() const
{
    return index;
}
