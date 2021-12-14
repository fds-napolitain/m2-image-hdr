#ifndef IMAGEVIEWERUP_HPP
#define IMAGEVIEWERUP_HPP

#include <QLabel>
#include "../model/Image.hpp"
#include "Pipeline.hpp"
#include <QHBoxLayout>
#include <QGroupBox>
#include <QGridLayout>
#include <QMouseEvent>
#include <QScrollArea>

/**
 * Widget englobant une image.
 */
class ImageViewerUp : public QWidget {

private:
    QWidget* parent;
    Image image;
    QLabel* label;
    QBoxLayout *layout;
    float arWidth; // aspect ratio width
    float arHeight; // aspect ratio height
    QScrollArea *scrollArea;
public:
    Merge merged = Merge::NONE;
    Tonemap tonemapped = Tonemap::NONE;
    Contrast contrasted = Contrast::NONE;
    ImageViewerUp();
    explicit ImageViewerUp(QWidget* parent);
    ~ImageViewerUp() override;
    void loadImage(const Image& image);
    void reloadImage();
    Image* getImage();
    void loadImage(const QString& filename, QGroupBox *stack);
    QLabel* getQLabel();
    void reset();
    void resizeEvent(QResizeEvent *event) override;

};


#endif // IMAGEVIEWERUP_HPP
