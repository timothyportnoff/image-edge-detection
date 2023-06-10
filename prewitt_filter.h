#include <vector>
#include <cmath>
//#include <iostream> FIXME remove?

//Global constants
const int R = 0, G = 1, B = 2, T = 3;
const int num_colors = 3;
const int magnitude_threshold = 120;

void set_pixel(std::vector<std::vector<std::vector<int>>> &vec, size_t &i, size_t &j, int r, int g, int b) {
	vec[i][j][R]=r;
	vec[i][j][G]=g;
	vec[i][j][B]=b;
}

std::vector<int> prewitt_sum_horizontal(std::vector<std::vector<std::vector<int>>> &vec, size_t &i, size_t &j) {
	int r_total = 0, g_total = 0, b_total = 0;

	r_total += vec[i-1][j][R];
	r_total += vec[i-1][j+1][R];
	r_total += vec[i-1][j-1][R];
	r_total -= vec[i+1][j][R];
	r_total -= vec[i+1][j-1][R];
	r_total -= vec[i+1][j+1][R];

	g_total += vec[i-1][j][G];
	g_total += vec[i-1][j+1][R];
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

std::vector<int> prewitt_sum_vertical(std::vector<std::vector<std::vector<int>>> &vec, size_t &i, size_t &j) {
	int r_total = 0, g_total = 0, b_total = 0;

	r_total += vec[i][j-1][R];
	r_total += vec[i+1][j-1][R];
	r_total += vec[i-1][j-1][R];
	r_total -= vec[i][j+1][R];
	r_total -= vec[i-1][j+1][R];
	r_total -= vec[i+1][j+1][R];

	g_total += vec[i][j-1][G];
	g_total += vec[i+1][j-1][R];
	g_total += vec[i-1][j-1][G];
	g_total -= vec[i][j+1][G];
	g_total -= vec[i-1][j+1][G];
	g_total -= vec[i+1][j+1][G];

	b_total += vec[i][j-1][B];
	b_total += vec[i+1][j-1][B];
	b_total += vec[i-1][j-1][B];
	b_total -= vec[i][j+1][B];
	b_total -= vec[i-1][j+1][B];
	b_total -= vec[i+1][j+1][B];

	return {r_total,g_total,b_total};
}

void prewitt_filter(std::vector<std::vector<std::vector<int>>> &vec) {
	//Get the number of rows, columns, and colors in vector and vet
	size_t rows = vec.size();
	if (!rows) exit(1);
	size_t cols = vec[0].size();
	if (!cols) exit(1);
	size_t num_colors = vec[0][0].size();
	if (!num_colors) exit(1);

	//Do the image filtering on every row and column in this image
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			//Don't even fuck with any of the edge cases. Deal with that shit later
			if(i == 0) continue;
			if(i == rows - 1) continue;
			if(j == 0) continue;
			if(j == cols - 1) continue;

			//Reset our totals to 0
			int r_total = 0;
			int g_total = 0;
			int b_total = 0;

			//Assign rgb for better readability
			int r = vec[i][j][R];
			int g = vec[i][j][G];
			int b = vec[i][j][B];

			//Red, blue and green channel totals of our prewitt kernel 
			std::vector<int> horizontal_totals = prewitt_sum_horizontal(vec, i, j);
			std::vector<int> vertical_totals 	= prewitt_sum_vertical(vec, i, j);
			std::vector<int> total_totals 	= {0,0,0};
			for (int &t : horizontal_totals) 	{ t = t*t; }
			for (int &t : vertical_totals) 	{ t = t*t; }
			for (int &t : total_totals) 		{ t = t*t; }
			for (size_t k = 0; k < total_totals.size(); k++) total_totals[k] = sqrt(horizontal_totals[k] + vertical_totals[k]);
			for (size_t k = 0; k < total_totals.size(); k++) if (total_totals[k] >= magnitude_threshold) set_pixel(vec, i, j, 30, 30, 30);
			//else if (dot[i % dot.size()][j % dot.size()] == 'R') {
		}
	}
}
