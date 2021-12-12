//
// Created by Maxime Boucher on 14/11/2021.
//

#ifndef QTHDR_STACKIMAGEWIDGET_HPP
#define QTHDR_STACKIMAGEWIDGET_HPP

#include <vector>
#include <QGroupBox>
#include "ImageWidget.hpp"
#include "../model/StackImage.hpp"
#include "../model/Pipeline.hpp"
#include <QHBoxLayout>
#include <QScrollBar>
#include <QScrollArea>

class StackImageWidget : public QWidget {

private:
	std::vector<ImageWidget*> images;
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
	Image mergeMertens();
};


#endif //QTHDR_STACKIMAGEWIDGET_HPP
