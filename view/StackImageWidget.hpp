//
// Created by Maxime Boucher on 14/11/2021.
//

#ifndef QTHDR_STACKIMAGEWIDGET_HPP
#define QTHDR_STACKIMAGEWIDGET_HPP

#include <vector>
#include <QGroupBox>
#include "ImageViewerUp.hpp"
#include "../model/StackImage.hpp"
#include "Pipeline.hpp"
#include <QHBoxLayout>
#include <QScrollBar>
#include <QScrollArea>

class StackImageWidget : public QWidget {

private:
    std::vector<ImageViewerUp*> images;
	QWidget* parent;
	QScrollArea* scroll;
	QVBoxLayout* scrollLayout;
public:
	Align aligned = Align::NONE;
	QGroupBox* stack;
	StackImageWidget();
	explicit StackImageWidget(QWidget* parent);
	~StackImageWidget() override;
	void loadImages(const QStringList& filenames);
	StackImage getImages();
	// -- méthodes hdr
	void alignMTB();
	Image merge();
	Image mergeDebevec();
	Image mergeRobertson();
	Image mergeMertens(bool s = false);
};


#endif //QTHDR_STACKIMAGEWIDGET_HPP
