#include "goertzel.cpp"
#include<iostream>

#define fs 8000
#define PI 3.1415926

std::vector<double> sin_wave;
void sin_generator(int freq1,int freq2,double time);
void sin_generator(int freq1,int freq2,double time)
{
    using namespace std;
    int N=time*fs;
    cout<<N<<endl;
    for (int i = 0; i <N; i++)
    {
        sin_wave.push_back(sin(2*PI*i*freq1/8000)/2);
        sin_wave[i]+=sin(2*PI*i*freq2/8000)/2;
        //cout<<sin_wave[i]<<endl;
    }
    
}
int main(int argc, char const *argv[])
{

    //double x={{},{}}
    sin_generator(941,852,1.25);
    goertzel a(sin_wave);
    a.k_count();
    std::cout<<a.K<<std::endl;
    for (int i=0;i<7;i++)
    {
        std::cout<<"k:"<<a.Ks[i]<<std::endl;
    }
    std::cout<<"sum_arv:"<<a.sum_arv<<std::endl;
    return 0;
}
