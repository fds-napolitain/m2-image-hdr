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
	int flags;
	Image();
	explicit Image(const cv::Mat& image);
	explicit Image(const QString& filename);
	Image(const Image& image);
	~Image();
	void loadImage(const QString& filename);
	[[nodiscard]] std::string printFlags() const;
	// -- méthodes sur une image
	[[nodiscard]] float getExposure() const;
	[[nodiscard]] QImage getQImage() const;
	float getAverageEntropy();
	static std::vector<cv::Mat> getHistogram(cv::Mat& mat, int size, float minRange, float maxRange, std::vector<cv::Mat>& result);
	void tonemapDrago(float gamma, float saturation, float bias);
	void tonemapReinhard(float gamma, float intensity, float lightAdapt, float colorAdapt);
	cv::Mat calcEqualization(bool clahe);

};


#endif //QTHDR_IMAGE_HPP
