#ifndef GOERTZEL_H
#define GOERTZEL_H


#include<complex>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
class goertzel
{
private:
public:
    void k_count();
    void dp_start(double [8][3]);
    goertzel();
    ~goertzel();
    /*原理解释：
        K=Nf/R,N--每隔几个采样对这个频率给出评价，R--采样率，f--目标频率，K--包含频率段的区间个数K
        根据经验，N=205为最佳
    */
   int K=0;
   double R=8200.00000;
    int fs=8000;
    std::vector<int> f={697,770,852,941,1209,1336,1477};//目标频率组 //TODO: 请用vector改写
    int temp=0;
    std::vector<int> K_temp;
    std::vector<int> Ks={18,20,22,24,31,34,38};
    double sum_arv;//计算每组k时
    /*
    S：采样值
    算法部分：Q0=CQ1-Q2+S
    Q1=Q0
    Q2=Q1

    C=2*cos(2*pi*Ks/N) //
    */

   goertzel(std::vector<double> a);
   double encode(int x);//对频率fx进行功率读取
   std::vector<std::complex< double > > C_c;
   std::vector<std::complex< double > > P_p;
   std::vector<double> S;//TODO:取一个块，S的处理
   double pi=3.1415926535;
};

#endif // GOERTZEL_H
