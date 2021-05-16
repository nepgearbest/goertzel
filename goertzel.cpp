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
    std::vector<int> f={697,770,852,941,1209,1336,1477,1633};//目标频率组 //TODO: 请用vector改写
    int temp=0;
    std::vector<int> K_temp;
    std::vector<int> Ks={17,19,21,24,30,33,37,41};
    double sum_arv;//计算每组k时
    /*
    S：采样值
    算法部分：Q0=CQ1-Q2+S
    Q1=Q0
    Q2=Q1

    C=2*cos(2*pi*Ks/N) //
    */

   goertzel(std::vector<double> a);
   void encode(int x);//对频率fx进行功率读取
   std::vector<std::complex< double > > C_c;
   std::vector<std::complex< double > > P_p;
   std::vector<double> S;//TODO:取一个块，S的处理
   double pi=3.1415926535;
};


goertzel::goertzel(std::vector<double> a)
{
/*
执行K,N的初始化取值
*/
K=205;
S.assign(a.begin(),a.end());
}

goertzel::~goertzel()
{
}

void goertzel::encode(int x)
{
    std::complex<double> Q0,Q1,Q2,C,P;
    C=2*std::cos(2*pi*Ks[x]/K);
    for (int i = 0; i < S.size(); i++)
    {
        Q0=C*Q1-Q2+S[i];
        Q2=Q1;
        Q1=Q0;
    }
    P=std::norm(Q1)+std::norm(Q2)-Q1*Q2*C;
    P_p.push_back(P);
   std::cout<<std::norm(P)<<std::endl;
}

void goertzel::dp_start(double a[8][3])
{
    double dp[8][3];

    dp[0][1]=(a[0][0]-a[0][1])/a[0][0];
    dp[0][2]=(a[0][2]-a[0][0])/a[0][0];
    for (int i = 1; i < 8; i++)//分类讨论，区间重叠，误差恒为1，区间不重叠，脚踩头，脚没法min,只能取dp[i-1]的脚，两边区间无交点，//漏洞：3个区间相交无解(如何避免这种情况？频率相差大一点，N大一点)
    {
        if(a[i][0]==a[i-1][0])
        {
            dp[i][1]=dp[i-1][2]+(a[i][0]-a[i][1])/a[i][0];
            dp[i][2]=dp[i-1][2]+(-a[i][0]+a[i][2])/a[i][0];
            continue;
        }
        if(a[i][1]==a[i-1][2])
        {
            dp[i][2]=std::min(dp[i-1][1],dp[i-1][2])+(a[i][2]-a[i][0])/a[i][0];
            dp[i][1]=dp[i-1][1]+(a[i][0]-a[i][1])/a[i][0];
            continue;
        }
        dp[i][2]=std::min(dp[i-1][1],dp[i-1][2])+(a[i][2]-a[i][0])/a[i][0];
        dp[i][1]=std::min(dp[i-1][1],dp[i-1][2])+(a[i][0]-a[i][1])/a[i][0];
    }
    //接下来读取K[8]
    double source =0;
    K_temp.clear();
    source=std::min(dp[7][1],dp[7][2]);
    sum_arv=source;
    for (int i = 7; i>=1; i--)
    {
        if(source>dp[i][2])
        {
        source-=dp[i][2];
        K_temp.push_back(a[i][2]);
        }
        else 
        {
        source-=dp[i][1];
        K_temp.push_back(a[i][1]);
        } 
    }
    
}
void goertzel::k_count()
{
    double min_arv=100000;

    for (int i = 195; i < 250; i++)//遍历N,N!=1
    {
        sum_arv=0.000;
        double last_k=0;
        double s_save[8][3];//TODO: 修改为动态大小，适配f
        for (int j = 0; j < f.size(); j++)//注意检查K的值不能是一样的，要跟上一个K比较，使用dp解决。不然在200~210范围内会出现重复解
        {
            s_save[j][0]=f[j]*i/R;//实际值
            s_save[j][1]=floor(s_save[j][0]);//向下取整
            s_save[j][2]=ceil(s_save[j][0]);//向上取整
            //注意使用fabs，abs会将浮点数截断 4.29update:c++这int()取整看不懂，随缘取整，佛了//
        }
        goertzel::dp_start(s_save);
        if (sum_arv<min_arv)
        {
                min_arv=sum_arv;
                K=i;
                Ks.assign(K_temp.begin(),K_temp.end());
        }
    }
    
}

