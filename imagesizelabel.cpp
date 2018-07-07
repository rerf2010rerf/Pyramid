#include "imagesizelabel.h"

void ImageSizeLabel::setImageSize(int width, int height) {
    setText(QString("Size: %1*%2").arg(width).arg(height));
}
