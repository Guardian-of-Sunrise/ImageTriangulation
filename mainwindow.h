#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "QVBoxLayout"
#include "shtriangulation.h"
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




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void mouseMoveEvent(QMouseEvent *event);
    virtual ~MainWindow();
private slots:

    void on_find_countour_triggered();
    void on_action_zoom_in_triggered();
    void on_action_zoom_out_triggered();
    void on_shift_up_y_triggered();
    void on_actionshift_down_y_triggered();
    void on_shift_left_triggered();
    void on_shift_right_triggered();
    void checkBoxCanged();
    void horizontalSliderCanged();
    void on_Triangulation_clicked();
    void on_Shredding_clicked();
    void on_Save_triggered();
    void on_action_triggered();
    void on_NumbContour_valueChanged(int arg1);
    void on_checkBox_2_stateChanged(int arg1);
    void on_action_2_triggered();
    void on_actionOneAreaTriang_triggered();
    void on_horizontalSlider_valueChanged(int value);
    void on_actionSvg_save_triggered();
    void on_actionCany_triggered();
    void on_actionTesttriangCanny_triggered();

private:
     Ui::MainWindow *ui;
     QString namefile;
     ShTriangulation* triangulator;
};
#endif // MAINWINDOW_H



















































