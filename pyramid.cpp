#include <QtMath>
#include <exception>

#include "pyramid.h"

const int Pyramid::originImageLayer = 0;
const double Pyramid::minimumStep = 1.1;
const double Pyramid::maximumStep = 10;


void Pyramid::openImage(const QString &fileName, double step)
{
    checkStep(step);
    QImage newImage(fileName);
    if (newImage.isNull()) {
        throw PyramidException("Error reading image file");
    }
    layers.clear();
    layers.insert(originImageLayer, newImage);

    rebuildForStep(step);
}

int Pyramid::size() const
{
    return pyramidSize;
}

const QImage &Pyramid::getLayer(int id)
{
    if (id < 0 || id >= pyramidSize) {
        throw std::out_of_range(QString("Layer not exists: %1").arg(id).toStdString());
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
    double denominator = qPow(stepKoeff, layerId);
    return QSize(originSize.width() / denominator, originSize.height() / denominator);
}

void Pyramid::rebuildForStep(double step)
{
    checkStep(step);
    stepKoeff = step;

    auto keys = layers.keys();
    for (auto key : keys) {
        if (key != originImageLayer) {
            layers.remove(key);
        }
    }

    QSize imageSize = layers.value(originImageLayer).size();
    int minSize = imageSize.height() > imageSize.width() ? imageSize.width() : imageSize.height();
    /*
     * Двоичный логарифм вычисляем по формуле logA(x) = ln(x)/ln(A)
     * Размер пирамиды равен округлённому вверх logA(min(width, height)
     */
    double koeff = qLn(stepKoeff);
    pyramidSize = qCeil(qLn(minSize) / koeff);

}

double Pyramid::getPyramidStep() const
{
    return stepKoeff;
}

void Pyramid::checkStep(double step)
{
    if (step < minimumStep || step > maximumStep) {
        throw std::invalid_argument(QString("Invalid pyramid step: %1").arg(step).toStdString());
    }
}
