#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include<fstream>
#include<math.h>

#define WAVE_HEAD_LENGTH 44//wav头文件长度
#define m_samplefreq 8000
#define m_channels 1
#define m_channelbits 8
#define MATH_PI 3.1415

using namespace std;
//.wav文件的文件头结构
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
void MakeWaveData(int rate, int freq, int freq2,int amp, char* p, int len)//采样率、频率、音量、采样点数
{
        if (m_channels == 1)
        {
            for (int i = 0; i < len; i++)
            {
                *(p + i) = (sin(i * (MATH_PI * 2) / rate * freq) *63 + 128)/2;
                *(p + i) += (sin(i * (MATH_PI * 2) / rate * freq2) * 63  + 128)/2;
                //*(p + i) += sin(i * (MATH_PI * 2) / rate * freq2) * amp * 128 / 100/2 + 128;
            }
        }
}
int Create(int freq[6][2], int volume, int durations)//频率、音量、持续时间
{
    WaveHeader *pHeader = new WaveHeader;
    DWORD totalLen = (m_samplefreq * m_channels * m_channelbits / 8) * durations + 44;//文件总长度=(采样率 * 通道数 * 比特数 / 8) * 持续时间(s)
    pHeader->chRIFF[0] = 'R';
    pHeader->chRIFF[1] = 'I';
    pHeader->chRIFF[2] = 'F';
    pHeader->chRIFF[3] = 'F';
    pHeader->dwRIFFLen = totalLen - 8;//文件的总长度-8bits

    pHeader->chWAVE[0] = 'W';
    pHeader->chWAVE[1] = 'A';
    pHeader->chWAVE[2] = 'V';
    pHeader->chWAVE[3] = 'E';

    pHeader->chFMT[0] = 'f';
    pHeader->chFMT[1] = 'm';
    pHeader->chFMT[2] = 't';
    pHeader->chFMT[3] = ' ';

    pHeader->dwFMTLen = 0x0010;//一般情况下Size为16，如果为18则最后多了2个字节的附加信息
    pHeader->pwf.wf.wFormatTag = 0x0001;//编码方式
    pHeader->pwf.wf.nChannels = m_channels; //1为单通道，2为双通道
    pHeader->pwf.wf.nSamplesPerSec = m_samplefreq;  //=44.1KHz
    pHeader->pwf.wf.nAvgBytesPerSec = m_samplefreq * m_channels * m_channelbits / 8;//每秒所需字节数
    pHeader->pwf.wf.nBlockAlign = m_channels * m_channelbits / 8;//一个采样的字节数
    pHeader->pwf.wBitsPerSample = m_channelbits;//16位，即设置PCM的方式为16位立体声(双通道)

    pHeader->chDATA[0] = 'd';
    pHeader->chDATA[1] = 'a';
    pHeader->chDATA[2] = 't';
    pHeader->chDATA[3] = 'a';
    pHeader->dwDATALen = totalLen - WAVE_HEAD_LENGTH;//数据的长度，=文件总长度-头长度(44bit)

    char *pWaveBuffer = new char[totalLen]; //音频数据
    memcpy(pWaveBuffer, pHeader, WAVE_HEAD_LENGTH);
    for(int i=0;i<6;i++){
    MakeWaveData(pHeader->pwf.wf.nSamplesPerSec, freq[i][0],freq[i][1], volume, pWaveBuffer+ WAVE_HEAD_LENGTH+i*m_samplefreq, m_samplefreq);//采样点数
      }
    ofstream ocout;
    ocout.open("newWave0.wav", ios::out | ios::binary);//以二进制形式打开文件
    if (ocout)
        ocout.write(pWaveBuffer, totalLen);
    else
        return 0;
    ocout.close();

    delete(pHeader);
    return 1;
}

