//
// Created by Maxime Boucher on 30/11/2021.
//

#ifndef QTHDR_ZOOMABLEIMAGEWIDGET_HPP
#define QTHDR_ZOOMABLEIMAGEWIDGET_HPP


#include "ImageWidget.hpp"

class ZoomableImageWidget : public QWidget  {

private:
	ImageWidget imageWidget;
	void mouseDoubleClickEvent(QMouseEvent *e) override;

};


#endif //QTHDR_ZOOMABLEIMAGEWIDGET_HPP
