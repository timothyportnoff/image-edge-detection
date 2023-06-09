#include <CImg.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include "prewitt_filter.h"
#include "blur_filter.h"
using namespace cimg_library;
using namespace std;

//Global varibales
const int COLORS = 3;
int cols, rows, stride;

void die (string s = "No reason given.") {
	cout << "Program Terminated: " << s << endl;
	exit(1);
}

void warning (string s = "No warning given.") {
	cout << "Warning: " << s << endl;
	return;
}

//This code must be run with a command line parameter, so print error and quit if they don't run it right
void usage() {
	cout << "INCORRECT USAGE: Needs to be called with a.out [~/path/to/image.jpg] [threshold 0-255]\n";
	cout << "For example, a.out ~/pictures/kyoto_original.jpg 80\n";
	exit(1);
}

//Copy values from image into a 3D vector
void image_to_vec(const CImg<unsigned char> &image, vector<vector<vector<int>>> &vec) {
	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {
			for (int k = 0; k < COLORS; k++) {
				vec.at(i).at(j).at(k) = image[k * stride + j * cols + i];
			}
		}
	}
}

//Clamp the values in vec to [0..255] then copy to image
void vec_to_image(CImg<unsigned char> &image, vector<vector<vector<int>>> &vec) {
	const int MAX_COLOR = 255;
	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {
			for (int k = 0; k < COLORS; k++) {
				//Saturate the values, meaning values above 255 just become white, below 0 become black
				int temp = vec.at(i).at(j).at(k);
				if (temp > MAX_COLOR) temp = MAX_COLOR;
				if (temp < 0) temp = 0;
				vec[i][j][k] = temp;
				image[k * stride + j * cols + i] = temp;
			}
		}
	}
}

//Comment
int main(int argc, char **argv) {
	//Check command line parameters
	if (argc != 3) usage(); 

	//Load the image
	clock_t start_time = clock();
	CImg<unsigned char> image(argv[1]);
	
	//Get our line threshold for the prewitt_filter function
	int threshold = std::atoi(argv[2]);
	if (threshold > 360) die("Threshold above max! Maximum = sqrt(2pow(255,2)) = 360");

	//Set globals
	cols = image.width();
	rows = image.height();
	stride = cols * rows;

	//Create a new 3D vector to pass to the image filter code. even though it is of ints, it is really uint8_t's, any value over 255 will cap at 255
	vector<vector<vector<int>>> vec(cols, vector<vector<int>>(rows, vector<int>(COLORS)));

	//Copy data from image to vec to make it easier to manipulate
	image_to_vec(image, vec); 

	clock_t end_time = clock();
	cerr << "Image load time: " << double (end_time - start_time) / CLOCKS_PER_SEC << " secs\n";

	//TODO Blur image to fix compression loss on lower quality images

	//Run filter
	start_time = clock();
	blur_filter(vec, threshold);
	prewitt_filter(vec, threshold);
	end_time = clock();
	cerr << "Filter time: " << double (end_time - start_time) / CLOCKS_PER_SEC << " secs\n";

	//Save image
	vec_to_image(image, vec); 			//Copy from the vec to the image object
	if (1) image.save_png("png.png"); 		//PNG output
	else image.save_jpeg("dot.jpg", 100); 	//JPG Output with compression
	end_time = clock();
	cerr << "Time to write image: " << double (end_time - start_time) / CLOCKS_PER_SEC << " secs\n";
}
