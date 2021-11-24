//
// Created by Maxime Boucher on 30/10/2021.
//


#include <utility>
#include "Image.hpp"


Image::Image() = default;

Image::Image(cv::Mat image) {
	this->image = std::move(image);
}

/**
 * Initialise une image avec OpenCV.
 * @param filename
 * @param isHDR
 */
Image::Image(const QString& filename) {
	loadImage(filename);
	QStringList tmp = filename.split('/');
	tmp = tmp.at(tmp.size()-1).split('_').at(1).split('.');
	if (tmp.size() == 3) { // floating point
		this->exposure = (tmp.at(0) + "." + tmp.at(1)).toFloat();
	} else {
		this->exposure = tmp.at(0).toFloat();
	}
	std::cout << this->exposure << "\n";
}

/**
 * Destructeur
 */
Image::~Image() = default;

/**
 * Charge une image avec OpenCV
 * @param filename chemin d'accès à l'image
 */
void Image::loadImage(const QString& filename) {
	image = cv::imread(filename.toStdString());
}

/**
 * Return normalized 8 bit unsigned char cv matrix unique (automatic destruction) pointer.
 * @return
 */
cv::Mat Image::getMatrix() const {
	if (image.depth() == 5) {
		cv::Mat image8;
		image.convertTo(image8, CV_8U, 255);
		return image8;
	} else {
		return image;
	}
}

/**
 * Retourne une image au format QImage (à utiliser dans les widgets UI Qt).
 * @return
 */
QImage Image::getQImage() const {
	cv::Mat mat = getMatrix();
	return QImage((uchar*) mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888).rgbSwapped();
}

/**
 * Retourne le temps d'exposition de l'image
 * @return
 */
float Image::getExposure() const {
	return exposure;
}

/**
 * Get local entropy to measure HDR like DxOMark.
 * @return
 */
float Image::getAverageEntropy() {
	cv::Mat mat = getMatrix();
	const int boxOffset = 8; // nombre de sous image par longueur
	const int w = mat.rows / boxOffset; // longueur, largeur sous image
	const int h = mat.cols / boxOffset;
	float entropy = 0.0; // entropie moyenne
	for (int i = 0; i < boxOffset; ++i) {
		for (int j = 0; j < boxOffset; ++j) {
			cv::Mat subImg = mat(cv::Range(w * i, w * (i + 1)), cv::Range(h * j, h * (j + 1)));
			std::vector<unsigned char> histogram(256);
			uchar* p = subImg.data;

			for (int l = 0; l < subImg.total(); ++l) {
				histogram[*(p++)]++; // incrément histogramme et pointeur
			}
 			//cv::normalize(histogram, histogram, 0, 255, cv::NORM_MINMAX);
			for (int k = 0; k < 256; ++k) {
				float pi = histogram[k] / (float) subImg.total();
				if (pi == 0) continue;
				entropy +=  -pi * log(pi); //histogram[k] * log(1.0/histogram[k]);
			}
		}
	}
	return entropy/boxOffset; // retourne entropie moyenne des sous images
}

/**
 * Applique sur place une image à gamme dynamique classique mais étalonnée à partir des images HDR, de 0 à 255.
 * @return
 */
void Image::tonemapDrago() {
	std::cout << "4. Exécute le mappage ton-local de Drago\n";
	cv::Mat result;
	cv::Ptr<cv::TonemapDrago> tonemap = cv::createTonemapDrago();
	tonemap->process(image, result);
	image = std::move(result);
}

/**
 * Applique sur place une image à gamme dynamique classique mais étalonnée à partir des images HDR, de 0 à 255.
 * @return
 */
void Image::tonemapReinhard() {
	std::cout << "4. Exécute le mappage ton-local de Reinhard\n";
	cv::Mat result;
	cv::Ptr<cv::TonemapReinhard> tonemap = cv::createTonemapReinhard();
	tonemap->process(image, result);
	image = std::move(result);
}
