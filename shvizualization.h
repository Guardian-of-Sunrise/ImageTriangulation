#ifndef SHVIZUALIZATION_H
#define SHVIZUALIZATION_H

#include <QWidget>
#include <QMainWindow>
#include <QPainter>
#include <QImage>
#include <QMouseEvent>
#include <QPoint>
#include <QPair>
#include <QStack>
#include <opencv2/imgproc.hpp>
#include "opencv2/highgui.hpp"
#include <opencv2/opencv.hpp>
#include "CDT.h"
#include "triangulation.h"
#include "shtriangulation.h"

class ShVizualization : public QWidget
{
    Q_OBJECT

public:
    explicit ShVizualization(QWidget *parent = nullptr);
    virtual ~ShVizualization();

    //Визуализация
    void setVizualizationObject(ShTriangulation* obj);
    void shiftRight();
    void shiftLeft();
    void shiftUp();
    void shiftDawn();
    void scaleUp();
    void scaleDawn();
    void contourDisplay(bool p,bool s);


private:

    //Фунции отрисовки визуализатора
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent*event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void resizeEvent(QResizeEvent *event) override;

    //Управление визуализацией
    ShTriangulation* trobject;
    int index;
    int index2;
    double scale;
    int shiftX,shiftY;
    bool contourViz = true;
    bool allContourShow =true;
    QPoint oldMousePoint;
    int orientation;
    QImage* img;//холст рисования
    QPainter* painter;//объект рисования
    QPoint* tempPoint;//исп для отрисовки точки до окончательной её вставки в искохдный вектор

};

#endif // SHTRIANGULATION_H


