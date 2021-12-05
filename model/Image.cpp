//
// Created by Maxime Boucher on 30/10/2021.
//


#include <utility>
#include "Image.hpp"


Image::Image() = default;

Image::Image(const cv::Mat& image) {
	this->image = image.clone();
}

/**
 * Initialise une image avec OpenCV.
 * @param filename
 */
Image::Image(const QString& filename) {
	if (filename.endsWith(".hdr")) {
		loadImage(filename);
	} else {
		loadImage(filename);
		QStringList tmp = filename.split('/');
		tmp = tmp.at(tmp.size()-1).split('_');
		tmp = tmp.at(1).split('.');
		if (tmp.size() == 3) { // floating point
			this->exposure = (tmp.at(0) + "." + tmp.at(1)).toFloat();
		} else {
			this->exposure = tmp.at(0).toFloat();
		}
		std::cout << this->exposure << "\n";
	}
}

/**
 * Constructeur par recopie
 * @param image
 */
Image::Image(const Image &image) {
	this->image = image.image.clone();
	this->exposure = image.getExposure();
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
	image = cv::imread(filename.toStdString(), cv::IMREAD_UNCHANGED);
}

/**
 * Retourne le flags (CV_8C3 etc...)
 * @return
 */
std::string Image::getFlags() const {
	std::string r;
	uchar depth = image.type() & CV_MAT_DEPTH_MASK;
	uchar chans = 1 + (image.type() >> CV_CN_SHIFT);
	switch (depth) {
		case CV_8U:  r = "8U"; break;
		case CV_8S:  r = "8S"; break;
		case CV_16U: r = "16U"; break;
		case CV_16S: r = "16S"; break;
		case CV_32S: r = "32S"; break;
		case CV_32F: r = "32F"; break;
		case CV_64F: r = "64F"; break;
		default:     r = "User"; break;
	}
	r += "C";
	r += (chans+'0');
	return r;
}

/**
 * Return normalized 8 bit unsigned char cv matrix unique (automatic destruction) pointer.
 * @return
 */
cv::Mat Image::getMatrix() const {
	if (getFlags() == "32FC3") {
		cv::Mat image8 = cv::Mat(image.size(), CV_8UC3);
		image.convertTo(image8, CV_8UC3, 255);
		return image8;
	} else {
		return image.clone();
	}
}

/**
 * Retourne une image au format QImage (à utiliser dans les widgets UI Qt).
 * @return
 */
QImage Image::getQImage() const {
	cv::Mat mat = getMatrix();
	std::cout << Image(mat).getFlags();
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
 * Renvoit l'histogramme
 * @param mat
 * @param size
 * @param minRange
 * @param maxRange
 * @param result
 * @return
 */
std::vector<cv::Mat> Image::getHistogram(cv::Mat& mat, int size, float minRange, float maxRange, std::vector<cv::Mat>& result) {

	std::vector<cv::Mat> bgr_planes;
	split( mat, bgr_planes );

	int histSize = size;
	float range[] = { minRange, maxRange }; //the upper boundary is exclusive
	const float* histRange[] = { range };
	int x = mat.channels();




	cv::Mat b_hist, g_hist, r_hist, complete_hist;
	calcHist( &bgr_planes[0], 1, nullptr, cv::Mat(), b_hist, 1, &histSize, histRange, true, false );
	calcHist( &bgr_planes[1], 1, nullptr, cv::Mat(), g_hist, 1, &histSize, histRange, true, false );
	calcHist( &bgr_planes[2], 1, nullptr, cv::Mat(), r_hist, 1, &histSize, histRange, true, false );
	calcHist( &mat, 1, &x, cv::Mat(), r_hist, 1, &histSize, histRange, true, false );

	normalize(b_hist, b_hist, 0, mat.rows, cv::NORM_MINMAX, -1, cv::Mat() );
	normalize(g_hist, g_hist, 0, mat.rows, cv::NORM_MINMAX, -1, cv::Mat() );
	normalize(r_hist, r_hist, 0, mat.rows, cv::NORM_MINMAX, -1, cv::Mat() );

	result.resize(4);
	result[0] = r_hist;
	result[1] = g_hist;
	result[2] = b_hist;
	result[3] = complete_hist;

	int hist_w = 512, hist_h = 400;
	int bin_w = cvRound( (double) hist_w/histSize );
	cv::Mat histImage( hist_h, hist_w, CV_8UC3, cv::Scalar( 0,0,0) );
	for( int i = 1; i < histSize; i++ )
	{
		line( histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ),
			  cv::Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
			  cv::Scalar( 255, 0, 0), 2, 8, 0  );
		line( histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ),
			  cv::Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
			  cv::Scalar( 0, 255, 0), 2, 8, 0  );
		line( histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ),
			  cv::Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
			  cv::Scalar( 0, 0, 255), 2, 8, 0  );
	}

	cv::imshow("Histogramme", histImage);
	return result;
}

/**
 * Égalisation d'histogramme pour amélioration de contraste.
 * @param Clahe
 * @return
 */
cv::Mat Image::calcEqualization(bool Clahe){
	std::cout << "5. Exécute l'égalisation d'histogramme.\n";

	cv::Mat mat = this->getMatrix();
    cv::Mat value;
    cv::Mat matrices[3];
    cv::cvtColor(mat, value, cv::COLOR_BGR2HSV);
    cv::split(value, matrices);

    if (Clahe) {
        cv::Ptr<cv::CLAHE> cl  =  cv::createCLAHE(2.0);
        cl->apply(matrices[2], matrices[2]);
    } else {
        cv::equalizeHist(matrices[2], matrices[2]);
    }

    cv::merge(matrices, 3 , value);
    cv::cvtColor(value, mat, cv::COLOR_HSV2BGR);

    return mat;
}

/**
 * Get local entropy to measure HDR like DxOMark.
 * @return
 */
float Image::getAverageEntropy() {
	cv::Mat mat = getMatrix();
	cv::Mat value;
	cv::cvtColor(mat, value, cv::COLOR_BGR2GRAY);
	constexpr int boxOffset = 8; // nombre de sous image par longueur
	const int w = value.rows / boxOffset; // longueur, largeur sous image
	const int h = value.cols / boxOffset;

    float entropy = 0.0; // entropie moyenne
    for (int i = 0; i < boxOffset; ++i) {
        for (int j = 0; j < boxOffset; ++j) {
            cv::Mat subImg = value(cv::Range(w * i, w * (i + 1)), cv::Range(h * j, h * (j + 1)));
            //cv::cvtColor(subImg, subImg, cv::COLOR_BGR2GRAY);
            std::vector<float> histogram(256);
            //getHistogram(subImg, 256, 0.f, 255.f, histogram);
            //cv::normalize(histogram, histogram, 0, 255, cv::NORM_MINMAX);
            unsigned char* p = subImg.data;
            for(int i = 0; i < subImg.total(); i++) {
                histogram[*p]++;
                p++;
            }
            for (int k = 0; k < 256; ++k) {
                float pi = histogram[k] / (float) subImg.total();
                if (pi != 0) {
                    entropy -= (pi * log2(pi)); //histogram[k] * log(1.0/histogram[k]);
                }
            }
        }
    }

	return entropy / pow(boxOffset, 2)  ; // retourne entropie moyenne des sous images
}

/**
 * Applique sur place une image à gamme dynamique classique mais étalonnée à partir des images HDR, de 0 à 255.
 * @return
 */
void Image::tonemapDrago( float gamma = 1.0) {
	std::cout << "4. Exécute le mappage ton-local de Drago\n";
	cv::Ptr<cv::TonemapDrago> tonemap = cv::createTonemapDrago(gamma);
	tonemap->process(image, image);
}

/**
 * Applique sur place une image à gamme dynamique classique mais étalonnée à partir des images HDR, de 0 à 255.
 * @return
 */
void Image::tonemapReinhard(float gamma = 1.0) {
	std::cout << "4. Exécute le mappage ton-local de Reinhard\n";
	cv::Ptr<cv::TonemapReinhard> tonemap = cv::createTonemapReinhard(gamma);
	tonemap->process(image, image);
}
