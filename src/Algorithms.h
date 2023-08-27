#pragma once
#include <fstream>
#include <string>
#include "tga.h"

using namespace std;

void outputTGA(tga &tgaFile, string outputFileName);
tga Multiply(tga& layer1, tga& layer2);
tga Screen(tga& layer1, tga& layer2);
tga Subtract(tga& layer1, tga& layer2);
tga Overlay(tga& layer1, tga& layer2);
tga Add(tga& layer1, int value);
tga Add(tga& layer1, int value, char channel);
tga Scale(tga& layer1, int scaleValue, char channel);
tga channelIsolate(tga& layer1, char channel);
tga combineChannels(tga& redlayer, tga& greenlayer, tga& bluelayer);
tga Flip(tga& layer1);


