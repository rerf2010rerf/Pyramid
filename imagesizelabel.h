#ifndef IMAGESIZELABEL_H
#define IMAGESIZELABEL_H

#include <QLabel>

class ImageSizeLabel : public QLabel
{
public:
    void setImageSize(int width, int height);
};

#endif // IMAGESIZELABEL_H
