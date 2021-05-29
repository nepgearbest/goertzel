#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <QImage>
#include <QString>
#include <iostream>
#include <QMessageBox>
#include "sin_generator.h"
#include "wav_read.h"
#include "wave_creat.cpp"
#include <QMediaPlayer>
#include <QSoundEffect>
#include <QApplication>
#include <QFile>
#include <QAudioFormat>
#include <QAudioOutput>
#include <QtMultimedia/QSound>
//#include "opencv2/opencv.hpp"
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  using namespace cv;

  //ui->label->clear();
  //背景图片显示
  Mat src,dst;
  Mat temp=imread("./test.png",cv::IMREAD_COLOR);

  cvtColor(temp, src,COLOR_BGR2RGB);

  //Rect sel=Rect(0,0,680,480);
  //cv::resize(src,dst,cv::Size(),2,2);
  //dst = src(sel);
  std::cout<<src.channels()<<std::endl;
  std::cout<<std::flush;

  //imshow("test",dst);
  //QImage Qtemp1=QImage::
  QImage Qtemp=QImage((unsigned char*)(src.data),src.cols,src.rows,src.cols*src.channels(),QImage::Format_RGB888);
  ui->label->setPixmap(QPixmap::fromImage(Qtemp));
  ui->label->resize(Qtemp.size());
  ui->label->show();
  //背景图片显示
  //设置label格式
  QFont format_nums;
  format_nums.setBold(1);
  ui->label_2->setFont(format_nums);
  //设置label格式
}

MainWindow::~MainWindow()
{
  delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    //1号按钮启动
  QString a;
  a=ui->label_2->text();
  a.append("1");
  ui->label_2->setText(a);
}

void MainWindow::on_pushButton_2_clicked()
{
  QString a;
  a=ui->label_2->text();
  a.append("2");
  ui->label_2->setText(a);
}

void MainWindow::on_pushButton_3_clicked()
{
  QString a;
  a=ui->label_2->text();
  a.append("3");
  ui->label_2->setText(a);
}

void MainWindow::on_pushButton_4_clicked()
{
  QString a;
  a=ui->label_2->text();
  a.append("4");
  ui->label_2->setText(a);
}

void MainWindow::on_pushButton_5_clicked()
{
  QString a;
  a=ui->label_2->text();
  a.append("5");
  ui->label_2->setText(a);
}

void MainWindow::on_pushButton_6_clicked()
{
  QString a;
  a=ui->label_2->text();
  a.append("6");
  ui->label_2->setText(a);
}

void MainWindow::on_pushButton_7_clicked()
{
  QString a;
  a=ui->label_2->text();
  a.append("7");
  ui->label_2->setText(a);
}

void MainWindow::on_pushButton_8_clicked()
{
  QString a;
  a=ui->label_2->text();
  a.append("8");
  ui->label_2->setText(a);
}

void MainWindow::on_pushButton_9_clicked()
{
  QString a;
  a=ui->label_2->text();
  a.append("9");
  ui->label_2->setText(a);
}

void MainWindow::on_pushButton_10_clicked()
{
  QString a;
  a=ui->label_2->text();
  a.append("*");
  ui->label_2->setText(a);
}

void MainWindow::on_pushButton_11_clicked()
{
  QString a;
  a=ui->label_2->text();
  a.append("0");
  ui->label_2->setText(a);
}

void MainWindow::on_pushButton_12_clicked()
{
  QString a;
  a=ui->label_2->text();
  a.append("#");
  ui->label_2->setText(a);
}

void MainWindow::on_pushButton_13_clicked()
{
    QString input_text;
    int f1[4]={697,770,852,941};
    int f2[3]={1209,1336,1477};
    input_text=ui->label_2->text();
    ui->label_2->clear();
    if(input_text.length()>6)
      {
        //长度出错信息
        QMessageBox::information(NULL, "出错啦", "太长了",
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return ;
      }
    if(input_text.length()<6)
      {
        //长度出错信息
        QMessageBox::information(NULL, "出错啦", "太短了",
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return ;
      }
  std::string cc=input_text.toStdString();
  int sin_wave_freq[6][2];
      for(int i=0;i<6;i++)
        {
          char a=cc[i];
          //printf("%c",a);
          //fflush(stdout);
          if(a=='1')
            {
              sin_wave_freq[i][0]=f1[0];
              sin_wave_freq[i][1]=f2[0];
            }
          if(a=='2')
            {
              sin_wave_freq[i][0]=f1[0];
              sin_wave_freq[i][1]=f2[1];
            }
          if(a=='3')
            {
              sin_wave_freq[i][0]=f1[0];
              sin_wave_freq[i][1]=f2[2];
            }
          if(a=='4')
            {
              sin_wave_freq[i][0]=f1[1];
              sin_wave_freq[i][1]=f2[0];
            }
          if(a=='5')
            {
              sin_wave_freq[i][0]=f1[1];
              sin_wave_freq[i][1]=f2[1];
            }
          if(a=='6')
            {
              sin_wave_freq[i][0]=f1[1];
              sin_wave_freq[i][1]=f2[2];
            }
          if(a=='7')
            {
              sin_wave_freq[i][0]=f1[2];
              sin_wave_freq[i][1]=f2[0];
            }
          if(a=='8')
            {
              sin_wave_freq[i][0]=f1[2];
              sin_wave_freq[i][1]=f2[1];
            }
          if(a=='9')
            {
              sin_wave_freq[i][0]=f1[2];
              sin_wave_freq[i][1]=f2[2];
            }
          if(a=='0')
            {
              sin_wave_freq[i][0]=f1[3];
              sin_wave_freq[i][1]=f2[1];
            }
          if(a=='*')
            {
              sin_wave_freq[i][0]=f1[3];
              sin_wave_freq[i][1]=f2[0];
            }
          if(a=='#')
            {
              sin_wave_freq[i][0]=f1[3];
              sin_wave_freq[i][1]=f2[2];
            }
        }
      Create(sin_wave_freq,10,6);
      ui->label->clear();
      code.clear();
      code=input_text;
}

void MainWindow::on_pushButton_14_clicked()
{
  using namespace std;
  wav_read aaa;
  std::vector<char>res;
  res=aaa.wav_reading();

  string res_temp;
  for(int i=0;i<res.size();i++)
    {
      res_temp+=res[i];
    }
  //cout<<res_temp<<endl;
  //cout<<flush;
  QString a=QString::fromStdString(res_temp);
  //a=QString(QLatin1String(aaa.s));
  QMessageBox::information(NULL,"偷偷告诉你一个秘密",a,QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}

void MainWindow::on_pushButton_15_clicked()
{
  using namespace cv;
  Mat src;
  Mat temp=imread("./test.png",1);
 cvtColor(temp, src,COLOR_BGR2RGB);
  QImage Qtemp=QImage((unsigned char*)(src.data),src.cols,src.rows,src.cols*src.channels(),QImage::Format_RGB888);
    QString a=ui->textEdit_2->toPlainText();
    if(a==code)
      {
            QSound::play("newWave0.wav");


            ui->label->setPixmap(QPixmap::fromImage(Qtemp));
            ui->label->resize(Qtemp.size());
            ui->label->show();
      }
    else
      {
          cvtColor(temp,src,COLOR_RGB2GRAY);
           Qtemp=QImage((unsigned char*)(src.data),src.cols,src.rows,src.cols*src.channels(),QImage::Format_Grayscale8);
           ui->label->setPixmap(QPixmap::fromImage(Qtemp));
           ui->label->resize(Qtemp.size());
           ui->label->show();
      }
}
