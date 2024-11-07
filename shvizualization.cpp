#include "shvizualization.h"
#include "QMouseEvent"
#include "QPainter"



ShVizualization::ShVizualization(QWidget *parent)
    : QWidget{parent}
{

    setMouseTracking(true);
    img=new QImage(this->width(),this->height(),QImage::Format_ARGB32_Premultiplied);
    img->fill(qRgb(0,0,0));
    this->setMouseTracking(true);
    painter=new QPainter();
    painter->begin(this);
    painter->drawImage(0,0,*img);
    painter->end();
    scale=1;
    shiftX=0;
    shiftY=0;
}


void ShVizualization::setVizualizationObject(ShTriangulation* obj){
    this->trobject = obj;
}



void ShVizualization::resizeEvent(QResizeEvent *event)
{
   Q_UNUSED(event);
   QImage* timg=img;
   img =new  QImage(this->width(),this->height(),QImage::Format_ARGB32_Premultiplied);
   img->fill(qRgb(0,0,0));
   delete timg;

    repaint();
}
void ShVizualization::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QImage* imgTemp=new QImage(this->width(),this->height(),QImage::Format_ARGB32_Premultiplied);
    imgTemp->fill(qRgb(255,255,255));
    painter->setRenderHint(QPainter::Antialiasing);
    painter->begin(imgTemp);
    painter->translate(shiftX+this->width()/2,shiftY+this->height()/2);
    painter->scale(scale,scale); 
    if(trobject!=nullptr){
    painter->setPen(QPen(Qt::red,2));
    for(auto i:trobject->getAproxContours()){
        for (int j = 0;j<i.size()-1; j++){
            if(i.size()>1){
                painter->drawLine(i[j],i[j+1]);
            }
        }
        if(i.size()>1){
            painter->drawLine(i[i.size()-1],i[0]);
        }
    }

    painter->setPen(QPen(Qt::blue,2));
    for(auto i:trobject->getTriangulations()){
        auto points = i.getTriangulationPoints();
        auto triangles = i.getTriangles();
        for(auto j :triangles){
            painter->drawLine(points[j[0]],points[j[1]]);
            painter->drawLine(points[j[1]],points[j[2]]);
            painter->drawLine(points[j[2]],points[j[0]]);
        }
    }
    painter->end();
    }

    painter->begin(this);
    painter->restore();
    auto del=img;
    img=imgTemp;
    painter->drawImage(0,0,*img);
    delete del;
    painter->end();
}
void ShVizualization::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){

    tempPoint=new QPoint((-shiftX+event->pos().x()-this->width()/2)/scale,(-shiftY+event->pos().y()-this->height()/2)/scale);
    repaint();
    }
    if(event->button() == Qt::RightButton){
    oldMousePoint=event->pos();
    repaint();
    }
}

void ShVizualization::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton){
        if(tempPoint!=nullptr){
            (*tempPoint)=QPoint((-shiftX+event->pos().x()-this->width()/2)/scale,(-shiftY+event->pos().y()-this->height()/2)/scale);
        }
        repaint();
        return;
    }
    if(event->buttons() == Qt::RightButton){
            shiftX+=event->pos().x()-oldMousePoint.x();
            shiftY+=event->pos().y()-oldMousePoint.y();
            oldMousePoint=event->pos();
            repaint();
            return;
        }
}

 ShVizualization::~ShVizualization()
{
    delete painter;
    delete img;
    if(tempPoint!=nullptr){
    delete tempPoint;
    }
}

void ShVizualization::shiftRight()
{
    shiftX+=20;
    repaint();
}
void ShVizualization::shiftLeft()
{
    shiftX-=20;
    repaint();
}
void ShVizualization::contourDisplay(bool p,bool s){
    contourViz = p;
    allContourShow = s;
    repaint();
}
void ShVizualization::shiftUp()
{
   shiftY+=20;
   repaint();
}
void ShVizualization::shiftDawn()
{
    shiftY-=20;
    repaint();
}

void ShVizualization::scaleUp()
{
    scale+=0.1;
    qDebug()<<scale;
    repaint();
}

void ShVizualization::scaleDawn()
{
    if((scale>0.19)){
    scale-=0.1;
    qDebug()<<scale;
    }
    repaint();
}




