#ifndef QTHDR_IMAGE_HPP
#define QTHDR_IMAGE_HPP

#include <QImage>
#include <opencv2/opencv.hpp>

/**
 * Classe qui fait le pont entre une cv::Mat opencv (pour le traitement d'image) et QImage (pour l'interface graphique).
 */
class Image {

private:
	cv::Mat image;
	bool isHDR = false;

public:
	Image();
	explicit Image(const QString& filename, bool isHDR  = false);
	void loadImage(const QString& filename);
	void loadImages(const QStringList& filenames);
	[[nodiscard]] QImage getImage() const;

};


#endif //QTHDR_IMAGE_HPP
