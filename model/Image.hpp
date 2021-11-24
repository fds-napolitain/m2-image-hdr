#ifndef QTHDR_IMAGE_HPP
#define QTHDR_IMAGE_HPP

#include <QImage>
#include <opencv2/opencv.hpp>

/**
 * Classe qui fait le pont entre une cv::Mat opencv (pour le traitement d'image) et QImage (pour l'interface graphique).
 */
class Image {

private:
	float exposure;
	[[nodiscard]] cv::Mat getMatrix() const;
public:
	cv::Mat image;
	Image();
	explicit Image(cv::Mat image);
	explicit Image(const QString& filename);
	~Image();
	void loadImage(const QString& filename);
	[[nodiscard]] QImage getQImage() const;
	[[nodiscard]] float getExposure() const;
	std::vector<cv::Mat> getHistogram(cv::Mat& mat, int size, float minRange, float maxRange, std::vector<cv::Mat>& result);
	float getAverageEntropy();
	// -- méthodes sur une image
	void tonemapDrago();
	void tonemapReinhard();

};


#endif //QTHDR_IMAGE_HPP
