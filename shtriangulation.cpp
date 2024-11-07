#include "shtriangulation.h"
#include "QMouseEvent"
#include "QPainter"
#include <QDebug>
#include <fstream>
#include <QMessageBox>
#include <QtGlobal>
#include <QDebug>
#include <QtAlgorithms>
#include <QProgressBar>
#include <QSet>
#include <QElapsedTimer>
#include <QSvgGenerator>
#include "CDT.h"
#include <opencv2/imgproc.hpp>
#include "opencv2/highgui.hpp"
#include <opencv2/opencv.hpp>



ShTriangulation::ShTriangulation()
{
    ContoursCount=0;
    shreddingState = false;
}

ShTriangulation::~ShTriangulation()
{

}

const QVector<QVector<QPoint>>& ShTriangulation::getAproxContours(){
    return this->aproxContours;
}
const QVector<Triangulation>& ShTriangulation::getTriangulations(){
    return this->triangulations;
}





int ShTriangulation::findContour(QString filename,int numberСontour )
{
        oldimg =cv::imread(filename.toStdString());
        cv:: Mat gray;
        cv::Mat filter;
        cv::medianBlur(oldimg,filter,7);

        cv::cvtColor(filter, gray, cv::COLOR_BGR2GRAY);
        cv:: Mat thresh;
        //200
        cv::threshold(gray,thresh,90,255,cv::THRESH_BINARY);
        ierarhy.clear();
        contours.clear();

        cv::findContours(thresh, stdContours, ierarhy, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);

        contours.resize(stdContours.size());

        for(int i = 0;i<stdContours.size();i++){
            for(int j=0;j<stdContours[i].size();j++){
                contours[i].push_back(QPoint(stdContours[i][j].x,stdContours[i][j].y));
                  }
                }
        aproxAllContours(0.1);

        if(contours.size()!=0){
            return 1;
           }
            else{
            return 0;
        }
}


void ShTriangulation::aproxAllContours(double eps){
        aproxContours.clear();
        aproxContours.resize(stdContours.size());
        std::vector<cv::Point> Aproxcontours;

        for(int i = 0;i< stdContours.size();i++){
            Aproxcontours.clear();


            cv::approxPolyDP(stdContours[i],Aproxcontours,eps,true);

            for(int j = 0;j<Aproxcontours.size();j++){

                aproxContours[i].push_back(QPoint(Aproxcontours[j].x,Aproxcontours[j].y));
            }
        }
/*
        if(aproxContours.size()>0){
            aproxContours[0].clear();
            aproxContours[0].resize(40);
            for(int i=0 ;i<11;i++){

                if(i>0&&i<10){
                    aproxContours[0][i+30]   =  (QPoint(0,i*(oldimg.cols-1)/10));
                    aproxContours[0][i+10]  =  (QPoint(oldimg.rows-1,(10-i)*(oldimg.cols-1)/10));
                }

                aproxContours[0][i] = (QPoint(i*(oldimg.rows-1)/10,0));
                aproxContours[0][i+20] =  (QPoint((10-i)*(oldimg.rows-1)/10,oldimg.cols-1));
        }

    }
*/
}


void ShTriangulation::saveToStl(QString directory){

    for(int t = 0;t<triangulations.size();t++){
        triangles = triangulations[t].getTriangles();
        summPoints = triangulations[t].getTriangulationPoints();
    if(!triangles.empty()){
        int k = 0, ia, ib, ic;
        std::fstream TRstl;
        std::string path = directory.toStdString();
        TRstl.open(path+"/triangulation"+std::to_string(t)+".stl", std::ios::out | std::ios::app);
        TRstl.close();
        TRstl.open(path+"/triangulation"+std::to_string(t)+".stl", std::ios::out | std::ios::in);
        TRstl << "solid <Triangulation>\n";
        for (k = 0; k <triangles.size(); k++)
        {
            ia = triangles[k][0];
            ib = triangles[k][1];
            ic = triangles[k][2];
            TRstl << "facet normal " << 0.0 << " " << 0.0 << " " << 1.0 << "\n";
            TRstl << "outer loop\n";
            TRstl << "vertex ";
            TRstl << summPoints[ia].x() << " " <<summPoints[ia].y() << " " << 0.0 << "\n";
            TRstl << "vertex ";
            TRstl << summPoints[ib].x() << " " << summPoints[ib].y() << " " << 0.0 << "\n";
            TRstl << "vertex ";
            TRstl << summPoints[ic].x() << " " << summPoints[ic].y() << " " << 0.0 << "\n";
            TRstl << "endloop\n";
            TRstl << "endfacet\n";
        }
        TRstl << "endsolid";
        TRstl.close();
    }
}
}

int  ShTriangulation::trianglesNumber(){
    return triangles.size();
}

void ShTriangulation::borderline(int a, int b, int c,int q,QVector<QPoint> &newpoints,QVector<QVector<int>> &newTriangles,bool AC,bool BC) {
    if(AC||BC){//если  2 стороны граничны приближаем их с помощью третьей
            if(BC){
                int temp=a;
                a=b;
                b=temp;//переобозначением сторон сведём к случаю когда внутренней станет BC а на AC
            }
            QVector<QVector2D> CB(q+1);
            CB[0] = QVector2D(summPoints[c].x(),summPoints[c].y());
            CB[q] = QVector2D(summPoints[b].x(),summPoints[b].y());
            QVector2D vector(summPoints[b].x()-summPoints[c].x(),summPoints[b].y()-summPoints[c].y());
            for (int i = 1; i < q; i++) {
                CB[i].setX(  CB[0].x() + i * vector.x() / q);
                CB[i].setY(  CB[0].y() + i * vector.y() / q);
            }//CB[i] Точки на прямой CB
            QVector2D direction_vector(summPoints[a].x()-summPoints[b].x(),summPoints[a].y()-summPoints[b].y());//напр. вектор стороны BA
            QVector2D CaDv;//доп точка луча
            QVector2D intersectpoint;//точка пересечения
            QVector2D first_point_segment;
            QVector2D sec_point_segment;//точки отрезка

            QVector<QVector2D> CA(q+1);
            CA[0] = QVector2D(summPoints[c].x(),summPoints[c].y());
            CA[q] = QVector2D(summPoints[a].x(),summPoints[a].y());
            //CA[i] Точки сдвинутой ломаной CA

            for(int j=1;j<q;j++){
                CaDv.setX(CB[j].x()+direction_vector.x());
                CaDv.setY(CB[j].y()+direction_vector.y());
                double dist=99999;
               for(int l = 0;l<contourPoints.size();l++){
                for(int k=0;k<contourPoints[l].size();k++){
                    if(k==contourPoints[l].size()-1){
                        first_point_segment.setX(contourPoints[l][k].x());
                        first_point_segment.setY(contourPoints[l][k].y());
                        sec_point_segment.setX(contourPoints[l][0].x());
                        sec_point_segment.setY(contourPoints[l][0].y());
                        }
                    else{
                        first_point_segment.setX(contourPoints[l][k].x());
                        first_point_segment.setY(contourPoints[l][k].y());
                        sec_point_segment.setX(contourPoints[l][k+1].x());
                        sec_point_segment.setY(contourPoints[l][k+1].y());

                    }
                    if(intersect(CB[j],CaDv,first_point_segment,sec_point_segment,intersectpoint)){
                        if(isIntersect(intersectpoint,first_point_segment,sec_point_segment,CB[j],CaDv)){
                            double tempdist=sqrt(pow(intersectpoint.x()-CB[j].x(),2)+pow(intersectpoint.y()-CB[j].y(),2));
                            if(tempdist<dist&&intersectpoint!=CB[j]){
                                dist=tempdist;
                              CA[j]= intersectpoint;
                            }
                        }
                      }
                   }
                 }
                }//смещение точек для граничной стороны CA
        QVector<QVector2D> r(q+1);//Массив векторов от начальной точки на прямой BC до точки пересечения с отрезками (разбиение стороны AB)
         direction_vector=QVector2D(summPoints[a].x()-summPoints[c].x(),summPoints[a].y()-summPoints[c].y());//напр. вектор стороны BA(summPoints[b].x()-summPoints[a].x(),summPoints[b].y()-summPoints[a].y());//напр. вектор стороны BA
        r[q]= QVector2D(CB[q]);
        r[0]=direction_vector;
        double dist=-1;
        QVector2D vec;//переменная точки пересечения
        for(int j=1;j<q;j++){
            CaDv.setX(CB[j].x()+direction_vector.x());//доп точка луча
            CaDv.setY(CB[j].y()+direction_vector.y());
            for(int l = 0;l<contourPoints.size();l++){
               for(int k=0;k<contourPoints[l].size();k++){
                if(k==contourPoints[l].size()-1){
                    first_point_segment.setX(contourPoints[l][k].x());
                    first_point_segment.setY(contourPoints[l][k].y());
                    sec_point_segment.setX(contourPoints[l][0].x());
                    sec_point_segment.setY(contourPoints[l][0].y());
                    }
                    else{
                        first_point_segment.setX(contourPoints[l][k].x());
                        first_point_segment.setY(contourPoints[l][k].y());
                        sec_point_segment.setX(contourPoints[l][k+1].x());
                        sec_point_segment.setY(contourPoints[l][k+1].y());
                    }
                if(intersect(CB[j],CaDv,first_point_segment,sec_point_segment,intersectpoint)){
                    if(isIntersect(intersectpoint,first_point_segment,sec_point_segment,CB[j],CaDv)){
                        if(dist==-1){
                            dist=sqrt(pow(CB[j].x()-intersectpoint.x(),2) +pow(CB[j].y()-intersectpoint.y(),2));
                            vec.setX(intersectpoint.x()-CB[j].x());
                            vec.setY(intersectpoint.y()-CB[j].y());
                        }else{
                            double tempdist=sqrt(pow(CB[j].x()-intersectpoint.x(),2) +pow(CB[j].y()-intersectpoint.y(),2));
                            if(dist>tempdist&&intersectpoint!=CB[j]){
                                dist=tempdist;
                                vec.setX(intersectpoint.x()-CB[j].x());
                                vec.setY(intersectpoint.y()-CB[j].y());
                            }
                        }
                    }
                }
               }
            }
            r[j]=vec;
            dist=-1;
        }//аппроксимация стороы AB прямыми параллельными АС до границы множества
            int k=newpoints.size();
            newpoints.push_back(QPoint(r[q].x(),r[q].y()));
            QVector2D temp;
            for (int i = 1; i < q + 1; i++) {
                    for (int j = 0; j < i; j++) {
                        if(i==q){
                        temp.setX(CA[j].x());
                        temp.setY(CA[j].y());
                        newpoints.push_back(QPoint(temp.x(),temp.y()));

                        }else{
                            temp.setX(CB[q-i].x()+j*r[q-i].x()/i);
                            temp.setY(CB[q-i].y()+j*r[q-i].y()/i);
                            newpoints.push_back(QPoint(temp.x(),temp.y()));
                        }
                    }
                    temp.setX(CB[q-i].x()+r[q-i].x());
                    temp.setY(CB[q-i].y()+r[q-i].y());
                     newpoints.push_back(QPoint(temp.x(),temp.y()));
                }//нумерация и добавление точек

            newTriangles.push_back(QVector<int>({k,k+1,k+2}));
            k++;
                for (int i = 0; i < q - 1; i++) {
                    for (int j = 0; j < 2 + i; j++) {
                        newTriangles.push_back(QVector<int>({k,k+2+i,k+3+i}));
                        if (j > 0) {
                            newTriangles.push_back(QVector<int>({k-1,k,k+2+i}));
                        }
                        k++;
                    }
                }//создание треугольников
        }
        else{//обе не граничны
            QVector<QVector2D> CA(q+1);
            CA[0] = QVector2D(summPoints[c].x(),summPoints[c].y());
            CA[q] = QVector2D(summPoints[a].x(),summPoints[a].y());

            QVector2D vector(summPoints[a].x()-summPoints[c].x(),summPoints[a].y()-summPoints[c].y());
            for (int i = 1; i < q; i++) {
                CA[i].setX(  CA[0].x() + i * vector.x() / q);
                CA[i].setY(  CA[0].y() + i * vector.y() / q);

            }//CA[i] Точки на прямой CA
            QVector2D direction_vector(summPoints[b].x()-summPoints[c].x(),summPoints[b].y()-summPoints[c].y());//напр. вектор стороны CB
            QVector<QVector2D> r(q+1);//Массив векторов от начальной точки на прямой СА до точки пересечения с отрезками
            r[q]= QVector2D(CA[q]);
            r[0]=direction_vector;
            QVector2D CaDv;//доп точка луча
            QVector2D intersectpoint;//точка пересечения
            QVector2D first_point_segment;
            QVector2D sec_point_segment;//точки отрезка
            double dist=-1;
            QVector2D vec;//переменная точки пересечения
            for(int j=1;j<q;j++){
                CaDv.setX(CA[j].x()+direction_vector.x());
                CaDv.setY(CA[j].y()+direction_vector.y());
                for(int l = 0;l<contourPoints.size();l++){
                    for(int k=0;k<contourPoints[l].size();k++){
                        if(k==contourPoints[l].size()-1){
                            first_point_segment.setX(contourPoints[l][k].x());
                            first_point_segment.setY(contourPoints[l][k].y());
                            sec_point_segment.setX(contourPoints[l][0].x());
                            sec_point_segment.setY(contourPoints[l][0].y());
                            }
                        else{
                            first_point_segment.setX(contourPoints[l][k].x());
                            first_point_segment.setY(contourPoints[l][k].y());
                            sec_point_segment.setX(contourPoints[l][k+1].x());
                            sec_point_segment.setY(contourPoints[l][k+1].y());
                        }
                        if(intersect(CA[j],CaDv,first_point_segment,sec_point_segment,intersectpoint)){
                            if(isIntersect(intersectpoint,first_point_segment,sec_point_segment,CA[j],CaDv)){
                                if(dist==-1){
                                    dist=sqrt(pow(CA[j].x()-intersectpoint.x(),2) +pow(CA[j].y()-intersectpoint.y(),2));
                                    vec.setX(intersectpoint.x()-CA[j].x());
                                    vec.setY(intersectpoint.y()-CA[j].y());
                                }else{
                                    double tempdist=sqrt(pow(CA[j].x()-intersectpoint.x(),2) +pow(CA[j].y()-intersectpoint.y(),2));
                                    if(dist>tempdist&&intersectpoint!=CA[j]){
                                        dist=tempdist;
                                        vec.setX(intersectpoint.x()-CA[j].x());
                                        vec.setY(intersectpoint.y()-CA[j].y());
                                }
                            }
                        }
                    }
                   }
                }
                r[j]=vec;
                dist=-1;
                }

            int k=newpoints.size();
            newpoints.push_back(QPoint(r[q].x(),r[q].y()));
            QVector2D temp;
            for (int i = 1; i < q + 1; i++) {
                    for (int j = 0; j < i; j++) {
                        if(i==q){
                        temp.setX(CA[q-i].x()+j*r[q-i].x()/i);
                        temp.setY(CA[q-i].y()+j*r[q-i].y()/i);
                        newpoints.push_back(QPoint(temp.x(),temp.y()));
                        }else{
                            temp.setX(CA[q-i].x()+j*r[q-i].x()/i);
                            temp.setY(CA[q-i].y()+j*r[q-i].y()/i);
                            newpoints.push_back(QPoint(temp.x(),temp.y()));
                        }
                    }
                    temp.setX(CA[q-i].x()+r[q-i].x());
                    temp.setY(CA[q-i].y()+r[q-i].y());
                     newpoints.push_back(QPoint(temp.x(),temp.y()));
                }
            newTriangles.push_back(QVector<int>({k,k+1,k+2}));
            k++;
                for (int i = 0; i < q - 1; i++) {
                    for (int j = 0; j < 2 + i; j++) {
                        newTriangles.push_back(QVector<int>({k,k+2+i,k+3+i}));
                        if (j > 0) {
                            newTriangles.push_back(QVector<int>({k-1,k,k+2+i}));
                        }
                        k++;
                    }
                }
        }
}
void ShTriangulation::notBorderline(int a, int b, int c,int q,QVector<QPoint> &newpoints,QVector<QVector<int>> &newTriangles ) {

    int numbDot = newpoints.size();
    float* ACDX = new float[q - 1]; //точки на прямой АС
    float* ACDY = new float[q - 1];
    float* ABDX = new float[q - 1];  // на прямой AB
    float* ABDY = new float[q - 1];
    float* internal_points_X = new float[(q - 1) * q / 2];
    float* internal_points_Y = new float[(q - 1) * q / 2];

        QVector2D at, bt, ct;
        at= QVector2D(summPoints[a].x(),summPoints[a].y());
        bt= QVector2D(summPoints[b].x(),summPoints[b].y());
        ct= QVector2D(summPoints[c].x(),summPoints[c].y());

        QVector2D vectorAC;
        vectorAC.setX(ct.x() - at.x());
        vectorAC.setY(ct.y() - at.y());//напр вектор АС

        QVector2D vectorAB;
        vectorAB.setX(bt.x() - at.x());
        vectorAB.setY(bt.y() - at.y());//напр вектор BС

        for (int i = 0; i < q - 1; i++) {
            ACDX[i] = ((i + 1) * vectorAC.x() / q) + at.x();
        }

        for (int i = 0; i < q - 1; i++) {
            ACDY[i] = ((i + 1) * vectorAC.y() / q) + at.y();
        }

        for (int i = 0; i < q - 1; i++) {
            ABDX[i] = ((i + 1) * vectorAB.x() / q) + at.x();
        }

        for (int i = 0; i < q - 1; i++) {
            ABDY[i] = ((i + 1) * vectorAB.y() / q) + at.y();
        }//заполняем массивы точками лежащими на прямых ас и бс

        int k = 0;
        QVector2D vectorABDACD;
        for (int i = 1; i < q; i++) {
            if (i != q - 1) {
                vectorABDACD.setX (ACDX[i] - ABDX[i]);
                vectorABDACD.setY (ACDY[i] - ABDY[i]);//вектор прямой между точками на AB и AC
            }
            else {
                vectorABDACD.setX (ct.x()-  bt.x());
                vectorABDACD.setY (ct.y() - bt.y());
            }
            for (int j = 0; j < i; j++) {
                if (i != q - 1) {
                    internal_points_X[k] = ABDX[i] + (j+1)*vectorABDACD.x()/(i+1);
                    internal_points_Y[k] = ABDY[i] + (j + 1)* vectorABDACD.y() / (i + 1);
                }
                else {
                    internal_points_X[k] = bt.x() + (j + 1) * vectorABDACD.x() / (i + 1);
                    internal_points_Y[k] =bt.y() + (j + 1) * vectorABDACD.y() / (i + 1); //точки на прямых между точками на AB и AC
                }
                k++;
            }
        }
        int numbDotTEMP = numbDot;
        newpoints.push_back(QPoint(at.x(),at.y()));
        newpoints.push_back(QPoint(ABDX[0],ABDY[0]));
        newpoints.push_back(QPoint(ACDX[0],ACDY[0]));
        newTriangles.push_back(QVector<int>({numbDot,numbDot+1,numbDot+2}));
        k = 0;
        for (int i = 1; i < q; i++) {
            if (i != q - 1) {
                newpoints.push_back(QPoint(ABDX[i],ABDY[i]));

            }
            else {
                newpoints.push_back(QPoint(bt.x(),bt.y()));

            }

            for (int j = 0; j < i; j++) {
               newpoints.push_back(QPoint(internal_points_X[k],internal_points_Y[k]));
                k++;

            }
            if (i != q - 1) {
                newpoints.push_back(QPoint(ACDX[i],ACDY[i]));

            }
            else {
                newpoints.push_back(QPoint(ct.x(),ct.y()));

            }

        }
        numbDotTEMP++;
        for (int i = 0; i < q - 1; i++) {
            for (int j = 0; j < 2 + i; j++) {
                newTriangles.push_back(QVector<int>({numbDotTEMP,numbDotTEMP + 2 + i,numbDotTEMP + 3 + i}));
                if (j > 0) {
                    newTriangles.push_back(QVector<int>({numbDotTEMP - 1,numbDotTEMP,numbDotTEMP + 2 + i}));
                }
                numbDotTEMP++;
            }
        }
    delete[] ACDX;
    delete[] ABDX;
    delete[] ACDY;
    delete[] ABDY;
    delete[] internal_points_X;
    delete[] internal_points_Y;
}

double ShTriangulation::det(double a, double b, double c, double d)
{
    return a*d-b*c;
}

bool ShTriangulation::intersect(const QVector2D &point1,const QVector2D &point2, const QVector2D &point3,const QVector2D &point4, QVector2D &intersect)
{
    double A1,A2,B1,B2,C1,C2;
    A1=(point2.y()-point1.y());
    A2=(point4.y()-point3.y());
    B1=-(point2.x()-point1.x());
    B2=-(point4.x()-point3.x());
    C1=-1*point1.x()*(point2.y()-point1.y())+point1.y()*(point2.x()-point1.x());
    C2=-1*point3.x()*(point4.y()-point3.y())+point3.y()*(point4.x()-point3.x());
    double zn=det(A1,B1,A2,B2);
    if(abs(zn)<1e-9){
        return false;
    }else{
        intersect.setX(-det(C1,B1,C2,B2)/zn);
        intersect.setY(-det(A1,C1,A2,C2)/zn);
        return true;
    }
}

bool ShTriangulation::isIntersect(const QVector2D &point, const QVector2D &fpointSegment, const QVector2D &spointSegment, const QVector2D &fpointRay, const QVector2D &spointRay)
{
    double xmax;
    double xmin;
    double ymax;
    double ymin;
    if(fpointSegment.x()>spointSegment.x()){
        xmax=fpointSegment.x();
        xmin=spointSegment.x();
    }else{
        xmin=fpointSegment.x();
        xmax=spointSegment.x();
    }
    if(fpointSegment.y()>spointSegment.y()){
        ymax=fpointSegment.y();
        ymin=spointSegment.y();
    }else{
        ymin=fpointSegment.y();
        ymax=spointSegment.y();
    }
    if(point.x()>=xmin&&point.x()<=xmax&&point.y()<=ymax&&point.y()>=ymin){
        QVector2D rayvec(spointRay.x()-fpointRay.x(),spointRay.y()-fpointRay.y());
        QVector2D pointvec(point.x()-fpointRay.x(),point.y()-fpointRay.y());
       if((rayvec.x()* pointvec.x()+ rayvec.y()* pointvec.y())>=0){
           return true;
       }
       else{
           return false;
       }

    }
    else{
        return false;
    }





}

void ShTriangulation::shredding(int q,bool borderflag)
{

    QElapsedTimer timer1;
    timer1.start();

    if(triangles.size()>1){
        steps+=1;
        QVector<QPoint> newPoints;
        QVector<QPoint> rezultPoints;
        QVector<QVector<int>> newtriangles;
        int s1,s2,s3;
for(int i=0;i<triangles.size();i++){

    s1=triangles[i][0];
    s2=triangles[i][1];
    s3=triangles[i][2];
    bool s1s2=true;
    bool s1s3=true;
    bool s2s3=true;
    for(int j=0;j<triangles.size();j++){
        if(j==i){
            continue;
        }else{
            if(s1==triangles[j][0]||s1==triangles[j][1]||s1==triangles[j][2]){
                if(s2==triangles[j][0]||s2==triangles[j][1]||s2==triangles[j][2]){
                   s1s2=false;
                }
                if(s3==triangles[j][0]||s3==triangles[j][1]||s3==triangles[j][2]){
                   s1s3=false;
                }
            }
            if(s2==triangles[j][0]||s2==triangles[j][1]||s2==triangles[j][2]){
                            if(s3==triangles[j][0]||s3==triangles[j][1]||s3==triangles[j][2]){
                               s2s3=false;
                            }
                        }
        }
    }




 if(s1s2&borderflag){
     if(steps%2==0){
         borderline(s2,s1,s3,q,newPoints,newtriangles,s2s3,s1s3);
     }else{
     borderline(s1,s2,s3,q,newPoints,newtriangles,s1s3,s2s3);
     }
 }else if(s1s3&borderflag){
     if(steps%2==0){
         borderline(s3,s1,s2,q,newPoints,newtriangles,s2s3,s1s2);
     }else{
    borderline(s1,s3,s2,q,newPoints,newtriangles,s1s2,s2s3);
     }
}else if(s2s3&borderflag){
     if(steps%2==0){
         borderline(s3,s2,s1,q,newPoints,newtriangles,false,false);
     }
     else{
    borderline(s2,s3,s1,q,newPoints,newtriangles,false,false);
     }
}else{
     notBorderline(s1,s2,s3,q,newPoints,newtriangles);
 }
}
qDebug() << "Измельчение" << timer1.elapsed() << "milliseconds";

QElapsedTimer timer;
timer.start();


QSet<QPoint>* set = new QSet(newPoints.begin(),newPoints.end());


triangles.clear();

triangles = newtriangles;

for(auto i:*set){
    rezultPoints.push_back(i);
    for(int j = 0;j<newtriangles.size();j++){
        if(newPoints[newtriangles[j][0]]==i){

            triangles[j][0]=rezultPoints.size()-1;

        }
        if(newPoints[newtriangles[j][1]]==i){

            triangles[j][1]=rezultPoints.size()-1;

        }
        if(newPoints[newtriangles[j][2]]==i){

           triangles[j][2]=rezultPoints.size()-1;

        }
    }
}

summPoints=newPoints;

delete set;
     }
}



void ShTriangulation::oneAreaTriang(){

            QVector<QPair<int,int>> edges;
            QVector<QPoint> points;
            QVector<QVector<int>> triangle;

            edges.clear();
            points.clear();
            triangle.clear();
            contours.clear();
            aproxContours.clear();


            points.push_back(QPoint(0,0));
            points.push_back(QPoint(0,oldimg.rows-1));
            points.push_back(QPoint(oldimg.cols-1,oldimg.rows-1));
            points.push_back(QPoint(oldimg.cols-1,0));


            contours.push_back(points);
            aproxContours.push_back(points);

            for(int i =0;i<points.size();i++){

            if(i!=points.size()-1){
                edges.push_back(QPair<int,int>(i,i+1));
            }else{
                edges.push_back(QPair<int,int>(i,0));
            }

            }

            CDT::Triangulation<double> cdt;
            cdt.insertVertices(points.begin(),points.end(),[](QPoint& p){return (int)p.x();},[](QPoint& p){return (int)p.y();});
            cdt.insertEdges(edges.begin(),edges.end(),[](QPair<int,int>& p){return (int)p.first;},[](QPair<int,int>& p){return (int)p.second;});
            cdt.eraseOuterTrianglesAndHoles();
            auto trianglesdelone = cdt.triangles;
            for(auto i:trianglesdelone){
                triangle.push_back(QVector<int>({(int)i.vertices[0],(int)i.vertices[1],(int)i.vertices[2]}));
            }
            triangulations.push_back(Triangulation(triangle,points));
}


void ShTriangulation::triangulation(){
    QVector<QPair<int,int>> edges;

        QVector<QPoint> points;
        QVector<QVector<int>> triangle;

        for( int i = 0; i < ierarhy.size(); i++){
            edges.clear();
            points.clear();
            triangle.clear();

            int countpoint = 0;

            for (int j = 0 ;j< aproxContours[i].size();j++){
                points.push_back(QPoint(aproxContours[i][j].x(),aproxContours[i][j].y()));
                countpoint++;
                if(j!=aproxContours[i].size()-1){
                    edges.push_back(QPair<int,int>(j,j+1));
                }else{
                    edges.push_back(QPair<int,int>(j,0));
                }
            }

            int ierarhy_index = ierarhy[i][2];
            while(ierarhy_index!=-1){
                int countstart = countpoint;
                for (int j = 0 ;j< aproxContours[ierarhy_index].size();j++){
                    points.push_back(QPoint(aproxContours[ierarhy_index][j].x(),aproxContours[ierarhy_index][j].y()));
                    countpoint++;
                    if(j!=aproxContours[ierarhy_index].size()-1){
                        edges.push_back(QPair<int,int>(countpoint-1,countpoint));
                    }else{
                        edges.push_back(QPair<int,int>(countpoint-1,countstart));
                    }
                }
                ierarhy_index = ierarhy[ierarhy_index][2];

            }
            CDT::Triangulation<double> cdt;
            cdt.insertVertices(points.begin(),points.end(),[](QPoint& p){return (int)p.x();},[](QPoint& p){return (int)p.y();});
            cdt.insertEdges(edges.begin(),edges.end(),[](QPair<int,int>& p){return (int)p.first;},[](QPair<int,int>& p){return (int)p.second;});
            cdt.eraseOuterTrianglesAndHoles();
            auto trianglesdelone = cdt.triangles;
            for(auto i:trianglesdelone){
                int x = (points[(int)i.vertices[0]].x() + points[(int)i.vertices[1]].x() + points[(int)i.vertices[2]].x())/3;
                int y = (points[(int)i.vertices[0]].y() + points[(int)i.vertices[1]].y() + points[(int)i.vertices[2]].y())/3;
                if(!points.contains(QPoint(x,y))){
                    points.push_back(QPoint(x,y));
                }
            }

            CDT::Triangulation<double> cdt2;

            cdt2.insertVertices(points.begin(),points.end(),[](QPoint& p){return (int)p.x();},[](QPoint& p){return (int)p.y();});
            cdt2.insertEdges(edges.begin(),edges.end(),[](QPair<int,int>& p){return (int)p.first;},[](QPair<int,int>& p){return (int)p.second;});
            cdt2.eraseOuterTrianglesAndHoles();


            trianglesdelone = cdt2.triangles;
            for(auto i:trianglesdelone){
                triangle.push_back(QVector<int>({(int)i.vertices[0],(int)i.vertices[1],(int)i.vertices[2]}));
            }
            triangulations.push_back(Triangulation(triangle,points));
        }
}

void ShTriangulation::shreddingAllImage(){

    for(int i = 0;i<triangulations.size();i++){

            contourPoints.clear();
            summPoints.clear();
            triangles.clear();

            summPoints = triangulations[i].getTriangulationPoints();
            triangles = triangulations[i].getTriangles();

            contourPoints.push_back(contours[i]);

            int inner_index = ierarhy[i][2];

            while(inner_index != -1&&contourPoints.size()>1){
                contourPoints.push_back(contours[inner_index]);
                inner_index = ierarhy[inner_index][2];
            }

            shredding(2,shreddingState);

            triangulations[i].UpdatePoints(summPoints);
            triangulations[i].ChangeTriangulation(triangles);

        }
    shreddingState = false;
}


void ShTriangulation::saveNewImage(QString name){

    using namespace cv;
    Mat* newimg = new Mat(oldimg.rows,oldimg.cols,CV_8UC3);
    int pointscount = 0;
    std::vector<cv::Vec3b> pointsColors;
    QVector<QPoint> points;
    QVector<QVector<int>> triangles;
    for (int i =0;i<triangulations.size();i++)  {
        points = triangulations[i].getTriangulationPoints();
        pointscount+=points.size();
        triangles = triangulations[i].getTriangles();

        for(int i = 0;i<triangles.size();i++){

            int x1 = points[triangles[i][0]].x();

            int y1 = points[triangles[i][0]].y();

            int x2 = points[triangles[i][1]].x();

            int y2 = points[triangles[i][1]].y();

            int x3 = points[triangles[i][2]].x();

            int y3 = points[triangles[i][2]].y();


            Point a(x1, y1);
            Point b(x2, y2);
            Point c(x3, y3);

            std::vector<cv::Point> pts = {cv::Point(x1,y1),cv::Point(x2,y2),cv::Point(x3,y3)};

            Scalar first = Scalar(oldimg.ptr<Vec3b>(y1)[x1]);
            Scalar sec = Scalar(oldimg.ptr<Vec3b>(y2)[x2]);
            Scalar third = Scalar(oldimg.ptr<Vec3b>(y3)[x3]);

            Mat triArr = (Mat_<double>(3, 3) << a.x, b.x, c.x, a.y, b.y, c.y, 1, 1, 1);

            int xleft = min(min(a.x, b.x), c.x);
            int xright = max(max(a.x, b.x), c.x);
            int ytop = min(min(a.y, b.y), c.y);
            int ybottom = max(max(a.y, b.y), c.y);

            newimg->at<Vec3b>(a.y, a.x) = Vec3b(first[0], first[1], first[2]);
            newimg->at<Vec3b>(b.y, b.x) = Vec3b(sec[0], sec[1], sec[2]);
            newimg->at<Vec3b>(c.y, c.x) = Vec3b(third[0], third[1], third[2]);

            drawLine(newimg, a, b, first, sec);
            drawLine(newimg, b, c, sec, third);
            drawLine(newimg, c, a, third, first);

            for (int y = ytop; y <= ybottom; y++) {
                for (int x = xleft; x <= xright; x++) {
                    Mat p = (Mat_<double>(3, 1) << x, y, 1);

                    Mat barycentric = triArr.inv() * p;

                    double alpha = barycentric.at<double>(0, 0);
                    double beta = barycentric.at<double>(1, 0);
                    double gamma = barycentric.at<double>(2, 0);

                    if (alpha > 0 && beta > 0 && gamma > 0) {
                        Scalar color = first * alpha + sec * beta + third * gamma;
                        newimg->at<Vec3b>(y, x) = Vec3b(color[0], color[1], color[2]);
                    }
                }
            }

        }
    }

    qDebug()<<"КОЛ ТОЧЕК"<<pointscount;
    imwrite("C:\\TEST\\NEWTEST.png", *newimg);
}


void ShTriangulation::saveNewSvgImage(QString name){

        QSvgGenerator generator;
        generator.setFileName("C:\\TEST\\NEWTESTSVG.svg");


        int xsize = oldimg.cols;
        int ysize = oldimg.rows;

        generator.setSize(QSize(xsize, ysize));
        generator.setViewBox(QRectF(0, 0, xsize, ysize));
        QImage image(xsize, ysize, QImage::Format_RGB32);
        image.fill(Qt::white);

        std::vector<cv::Vec3b> pointsColors;
        QVector<QPoint> points;
        QVector<QVector<int>> triangles;


        for (int i =0;i<triangulations.size();i++)  {

            points = triangulations[i].getTriangulationPoints();
            triangles = triangulations[i].getTriangles();

            for(int i = 0;i<triangles.size();i++){


                int x1 = points[triangles[i][0]].x();

                int y1 = points[triangles[i][0]].y();

                int x2 = points[triangles[i][1]].x();

                int y2 = points[triangles[i][1]].y();

                int x3 = points[triangles[i][2]].x();

                int y3 = points[triangles[i][2]].y();


                // Specify (x,y) triangle vertices
                QPoint a(x1, y1);
                QPoint b(x2, y2);
                QPoint c(x3, y3);



                // Specify colors
                cv::Scalar first = cv::Scalar(oldimg.ptr<cv::Vec3b>(y1)[x1]);
                cv::Scalar sec = cv::Scalar(oldimg.ptr<cv::Vec3b>(y2)[x2]);
                cv::Scalar third = cv::Scalar(oldimg.ptr<cv::Vec3b>(y3)[x3]);



                QColor c1(first[0], first[1], first[2]);
                QColor c2(sec[0], sec[1], sec[2]);
                QColor c3(third[0], third[1], third[2]);



                QPainter imagePainter(&image);




                 int xleft = cv::min(cv::min(a.x(), b.x()), c.x());
                 int xright = cv::max(cv::max(a.x(), b.x()), c.x());
                 int ytop = cv::min(cv::min(a.y(), b.y()), c.y());
                 int ybottom = cv::max(cv::max(a.y(), b.y()), c.y());

                  cv::Mat triArr = (cv::Mat_<double>(3, 3) << a.x(), b.x(), c.x(), a.y(), b.y(), c.y(), 1, 1, 1);




                   for (int y = ytop; y <= ybottom; y++) {
                       for (int x = xleft; x <= xright; x++) {
                          cv::Mat p = (cv::Mat_<double>(3, 1) << x, y, 1);

                          cv::Mat barycentric = triArr.inv() * p;

                          double alpha = barycentric.at<double>(0, 0);
                          double beta = barycentric.at<double>(1, 0);
                          double gamma = barycentric.at<double>(2, 0);

                           if (alpha > 0 && beta > 0 && gamma > 0) {
                                cv::Scalar color = first * alpha + sec * beta + third * gamma;
                                image.setPixelColor(x, y, QColor(color[0], color[1], color[2]));

                            }
                        }
                    }
                  }
        }

            QPainter svgPainter(&generator);
            svgPainter.drawImage(0, 0, image);
            svgPainter.end();
            image.save("C:\\TEST\\PPPPNG.svge.png");

}



int ShTriangulation::findCannyEges(QString filename){

    oldimg =cv::imread(filename.toStdString());
    cv::Mat filter;
    cv::GaussianBlur(oldimg,filter,cv::Size(5,5),0);
    cv::Mat eges_cany;
    cv::Canny(filter,eges_cany,0,255);

    QVector<QPair<int,int>> edges;
    QVector<QPoint> points;
    QVector<QVector<int>> triangle;

    points.push_back(QPoint(0,0));
    points.push_back(QPoint(0,oldimg.rows-1));
    points.push_back(QPoint(oldimg.cols-1,oldimg.rows-1));
    points.push_back(QPoint(oldimg.cols-1,0));

    contours.push_back(points);
    aproxContours.push_back(points);

    for(int i =0;i<points.size();i++){
        if(i!=points.size()-1){
            edges.push_back(QPair<int,int>(i,i+1));
        }else{
            edges.push_back(QPair<int,int>(i,0));
        }
    }


    std::vector<std::vector<cv::Point>> canycontours;
    cv::findContours(eges_cany, canycontours,ierarhy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    for(int i=0;i<canycontours.size();i++){
        contours.push_back(QVector<QPoint>());
        for(int j=0;j<canycontours[i].size();j++){
            contours[i+1].push_back(QPoint(canycontours[i][j].x,canycontours[i][j].y));
        }
    }

    for (const auto& contour : canycontours) {
            std::vector<cv::Point> approx;
            cv::approxPolyDP(contour, approx, 0.1, true);
            if(approx.size()!=0){
                aproxContours.push_back(QVector<QPoint>());
                for (int i = 0; i < approx.size() ; ++i) {
                    aproxContours[aproxContours.size()-1].push_back(QPoint(approx[i].x,approx[i].y));
                }
            }
        }

    for (int i=0;i<aproxContours.size();i++){
            int t = points.size();
            if(points.indexOf(aproxContours[i][0])==-1){
                points.push_back(aproxContours[i][0]);
            }else{
                t = points.indexOf(aproxContours[i][0]);
            }


            for(int j=1;j<aproxContours[i].size();j++){
                if(j==1){
                    int r = points.indexOf(aproxContours[i][j]);
                    if(r==-1){
                        points.push_back(aproxContours[i][j]);
                        edges.push_back(QPair<int,int>(t,points.size()-1));
                    }else{
                        edges.push_back(QPair<int,int>(t,r));
                    }
                }else{
                    int r = points.indexOf(aproxContours[i][j]);
                    if(r==-1){
                        points.push_back(aproxContours[i][j]);
                        edges.push_back(QPair<int,int>(points.size()-2,points.size()-1));
                    }else{
                        edges.push_back(QPair<int,int>(points.size()-1,r));
                    }
                }
            }
    }

        CDT::Triangulation<double> cdt;
        cdt.insertVertices(points.begin(),points.end(),[](QPoint& p){return (int)p.x();},[](QPoint& p){return (int)p.y();});
        cdt.insertEdges(edges.begin(),edges.end(),[](QPair<int,int>& p){return (int)p.first;},[](QPair<int,int>& p){return (int)p.second;});
        auto trianglesdelone = cdt.triangles;
        for(auto i:trianglesdelone){
            int x = (points[(int)i.vertices[0]].x() + points[(int)i.vertices[1]].x() + points[(int)i.vertices[2]].x())/3;
            int y = (points[(int)i.vertices[0]].y() + points[(int)i.vertices[1]].y() + points[(int)i.vertices[2]].y())/3;
            if(!points.contains(QPoint(x,y))){
                points.push_back(QPoint(x,y));
            }
        }
        trianglesdelone = cdt.triangles;
        for(auto i:trianglesdelone){
            triangle.push_back(QVector<int>({(int)i.vertices[0],(int)i.vertices[1],(int)i.vertices[2]}));
        }
        triangulations.push_back(Triangulation(triangle,points));
        return 0;
}

void ShTriangulation::shreedCanny(int q,bool borderflag){

    QVector<QPoint> points;
    QVector<QVector<int>> triangles;

    points = triangulations[0].getTriangulationPoints();
    triangles = triangulations[0].getTriangles();

    QVector<QPoint> newPoints;
    QVector<QPoint> rezultPoints;
    QVector<QVector<int>> newtriangles;

    int s1,s2,s3;

    for(int i=0;i<triangles.size();i++){

        s1=triangles[i][0];
        s2=triangles[i][1];
        s3=triangles[i][2];
        bool s1s2=true;
        bool s1s3=true;
        bool s2s3=true;
        for(int j=0;j<triangles.size();j++){
            if(j==i){
                continue;
            }else{
                if(s1==triangles[j][0]||s1==triangles[j][1]||s1==triangles[j][2]){
                    if(s2==triangles[j][0]||s2==triangles[j][1]||s2==triangles[j][2]){
                       s1s2=false;
                    }
                    if(s3==triangles[j][0]||s3==triangles[j][1]||s3==triangles[j][2]){
                       s1s3=false;
                    }
                }
                if(s2==triangles[j][0]||s2==triangles[j][1]||s2==triangles[j][2]){
                                if(s3==triangles[j][0]||s3==triangles[j][1]||s3==triangles[j][2]){
                                   s2s3=false;
                                }
                            }
            }
        }
     if(s1s2&borderflag){
         if(steps%2==0){
             borderline(s2,s1,s3,q,newPoints,newtriangles,s2s3,s1s3);
         }else{
         borderline(s1,s2,s3,q,newPoints,newtriangles,s1s3,s2s3);
         }
     }else if(s1s3&borderflag){
         if(steps%2==0){
             borderline(s3,s1,s2,q,newPoints,newtriangles,s2s3,s1s2);
         }else{
        borderline(s1,s3,s2,q,newPoints,newtriangles,s1s2,s2s3);
         }
    }else if(s2s3&borderflag){
         if(steps%2==0){
             borderline(s3,s2,s1,q,newPoints,newtriangles,false,false);
         }
         else{
        borderline(s2,s3,s1,q,newPoints,newtriangles,false,false);
         }
    }else{
         notBorderline(s1,s2,s3,q,newPoints,newtriangles);
     }
    }

}

int ShTriangulation::testTriangCanny(QString fileName){
    oldimg =cv::imread(fileName.toStdString());
    cv::Mat filter;
    cv::GaussianBlur(oldimg,filter,cv::Size(5,5),0);
    cv::Mat eges_cany;
    cv::Canny(filter,eges_cany,20,128);

    QVector<QPoint> points;
    QVector<QVector<int>> triangle;

    points.push_back(QPoint(0,0));
    points.push_back(QPoint(0,oldimg.rows-1));
    points.push_back(QPoint(oldimg.cols-1,oldimg.rows-1));
    points.push_back(QPoint(oldimg.cols-1,0));



    for(int j = 1;j<43;j++){
        points.push_back(QPoint((oldimg.cols-1)*j/43,0));
        points.push_back(QPoint((oldimg.cols-1)*j/43,oldimg.rows-1));
    }

    for(int j = 1;j<70;j++){
        points.push_back(QPoint(0,(oldimg.rows-1)*j/70));
        points.push_back(QPoint(oldimg.cols-1,(oldimg.rows-1)*j/70));
    }



    contours.push_back(points);
    aproxContours.push_back(points);


    std::vector<std::vector<cv::Point>> canycontours;
    cv::findContours(eges_cany, canycontours,ierarhy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);



    for (const auto& contour : canycontours) {

            if(contour.size()!=0){
                aproxContours.push_back(QVector<QPoint>());
                for (int i = 0; i < contour.size() ; ++i) {
                    aproxContours[aproxContours.size()-1].push_back(QPoint(contour[i].x,contour[i].y));
                }
            }
        }
    for (auto i: aproxContours){
        for(auto j:i){
            if(!points.contains(j)){
                points.push_back(j);
            }
        }

    }

    for(int j = 1;j<70;j++){
        for (int k =1 ;k<43;k++){
            auto poi = QPoint((oldimg.cols-1)*k/43,(oldimg.rows-1)*j/70);
            if(!points.contains(poi)){
                points.push_back(poi);
            }
        }
    }

        CDT::Triangulation<double> cdt;
        cdt.insertVertices(points.begin(),points.end(),[](QPoint& p){return (int)p.x();},[](QPoint& p){return (int)p.y();});
        cdt.eraseSuperTriangle();
        auto trianglesdelone = cdt.triangles;
        auto pointsdelone = cdt.vertices;
        for(auto i:trianglesdelone){
            triangle.push_back(QVector<int>({(int)i.vertices[0],(int)i.vertices[1],(int)i.vertices[2]}));
        }
        points.clear();
        for(auto i:pointsdelone){
            points.push_back(QPoint(i.x,i.y));
        }
        triangulations.push_back(Triangulation(triangle,points));
        shreddingState = false;
        return 0;
}

void drawLine(cv::Mat* image, cv::Point start, cv::Point end, cv::Scalar startColor, cv::Scalar endColor) {
    int length = std::max(abs(end.x - start.x), abs(end.y - start.y)) + 1;
    std::vector<cv::Point> points;
    cv::LineIterator it(*image, start, end);
    for (int i = 0; i < length; i++, ++it) {
        float alpha = (float)i / (length - 1);
        cv::Scalar color = startColor * (1.0 - alpha) + endColor * alpha;
        image->at<cv::Vec3b>(it.pos()) = cv::Vec3b(color[0], color[1], color[2]);
    }
}

void ShTriangulation::SH(){
    QVector<QPoint> points;
    QVector<QVector<int>> triangle;
    CDT::Triangulation<double> cdt;

    triangulations.clear();

    cdt.insertVertices(points.begin(),points.end(),[](QPoint& p){return (int)p.x();},[](QPoint& p){return (int)p.y();});
    cdt.eraseSuperTriangle();
    auto trianglesdelone = cdt.triangles;
    auto pointsdelone = cdt.vertices;
    for(auto i:trianglesdelone){
        triangle.push_back(QVector<int>({(int)i.vertices[0],(int)i.vertices[1],(int)i.vertices[2]}));
    }
    points.clear();
    for(auto i:pointsdelone){
        points.push_back(QPoint(i.x,i.y));
    }
    triangulations.push_back(Triangulation(triangle,points));
}

