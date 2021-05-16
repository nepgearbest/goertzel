#ifndef WAV_READ_H
#define WAV_READ_H

#include "goertzel.h"
#include <iostream>
#include <fstream>
class wav_read
{
public:
  wav_read();
  std::vector<char> wav_reading();

};

#endif // WAV_READ_H
