#include <windows.h> 
#include <mmsystem.h>
#include <iostream>
#include<fstream> 
#include<math.h>
#include <vector>
using namespace std;

void sin_generator(int freq1,int freq2,int time);
#define fs 8000
#define PI 3.1415926
#define amp 128/100 

/*
//.wav文件的文件头结构 
*/
typedef struct
{
    char chRIFF[4];
    DWORD dwRIFFLen;
    char chWAVE[4];
    char chFMT[4];
    DWORD dwFMTLen;
    PCMWAVEFORMAT pwf;
    char chDATA[4];
    DWORD dwDATALen;
    //UINT8* pBufer;
}WaveHeader;
void sin_generator(int freq1,int freq2,int time)//生成8bit单通道wav文件
{
    
    int N=time*fs;
    cout<<N<<endl;//N为数据长度
    WaveHeader *pHeader = new WaveHeader;
    DWORD totalLen =(8000*1*8/8)*time+44; //文件总长度=(采样率 * 通道数 * 比特数 / 8) * 持续时间(s)

    
    pHeader->chRIFF[0] = 'R';
    pHeader->chRIFF[1] = 'I';
    pHeader->chRIFF[2] = 'F';
    pHeader->chRIFF[3] = 'F';//写入RIFF标识
    pHeader->dwRIFFLen = totalLen - 8;//文件的总长度-8bits

    pHeader->chWAVE[0] = 'W';
    pHeader->chWAVE[1] = 'A';
    pHeader->chWAVE[2] = 'V';
    pHeader->chWAVE[3] = 'E';//文件wave标识写入

    pHeader->chFMT[0] = 'f';
    pHeader->chFMT[1] = 'm';
    pHeader->chFMT[2] = 't';
    pHeader->chFMT[3] = ' ';//文件fmt标识写入

        pHeader->dwFMTLen = 0x0010;//一般情况下Size为16，如果为18则最后多了2个字节的附加信息
    pHeader->pwf.wf.wFormatTag = 0x0001;//编码方式
    pHeader->pwf.wf.nChannels = 1; //1为单通道，2为双通道
    pHeader->pwf.wf.nSamplesPerSec = 8000;  //8KHz
    pHeader->pwf.wf.nAvgBytesPerSec = 8000;//每秒所需字节数
    pHeader->pwf.wf.nBlockAlign = 1;//一个采样的字节数
    pHeader->pwf.wBitsPerSample = 8;//位，即设置PCM的方式为8位声(单通道)

    pHeader->chDATA[0] = 'd';
    pHeader->chDATA[1] = 'a';
    pHeader->chDATA[2] = 't';
    pHeader->chDATA[3] = 'a';
    pHeader->dwDATALen = totalLen - 44;

    char *sin_wave=new char[totalLen];
    memcpy(sin_wave,pHeader,44);
    for (int i = 0; i <N; i++)
    {
        sin_wave[i+44]=(sin(2*PI*i*freq1/8000)/2)*128;
        sin_wave[i+44]+=sin(2*PI*i*freq2/8000)/2*128;
        //cout<<sin_wave[i]<<endl;//test
    }
    ofstream sin_out;
    sin_out.open("E:\\goertzel\\sin_wave.wav", ios::out | ios::binary);//新建文件，一定要以二进制形式打开！
    if (sin_out)
        sin_out.write(sin_wave, totalLen);
    sin_out.close();
    delete pHeader;
    delete sin_wave;

}
int main(int argc, char const *argv[])
{
    sin_generator(10000,10000,6);//频率1，频率2，时间（整数）
    return 0;
}
