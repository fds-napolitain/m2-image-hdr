#include "StackImage.hpp"

StackImage::StackImage() = default;

/**
 * Crée et charge un ensemble d'images à partir d'une liste de chemins de fichiers
 * @param filenames liste de chemins de fichiers
 */
StackImage::StackImage(const QStringList& filenames) {
	loadImages(filenames);
}

/**
 * Charge un ensemble d'images à partir d'une liste de chemins de fichiers
 * @param filenames liste de chemins de fichiers
 */
void StackImage::loadImages(const QStringList& filenames) {
	images.reserve(filenames.size());
	int i = 0;
	for (const QString &image: filenames) {
		images[i] = Image(image);
	}
}
