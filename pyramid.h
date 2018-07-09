#ifndef PYRAMID_H
#define PYRAMID_H

#include <QImage>
#include <QVector>
#include <QMap>
#include <exception>

class Pyramid
{
public:
    void openImage(const QString &fileName);
    int size() const;
    const QImage &getLayer(int id);
    QSize getOriginSize() const;
    QSize getLayerSize(int layerId) const;
    const static int originImageLayer;

private:
    QMap<int, QImage> layers;
    int pyramidSize;
};

class PyramidException : public std::logic_error {
public:
    using logic_error::logic_error;
};

#endif // PYRAMID_H
