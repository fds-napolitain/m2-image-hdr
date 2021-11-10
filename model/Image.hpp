#ifndef QTHDR_IMAGE_HPP
#define QTHDR_IMAGE_HPP

#include <QImage>
#include <opencv2/opencv.hpp>

/**
 * Ici, faudra utiliser peut etre une Mat OpenCV pour avoir une même base de travail
 */
class Image {

private:
	cv::Mat image;
	bool isHDR = false;

public:
	Image();
	explicit Image(const QString& filename, bool isHDR  = false);
	void loadImage(const QString& filename);
	[[nodiscard]] QImage getImage() const;
};


#endif //QTHDR_IMAGE_HPP
