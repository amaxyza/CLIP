#include <iostream>
#include <fstream>
#include <cstring>
#include "tga.h"
#include "Algorithms.h"


using namespace std;

int main(int argc, char* argv[]) {

	if (argc < 2) {
		cout << "Project 2: Image Processing, Spring 2023 \n\n" << "Usage:\n" << " 	./project2,out [output] [firstImage] [method] [...]";
	} else if (argc == 2 && !strcmp(argv[1], "--help")) {
		cout << "Project 2: Image Processing, Spring 2023 \n\n" << "Usage:\n" << " 	./project2,out [output] [firstImage] [method] [...]";
	}
	else {
		string outputFile = argv[1];
		if (outputFile.substr(outputFile.find_last_of(".") + 1) != "tga") {
			cout << "Invalid file name.";
			return -1;
		}

		if (argc == 2) {
			cout << "Invalid file name.";
			return -1;
		}
		
		string sourceFile = argv[2];
		if (outputFile.substr(outputFile.find_last_of(".") + 1) != "tga") {
			cout << "Invalid file name.";
			return -1;
		}

		fstream sourceFileStream(sourceFile, ios_base::in | ios_base::binary);
		if (!sourceFileStream.is_open()) {
			cout << "File does not exist.";
			return -1;
		}
		
		tga trackedFile(sourceFileStream);
		int safeIndex = 0;
		for (int i = 3; i < argc; i++) {
			if (!strcmp(argv[i], "multiply")) {

				if (argc == i + 1) {
					cout << "Missing argument.";
					return -1;
				}
				else {
					string argumentFileName = argv[i + 1];
					if (argumentFileName.substr(argumentFileName.find_last_of(".") + 1) != "tga") {
						cout << "Invalid argument, invalid file name.";
						return -1;
					}
					fstream argumentLayer(argv[i + 1], ios_base::in | ios_base::binary);
					if (argumentLayer.is_open()) {
						if (i == 3) {
							cout << "Multiplying " << sourceFile << " and " << argv[i + 1] << " ..." << endl;
						}
						else {
							cout << "... and multiplying the previous step and " << argv[i + 1] << " ..." << endl;
						}
						tga argumentFile(argumentLayer);
						trackedFile = Multiply(trackedFile, argumentFile);
						safeIndex = i + 1;
					}
					else {
						cout << "Invalid argument, file does not exist.";
						return -1;
					}
				}
			}

			else if (!strcmp(argv[i], "subtract")) {
				if (argc == i + 1) {
					cout << "Missing argument.";
					return -1;
				}
				else {
					string argumentFileName = argv[i + 1];
					if (argumentFileName.substr(argumentFileName.find_last_of(".") + 1) != "tga") {
						cout << "Invalid argument, invalid file name.";
						return -1;
					}
					fstream argumentLayer(argv[i + 1], ios_base::in | ios_base::binary);
					if (argumentLayer.is_open()) {
						if (i == 3) {
							cout << "Subtracting " << sourceFile << " and " << argv[i + 1] << " ..." << endl;
						}
						else {
							cout << "... and subtracting " << argv[i + 1] << " from previous step ..." << endl;
						}
						tga argumentFile(argumentLayer);
						trackedFile = Subtract(trackedFile, argumentFile);
						safeIndex = i + 1;
					}
					else {
						cout << "Invalid argument, file does not exist.";
						return -1;
					}
				}
			}

			else if (!strcmp(argv[i], "overlay")) {
				if (argc == i + 1) {
					cout << "Missing argument.";
					return -1;
				}
				else {
					string argumentFileName = argv[i + 1];
					if (argumentFileName.substr(argumentFileName.find_last_of(".") + 1) != "tga") {
						cout << "Invalid argument, invalid file name.";
						return -1;
					}
					fstream argumentLayer(argv[i + 1], ios_base::in | ios_base::binary);
					if (argumentLayer.is_open()) {
						if (i == 3) {
							cout << "Overlaying " << sourceFile << " and " << argv[i + 1] << " ..." << endl;
						}
						else {
							cout << "... and overlaying " << argv[i + 1] << " from previous step ..." << endl;
						}
						tga argumentFile(argumentLayer);
						trackedFile = Overlay(trackedFile, argumentFile);
						safeIndex = i + 1;
					}
					else {
						cout << "Invalid argument, file does not exist.";
						return -1;
					}
				}
			}

			else if (!strcmp(argv[i], "screen")) {
				if (argc == i + 1) {
					cout << "Missing argument.";
					return -1;
				}
				else {
					string argumentFileName = argv[i + 1];
					if (argumentFileName.substr(argumentFileName.find_last_of(".") + 1) != "tga") {
						cout << "Invalid argument, invalid file name.";
						return -1;
					}
					fstream argumentLayer(argv[i + 1], ios_base::in | ios_base::binary);
					if (argumentLayer.is_open()) {
						if (i == 3) {
							cout << "Screening " << sourceFile << " and " << argv[i + 1] << " ..." << endl;
						}
						else {
							cout << "... and screening " << argv[i + 1] << " on previous step ..." << endl;
						}
						tga argumentFile(argumentLayer);
						trackedFile = Screen(argumentFile, trackedFile);
						safeIndex = i + 1;
					}
					else {
						cout << "Invalid argument, file does not exist.";
						return -1;
					}
				}
			}

			else if (!strcmp(argv[i], "flip")) {
				if (i == 3) {
					cout << "Flipping " << sourceFile << " ..." << endl;
				}
				else {
					cout << "... and flipping output of previous step ..." << endl;
				}
				trackedFile = Flip(trackedFile);
			}

			else if (!strcmp(argv[i], "onlyred")) {
				if (i == 3) {
					cout << "Retrieving only the red scale of " << sourceFile << " ..." << endl;
				}
				else {
					cout << "... and retrieving the red scale previous step ..." << endl;
				}
				trackedFile = channelIsolate(trackedFile, 'R');
			}

			else if (!strcmp(argv[i], "onlygreen")) {
				if (i == 3) {
					cout << "Retrieving only the green scale of " << sourceFile << " ..." << endl;
				}
				else {
					cout << "... and retrieving the green scale previous step ..." << endl;
				}
				trackedFile = channelIsolate(trackedFile, 'G');
			}

			else if (!strcmp(argv[i], "onlyblue")) {
				if (i == 3) {
					cout << "Retrieving only the blue scale of " << sourceFile << " ..." << endl;
				}
				else {
					cout << "... and retrieving the blue scale previous step ..." << endl;
				}
				trackedFile = channelIsolate(trackedFile, 'B');
			}

			else if (!strcmp(argv[i], "addred")) {
				if (argc == i + 1) {
					cout << "Missing argument.";
					return -1;
				}
				else {
					try {
						if (i == 3) {
							cout << "Adding " << stoi(argv[i + 1]) << " to the red channel of" << sourceFile << " ..." << endl;
						}
						else {
							cout << "... and adding " << stoi(argv[i + 1]) << " to the red scale previous step ..." << endl;
						}
						trackedFile = Add(trackedFile, stoi(argv[i + 1]), 'R');
						safeIndex = i + 1;
					}
					catch (invalid_argument) {
						cout << "Invalid argument, expected number.";
						return -1;
					}
				}
			}

			else if (!strcmp(argv[i], "addgreen")) {
				if (argc == i + 1) {
					cout << "Missing argument.";
					return -1;
				}
				else {
					try {
						if (i == 3) {
							cout << "Adding " << stoi(argv[i + 1]) << " to the green channel of" << sourceFile << " ..." << endl;
						}
						else {
							cout << "... and adding " << stoi(argv[i + 1]) << " to the green scale previous step ..." << endl;
						}
						trackedFile = Add(trackedFile, stoi(argv[i + 1]), 'G');
						safeIndex = i + 1;
					}
					catch (invalid_argument) {
						cout << "Invalid argument, expected number.";
						return -1;
					}
				}
			}

			else if (!strcmp(argv[i], "addblue")) {
				if (argc == i + 1) {
					cout << "Missing argument.";
					return -1;
				}
				else {
					try {
						if (i == 3) {
							cout << "Adding " << stoi(argv[i + 1]) << " to the blue channel of" << sourceFile << " ..." << endl;
						}
						else {
							cout << "... and adding " << stoi(argv[i + 1]) << " to the blue scale previous step ..." << endl;
						}
						trackedFile = Add(trackedFile, stoi(argv[i + 1]), 'B');
						safeIndex = i + 1;
					}
					catch (invalid_argument) {
						cout << "Invalid argument, expected number.";
						return -1;
					}
					
				}
			}

			else if (!strcmp(argv[i], "scalered")) {
				if (argc == i + 1) {
					cout << "Missing argument.";
					return -1;
				}
				else {
					try {
						if (i == 3) {
							cout << "Scaling by" << stoi(argv[i + 1]) << " to the red channel of" << sourceFile << " ..." << endl;
						}
						else {
							cout << "... and scaling by " << stoi(argv[i + 1]) << " to the red scale previous step ..." << endl;
						}
						trackedFile = Scale(trackedFile, stoi(argv[i + 1]), 'R');
						safeIndex = i + 1;
					}
					catch (invalid_argument) {
						cout << "Invalid argument, expected number.";
						return -1;
					}
				}
			}

			else if (!strcmp(argv[i], "scalegreen")) {
				if (argc == i + 1) {
					cout << "Missing argument.";
					return -1;
				}
				else {
					try {
						if (i == 3) {
							cout << "Scaling by" << stoi(argv[i + 1]) << " to the green channel of" << sourceFile << " ..." << endl;
						}
						else {
							cout << "... and scaling by " << stoi(argv[i + 1]) << " to the green scale previous step ..." << endl;
						}
						trackedFile = Scale(trackedFile, stoi(argv[i + 1]), 'G');
						safeIndex = i + 1;
					}
					catch (invalid_argument) {
						cout << "Invalid argument, expected number.";
						return -1;
					}
				}
			}

			else if (!strcmp(argv[i], "scaleblue")) {
				if (argc == i + 1) {
					cout << "Missing argument.";
					return -1;
				}
				else {
					try {
						if (i == 3) {
							cout << "Scaling by" << stoi(argv[i + 1]) << " to the blue channel of" << sourceFile << " ..." << endl;
						}
						else {
							cout << "... and scaling by " << stoi(argv[i + 1]) << " to the blue scale previous step ..." << endl;
						}
						trackedFile = Scale(trackedFile, stoi(argv[i + 1]), 'B');
						safeIndex = i + 1;
					}
					catch (invalid_argument) {
						cout << "Invalid argument, expected number.";
						return -1;
					}
				}
			}

			else if (!strcmp(argv[i], "combine")) {
				if (argc < i + 2) {
					cout << "Missing argument.";
					return -1;
				}
				else {
					string greenlayerName = argv[i + 1];
					string bluelayerName = argv[i + 2];
					if (greenlayerName.substr(greenlayerName.find_last_of(".") + 1) != "tga" || bluelayerName.substr(bluelayerName.find_last_of(".") + 1) != "tga") {
						cout << "Invalid argument, invalid file name.";
						return -1;
					}
					fstream greenlayer(greenlayerName, ios_base::in | ios_base::binary);
					fstream bluelayer(bluelayerName, ios_base::in | ios_base::binary);

					if (greenlayer.is_open() && bluelayer.is_open()) {
						if (i == 3) {
							cout << "Combining channels of " << sourceFile << ", " << bluelayerName << ", and " << greenlayerName << " ..." << endl;
						}
						else {
							cout << "... and combining channels of the previous step, " << bluelayerName << ", and " << greenlayerName << " ... " << endl;
						}
						tga greenlayerTGA(greenlayer);
						tga bluelayerTGA(bluelayer);
						tga redlayerTGA = channelIsolate(trackedFile, 'R');

						trackedFile = combineChannels(redlayerTGA, greenlayerTGA, bluelayerTGA);
						safeIndex = i + 2;
					}
					else {
						cout << "Invalid argument, file does not exist.";
						return -1;
					}
				}
			}
			else if (i > safeIndex) {
				cout << "Invalid method name.";
				return -1;
			}

		}
		cout << "... and saving output to " << outputFile << "!";
		outputTGA(trackedFile, outputFile);
		return 0;
	}
	/*cout << "Part 1: " << endl;

	cout << "Loading \"layer1.tga\" . . . " << endl;
	fstream layer1("input/layer1.tga", ios_base::in | ios_base::binary);
	tga layer1TGA(layer1);

	cout << "Loading \"pattern1.tga\" . . . " << endl;
	fstream pattern1("input/pattern1.tga", ios_base::in | ios_base::binary);
	tga pattern1TGA(pattern1);

	cout << "Multiplying layer1.tga and pattern1.tga . . . " << endl;
	tga result = Multiply(layer1TGA, pattern1TGA);
	outputTGA(result, "output/part1.tga");
	cout << endl;

	cout << "Part 2: " << endl;

	cout << "Loading \"layer2.tga\" . . . " << endl;
	fstream layer2("input/layer2.tga", ios_base::in | ios_base::binary);
	tga layer2TGA(layer2);

	cout << "Loading \"car.tga\" . . . " << endl;
	fstream car("input/car.tga", ios_base::in | ios_base::binary);
	tga carTGA(car);

	cout << "Subtracting car.tga from layer2.tga . . . " << endl;
	result = Subtract(carTGA, layer2TGA);
	outputTGA(result, "output/part2.tga");
	cout << endl;

	cout << "Part 3: " << endl;

	cout << "Loading \"pattern2.tga\" . . . " << endl;
	fstream pattern2("input/pattern2.tga", ios_base::in | ios_base::binary);
	tga pattern2TGA(pattern2);

	cout << "Multiplying layer1 and pattern2 without outputting the file . . ." << endl;
	result = Multiply(layer1TGA, pattern2TGA);

	cout << "Loading \"text.tga\" . . . " << endl;
	fstream text("input/text.tga", ios_base::in | ios_base::binary);
	tga textTGA(text);

	cout << "Screening text onto the results from the previous operation . . ." << endl;
	result = Screen(result, textTGA);
	outputTGA(result, "output/part3.tga");
	cout << endl;

	cout << "Part 4: " << endl;

	cout << "Loading \"circles.tga\" . . . " << endl;
	fstream circles("input/circles.tga", ios_base::in | ios_base::binary);
	tga circlesTGA(circles);

	cout << "Multiplying layer2 and circles without outputting the file . . ." << endl;
	result = Multiply(layer2TGA, circlesTGA);
	
	cout << "Subtracting pattern2 from the results of the previous operation . . . " << endl;
	result = Subtract(result, pattern2TGA);
	outputTGA(result, "output/part4.tga");
	cout << endl;

	cout << "Part 5: " << endl;

	cout << "Combining layer1 and pattern1 with Overlay . . . " << endl;
	result = Overlay(layer1TGA, pattern1TGA);
	outputTGA(result, "output/part5.tga");
	cout << endl;

	cout << "Part 6: " << endl;

	cout << "Adding 200 to car.tga's green channel . . ." << endl;
	result = Add(carTGA, 200, 'G');
	outputTGA(result, "output/part6.tga");
	cout << endl;

	cout << "Part 7: " << endl;

	cout << "Scaling car.tga's red channel by 4 . . ." << endl;
	result = Scale(carTGA, 4, 'R');
	
	cout << "Scaling car.tga's blue channel by 0 . . ." << endl;
	result = Scale(result, 0, 'B');
	outputTGA(result, "output/part7.tga");
	cout << endl;

	cout << "Part 8:" << endl;

	cout << "Writing car.tga's red channel to part8_r.tga . . ." << endl;
	result = channelIsolate(carTGA, 'R');
	outputTGA(result, "output/part8_r.tga");

	cout << "Writing car.tga's green channel to part8_g.tga . . ." << endl;
	result = channelIsolate(carTGA, 'G');
	outputTGA(result, "output/part8_g.tga");

	cout << "Writing car.tga's blue channel to part8_b.tga . . ." << endl;
	result = channelIsolate(carTGA, 'B');
	outputTGA(result, "output/part8_b.tga");
	cout << endl;

	cout << "Part 9: " << endl;

	cout << "Loading \"layer_red.tga\" . . ." << endl;
	fstream layer_red("input/layer_red.tga", ios_base::in | ios_base::binary);
	tga layer_redTGA(layer_red);

	cout << "Loading \"layer_green.tga\" . . ." << endl;
	fstream layer_green("input/layer_green.tga", ios_base::in | ios_base::binary);
	tga layer_greenTGA(layer_green);

	cout << "Loading \"layer_blue.tga\" . . ." << endl;
	fstream layer_blue("input/layer_blue.tga", ios_base::in | ios_base::binary);
	tga layer_blueTGA(layer_blue);

	cout << "Combining all color channels and outputting the result . . ." << endl;
	result = combineChannels(layer_redTGA, layer_greenTGA, layer_blueTGA);
	outputTGA(result, "output/part9.tga");
	cout << endl;

	cout << "Part 10: " << endl;
	cout << "Loading \"text2.tga\" . . ." << endl;
	fstream text2("input/text2.tga", ios_base::in | ios_base::binary);
	tga text2TGA(text2);

	cout << "Flipping text2.tga . . ." << endl;
	result = Flip(text2TGA);
	outputTGA(result, "output/part10.tga");
	cout << endl;*/

}