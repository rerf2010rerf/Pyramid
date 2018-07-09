#ifndef PYRAMID_H
#define PYRAMID_H

#include <QImage>
#include <QVector>
#include <QMap>
#include <exception>

class Pyramid
{
public:
    void openImage(const QString &fileName, double step = 2);
    int size() const;
    const QImage &getLayer(int id);
    QSize getOriginSize() const;
    QSize getLayerSize(int layerId) const;
    void rebuildForStep(double step);
    double getPyramidStep() const;

    const static int originImageLayer;
    const static double minimumStep;
    const static double maximumStep;

private:
    void checkStep(double step);

    QMap<int, QImage> layers;
    int pyramidSize;
    double stepKoeff;
};

class PyramidException : public std::logic_error {
public:
    using logic_error::logic_error;
};

#endif // PYRAMID_H
