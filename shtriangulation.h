#ifndef SHTRIANGULATION_H
#define SHTRIANGULATION_H


#include <QString>
#include <QPoint>
#include <QVector>
#include <triangulation.h>
#include <opencv2/imgproc.hpp>
#include "opencv2/highgui.hpp"
#include <opencv2/opencv.hpp>
#include "QVector2D"
#include "QSet"


class ShTriangulation
{
public:

    int ContoursCount;

    explicit ShTriangulation();
    ~ShTriangulation();
    const QVector<QVector<QPoint>>& getAproxContours();
    const QVector<class Triangulation>& getTriangulations();
    //Обработка
    void aproxAllContours(double eps);
    void shredding(int q,bool borderFlag);
    int findContour(QString fileName,int numberContour = 0);//поиск контура
    void triangulation();
    void shreddingAllImage();
    void saveToStl(QString directory);
    int trianglesNumber();
    void saveNewImage(QString name);
    void oneAreaTriang();
    void saveNewSvgImage(QString name);
    int findCannyEges(QString fileName);
    void shreedCanny(int q,bool borderFlag);
    int testTriangCanny(QString name);
    void SH();

private:

    //Обработка изображения

    QVector<QVector<QPoint>> contourPoints;
    cv::Mat oldimg;
    QVector<class Triangulation> triangulations;
    QVector<QVector<QPoint>> contours;
    std::vector<std::vector<cv::Point>> stdContours;
    QVector<QVector<QPoint>> aproxContours;
    std::vector<cv::Vec4i> ierarhy;
    QVector<QVector<int>> triangles;//триангуляция
    QVector<QPoint> summPoints;
    bool shreddingState;
    int steps=0;



    //Функции обработки
    void notBorderline(int a, int b, int c,int q,QVector<QPoint> &newpoints,QVector<QVector<int>> &newTriangles );
    void borderline(int a, int b, int c,int q,QVector<QPoint> &newPoints,QVector<QVector<int>> &newTriangles,bool AC,bool BC);
    double det(double a,double b,double c,double d);
    bool intersect(const QVector2D &point1, const QVector2D &point2, const QVector2D &point3,const QVector2D &point4,QVector2D & intersect);//поиск точки пересечения
    bool isIntersect(const QVector2D &point,const QVector2D &fpointSegment,const QVector2D &spointSegment,const QVector2D &fpointRay,const QVector2D &spointRay);//принадлежит ли точка отрезку и лучу

};

//Отрисовка границ град. треугольника
void drawLine(cv::Mat* image, cv::Point start, cv::Point end, cv::Scalar startColor, cv::Scalar endColor);

#endif // SHTRIANGULATION_H
