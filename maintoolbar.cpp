#include "maintoolbar.h"



MainToolbar::MainToolbar() :
    layerBox(new LayerComboBox()),
    imageSizeLabel(new ImageSizeLabel())
{
    addWidget(layerBox);
    connect(layerBox, QOverload<int>::of(&LayerComboBox::layerChanged), this, &MainToolbar::layerComboBoxChanged);
    addWidget(imageSizeLabel);

}

void MainToolbar::updateForPyramid(const Pyramid &pyramid)
{
    imageSizeLabel->setImageSize(pyramid.getOriginSize());
    layerBox->update(pyramid);
}

void MainToolbar::layerComboBoxChanged(int index)
{
    emit layerChanged(index);
}



LayerComboBox::LayerComboBox()
{
    setSizeAdjustPolicy(QComboBox::SizeAdjustPolicy::AdjustToContents);
    connect(this, QOverload<int>::of(&QComboBox::activated), this, &LayerComboBox::qComboBoxActivate);
}

void LayerComboBox::update(const Pyramid &pyramid) {
    clear();
    for (int i = 0; i < pyramid.size(); ++i) {
        QSize size = pyramid.getLayer(i).size();
        addItem(
            QString("Layer %1: %2*%3").arg(i).arg(size.width()).arg(size.height()),
            QVariant(i)
        );
    }
}

void LayerComboBox::qComboBoxActivate(int id)
{
    emit layerChanged(itemData(id).toInt());
}

void ImageSizeLabel::setImageSize(const QSize &size) {
    setText(QString("Original image size: %1*%2").arg(size.width()).arg(size.height()));
}
