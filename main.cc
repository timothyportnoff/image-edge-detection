#include <CImg.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cstdlib>
//#include <cmath>
#include "prewitt_filter.h"
using namespace cimg_library;
using namespace std;

//Global varibales
const int COLORS = 3;
int cols, rows, stride;

void filter1(vector<vector<vector<int>>> &vec);

void die (string s = "No rason given.") {
	cout << "Program Terminated: " << s << endl;
	exit(1);
}

void warning (string s = "No warning given.") {
	cout << "Warning: " << s << endl;
	return;
}

//This code must be run with a command line parameter, so print error and quit if they don't run it right
void usage() {
	cout << "INCORRECT USAGE: Needs to be called with a.out [image.jpg]\n";
	cout << "For example, a.out ~/pictures/kyoto_original.jpg\n";
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
	if (argc != 2) usage(); 

	//Load the image, make the dot.
	clock_t start_time = clock();
	CImg<unsigned char> image(argv[1]);

	//Set globals
	cols = image.width();
	rows = image.height();
	stride = cols * rows;

	//Create a new 3D vector to pass to the image filter code. even though it is of ints, it is really uint8_t's, any value over 255 will cap at 255
	vector<vector<vector<int>>> vec(cols, vector<vector<int>>(rows, vector<int>(COLORS)));

	//Copy data from image to vec to make it easier on students
	//TODO I'm not a student anymore, I'm cool now. Get rid of this to make it harder on students
	image_to_vec(image, vec); 

	clock_t end_time = clock();
	cerr << "Image load time: " << double (end_time - start_time) / CLOCKS_PER_SEC << " secs\n";

	//Run filter
	start_time = clock();
	//FIXME dot_image(vec, dot);
	prewitt_filter(vec);
	end_time = clock();
	cerr << "Filter time: " << double (end_time - start_time) / CLOCKS_PER_SEC << " secs\n";

	//Save image
	vec_to_image(image, vec); //Copy from the vec to the image object
	image.save_png("png.png"); //Use this for higher quality output
	//image.save_jpeg("dot.jpg", 100); //Output result after filter 1
	end_time = clock();
	cerr << "Time to write image: " << double (end_time - start_time) / CLOCKS_PER_SEC << " secs\n";
}
