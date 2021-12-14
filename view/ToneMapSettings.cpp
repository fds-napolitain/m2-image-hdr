
#include "ToneMapSettings.hpp"

ToneMapSettings::ToneMapSettings(QWidget *parent, float step) :
        QWidget(parent),
        m_step(step),
        m_gammaSlider(new QSlider(Qt::Horizontal)),
        m_saturationSlider(new QSlider(Qt::Horizontal)),
        m_biasSlider(new QSlider(Qt::Horizontal)),
        m_intensitySlider(new QSlider(Qt::Horizontal)),
        m_lightAdaptSlider(new QSlider(Qt::Horizontal)),
        m_colorAdaptSlider(new QSlider(Qt::Horizontal)),
        m_gammaLabel(new QLabel("Gamma : \n 1.0")),
        m_SaturationLabel(new QLabel("Saturation : \n 1.0")),
        m_biasLabel(new QLabel("Bias : \n 1.0")),
        m_intensityLabel(new QLabel("Intensity : \n 0.0")),
        m_lightAdaptLabel(new QLabel("Light Adaptation : \n 1.0")),
        m_colorAdaptLabel(new QLabel("Color Adaptation : \n 0.0"))
{
    mainLayout  = new QStackedLayout(this);

    drago       =  new QWidget(this);
    dragoLayout =  new QGridLayout();

    drago->setLayout(dragoLayout);
    setupDragoLayout();

    reinhard          = new QWidget(this);
    reinhardLayout    = new QGridLayout();
    reinhard->setLayout(reinhardLayout);
    setupReinhardLayout();

    mainLayout->addWidget(drago);
    mainLayout->addWidget(reinhard);

    connect(m_gammaSlider, &QSlider::valueChanged, this, &ToneMapSettings::setGamma);
    connect(m_saturationSlider, &QSlider::valueChanged, this, &ToneMapSettings::setSaturation);
    connect(m_biasSlider, &QSlider::valueChanged, this, &ToneMapSettings::setBias);
    connect(m_intensitySlider, &QSlider::valueChanged, this, &ToneMapSettings::setIntensity);
    connect(m_lightAdaptSlider, &QSlider::valueChanged, this, &ToneMapSettings::setLightAdaptation);
    connect(m_colorAdaptSlider, &QSlider::valueChanged, this, &ToneMapSettings::setColorAdaptation);


}

void ToneMapSettings::setupDragoLayout() {
    int tickInterval = 1/m_step;

    m_gammaSlider->setTickPosition(QSlider::TicksAbove);
    m_saturationSlider->setTickPosition(QSlider::TicksAbove);
    m_biasSlider->setTickPosition(QSlider::TicksAbove);

    m_gammaSlider->setTickInterval(tickInterval);
    m_saturationSlider->setTickInterval(tickInterval);
    m_biasSlider->setTickInterval(tickInterval);

    m_gammaSlider->setValue(tickInterval);
    m_saturationSlider->setValue(tickInterval);
    m_biasSlider->setValue(tickInterval);

    dragoLayout->addWidget(m_SaturationLabel,1,0);
    dragoLayout->addWidget(m_saturationSlider, 1,1);

    dragoLayout->addWidget(m_biasLabel,2,0);
    dragoLayout->addWidget(m_biasSlider, 2, 1);
}

void ToneMapSettings::setupReinhardLayout() {
    int tickInterval = 1/m_step;
    QSlider test(Qt::Horizontal);

    m_intensitySlider->setTickPosition(QSlider::TicksAbove);
    m_lightAdaptSlider->setTickPosition(QSlider::TicksAbove);
    m_colorAdaptSlider->setTickPosition(QSlider::TicksAbove);

    m_intensitySlider->setTickInterval(tickInterval);
    m_lightAdaptSlider->setTickInterval(tickInterval);
    m_colorAdaptSlider->setTickInterval(tickInterval);

    m_lightAdaptSlider->setValue(tickInterval);


    reinhardLayout->addWidget(m_intensityLabel,1,0);
    reinhardLayout->addWidget(m_intensitySlider, 1,1);

    reinhardLayout->addWidget(m_lightAdaptLabel,2,0);
    reinhardLayout->addWidget(m_lightAdaptSlider,2,1);

    reinhardLayout->addWidget(m_colorAdaptLabel,3,0);
    reinhardLayout->addWidget(m_colorAdaptSlider,3,1);

}

void ToneMapSettings::setToneMap(Tonemap type) {
    switch (type) {
        case Tonemap::Drago :
            this->setDisabled(false);
            dragoLayout->addWidget(m_gammaLabel, 0, 0);
            dragoLayout->addWidget(m_gammaSlider, 0, 1);
            mainLayout->setCurrentIndex(0);
            break;
        case Tonemap::Reinhard :

            this->setDisabled(false);
            reinhardLayout->addWidget(m_gammaLabel,0,0);
            reinhardLayout->addWidget(m_gammaSlider, 0, 1);
            mainLayout->setCurrentIndex(1);
            break;
        default:
            this->setDisabled(true);
    }
}

void ToneMapSettings::setGamma(int value) {
    float newValue = (float)value * m_step;
    m_gammaLabel->setText("Gamma : \n" + QString::number(newValue));
    emit gammeValueChanged(value);
    emit anyValueChanged(true);
}

void ToneMapSettings::setSaturation(int value) {
    float newValue = (float)value * m_step;
    m_SaturationLabel->setText("Saturation : \n" + QString::number(newValue));
    emit saturationValueChanged(value);
    emit anyValueChanged(true);
}

void ToneMapSettings::setBias(int value) {
    float newValue = (float)value * m_step;
    m_biasLabel->setText("Bias : \n" + QString::number(newValue));
    emit biasValueChanged(value);
    emit anyValueChanged(true);
}

void ToneMapSettings::setIntensity(int value) {
    float newValue = (float)value * m_step;
    m_intensityLabel->setText("Intensity : \n" + QString::number(newValue));
    emit intensityValueChanged(value);
    emit anyValueChanged(true);
}

void ToneMapSettings::setLightAdaptation(int value) {
    float newValue = (float)value * m_step;
    m_lightAdaptLabel->setText("Light Adaptation : \n" + QString::number(newValue));
    emit lightAdaptationValueChanged(value);
    emit anyValueChanged(true);
}

void ToneMapSettings::setColorAdaptation(int value) {
    float newValue = (float)value * m_step;
    m_colorAdaptLabel->setText("Color Adaptation : \n" + QString::number(newValue));
    emit colorAdaptationValueChanged(value);
    emit anyValueChanged(true);
}


QSlider *ToneMapSettings::getGammaSlider() {
    return m_gammaSlider;
}

QSlider *ToneMapSettings::getSaturationSlider() {
    return m_saturationSlider;
}

QSlider *ToneMapSettings::getBiasSlider() {
    return m_biasSlider;
}

float ToneMapSettings::getBiasValue() {
    return (float) m_biasSlider->value() * m_step;
}

float ToneMapSettings::getSaturationValue() {
    return (float) m_saturationSlider->value() * m_step;
}


float ToneMapSettings::getGammaValue() {
    return (float) m_gammaSlider->value() * m_step;
}

float ToneMapSettings::getIntensityValue() {
    return (float) m_intensitySlider->value() * m_step;
}

float ToneMapSettings::getLightAdaptationValue() {
    return (float) m_lightAdaptSlider->value() * m_step;
}

float ToneMapSettings::getColorAdaptationValue() {
    return (float) m_colorAdaptSlider->value() * m_step;
}
