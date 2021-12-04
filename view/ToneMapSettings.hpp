//
// Created by edgar on 01/12/2021.
//

#ifndef QTHDR_TONEMAPSETTINGS_HPP
#define QTHDR_TONEMAPSETTINGS_HPP
#include <QWidget>
#include <QSlider>
#include <QLabel>
class ToneMapSettings : public QWidget{
public:
    ToneMapSettings(QWidget* parent, float step) :
        QWidget(parent),
        m_step(step),
        m_gammaSlider(new QSlider(Qt::Horizontal)),
        m_saturationSlider(new QSlider(Qt::Horizontal)),
        m_biasSlider(new QSlider(Qt::Horizontal))
        {}

    QSlider* getGammaSlider();
    QSlider* getSaturationSlider();
    QSlider* getBiasSlider();

    float getBiasValue();
    float getSaturationValue();
    float getGammaValue();


private:
    float m_step;
    QSlider* m_gammaSlider;
    QSlider* m_saturationSlider;
    QSlider* m_biasSlider;

    QLabel* m_gammaLabel;
    QLabel* m_SaturationLabel;
    QLabel* m_biasLabel;



};


#endif //QTHDR_TONEMAPSETTINGS_HPP
