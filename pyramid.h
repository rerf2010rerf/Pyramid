#ifndef PYRAMID_H
#define PYRAMID_H

#include <QImage>
#include <QVector>
#include <exception>

class Pyramid
{
public:
    void openImage(const QString &fileName);
    int size() const;
    const QImage &getLayer(int id) const;
    QSize getOriginSize() const;
    const static int originImageLayer;

private:
    QVector<QImage> layers;

};

class PyramidException : public std::logic_error {
public:
    using logic_error::logic_error;
};

#endif // PYRAMID_H
