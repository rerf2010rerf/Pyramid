#include <QtMath>
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
    layers.insert(originImageLayer, newImage);

    QSize imageSize = layers.value(originImageLayer).size();
    int minSize = imageSize.height() > imageSize.width() ? imageSize.width() : imageSize.height();
    /*
     * Двоичный логарифм вычисляем по формуле log2(x) = ln(x)/ln(2)
     * Размер пирамиды равен округлённому вверх log2(min(width, height)
     */
    const static double koeff = qLn(2);
    pyramidSize = qCeil(qLn(minSize) / koeff);
}

int Pyramid::size() const
{
    return pyramidSize;
}

const QImage &Pyramid::getLayer(int id)
{
    if (id < 0 || id >= pyramidSize) {
        throw std::out_of_range("Layer not exists");
    }
    if (!layers.contains(id)) {
        layers.insert(id, layers.value(originImageLayer).scaled(getLayerSize(id)));
    }
    return layers[id];
}

QSize Pyramid::getOriginSize() const
{
    if (layers.isEmpty()) {
        throw PyramidException("Image not set yet");
    }
    return layers.value(originImageLayer).size();
}

QSize Pyramid::getLayerSize(int layerId) const
{
    QSize originSize = getOriginSize();
    int denominator = qPow(2, layerId);
    return QSize(originSize.width() / denominator, originSize.height() / denominator);
}
