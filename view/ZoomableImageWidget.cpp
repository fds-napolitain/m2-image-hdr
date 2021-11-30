//
// Created by Maxime Boucher on 30/11/2021.
//

#include "ZoomableImageWidget.hpp"

/**
 * Ouvrir une image en plein écran dans une deuxième fenêtre.
 * @param e
 */
void ZoomableImageWidget::mouseDoubleClickEvent(QMouseEvent *e) {
	if (e->button() == Qt::LeftButton) {
		std::cout << "double clicked\n";
	}
}
