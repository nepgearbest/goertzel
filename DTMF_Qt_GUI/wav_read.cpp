#include "wav_read.h"

wav_read::wav_read()
{

}
std::vector<char> wav_read::wav_reading()
{
  using namespace std;
  vector<char> res;
  int f[8]={697,770,852,941,1209,1336,1477,1633};
  char f_g[4][3]={{'1','2','3'},{'4','5','6'},{'7','8','9'},{'*','0','#'}};
  ifstream file;
  file.open("newWave0.wav",ios::binary|ios::in);
  //if(file)
      //cout<<"open success"<<endl;
    //cout<<flush;
  char total[8000*6+44];
  file.read(total ,sizeof(char)*(8000*6+44));
  file.close();
unsigned char total0[8000*6+44];
    for(int i=0;i<48000+44;i++)
      {
        total0[i]=(unsigned char)(total[i]);
      }
  for(int i=0;i<6;i++)
    {
      vector<double> temp(total0+8000*(i)+44,total0+8000*(i+1)+44);//TODO:bug在这里！temp[45]应该是0.默认的构造函数不会对unsigned进行处理。修复完毕。5.17
      vector<double> s;
      //cout<<"size ="<<temp.size()<<endl;
      for(int j=0;j<7;j++)
        {
          goertzel a(temp);
         s.push_back(a.encode(j));
        // cout<<a.encode(j)<<endl;
         //a.~goertzel();
        }
      double max0=0;
      int pos_0=0,pos_1=0;;//找最大的两个能量值，
      for(int j=0;j<4;j++)
        {
          if(s[j]>max0)
            {
              max0=s[j];
              pos_0=j;
            }
        }
      s[pos_0]=0.00;
      max0=0;
      for(int j=4;j<7;j++)
        {
          if(s[j]>max0)
            {
              max0=s[j];
              pos_1=j;
            }
        }
     // cout<<f[pos_0]<<endl;
     // cout<<f[pos_1]<<endl;
     res.push_back(f_g[pos_0][pos_1-4]);
      //cout<<f_g[pos_0][pos_1-4]<<endl;
     // cout<<flush;
      s.clear();
      temp.clear();
    }

  return res;
}
