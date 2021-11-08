#ifndef QTHDR_IMAGE_HPP
#define QTHDR_IMAGE_HPP


#include <QImage>

/**
 * Ici, faudra utiliser peut etre une Mat OpenCV pour avoir une même base de travail
 */
class Image {

private:
	QImage image;
	bool isHDR = false;

public:
	Image();
	explicit Image(const QString& filename, bool isHDR);
	bool loadImage(const QString& filename);
};


#endif //QTHDR_IMAGE_HPP
