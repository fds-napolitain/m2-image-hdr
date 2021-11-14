#ifndef QTHDR_STACKIMAGE_HPP
#define QTHDR_STACKIMAGE_HPP


#include <vector>
#include <QDir>
#include "Image.hpp"

class StackImage {

private:
	std::vector<Image> images;
public:
	StackImage();
	explicit StackImage(const QStringList& filenames);
	void loadImages(const QStringList& filenames);
	[[nodiscard]] std::vector<cv::Mat> getMatrices();
	[[nodiscard]] std::vector<float> getExposures();
	// -- méthodes sur des images (ex: HDR)
	Image mergeDebevec();

};


#endif //QTHDR_STACKIMAGE_HPP
