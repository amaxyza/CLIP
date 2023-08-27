#pragma once
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

struct tgaHeader {
	// use (int) caster to recast chars into ints
	char idLength;
	char colorMapType;
	char dataTypeCode;
	short colorMapOrigin;
	short colorMapLength;
	char colorMapDepth;
	short xOrigin;
	short yOrigin;
	short width;
	short height;
	char bitsPerPixel;
	char imageDescriptor;

};

struct Pixel {
	unsigned char R = '0';
	unsigned char G = '0';
	unsigned char B = '0';
};

struct tga {

	tgaHeader header;

	//pixelData.size() == # of pixels
	vector<Pixel> pixelData;


	tga(tgaHeader& header) {
		this->header.idLength = header.idLength;
		this->header.colorMapType = header.colorMapType;
		this->header.dataTypeCode = header.dataTypeCode;
		this->header.colorMapOrigin = header.colorMapOrigin;
		this->header.colorMapLength = header.colorMapLength;
		this->header.colorMapDepth = header.colorMapDepth;
		this->header.xOrigin = header.xOrigin;
		this->header.yOrigin = header.yOrigin;
		this->header.width = header.width;
		this->header.height = header.height;
		this->header.bitsPerPixel = header.bitsPerPixel;
		this->header.imageDescriptor = header.imageDescriptor;

		pixelData = {};
	}

	// constructor with a file
	tga(fstream &tgaFile) {

		// header data
		tgaFile.read(&header.idLength, 1);
		tgaFile.read(&header.colorMapType, 1);
		tgaFile.read(&header.dataTypeCode, 1);
		tgaFile.read(reinterpret_cast<char*>(&header.colorMapOrigin), 2); // should be zero
		tgaFile.read(reinterpret_cast<char*>(&header.colorMapLength), 2); // should be zero
		tgaFile.read(&header.colorMapDepth, 1);						   // should be zero
		tgaFile.read(reinterpret_cast<char*>(&header.xOrigin), 2);		   // should be zero
		tgaFile.read(reinterpret_cast<char*>(&header.yOrigin), 2);        // should be zero
		tgaFile.read(reinterpret_cast<char*>(&header.width), 2);
		tgaFile.read(reinterpret_cast<char*>(&header.height), 2);
		tgaFile.read(reinterpret_cast<char*>(&header.bitsPerPixel), 1);   // should be 24
		tgaFile.read(reinterpret_cast<char*>(&header.imageDescriptor), 1);

		// pixel data
		int numPixels = (int)header.width * (int)header.height;
		for (int i = 0; i < numPixels; i++) {

			Pixel newpixel;

			tgaFile.read(reinterpret_cast<char*>(&newpixel.B), 1);
			tgaFile.read(reinterpret_cast<char*>(&newpixel.G), 1);
			tgaFile.read(reinterpret_cast<char*>(&newpixel.R), 1);
			pixelData.push_back(newpixel);
		}
	}

};