#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "shvizualization.h"
#include "QPalette"
#include "QApplication"
#include <QScreen>
#include <QPainter>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    triangulator = new  ShTriangulation();
    QScreen *Screen = QGuiApplication::screens().at(0);
    QSize rect=Screen->availableSize();
    ui->setupUi(this);
    this->setGeometry(0,0,rect.width(),rect.height());
    this->setMouseTracking(true);
    ui->centralwidget->setMouseTracking(true);
    ui->checkBox->setChecked(true);
    ui->checkBox_2->setChecked(true);
    ui->horizontalSlider->setMaximum(100);
    ui->horizontalSlider->setMinimum(1);
    ui->spinBox->setMaximum(10);
    ui->spinBox->setMinimum(2);
    connect(ui->checkBox,SIGNAL(stateChanged(int)),this,SLOT(checkBoxCanged()));
    connect(ui->horizontalSlider,SIGNAL(sliderMoved(int)),this,SLOT(horizontalSliderCanged()));
    ui->widget->setVizualizationObject(triangulator);
}

MainWindow::~MainWindow()
{
    delete triangulator;
    delete ui;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    QRect rect=ui->widget->geometry();
    if(event->pos().x()>=rect.x()&&event->pos().x()<=rect.x()+rect.width()){
        if(event->pos().y()>=rect.y()&&event->pos().y()<=rect.y()+rect.height()){
        }
    }
}

void MainWindow::on_find_countour_triggered()
{

     ui->NumbContour->setValue(0);
     namefile=QFileDialog::getOpenFileName(this, tr("Open File"),
                                                   "/home",
                                                   tr("Images (*.png *.jpg)"));
    if(namefile.size()!=0){
        triangulator->findContour(namefile,ui->horizontalSlider->value());

    }
    ui->widget->repaint();
}


void MainWindow::on_action_zoom_in_triggered()
{
    ui->widget->scaleUp();
}


void MainWindow::on_action_zoom_out_triggered()
{
    ui->widget->scaleDawn();
}


void MainWindow::on_shift_up_y_triggered()
{
    ui->widget->shiftDawn();
}


void MainWindow::on_actionshift_down_y_triggered()
{
    ui->widget->shiftUp();
}


void MainWindow::on_shift_left_triggered()
{
    ui->widget->shiftLeft();
}


void MainWindow::on_shift_right_triggered()
{
    ui->widget->shiftRight();
}

void MainWindow::checkBoxCanged(){
    ui->widget->contourDisplay(ui->checkBox->isChecked(),ui->checkBox_2->isChecked());
}

void MainWindow::horizontalSliderCanged(){
    auto eps = ui->horizontalSlider->value();
    triangulator->aproxAllContours(eps);
    ui->widget->repaint();
}

void MainWindow::on_Triangulation_clicked()
{
    switch (ui->comboBox->currentIndex()) {
    case 0:
         triangulator->triangulation();
        break;
    case 1:
        triangulator->triangulation();
        break;
    }
    ui->numtriang->setText("Количество триугольников: "+QString::number(triangulator->trianglesNumber()));
    ui->widget->repaint();
}


void MainWindow::on_Shredding_clicked()
{
    triangulator->shreddingAllImage();
    ui->numtriang->setText("Количество триугольников: "+QString::number(triangulator->trianglesNumber()));
    ui->widget->repaint();
}


void MainWindow::on_Save_triggered()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    if(dir.size()!=0){
    triangulator->saveToStl(dir);
    }
}


void MainWindow::on_action_triggered()
{
    triangulator->triangulation();
    ui->numtriang->setText("Количество триугольников: "+QString::number(triangulator->trianglesNumber()));
    ui->widget->repaint();
}


void MainWindow::on_NumbContour_valueChanged(int arg1)
{
  triangulator->findContour(namefile,ui->NumbContour->value()-1);
  ui->widget->repaint();
}


void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    ui->widget->contourDisplay(ui->checkBox->isChecked(),ui->checkBox_2->isChecked());
}




void MainWindow::on_action_2_triggered()
{
   triangulator->saveNewImage("NEWIMAGE");
}


void MainWindow::on_actionOneAreaTriang_triggered()
{
    triangulator->oneAreaTriang();
    ui->widget->repaint();
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    double t = (double)value/10.0;

    triangulator->aproxAllContours(t);
    ui->widget->repaint();
}


void MainWindow::on_actionSvg_save_triggered()
{
    triangulator->saveNewSvgImage("sdfsdf");
}


void MainWindow::on_actionCany_triggered()
{

    ui->NumbContour->setValue(0);
    namefile=QFileDialog::getOpenFileName(this, tr("Open File"),
                                                  "/home",
                                                  tr("Images (*.png *.jpg)"));
   if(namefile.size()!=0){
       triangulator->findCannyEges(namefile);
   }

   ui->widget->repaint();
}


void MainWindow::on_actionTesttriangCanny_triggered()
{

    ui->NumbContour->setValue(0);
    namefile=QFileDialog::getOpenFileName(this, tr("Open File"),
                                                  "/home",
                                                  tr("Images (*.png *.jpg)"));

    if(namefile.size()!=0){
        triangulator->testTriangCanny(namefile);
    }
    ui->widget->repaint();
}


