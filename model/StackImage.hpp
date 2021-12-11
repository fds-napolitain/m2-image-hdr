#ifndef QTHDR_STACKIMAGE_HPP
#define QTHDR_STACKIMAGE_HPP


#include <vector>
#include <QDir>
#include "Image.hpp"

class StackImage {

private:
	std::vector<Image*> images;
public:
	StackImage();

	void addImage(Image* image);

	[[nodiscard]] std::vector<cv::Mat> getMatrices();
	[[nodiscard]] std::vector<float> getExposures();
	// -- méthodes sur des images (ex: HDR)
	void alignMTB();
	Image mergeDebevec();
	Image mergeMertens();
	Image mergeRobertson();
	Image merge();
};


#endif //QTHDR_STACKIMAGE_HPP
