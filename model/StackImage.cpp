#include "StackImage.hpp"

StackImage::StackImage() = default;

StackImage::StackImage(const QString& foldername) {
	loadImages(foldername);
}

bool StackImage::loadImages(const QString& foldername) {
	QDir directory(foldername);
	QStringList stackImages = directory.entryList(QStringList() << "*.jpg" << "*.JPG", QDir::Files);
	images.reserve(stackImages.size());
	int i = 0;
	for (const QString &image: stackImages) {
		images[i] = Image(image);
	}
	return true;
}
