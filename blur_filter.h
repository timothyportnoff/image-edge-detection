#include <vector>
#include <cmath>

//Global constants
const int R = 0, G = 1, B = 2, T = 3;
const int num_colors = 3;

void set_pixel(std::vector<std::vector<std::vector<int>>> &vec, size_t &i, size_t &j, int r, int g, int b);
std::vector<int> average_4(std::vector<std::vector<std::vector<int>>> &vec, size_t &i, size_t &j); 
std::vector<int> average_8(std::vector<std::vector<std::vector<int>>> &vec, size_t &i, size_t &j);

void blur_filter(std::vector<std::vector<std::vector<int>>> &input, int &strength) {
	//Get the number of rows, columns, and colors in vector and vet
	size_t rows = input.size();
	if (!rows) exit(1);
	size_t cols = input[0].size();
	if (!cols) exit(1);
	size_t num_colors = input[0][0].size();
	if (!num_colors) exit(1);

	//Create a copy so that we're not fucking with our original image
	std::vector<std::vector<std::vector<int>>> output(rows, std::vector<std::vector<int>>(cols, std::vector<int>(num_colors)));

	//Do the image filtering on every row and column in this image
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			//Don't even fuck with any of the edge cases. Deal with that shit later
			if(i == 0) continue;
			if(i == rows - 1) continue;
			if(j == 0) continue;
			if(j == cols - 1) continue;

			//TODO Probably don't need this, unless we want to add it to the average. Probably will help the blur outcome.
			//Save rgb for better readability 
			int r = input[i][j][R];
			int g = input[i][j][G];
			int b = input[i][j][B];

			//Red, blue and green channel averages around us 
			std::vector<int> channel_averages = average_4(input, i, j);

			//Set the pixel of our output image
			set_pixel(output, i, j, channel_averages[R], channel_averages[G], channel_averages[B]);
		}
	}
	input = output;
}

void set_pixel(std::vector<std::vector<std::vector<int>>> &vec, size_t &i, size_t &j, int r, int g, int b) {
	vec[i][j][R]=r;
	vec[i][j][G]=g;
	vec[i][j][B]=b;
}

std::vector<int> average_8(std::vector<std::vector<std::vector<int>>> &vec, size_t &i, size_t &j) {
	//TODO not implemented
	int r_total = 0, g_total = 0, b_total = 0;

	r_total += vec[i-1][j][R];
	r_total += vec[i-1][j+1][R];
	r_total += vec[i-1][j-1][R];
	r_total -= vec[i+1][j][R];
	r_total -= vec[i+1][j-1][R];
	r_total -= vec[i+1][j+1][R];

	g_total += vec[i-1][j][G];
	g_total += vec[i-1][j+1][G];
	g_total += vec[i-1][j-1][G];
	g_total -= vec[i+1][j][G];
	g_total -= vec[i+1][j-1][G];
	g_total -= vec[i+1][j+1][G];

	b_total += vec[i-1][j][B];
	b_total += vec[i-1][j+1][B];
	b_total += vec[i-1][j-1][B];
	b_total -= vec[i+1][j][B];
	b_total -= vec[i+1][j-1][B];
	b_total -= vec[i+1][j+1][B];

	return {r_total,g_total,b_total};
}

std::vector<int> average_4(std::vector<std::vector<std::vector<int>>> &vec, size_t &i, size_t &j) {
	int r_total = 0, g_total = 0, b_total = 0;

	r_total += vec[i][j-1][R];
	r_total -= vec[i][j+1][R];
	r_total += vec[i-1][j][R];
	r_total -= vec[i+1][j][R];

	g_total += vec[i][j-1][G];
	g_total -= vec[i][j+1][G];
	g_total += vec[i-1][j][G];
	g_total -= vec[i+1][j][G];

	b_total += vec[i][j-1][B];
	b_total -= vec[i][j+1][B];
	b_total += vec[i-1][j][B];
	b_total -= vec[i+1][j][B];

	return {r_total/4.0,g_total/4.0,b_total/4.0};
}
