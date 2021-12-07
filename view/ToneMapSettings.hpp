//
// Created by edgar on 01/12/2021.
//

#ifndef QTHDR_TONEMAPSETTINGS_HPP
#define QTHDR_TONEMAPSETTINGS_HPP
#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QGridLayout>
#include <QStackedLayout>
#include "../model/Pipeline.hpp"
class ToneMapSettings : public QWidget{
    Q_OBJECT
public:
    ToneMapSettings(QWidget* parent, float step);

    QSlider* getGammaSlider();
    QSlider* getSaturationSlider();
    QSlider* getBiasSlider();

    void setToneMap(Tonemap type);

    float getBiasValue();
    float getSaturationValue();
    float getGammaValue();
    float getIntensityValue();
    float getLightAdaptationValue();
    float getColorAdaptationValue();


private:

    void setupDragoLayout();
    void setupReinhardLayout();

    float m_step;
    QSlider* m_gammaSlider;
    QSlider* m_saturationSlider;
    QSlider* m_biasSlider;
    QSlider* m_intensitySlider;
    QSlider* m_lightAdaptSlider;
    QSlider* m_colorAdaptSlider;

    QLabel* m_gammaLabel;
    QLabel* m_SaturationLabel;
    QLabel* m_biasLabel;
    QLabel* m_intensityLabel;
    QLabel* m_lightAdaptLabel;
    QLabel* m_colorAdaptLabel;

    QWidget* drago;
    QWidget* reinhard;

    QStackedLayout* mainLayout;
    QGridLayout* dragoLayout;
    QGridLayout* reinhardLayout;


public slots:
    void setGamma(int value);
    void setSaturation(int value);
    void setBias(int value);
    void setIntensity(int value);
    void setLightAdaptation(int value);
    void setColorAdaptation(int value);

signals:
    void gammeValueChanged(int newValue);
    void saturationValueChanged(int newValue);
    void biasValueChanged(int newValue);
    void intensityValueChanged(int newValue);
    void lightAdaptationValueChanged(int newValue);
    void colorAdaptationValueChanged(int newValue);
    void anyValueChanged(bool hasChanged);



};


#endif //QTHDR_TONEMAPSETTINGS_HPP
