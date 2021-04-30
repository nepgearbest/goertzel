#include "goertzel.cpp"
#include<iostream>
int main(int argc, char const *argv[])
{
    goertzel a;
    //double x={{},{}}
    a.k_count();
    std::cout<<a.K<<std::endl;
    for (int i=0;i<7;i++)
    {
        std::cout<<"k:"<<a.Ks[i]<<std::endl;
    }
    std::cout<<"sum_arv:"<<a.sum_arv<<std::endl;
    return 0;
}
