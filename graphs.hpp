// Teal Dulcet, CS546

#include <iostream>
#include <sstream>
#include <cstring>
#include <cmath>
#include <cfloat>
#include <iomanip>
#include <cwchar>
#include <clocale>
#include <cstdlib>
#include <algorithm>
#include <array>
#include <vector>
#include <iterator>
#include <numeric>
#include <functional>
#include <sys/ioctl.h>
#include <unistd.h>

namespace graphs
{
	using namespace std;

	enum style_type
	{
		style_ASCII,
		style_basic,
		style_light,
		style_heavy,
		style_double,
		style_light_dashed,
		style_heavy_dashed
	};

	enum style_type const style_types[] = {style_ASCII, style_basic, style_light, style_heavy, style_double, style_light_dashed, style_heavy_dashed};

	const char *const styles[][11] = {
		{"-", "|", "+", "+", "+", "+", "+", "+", "+", "+", "+"}, // ASCII
		{"—", "|", "+", "+", "+", "+", "+", "+", "+", "+", "+"}, // Basic
		{"─", "│", "┌", "┬", "┐", "├", "┼", "┤", "└", "┴", "┘"}, // Light
		{"━", "┃", "┏", "┳", "┓", "┣", "╋", "┫", "┗", "┻", "┛"}, // Heavy
		{"═", "║", "╔", "╦", "╗", "╠", "╬", "╣", "╚", "╩", "╝"}, // Double
		{"╌", "┊", "┌", "┬", "┐", "├", "┼", "┤", "└", "┴", "┘"}, // Light Dashed
		{"╍", "┋", "┏", "┳", "┓", "┣", "╋", "┫", "┗", "┻", "┛"}	 // Heavy Dashed
		// {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "}	 // No border
	};

	enum color_type
	{
		color_default,
		color_black,
		color_red,
		color_green,
		color_yellow,
		color_blue,
		color_magenta,
		color_cyan,
		color_light_gray,
		color_dark_gray,
		color_light_red,
		color_light_green,
		color_light_yellow,
		color_light_blue,
		color_light_magenta,
		color_light_cyan,
		color_white
	};

	enum color_type const color_types[] = {color_default, color_black, color_red, color_green, color_yellow, color_blue, color_magenta, color_cyan, color_light_gray, color_dark_gray, color_light_red, color_light_green, color_light_yellow, color_light_blue, color_light_magenta, color_light_cyan, color_white};

	const char *const colors[] = {"\e[39m", "\e[30m", "\e[31m", "\e[32m", "\e[33m", "\e[34m", "\e[35m", "\e[36m", "\e[37m", "\e[90m", "\e[91m", "\e[92m", "\e[93m", "\e[94m", "\e[95m", "\e[96m", "\e[97m"};

	const char *const dots[] = {"⠀", "⠁", "⠂", "⠃", "⠄", "⠅", "⠆", "⠇", "⠈", "⠉", "⠊", "⠋", "⠌", "⠍", "⠎", "⠏", "⠐", "⠑", "⠒", "⠓", "⠔", "⠕", "⠖", "⠗", "⠘", "⠙", "⠚", "⠛", "⠜", "⠝", "⠞", "⠟", "⠠", "⠡", "⠢", "⠣", "⠤", "⠥", "⠦", "⠧", "⠨", "⠩", "⠪", "⠫", "⠬", "⠭", "⠮", "⠯", "⠰", "⠱", "⠲", "⠳", "⠴", "⠵", "⠶", "⠷", "⠸", "⠹", "⠺", "⠻", "⠼", "⠽", "⠾", "⠿", "⡀", "⡁", "⡂", "⡃", "⡄", "⡅", "⡆", "⡇", "⡈", "⡉", "⡊", "⡋", "⡌", "⡍", "⡎", "⡏", "⡐", "⡑", "⡒", "⡓", "⡔", "⡕", "⡖", "⡗", "⡘", "⡙", "⡚", "⡛", "⡜", "⡝", "⡞", "⡟", "⡠", "⡡", "⡢", "⡣", "⡤", "⡥", "⡦", "⡧", "⡨", "⡩", "⡪", "⡫", "⡬", "⡭", "⡮", "⡯", "⡰", "⡱", "⡲", "⡳", "⡴", "⡵", "⡶", "⡷", "⡸", "⡹", "⡺", "⡻", "⡼", "⡽", "⡾", "⡿", "⢀", "⢁", "⢂", "⢃", "⢄", "⢅", "⢆", "⢇", "⢈", "⢉", "⢊", "⢋", "⢌", "⢍", "⢎", "⢏", "⢐", "⢑", "⢒", "⢓", "⢔", "⢕", "⢖", "⢗", "⢘", "⢙", "⢚", "⢛", "⢜", "⢝", "⢞", "⢟", "⢠", "⢡", "⢢", "⢣", "⢤", "⢥", "⢦", "⢧", "⢨", "⢩", "⢪", "⢫", "⢬", "⢭", "⢮", "⢯", "⢰", "⢱", "⢲", "⢳", "⢴", "⢵", "⢶", "⢷", "⢸", "⢹", "⢺", "⢻", "⢼", "⢽", "⢾", "⢿", "⣀", "⣁", "⣂", "⣃", "⣄", "⣅", "⣆", "⣇", "⣈", "⣉", "⣊", "⣋", "⣌", "⣍", "⣎", "⣏", "⣐", "⣑", "⣒", "⣓", "⣔", "⣕", "⣖", "⣗", "⣘", "⣙", "⣚", "⣛", "⣜", "⣝", "⣞", "⣟", "⣠", "⣡", "⣢", "⣣", "⣤", "⣥", "⣦", "⣧", "⣨", "⣩", "⣪", "⣫", "⣬", "⣭", "⣮", "⣯", "⣰", "⣱", "⣲", "⣳", "⣴", "⣵", "⣶", "⣷", "⣸", "⣹", "⣺", "⣻", "⣼", "⣽", "⣾", "⣿"};

	const int values[][4] = {{0x1, 0x2, 0x4, 0x40}, {0x8, 0x10, 0x20, 0x80}};

	const char *const fractions[] = {"¼", "½", "¾", "⅐", "⅑", "⅒", "⅓", "⅔", "⅕", "⅖", "⅗", "⅘", "⅙", "⅚", "⅛", "⅜", "⅝", "⅞"};
	const long double fractionvalues[] = {1.0L / 4.0L, 1.0L / 2.0L, 3.0L / 4.0L, 1.0L / 7.0L, 1.0L / 9.0L, 1.0L / 10.0L, 1.0L / 3.0L, 2.0L / 3.0L, 1.0L / 5.0L, 2.0L / 5.0L, 3.0L / 5.0L, 4.0L / 5.0L, 1.0L / 6.0L, 5.0L / 6.0L, 1.0L / 8.0L, 3.0L / 8.0L, 5.0L / 8.0L, 7.0L / 8.0L};

	const char *const constants[] = {"π", "e"};
	const long double constantvalues[] = {M_PI, M_E};

	const long double max_bit = scalbn(1.0L, LDBL_MANT_DIG - 1);
	const long double MAX = max_bit + (max_bit - 1);

	struct options
	{
		bool border = false;
		bool axis = true;
		bool axislabel = true;
		bool axistick = true;
		bool axisunitslabel = true;
		const char *title = nullptr;
		style_type style = style_light;
		color_type color = color_red;
		bool check = true;
	};

	const options defaultoptions;

	template <typename T>
	constexpr size_t size(const T &array)
	{
		return distance(begin(array), end(array));
	}

	// Number of columns needed to represent the string
	// Adapted from: https://stackoverflow.com/a/31124065
	int strcol(const char *const str)
	{
		size_t length = strlen(str);
		for (size_t i = 0; i < length; ++i)
			if (iscntrl(str[i]))
			{
				cerr << "\nError! Control character in string.\n";
				cout << "Control character: " << (int)str[i] << "\n";
			}

		length = mbstowcs(nullptr, str, 0);
		if (length == static_cast<size_t>(-1))
		{
			cerr << "\nError! mbstowcs failed. Invalid multibyte character.\n";
			exit(1);
		}
		++length;

		auto *wcstring = new wchar_t[length];

		if (mbstowcs(wcstring, str, length) == static_cast<size_t>(-1))
		{
			if (wcstring)
				delete[] wcstring;

			cerr << "\nError! mbstowcs failed. Invalid multibyte character.\n";
			exit(1);
		}

		int width = wcswidth(wcstring, length);
		if (width == -1)
		{
			cerr << "\nError! wcswidth failed. Nonprintable wide character.\n";
			exit(1);
		}

		if (wcstring)
			delete[] wcstring;

		return width;
	}

	// Word wrap
	// Source: https://gist.github.com/tdulcet/819821ca69501822ad3f84a060c640a0
	// Adapted from: https://stackoverflow.com/a/42016346 and https://stackoverflow.com/a/13094734
	string wrap(const char *const str, const size_t line_length)
	{
		string words = str;
		string wrapped;

		size_t index = 0;
		size_t linelen = 0;
		while (words[index] != '\0')
		{
			if (words[index] == '\n')
			{
				linelen = 0;
			}
			else if (isspace(words[index]))
			{
				size_t tempindex = index + 1;
				size_t templinelen = linelen;
				while (!isspace(words[tempindex]) and words[tempindex] != '\0')
				{
					++templinelen;

					++tempindex;
				}

				char temp[templinelen + 1];
				strncpy(temp, words.data() + (index - linelen), templinelen);
				temp[templinelen] = '\0';

				size_t width = strcol(temp);

				if (width >= line_length)
				{
					words[index] = '\n';
					linelen = 0;
				}
			}

			if (words[index] == '\t')
				linelen += 8 - (linelen % 8);
			else if (words[index] != '\n')
				++linelen;

			++index;
		}
		wrapped = words;
		return wrapped;
	}

	// Convert fractions and constants to Unicode characters
	size_t outputfraction(const long double number, ostringstream &strm)
	{
		bool output = false;

		const long double n = abs(number);
		if (n <= MAX)
		{
			long double intpart = 0;
			long double fractionpart = abs(modf(number, &intpart));

			for (size_t i = 0; i < graphs::size(fractions) and !output; ++i)
			{
				if (abs(fractionpart - fractionvalues[i]) <= DBL_EPSILON * n)
				{
					if (intpart == 0 and number < 0)
						strm << "-";
					else if (intpart != 0)
						strm << setprecision(LDBL_DIG) << intpart;

					strm << fractions[i];

					output = true;
				}
			}

			if (n > DBL_EPSILON)
			{
				for (size_t i = 0; i < graphs::size(constants) and !output; ++i)
				{
					if (abs(fmod(number, constantvalues[i])) <= DBL_EPSILON * n)
					{
						intpart = number / constantvalues[i];

						if (intpart == -1)
							strm << "-";
						else if (intpart != 1)
							strm << setprecision(LDBL_DIG) << intpart;

						strm << constants[i];

						output = true;
					}
				}
			}
		}

		if (!output)
			strm << number;

		size_t length = strcol(strm.str().c_str());

		return length;
	}

	// Output graph
	int graph(const size_t height, const size_t width, const long double xmin, const long double xmax, const long double ymin, const long double ymax, const vector<vector<unsigned short>> &array, const options &aoptions)
	{
		if (!graphs::size(array))
			return 1;

		const bool border = aoptions.border;
		const bool axis = aoptions.axis;
		const bool axislabel = aoptions.axislabel;
		const bool axistick = aoptions.axistick;
		const bool axisunitslabel = aoptions.axisunitslabel;
		const char *const title = aoptions.title;
		const style_type style = aoptions.style;

		if (height == 0)
			return 1;

		if (width == 0)
			return 1;

		struct winsize w;
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

		const size_t aheight = height / 4;
		const size_t awidth = width / 2;

		if (aoptions.check)
		{
			if (aheight > w.ws_row)
			{
				cerr << "The height of the graph (" << aheight << ") is greater then the height of the terminal (" << w.ws_row << ").\n";
				return 1;
			}

			if (awidth > w.ws_col)
			{
				cerr << "The width of the graph (" << awidth << ") is greater then the width of the terminal (" << w.ws_col << ").\n";
				return 1;
			}
		}

		if (xmin >= xmax)
		{
			cerr << "xmin must be less than xmax.\n";
			return 1;
		}

		if (ymin >= ymax)
		{
			cerr << "ymin must be less than ymax.\n";
			return 1;
		}

		const long double xstep = (xmax - xmin) / width;
		const long double ystep = (ymax - ymin) / height;
		const long double xaxis = xmin > 0 ? 0 : xmax < 0 ? width
														  : width - (xmax / xstep);
		const long double yaxis = ymin > 0 ? height : ymax < 0 ? 0
															   : ymax / ystep;
		const int xdivisor = 2 * 4 * ((width / 160) + 2);
		const int ydivisor = 2 * 4 * ((height / 160) + 2);

		setlocale(LC_ALL, "");

		if (title and title[0] != '\0')
			cout << wrap(title, awidth) << "\n";

		if (border)
		{
			cout << styles[style][2];

			for (size_t k = 0; k < awidth; ++k)
				cout << styles[style][0];

			cout << styles[style][4] << "\n";
		}

		for (size_t i = 0; i < height; i += 4)
		{
			const bool ayaxis = yaxis <= (height - 4) ? i <= yaxis and (i + 4) > yaxis : i < yaxis and (i + 4) >= yaxis;
			const bool yaxislabel = yaxis <= (height - 4) ? i <= (yaxis + 4) and (i + 4) > (yaxis + 4) : i < (yaxis - 4) and (i + 4) >= (yaxis - 4);

			ostringstream ylabelstrm;
			size_t ylabellength = 0;

			if (axis and axislabel and axistick and axisunitslabel and yaxis >= 0 and yaxis <= height)
			{
				bool output = false;
				long double label = 0;
				int adivisor = i < yaxis ? -ydivisor : ydivisor;

				for (long double k = yaxis + adivisor; (i < yaxis ? k >= i : k < (i + 4)) and i >= 4 and !output; k += adivisor)
				{
					if (i <= k and (i + 4) > k)
					{
						label = ymax - ((k > height ? height : k) * ystep);

						output = true;
					}
				}

				if (output)
				{
					ylabellength = outputfraction(label, ylabelstrm);
					ylabellength *= 2;
				}
			}

			if (border)
				cout << styles[style][1];

			for (size_t j = 0; j < width; j += 2)
			{
				const bool axaxis = xaxis >= 2 ? j < xaxis and (j + 2) >= xaxis : j <= xaxis and (j + 2) > xaxis;
				const bool xaxislabel = xaxis >= 2 ? j < (xaxis - 2) and (j + 2) >= (xaxis - 2) : j <= (xaxis + 2) and (j + 2) > (xaxis + 2);

				bool output = false;

				if (axis)
				{
					if (axaxis and ayaxis)
					{
						cout << styles[style][6];
						output = true;
					}
					else if (axaxis)
					{
						if (i == 0)
						{
							cout << styles[style][4];
							output = true;
						}
						else if (i >= (height - 4))
						{
							cout << styles[style][10];
							output = true;
						}
						else if (axislabel and axistick)
						{
							int adivisor = i < yaxis ? -ydivisor : ydivisor;

							for (long double k = yaxis + adivisor; (i < yaxis ? k >= i : k < (i + 4)) and i >= 4 and !output; k += adivisor)
							{
								if (i <= k and (i + 4) > k)
								{
									cout << styles[style][xaxis >= 2 ? 7 : 5];
									output = true;
								}
							}
						}
						if (!output)
						{
							cout << styles[style][1];
							output = true;
						}
					}
					else if (ayaxis)
					{
						if (j == 0)
						{
							cout << styles[style][2];
							output = true;
						}
						else if (j >= (width - 2))
						{
							cout << styles[style][4];
							output = true;
						}
						else if (axislabel and axistick)
						{
							int adivisor = j < xaxis ? -xdivisor : xdivisor;

							for (long double k = xaxis + adivisor; (j < xaxis ? k >= j : k < (j + 2)) and j < (width - (2 * 2)) and !output; k += adivisor)
							{
								if (j <= k and (j + 2) > k)
								{
									cout << styles[style][yaxis <= (height - 4) ? 3 : 9];
									output = true;
								}
							}
						}
						if (!output)
						{
							cout << styles[style][0];
							output = true;
						}
					}
					else if (yaxislabel and xaxislabel and axislabel and axistick and axisunitslabel and ymin <= 0 and ymax >= 0 and xmin <= 0 and xmax >= 0)
					{
						cout << "0";
						output = true;
					}
					else if ((xaxis <= (width - 2) ? j >= (width - 2) : j == 0) and yaxislabel and axislabel)
					{
						cout << "x";
						output = true;
					}
					else if (yaxislabel and axislabel and axistick and axisunitslabel)
					{
						long double label = 0;
						int adivisor = j < xaxis ? -xdivisor : xdivisor;
						if (j < xaxis)
							j += 2;

						for (long double k = xaxis + adivisor; (j < xaxis ? k >= j : k < (j + 2)) and j < (width - 2) and !output; k += adivisor)
						{
							if (j <= k and (j + 2) > k)
							{
								label = ((k > width ? width : k) * xstep) + xmin;

								output = true;
							}
						}

						if (adivisor < 0)
							j -= 2;

						if (output)
						{
							output = false;

							ostringstream strm;
							size_t length = outputfraction(label, strm);
							length *= 2;
							if ((j >= xaxis or (j + length) < (ymin <= 0 and ymax >= 0 and xmin <= 0 and xmax >= 0 ? xaxis - 4 : xaxis)) and (j + length) < (width - 2) and (xaxis <= (width - 2) or j > 2))
							{
								cout << strm.str();

								if (length > 2)
									j += length - 2;

								if (adivisor < 0)
									output = true;
								else
									j += 2;
							}
						}
					}
					else if ((yaxis >= 4 ? i == 0 : i >= (height - 4)) and xaxislabel and axislabel)
					{
						cout << "y";
						output = true;
					}
					else if (ylabellength and (xaxis < 2 ? xaxislabel : j < (xaxis - ylabellength) and (j + 2) >= (xaxis - ylabellength)) and (yaxis >= 4 or i < (height - 4)) and axislabel and axistick and axisunitslabel)
					{
						cout << ylabelstrm.str();
						output = true;
						if (ylabellength > 2)
							j += ylabellength - 2;
					}
				}

				if (!output)
				{
					size_t dot = 0;
					unsigned short color = 0;

					for (size_t k = 0; k < 2 and k < (width - j); ++k)
					{
						for (size_t l = 0; l < 4 and l < (height - i); ++l)
						{
							const unsigned short value = array[j + k][i + l];
							if (value)
								dot += values[k][l];
							if (color)
							{
								if (value and color != value)
									color = 1;
							}
							else
								color = value;
						}
					}

					if (color)
						--color;

					if (color)
						cout << colors[color];

					cout << dots[dot];

					if (color)
						cout << colors[0];
				}
			}

			if (border)
				cout << styles[style][1];

			if (i < (height - 4) or border)
				cout << "\n";
		}

		if (border)
		{
			cout << styles[style][8];

			for (size_t k = 0; k < awidth; ++k)
				cout << styles[style][0];

			cout << styles[style][10];
		}

		cout << endl;

		return 0;
	}

	// Convert one or more arrays to graph and output
	template <typename T>
	int arrays(size_t height, size_t width, long double xmin, long double xmax, long double ymin, long double ymax, const T &arrays, const options &aoptions = defaultoptions)
	{
		if (!graphs::size(arrays))
			return 1;

		if (!all_of(begin(arrays), end(arrays), [](const auto &array)
					{ return all_of(begin(array), end(array), [](const auto &x)
									{ return graphs::size(x) == 2; }); }))
		{
			cerr << "Error: The arrays must have two columns.\n";
			return 1;
		}

		const color_type color = aoptions.color;

		struct winsize w;
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

		if (height == 0)
			height = w.ws_row * 4;

		if (width == 0)
			width = w.ws_col * 2;

		if (aoptions.check)
		{
			const size_t aheight = height / 4;
			const size_t awidth = width / 2;

			if (aheight > w.ws_row)
			{
				cerr << "The height of the graph (" << aheight << ") is greater then the height of the terminal (" << w.ws_row << ").\n";
				return 1;
			}

			if (awidth > w.ws_col)
			{
				cerr << "The width of the graph (" << awidth << ") is greater then the width of the terminal (" << w.ws_col << ").\n";
				return 1;
			}
		}

		if (xmin == 0 and xmax == 0)
		{
			const auto compare = [](const auto &a, const auto &b)
			{ return a[0] < b[0]; };
			const auto result = accumulate(begin(arrays), end(arrays), make_pair(arrays[0][0], arrays[0][0]), [compare](const auto &current, const auto &array)
										   { const auto minmax = minmax_element(begin(array), end(array), compare); return make_pair(min(current.first, *minmax.first, compare), max(current.second, *minmax.second, compare)); });
			xmin = result.first[0];
			xmax = result.second[0];
		}

		if (ymin == 0 and ymax == 0)
		{
			const auto compare = [](const auto &a, const auto &b)
			{ return a[1] < b[1]; };
			const auto result = accumulate(begin(arrays), end(arrays), make_pair(arrays[0][0], arrays[0][0]), [compare](const auto &current, const auto &array)
										   { const auto minmax = minmax_element(begin(array), end(array), compare); return make_pair(min(current.first, *minmax.first, compare), max(current.second, *minmax.second, compare)); });
			ymin = result.first[1];
			ymax = result.second[1];
		}

		if (xmin >= xmax)
		{
			cerr << "xmin must be less than xmax.\n";
			return 1;
		}

		if (ymin >= ymax)
		{
			cerr << "ymin must be less than ymax.\n";
			return 1;
		}

		const long double xstep = (xmax - xmin) / width;
		const long double ystep = (ymax - ymin) / height;
		const long double xaxis = width - (xmax / xstep);
		const long double yaxis = ymax / ystep;

		vector<vector<unsigned short>> aarray(width, vector<unsigned short>(height, 0));

		for (size_t j = 0; j < graphs::size(arrays); ++j)
		{
			const auto &array = arrays[j];
			const unsigned int acolor = graphs::size(arrays) == 1 ? color + 1 : (j % (graphs::size(colors) - 2)) + 3;

			for (size_t i = 0; i < graphs::size(array); ++i)
			{
				const auto &x = array[i][0], &y = array[i][1];

				if (x >= xmin and x < xmax and y >= ymin and y < ymax)
				{
					const size_t ax = (x / xstep) + xaxis;
					const size_t ay = (yaxis - (y / ystep)) - 1;

					if (aarray[ax][ay])
					{
						if (aarray[ax][ay] != acolor)
							aarray[ax][ay] = 1;
					}
					else
						aarray[ax][ay] = acolor;
				}
			}
		}

		return graph(height, width, xmin, xmax, ymin, ymax, aarray, aoptions);
	}

	// Convert single array to graph and output
	template <typename T>
	int array(size_t height, size_t width, long double xmin, long double xmax, long double ymin, long double ymax, const T &aarray, const options &aoptions = defaultoptions)
	{
		const std::array<T, 1> aaarray = {aarray};

		return arrays(height, width, xmin, xmax, ymin, ymax, aaarray, aoptions);
	}

	// Convert single array to graph and output
	template <typename T>
	int array(size_t height, size_t width, long double xmin, long double xmax, long double ymin, long double ymax, const size_t rows, T **aarray, const options &aoptions = defaultoptions)
	{
		if (rows == 0)
			return 1;

		const size_t columns = 2;
		vector<std::array<T, columns>> aaarray(rows);
		for (size_t i = 0; i < rows; ++i)
			copy(aarray[i], aarray[i] + columns, aaarray[i].begin());

		return array(height, width, xmin, xmax, ymin, ymax, aaarray, aoptions);
	}

	// Convert one or more functions to graph and output
	template <typename T>
	int functions(size_t height, size_t width, const long double xmin, const long double xmax, const long double ymin, const long double ymax, const size_t numfunctions, function<T(T)> functions[], const options &aoptions = defaultoptions)
	{
		const color_type color = aoptions.color;

		if (numfunctions == 0)
			return 1;

		struct winsize w;
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

		if (height == 0)
			height = w.ws_row * 4;

		if (width == 0)
			width = w.ws_col * 2;

		if (aoptions.check)
		{
			const size_t aheight = height / 4;
			const size_t awidth = width / 2;

			if (aheight > w.ws_row)
			{
				cerr << "The height of the graph (" << aheight << ") is greater then the height of the terminal (" << w.ws_row << ").\n";
				return 1;
			}

			if (awidth > w.ws_col)
			{
				cerr << "The width of the graph (" << awidth << ") is greater then the width of the terminal (" << w.ws_col << ").\n";
				return 1;
			}
		}

		if (xmin >= xmax)
		{
			cerr << "xmin must be less than xmax.\n";
			return 1;
		}

		if (ymin >= ymax)
		{
			cerr << "ymin must be less than ymax.\n";
			return 1;
		}

		const size_t rows = width;

		const long double xstep = (xmax - xmin) / width;
		const long double ystep = (ymax - ymin) / height;
		const long double xaxis = width - (xmax / xstep);
		const long double yaxis = ymax / ystep;
		const size_t xres = 2;

		vector<vector<unsigned short>> array(width, vector<unsigned short>(height, 0));

		for (size_t j = 0; j < numfunctions; ++j)
		{
			unsigned short acolor = numfunctions == 1 ? color + 1 : (j % (graphs::size(colors) - 2)) + 3;

			for (size_t i = 0; i < rows * xres; ++i)
			{
				T x = ((i / (long double)xres) * xstep) + xmin;
				T y = (functions[j])(x);

				if (x >= xmin and x < xmax and y >= ymin and y < ymax)
				{
					const size_t ax = (x / xstep) + xaxis;
					const size_t ay = (yaxis - (y / ystep)) - 1;

					if (array[ax][ay])
					{
						if (array[ax][ay] != acolor)
							array[ax][ay] = 1;
					}
					else
						array[ax][ay] = acolor;
				}
			}
		}

		return graph(height, width, xmin, xmax, ymin, ymax, array, aoptions);
	}

	// Convert single function to function array and output
	template <typename T>
	int function(size_t height, size_t width, const long double xmin, const long double xmax, const long double ymin, const long double ymax, const function<T(T)> &afunction, const options &aoptions = defaultoptions)
	{
		std::function<T(T)> afunctions[] = {afunction};

		return functions(height, width, xmin, xmax, ymin, ymax, 1, afunctions, aoptions);
	}

	// Convert single function to function array and output
	template <typename T>
	int function(size_t height, size_t width, const long double xmin, const long double xmax, const long double ymin, const long double ymax, T afunction(T), const options &aoptions = defaultoptions)
	{
		std::function<T(T)> afunctions[] = {afunction};

		return functions(height, width, xmin, xmax, ymin, ymax, 1, afunctions, aoptions);
	}

}
