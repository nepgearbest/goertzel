#include "goertzel.h"




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
double goertzel::encode(int x)
{
    std::complex<double> Q0,Q1,Q2,C,P;
    C=2*std::cos(2*pi*Ks[x]/K);
    Q1=0;
    Q0=0;
    for (int i = 0; i < S.size(); i++)
    {
        Q0=C*Q1-Q2+S[i];
        Q2=Q1;
        Q1=Q0;

    }
    P=norm(Q1)+norm(Q2)-Q1*Q2*C;


    S.clear();
    //P_p.push_back(P);
    return norm(P);
    //std::cout<<P.real()<<std::endl;
}
