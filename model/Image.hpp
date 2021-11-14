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
	float exposure;
	float focal;
	float ISO;
	bool isHDR = false;
public:
	Image();
	explicit Image(cv::Mat image, bool isHDR = true);
	explicit Image(const QString& filename, bool isHDR = false);
	~Image();
	void loadImage(const QString& filename);
	[[nodiscard]] cv::Mat getMat();
	[[nodiscard]] QImage getQImage() const;
	[[nodiscard]] float getExposure() const;
	[[nodiscard]] float getFocal() const;
	[[nodiscard]] float getISO() const;
	// -- méthodes sur une image

};


#endif //QTHDR_IMAGE_HPP
