#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <QImage>
//#include "opencv2/opencv.hpp"
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  using namespace cv;
  //ui->label->clear();
  Mat src;
  Mat temp=imread("E:\\goertzel\\test.png",1);
 cvtColor(temp, src,COLOR_BGR2RGB);
  QImage Qtemp=QImage((unsigned char*)(src.data),src.cols,src.rows,QImage::Format_RGB888);
  ui->label->setPixmap(QPixmap::fromImage(Qtemp));
  ui->label->resize(Qtemp.size());
  ui->label->show();
}

MainWindow::~MainWindow()
{
  delete ui;
}


void MainWindow::on_pushButton_13_clicked()
{

}

