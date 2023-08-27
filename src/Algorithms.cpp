#include "Algorithms.h"
#include "tga.h"

void outputTGA(tga &tgaFile, string outputFileName)
{
	fstream output(outputFileName, ios_base::out | ios_base::binary);
	output.write(reinterpret_cast<char*>(&tgaFile.header.idLength), 1);
	output.write(reinterpret_cast<char*>(&tgaFile.header.colorMapType), 1);
	output.write(reinterpret_cast<char*>(&tgaFile.header.dataTypeCode), 1);
	output.write(reinterpret_cast<char*>(&tgaFile.header.colorMapOrigin), 2);
	output.write(reinterpret_cast<char*>(&tgaFile.header.colorMapLength), 2);
	output.write(reinterpret_cast<char*>(&tgaFile.header.colorMapDepth), 1);
	output.write(reinterpret_cast<char*>(&tgaFile.header.xOrigin), 2);
	output.write(reinterpret_cast<char*>(&tgaFile.header.yOrigin), 2);
	output.write(reinterpret_cast<char*>(&tgaFile.header.width), 2);
	output.write(reinterpret_cast<char*>(&tgaFile.header.height), 2);
	output.write(reinterpret_cast<char*>(&tgaFile.header.bitsPerPixel), 1);
	output.write(reinterpret_cast<char*>(&tgaFile.header.imageDescriptor), 1);

	for (int i = 0; i < tgaFile.pixelData.size(); i++) {
		output.write(reinterpret_cast<char*>(&tgaFile.pixelData[i].B), 1);
		output.write(reinterpret_cast<char*>(&tgaFile.pixelData[i].G), 1);
		output.write(reinterpret_cast<char*>(&tgaFile.pixelData[i].R), 1);
	}
}

tga Multiply(tga& layer1,tga& layer2)
{
	tga output(layer1.header);

	// Making each pixel of the new tga file with the multiply algorithm
	if (layer1.pixelData.size() == layer2.pixelData.size()) {

		for (int i = 0; i < layer1.pixelData.size(); i++) {

			Pixel newpixel;

			float normalB1 = (int)layer1.pixelData[i].B / 255.0f;
			float normalB2 = (int)layer2.pixelData[i].B / 255.0f;
			float normalB1_times_normalB2 = normalB1 * normalB2;
			newpixel.B = (unsigned char)((normalB1_times_normalB2 * 255.0f) + 0.5f);

			float normalG1 = (int)layer1.pixelData[i].G / 255.0f;
			float normalG2 = (int)layer2.pixelData[i].G / 255.0f;
			float normalG1_times_normalG2 = normalG1 * normalG2;
			newpixel.G = (unsigned char)((normalG1_times_normalG2 * 255.0f) + 0.5f);

			float normalR1 = (int)layer1.pixelData[i].R / 255.0f;
			float normalR2 = (int)layer2.pixelData[i].R / 255.0f;
			float normalR1_times_normalR2 = normalR1 * normalR2;
			newpixel.R = (unsigned char)((normalR1_times_normalR2 * 255.0f) + 0.5f);

			output.pixelData.push_back(newpixel);

		}
		
	}
	return output;
	
}

tga Screen(tga& layer1, tga& layer2)
{
	tga output(layer1.header);

	if (layer1.pixelData.size() == layer2.pixelData.size()) {

		for (int i = 0; i < layer1.pixelData.size(); i++) {
			Pixel newpixel;

			float normalB1 = (int)layer1.pixelData[i].B / 255.0f;
			float normalB2 = (int)layer2.pixelData[i].B / 255.0f;
			float operationB = 1 - ((1 - normalB1) * (1 - normalB2));
			newpixel.B = (unsigned char)((operationB * 255) + 0.5f);

			float normalG1 = (int)layer1.pixelData[i].G / 255.0f;
			float normalG2 = (int)layer2.pixelData[i].G / 255.0f;
			float operationG = 1 - ((1 - normalG1) * (1 - normalG2));
			newpixel.G = (unsigned char)((operationG * 255) + 0.5f);

			float normalR1 = (int)layer1.pixelData[i].R / 255.0f;
			float normalR2 = (int)layer2.pixelData[i].R / 255.0f;
			float operationR = 1 - ((1 - normalR1) * (1 - normalR2));
			newpixel.R = (unsigned char)((operationR * 255) + 0.5f);

			output.pixelData.push_back(newpixel);
		}
	}

	return output;

}

tga Subtract(tga& layer1, tga& layer2)
{
	tga output(layer1.header);
	// Making each pixel of the new tga file with the subtract algorithm
	if (layer1.pixelData.size() == layer2.pixelData.size()) {
		
		for (int i = 0; i < layer1.pixelData.size(); i++) {
			Pixel newpixel;

			int B_sub = (int)layer1.pixelData[i].B - (int)layer2.pixelData[i].B;
			if (B_sub < 0) { B_sub = 0; }
			newpixel.B = (unsigned char)B_sub;

			int G_sub = (int)layer1.pixelData[i].G - (int)layer2.pixelData[i].G;
			if (G_sub < 0) { G_sub = 0; }
			newpixel.G = (unsigned char)G_sub;

			int R_sub = (int)layer1.pixelData[i].R - (int)layer2.pixelData[i].R;
			if (R_sub < 0) { R_sub = 0; }
			newpixel.R = (unsigned char)R_sub;

			output.pixelData.push_back(newpixel);
			
		}
		
	}
	return output;
	
}

tga Overlay(tga& layer1, tga& layer2)
{
	tga output(layer1.header);

	for (int i = 0; i < layer1.pixelData.size(); i++) {

		Pixel newpixel;

		float nB1 = (int)layer1.pixelData[i].B / 255.0f;
		float nB2 = (int)layer2.pixelData[i].B / 255.0f;

		if (nB2 <= 0.5f) {
			newpixel.B = (unsigned char)(((2 * nB1 * nB2) * 255.0f) + 0.5f);
		}
		else if (nB2 > 0.5f) {
			newpixel.B = (unsigned char)(((1 - (2 * (1 - nB1) * (1 - nB2))) * 255.0f) + 0.5f);
		}

		float nG1 = (int)layer1.pixelData[i].G / 255.0f;
		float nG2 = (int)layer2.pixelData[i].G / 255.0f;

		if (nG2 <= 0.5f) {
			newpixel.G = (unsigned char)(((2 * nG1 * nG2) * 255.0f) + 0.5f);
		}
		else if (nG2 > 0.5f) {
			newpixel.G = (unsigned char)(((1 - (2 * (1 - nG1) * (1 - nG2))) * 255.0f) + 0.5f);
		}

		float nR1 = (int)layer1.pixelData[i].R / 255.0f;
		float nR2 = (int)layer2.pixelData[i].R / 255.0f;

		if (nR2 <= 0.5f) {
			newpixel.R = (unsigned char)(((2 * nR1 * nR2) * 255.0f) + 0.5f);
		}
		else if (nB2 > 0.5f) {
			newpixel.R = (unsigned char)(((1 - (2 * (1 - nR1) * (1 - nR2))) * 255.0f) + 0.5f);
		}
		output.pixelData.push_back(newpixel);
	}
	return output;
}

tga Add(tga& layer1, int value)
{
	tga output(layer1.header);
	for (int i = 0; i < layer1.pixelData.size(); i++) {
		Pixel newpixel;

		int newB = (int)layer1.pixelData[i].B + value;
		if (newB > 255) {
			newB = 255;
		}
		else if (newB < 0) {
			newB = 0;
		}
		newpixel.B = (unsigned char)newB;

		int newG = (int)layer1.pixelData[i].G + value;
		if (newG > 255) {
			newG = 255;
		}
		else if (newG < 0) {
			newG = 0;
		}
		newpixel.G = (unsigned char)newG;

		int newR = (int)layer1.pixelData[i].R + value;
		if (newR > 255) {
			newR = 255;
		}
		else if (newR < 0) {
			newR = 0;
		}
		newpixel.R = (unsigned char)newR;

		output.pixelData.push_back(newpixel);
	}
	return output;
}

tga Add(tga& layer1, int value, char channel)
{
	tga output(layer1.header);
	for (int i = 0; i < layer1.pixelData.size(); i++) {
		Pixel newpixel;

		if (channel == 'B') {

			int newB = (int)layer1.pixelData[i].B + value;
			if (newB > 255) {
				newB = 255;
			}
			else if (newB < 0) {
				newB = 0;
			}
			newpixel.B = (unsigned char)newB;
			newpixel.G = layer1.pixelData[i].G;
			newpixel.R = layer1.pixelData[i].R;
		} else if (channel == 'G') {

			int newG = (int)layer1.pixelData[i].G + value;
			if (newG > 255) {
				newG = 255;
			}
			else if (newG < 0) {
				newG = 0;
			}
			newpixel.G = (unsigned char)newG;
			newpixel.B = layer1.pixelData[i].B;
			newpixel.R = layer1.pixelData[i].R;
		} else if (channel == 'R') {

			int newR = (int)layer1.pixelData[i].R + value;
			if (newR > 255) {
				newR = 255;
			}
			else if (newR < 0) {
				newR = 0;
			}
			newpixel.R = (unsigned char)newR;
			newpixel.B = layer1.pixelData[i].B;
			newpixel.G = layer1.pixelData[i].G;
		}

		output.pixelData.push_back(newpixel);
	}
	return output;
}

tga Scale(tga& layer1, int scaleValue, char channel)
{
	tga output(layer1.header);
	for (int i = 0; i < layer1.pixelData.size(); i++) {
		Pixel newpixel;

		if (channel == 'B') {

			int newB = (int)layer1.pixelData[i].B * scaleValue;
			if (newB > 255) {
				newB = 255;
			}
			else if (newB < 0) {
				newB = 0;
			}
			newpixel.B = (unsigned char)newB;
			newpixel.G = layer1.pixelData[i].G;
			newpixel.R = layer1.pixelData[i].R;
		}
		else if (channel == 'G') {

			int newG = (int)layer1.pixelData[i].G * scaleValue;
			if (newG > 255) {
				newG = 255;
			}
			else if (newG < 0) {
				newG = 0;
			}
			newpixel.G = (unsigned char)newG;
			newpixel.B = layer1.pixelData[i].B;
			newpixel.R = layer1.pixelData[i].R;
		}
		else if (channel == 'R') {

			int newR = (int)layer1.pixelData[i].R * scaleValue;
			if (newR > 255) {
				newR = 255;
			}
			else if (newR < 0) {
				newR = 0;
			}
			newpixel.R = (unsigned char)newR;
			newpixel.B = layer1.pixelData[i].B;
			newpixel.G = layer1.pixelData[i].G;
		}

		output.pixelData.push_back(newpixel);
	}
	return output;
}

tga channelIsolate(tga& layer1, char channel)
{
	tga output(layer1.header);
	for (int i = 0; i < layer1.pixelData.size(); i++) {

		Pixel newpixel;

		if (channel == 'B') {
			newpixel.B = layer1.pixelData[i].B;
			newpixel.G = layer1.pixelData[i].B;
			newpixel.R = layer1.pixelData[i].B;
		}
		else if (channel == 'G') {
			newpixel.B = layer1.pixelData[i].G;
			newpixel.G = layer1.pixelData[i].G;
			newpixel.R = layer1.pixelData[i].G;
		}
		else if (channel == 'R') {
			newpixel.B = layer1.pixelData[i].R;
			newpixel.G = layer1.pixelData[i].R;
			newpixel.R = layer1.pixelData[i].R;
		}
		output.pixelData.push_back(newpixel);
	}
	return output;
}

tga combineChannels(tga& redlayer, tga& greenlayer, tga& bluelayer)
{
	tga output(redlayer.header);
	for (int i = 0; i < redlayer.pixelData.size(); i++) {
		Pixel newpixel;

		newpixel.B = bluelayer.pixelData[i].B;
		newpixel.G = greenlayer.pixelData[i].G;
		newpixel.R = redlayer.pixelData[i].R;

		output.pixelData.push_back(newpixel);
	}
	return output;
}

tga Flip(tga& layer1)
{
	tga output(layer1.header);
	for (int i = layer1.pixelData.size() - 1; i >= 0; --i) {
		Pixel newpixel;

		newpixel.B = layer1.pixelData[i].B;
		newpixel.G = layer1.pixelData[i].G;
		newpixel.R = layer1.pixelData[i].R;

		output.pixelData.push_back(newpixel);
	}
	return output;
}
