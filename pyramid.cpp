#include <exception>

#include "pyramid.h"

const int Pyramid::originImageLayer = 0;


void Pyramid::openImage(const QString &fileName)
{
    QImage newImage(fileName);
    if (newImage.isNull()) {
        throw PyramidException("Error reading image file");
    }
    layers.clear();
    layers.append(newImage);
    for (int w = layers.back().width() / 2, h = layers.back().height() / 2; w >= 1 && h >= 1; w /= 2, h /= 2) {
        layers.append(layers.back().scaled(w, h));
    }
}

int Pyramid::size() const
{
    return layers.size();
}

const QImage &Pyramid::getLayer(int id) const
{
    if (id < 0 || id >= layers.size()) {
        throw std::out_of_range("Layer not exists");
    }
    return layers.at(id);
}

QSize Pyramid::getOriginSize() const
{
    if (layers.isEmpty()) {
        throw PyramidException("Image not set yet");
    }
    return layers.at(originImageLayer).size();
}
