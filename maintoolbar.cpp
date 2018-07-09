#include "maintoolbar.h"

#include <QPushButton>

#include <algorithm>

MainToolbar::MainToolbar() :
    imageBox(new FileComboBox()),
    layerBox(new LayerComboBox()),
    imageSizeLabel(new ImageSizeLabel()),
    stepSpinBox(new QDoubleSpinBox())
{
    addWidget(imageBox);
    connect(imageBox, QOverload<const ImageItem &>::of(&FileComboBox::fileChanged), this, &MainToolbar::imageComboBoxChanged);

    addWidget(layerBox);

    connect(layerBox, QOverload<int>::of(&LayerComboBox::layerChanged), this, &MainToolbar::layerComboBoxChanged);
    addWidget(imageSizeLabel);

    stepSpinBox->setMinimum(Pyramid::minimumStep);
    stepSpinBox->setMaximum(Pyramid::maximumStep);
    stepSpinBox->setSingleStep(0.1);
    addWidget(new QLabel("Pyramid step: "));
    addWidget(stepSpinBox);

    QPushButton *updateStepButton = new QPushButton("update step");
    connect(updateStepButton, &QPushButton::clicked, this, &MainToolbar::updateStepClicked);
    addWidget(updateStepButton);
}

void MainToolbar::updateForPyramid(Pyramid &pyramid)
{
    imageSizeLabel->setImageSize(pyramid.getOriginSize());
    stepSpinBox->setValue(pyramid.getPyramidStep());
    layerBox->update(pyramid);
}

void MainToolbar::addNewImageItem(const ImageItem &imageItem)
{
    imageBox->addImageFile(imageItem);
}

void MainToolbar::layerComboBoxChanged(int index)
{
    emit layerChanged(index);
}

void MainToolbar::imageComboBoxChanged(const ImageItem &imageItem)
{
    emit imageChanged(imageItem);
}

void MainToolbar::updateStepClicked()
{
    emit pyramidStepChanged(stepSpinBox->value());
}



LayerComboBox::LayerComboBox()
{
    setSizeAdjustPolicy(QComboBox::SizeAdjustPolicy::AdjustToContents);
    connect(this, QOverload<int>::of(&QComboBox::activated), this, &LayerComboBox::qComboBoxActivate);
}

void LayerComboBox::update(Pyramid &pyramid) {
    clear();
    for (int i = 0; i < pyramid.size(); ++i) {
        QSize size = pyramid.getLayerSize(i);
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

FileComboBox::FileComboBox() : model(new FileListModel())
{
    setModel(model);
    setSizeAdjustPolicy(QComboBox::SizeAdjustPolicy::AdjustToContents);
    connect(this, QOverload<int>::of(&QComboBox::activated), this, &FileComboBox::qComboBoxActivate);
}

void FileComboBox::addImageFile(const ImageItem &imageItem)
{
    setCurrentIndex(model->addImage(imageItem));
}

void FileComboBox::qComboBoxActivate(int id)
{
    emit fileChanged(itemData(id).value<ImageItem>());
}



FileListModel::FileListModel(QObject *parent) :
    QAbstractListModel(parent) {
}

int FileListModel::rowCount(const QModelIndex &) const
{
    return items.size();
}

QVariant FileListModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        return QVariant(items.at(index.row()).value<ImageItem>().getFileName());
    } else if (role == Qt::UserRole) {
       return items.at(index.row());
    } else {
        return QVariant();
    }

}

int FileListModel::addImage(const ImageItem &imageItem)
{
    auto comparator = [](const QVariant &first, const QVariant &second) -> bool {
        QSize firstSize = first.value<ImageItem>().getImageSize();
        QSize secondSize = second.value<ImageItem>().getImageSize();
        double thisDiag = qSqrt(qPow(firstSize.width(), 2) + qPow(firstSize.height(), 2));
        double otherDiag = qSqrt(qPow(secondSize.width(), 2) + qPow(secondSize.height(), 2));
        return thisDiag < otherDiag;
    };

    auto positionIter = std::lower_bound(items.cbegin(), items.cend(), QVariant::fromValue(imageItem), comparator);
    int position = positionIter - items.cbegin();
    beginInsertRows(QModelIndex(), position, position);
    items.insert(position, QVariant::fromValue(imageItem));
    endInsertRows();
    return position;
}
