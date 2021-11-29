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
	explicit StackImage(int n);
	void addImage(Image* image);
	void addImage(Image* image, int i);
	[[nodiscard]] std::vector<cv::Mat> getMatrices();
	[[nodiscard]] std::vector<float> getExposures();
	// -- méthodes sur des images (ex: HDR)
	void alignMTB();
	Image mergeDebevec();
	Image mergeMertens();
	Image mergeRobertson();
};


#endif //QTHDR_STACKIMAGE_HPP
