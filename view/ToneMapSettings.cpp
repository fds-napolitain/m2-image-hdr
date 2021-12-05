//
// Created by edgar on 01/12/2021.
//

#include "ToneMapSettings.hpp"

ToneMapSettings::ToneMapSettings(QWidget *parent, float step) :
		QWidget(parent),
		m_step(step),
		m_gammaSlider(new QSlider(Qt::Horizontal)),
		m_saturationSlider(new QSlider(Qt::Horizontal)),
		m_biasSlider(new QSlider(Qt::Horizontal))
{}
