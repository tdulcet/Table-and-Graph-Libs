// Teal Dulcet, CS546

#include <iostream>
#include <sstream>
#include <cstring>
#include <cmath>
#include <limits>
#include <cfloat>
#include <iomanip>
#include <cwchar>
#include <clocale>
#include <cstdlib>
#include <sys/ioctl.h>
#include <unistd.h>

using namespace std;

const char *const styles[][11] = {
	{"-", "|", "+", "+", "+", "+", "+", "+", "+", "+", "+"}, //ASCII
	{"—", "|", "+", "+", "+", "+", "+", "+", "+", "+", "+"}, //Basic
	{"─", "│", "┌", "┬", "┐", "├", "┼", "┤", "└", "┴", "┘"}, //Light
	{"━", "┃", "┏", "┳", "┓", "┣", "╋", "┫", "┗", "┻", "┛"}, //Heavy
	{"═", "║", "╔", "╦", "╗", "╠", "╬", "╣", "╚", "╩", "╝"}, //Double
	{"╌", "╎", "┌", "┬", "┐", "├", "┼", "┤", "└", "┴", "┘"}, //Light Dashed
	{"╍", "╏", "┏", "┳", "┓", "┣", "╋", "┫", "┗", "┻", "┛"}	 //Heavy Dashed
};
// {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "}};//No border

const char *const colors[] = {"\e[39m", "\e[30m", "\e[31m", "\e[32m", "\e[33m", "\e[34m", "\e[35m", "\e[36m", "\e[37m", "\e[90m", "\e[91m", "\e[92m", "\e[93m", "\e[94m", "\e[95m", "\e[96m", "\e[97m"};

const char *const dots[] = {"⠀", "⠁", "⠂", "⠃", "⠄", "⠅", "⠆", "⠇", "⠈", "⠉", "⠊", "⠋", "⠌", "⠍", "⠎", "⠏", "⠐", "⠑", "⠒", "⠓", "⠔", "⠕", "⠖", "⠗", "⠘", "⠙", "⠚", "⠛", "⠜", "⠝", "⠞", "⠟", "⠠", "⠡", "⠢", "⠣", "⠤", "⠥", "⠦", "⠧", "⠨", "⠩", "⠪", "⠫", "⠬", "⠭", "⠮", "⠯", "⠰", "⠱", "⠲", "⠳", "⠴", "⠵", "⠶", "⠷", "⠸", "⠹", "⠺", "⠻", "⠼", "⠽", "⠾", "⠿", "⡀", "⡁", "⡂", "⡃", "⡄", "⡅", "⡆", "⡇", "⡈", "⡉", "⡊", "⡋", "⡌", "⡍", "⡎", "⡏", "⡐", "⡑", "⡒", "⡓", "⡔", "⡕", "⡖", "⡗", "⡘", "⡙", "⡚", "⡛", "⡜", "⡝", "⡞", "⡟", "⡠", "⡡", "⡢", "⡣", "⡤", "⡥", "⡦", "⡧", "⡨", "⡩", "⡪", "⡫", "⡬", "⡭", "⡮", "⡯", "⡰", "⡱", "⡲", "⡳", "⡴", "⡵", "⡶", "⡷", "⡸", "⡹", "⡺", "⡻", "⡼", "⡽", "⡾", "⡿", "⢀", "⢁", "⢂", "⢃", "⢄", "⢅", "⢆", "⢇", "⢈", "⢉", "⢊", "⢋", "⢌", "⢍", "⢎", "⢏", "⢐", "⢑", "⢒", "⢓", "⢔", "⢕", "⢖", "⢗", "⢘", "⢙", "⢚", "⢛", "⢜", "⢝", "⢞", "⢟", "⢠", "⢡", "⢢", "⢣", "⢤", "⢥", "⢦", "⢧", "⢨", "⢩", "⢪", "⢫", "⢬", "⢭", "⢮", "⢯", "⢰", "⢱", "⢲", "⢳", "⢴", "⢵", "⢶", "⢷", "⢸", "⢹", "⢺", "⢻", "⢼", "⢽", "⢾", "⢿", "⣀", "⣁", "⣂", "⣃", "⣄", "⣅", "⣆", "⣇", "⣈", "⣉", "⣊", "⣋", "⣌", "⣍", "⣎", "⣏", "⣐", "⣑", "⣒", "⣓", "⣔", "⣕", "⣖", "⣗", "⣘", "⣙", "⣚", "⣛", "⣜", "⣝", "⣞", "⣟", "⣠", "⣡", "⣢", "⣣", "⣤", "⣥", "⣦", "⣧", "⣨", "⣩", "⣪", "⣫", "⣬", "⣭", "⣮", "⣯", "⣰", "⣱", "⣲", "⣳", "⣴", "⣵", "⣶", "⣷", "⣸", "⣹", "⣺", "⣻", "⣼", "⣽", "⣾", "⣿"};

const int values[][4] = {{0x1, 0x2, 0x4, 0x40}, {0x8, 0x10, 0x20, 0x80}};

const char *const fractions[] = {"¼", "½", "¾", "⅐", "⅑", "⅒", "⅓", "⅔", "⅕", "⅖", "⅗", "⅘", "⅙", "⅚", "⅛", "⅜", "⅝", "⅞"};

const long double fractionvalues[] = {1.0L / 4.0L, 1.0L / 2.0L, 3.0L / 4.0L, 1.0L / 7.0L, 1.0L / 9.0L, 1.0L / 10.0L, 1.0L / 3.0L, 2.0L / 3.0L, 1.0L / 5.0L, 2.0L / 5.0L, 3.0L / 5.0L, 4.0L / 5.0L, 1.0L / 6.0L, 5.0L / 6.0L, 1.0L / 8.0L, 3.0L / 8.0L, 5.0L / 8.0L, 7.0L / 8.0L};

struct graphoptions
{
	bool border;
	bool axislabel;
	bool axisunitslabel;
	char *title;
	unsigned int style;
	unsigned int color;
	graphoptions(void);
	~graphoptions(void);
};

graphoptions::graphoptions(void)
{
	border = true;
	axislabel = true;
	axisunitslabel = true;
	style = 2;
	color = 2;
	title = NULL;
}

graphoptions::~graphoptions(void)
{
}

const graphoptions graphdefaultoptions;

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

	length = mbstowcs(NULL, str, 0);
	if (length == (size_t)-1)
	{
		cerr << "\nError! mbstowcs failed. Invalid multibyte character.\n";
		exit(1);
	}
	++length;

	wchar_t *wcstring = new wchar_t[length];

	if (mbstowcs(wcstring, str, length) == (size_t)-1)
	{
		if (wcstring != NULL)
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

	if (wcstring != NULL)
		delete[] wcstring;

	return width;
}

// Word wrap
// Source: https://gist.github.com/tdulcet/819821ca69501822ad3f84a060c640a0
// Adapted from: https://stackoverflow.com/a/42016346 and https://stackoverflow.com/a/13094734
string wrap(const char *const str, const size_t line_length)
{
	char words[strlen(str) + 1];
	strcpy(words, str);
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
			strncpy(temp, words + (index - linelen), templinelen);
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
size_t outputlabel(const long double label, ostringstream &strm)
{
	bool output = false;

	long double intpart = 0;
	long double fractionpart = abs(modf(label, &intpart));

	for (unsigned int i = 0; i < (sizeof fractions / sizeof fractions[0]) and !output; ++i)
	{
		if (abs(fractionpart - fractionvalues[i]) < DBL_EPSILON)
		{
			if (intpart != 0)
				strm << intpart;

			strm << fractions[i];

			output = true;
		}
	}

	if (abs(label) >= DBL_EPSILON)
	{
		if (!output and fmod(label, M_PI) == 0)
		{
			const char symbol[] = "π";

			intpart = label / M_PI;

			if (intpart == -1)
				strm << "-";
			else if (intpart != 1)
				strm << intpart;

			strm << symbol;

			output = true;
		}
		else if (!output and fmod(label, M_E) == 0)
		{
			const char symbol[] = "e";

			intpart = label / M_E;

			if (intpart == -1)
				strm << "-";
			else if (intpart != 1)
				strm << intpart;

			strm << symbol;

			output = true;
		}
	}

	if (!output)
		strm << label;

	size_t length = strcol(strm.str().c_str());

	return length;
}

// Output graph
int graph(const size_t height, const size_t width, const long double xmin, const long double xmax, const long double ymin, const long double ymax, unsigned short **array, const graphoptions &aoptions)
{
	if (array == NULL)
		return 1;

	const bool border = aoptions.border;
	const bool axislabel = aoptions.axislabel;
	const bool axisunitslabel = aoptions.axisunitslabel;
	const char *const title = aoptions.title;
	const unsigned int style = aoptions.style;

	if (style >= (sizeof styles / sizeof styles[0]))
		return 1;

	if (height == 0)
		return 1;

	if (width == 0)
		return 1;

	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	const int aheight = height / 4;
	const int awidth = width / 2;

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

	const long double xscl = width / (xmax - xmin);
	const long double yscl = height / (ymax - ymin);
	const long double xaxis = width - (xmax * xscl);
	const long double yaxis = ymax * yscl;
	const int divisor = 2 * 4 * ((width / 160.0) > 1 ? (width / 160) + 1 : 1);

	setlocale(LC_CTYPE, "");

	if (title != NULL and title[0] != '\0')
		cout << wrap(title, w.ws_col) << "\n";

	for (unsigned int i = 0; i < height; i += 4)
	{
		const bool ayaxis = (i <= yaxis and (i + 4) > yaxis);
		const bool yaxislabel = (i <= (yaxis + 4) and (i + 4) > (yaxis + 4));

		ostringstream ylabelstrm;
		size_t ylabellength = 0;

		if (border and axislabel and axisunitslabel)
		{
			bool output = false;
			long double label;
			int adivisor = divisor;
			if (i < yaxis)
				adivisor = -adivisor;

			for (long double k = yaxis + adivisor; ((i < yaxis and k >= i) or (i > yaxis and k < (i + 4))) and (i >= 4 or !axislabel) and !output; k += adivisor)
			{
				if (i <= k and (i + 4) > k)
				{
					label = ymax - (k / yscl);

					output = true;
				}
			}

			if (output)
			{
				ylabellength = outputlabel(label, ylabelstrm);
				ylabellength *= 2;
			}
		}

		for (unsigned int j = 0; j < width; j += 2)
		{
			const bool axaxis = (j <= xaxis and (j + 2) > xaxis);
			const bool xaxislabel = (j <= (xaxis - 2) and (j + 2) > (xaxis - 2));

			bool output = false;

			if (border)
			{
				if (axaxis and ayaxis)
				{
					cout << styles[style][6];
					output = true;
				}
				else if (axaxis)
				{
					if (axislabel and axisunitslabel)
					{
						int adivisor = divisor;
						if (i < yaxis)
							adivisor = -adivisor;

						for (long double k = yaxis + adivisor; ((i < yaxis and k >= i) or (i > yaxis and k < (i + 4))) and (i >= 4 or !axislabel) and !output; k += adivisor)
						{
							if (i <= k and (i + 4) > k)
							{
								cout << styles[style][7];
								output = true;
							}
						}
					}
					if (!output)
					{
						if (i == 0)
							cout << styles[style][4];
						else if (i >= (height - 4))
							cout << styles[style][10];
						else
							cout << styles[style][1];
						output = true;
					}
				}
				else if (ayaxis)
				{
					if (axislabel and axisunitslabel)
					{
						int adivisor = divisor;
						if (j < xaxis)
							adivisor = -adivisor;

						for (long double k = xaxis + adivisor; ((j < xaxis and k >= j) or (j > xaxis and k < (j + 2))) and (j < (width - 4) or !axislabel) and !output; k += adivisor)
						{
							if (j <= k and (j + 2) > k)
							{
								cout << styles[style][3];
								output = true;
							}
						}
					}
					if (!output)
					{
						if (j == 0)
							cout << styles[style][2];
						else if (j >= (width - 2))
							cout << styles[style][4];
						else
							cout << styles[style][0];
						output = true;
					}
				}
				else if (yaxislabel and xaxislabel and axislabel and axisunitslabel)
				{
					cout << "0";
					output = true;
				}
				else if (j >= (width - 2) and yaxislabel and axislabel)
				{
					cout << "x";
					output = true;
				}
				else if (yaxislabel and axislabel and axisunitslabel)
				{
					long double label;
					int adivisor = divisor;
					if (j < xaxis)
					{
						adivisor = -adivisor;
						j += 2;
					}

					for (long double k = xaxis + adivisor; ((j < xaxis and k >= j) or (j > xaxis and k < (j + 2))) and j < (width - 2) and !output; k += adivisor)
					{
						if (j <= k and (j + 2) > k)
						{
							label = (k / xscl) + xmin;

							output = true;
						}
					}

					if (adivisor < 0)
						j -= 2;

					if (output)
					{
						output = false;

						ostringstream strm;
						size_t length = outputlabel(label, strm);
						length *= 2;
						if ((j >= xaxis or (j + length) < (xaxis - 4)) and (j + length) < (width - 2))
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
				else if (i == 0 and xaxislabel and axislabel)
				{
					cout << "y";
					output = true;
				}
				else if ((j <= (xaxis - ylabellength) and (j + 2) > (xaxis - ylabellength)) and axislabel and axisunitslabel)
				{
					cout << ylabelstrm.str();
					output = true;
					if (ylabellength > 2)
						j += ylabellength - 2;
				}
			}

			if (!output)
			{
				unsigned int dot = 0;
				unsigned short color = 0;

				for (unsigned int k = 0; k < 2 and k < (width - j); ++k)
				{
					for (unsigned int l = 0; l < 4 and l < (height - i); ++l)
					{
						dot += (array[j + k][i + l] ? 1 : 0) * values[k][l];
						if (color)
						{
							if (array[j + k][i + l] and color != array[j + k][i + l])
								color = 1;
						}
						else
							color = array[j + k][i + l];
					}
				}

				if (color)
					--color;

				if (color)
					cout << colors[color];

				cout << "\e[1m" << dots[dot] << "\e[22m";

				if (color)
					cout << colors[0];
			}
		}

		cout << "\n";
	}

	cout << endl;

	return 0;
}

// Convert array to graph and output
template <typename T>
int graph(size_t height, size_t width, long double xmin, long double xmax, long double ymin, long double ymax, const size_t rows, T **array, const graphoptions &aoptions)
{
	if (rows == 0)
		return 1;

	if (array == NULL)
		return 1;

	const unsigned int color = aoptions.color;

	if (color >= (sizeof colors / sizeof colors[0]))
		return 1;

	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	if (height == 0)
		height = w.ws_row * 4;

	if (width == 0)
		width = w.ws_col * 2;

	const int aheight = height / 4;
	const int awidth = width / 2;

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

	if (xmin == 0 and xmax == 0)
	{
		xmin = numeric_limits<T>::max();
		xmax = numeric_limits<T>::min();

		for (unsigned int i = 0; i < rows; ++i)
		{
			if (array[i][0] < xmin)
				xmin = array[i][0];

			if (array[i][0] > xmax)
				xmax = array[i][0];
		}
	}

	if (ymin == 0 and ymax == 0)
	{
		ymin = numeric_limits<T>::max();
		ymax = numeric_limits<T>::min();

		for (unsigned int i = 0; i < rows; ++i)
		{
			if (array[i][1] < ymin)
				ymin = array[i][1];

			if (array[i][1] > ymax)
				ymax = array[i][1];
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

	const long double xscl = width / (xmax - xmin);
	const long double yscl = height / (ymax - ymin);
	const long double xaxis = width - (xmax * xscl);
	const long double yaxis = ymax * yscl;

	unsigned short **aarray;
	aarray = new unsigned short *[width];
	for (unsigned int i = 0; i < width; ++i)
		aarray[i] = new unsigned short[height];

	for (unsigned int i = 0; i < width; ++i)
		for (unsigned int j = 0; j < height; ++j)
			aarray[i][j] = 0;

	for (unsigned int i = 0; i < rows; ++i)
	{
		if (array[i][0] >= xmin and array[i][0] < xmax and array[i][1] >= ymin and array[i][1] < ymax)
		{
			const long long x = (array[i][0] * xscl) + xaxis;
			const long long y = (yaxis - (array[i][1] * yscl)) - 1;

			aarray[x][y] = color + 1;
		}
	}

	int code = graph(height, width, xmin, xmax, ymin, ymax, aarray, aoptions);

	if (aarray != NULL)
	{
		for (unsigned int i = 0; i < width; ++i)
			delete[] aarray[i];

		delete[] aarray;
	}

	return code;
}

// Convert one or more functions to graph and output
template <typename T>
int graph(size_t height, size_t width, const long double xmin, const long double xmax, const long double ymin, const long double ymax, const size_t numfunctions, T (*functions[])(T), const graphoptions &aoptions)
{
	const unsigned int color = aoptions.color;

	if (color >= (sizeof colors / sizeof colors[0]))
		return 1;

	if (numfunctions == 0)
		return 1;

	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	if (height == 0)
		height = w.ws_row * 4;

	if (width == 0)
		width = w.ws_col * 2;

	const int aheight = height / 4;
	const int awidth = width / 2;

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

	const long double xscl = width / (xmax - xmin);
	const long double yscl = height / (ymax - ymin);
	const long double xaxis = width - (xmax * xscl);
	const long double yaxis = ymax * yscl;

	unsigned short **array;
	array = new unsigned short *[width];
	for (unsigned int i = 0; i < width; ++i)
		array[i] = new unsigned short[height];

	for (unsigned int i = 0; i < width; ++i)
		for (unsigned int j = 0; j < height; ++j)
			array[i][j] = 0;

	for (unsigned int j = 0; j < numfunctions; ++j)
	{
		unsigned short acolor = numfunctions == 1 ? color + 1 : (j % ((sizeof colors / sizeof colors[0]) - 2)) + 3;

		for (long double i = 0; i < rows; i += 0.5)
		{
			T x = (i / xscl) + xmin;
			T y = (functions[j])(x);

			if (x >= xmin and x < xmax and y >= ymin and y < ymax)
			{
				const long long ax = (x * xscl) + xaxis;
				const long long ay = (yaxis - (y * yscl)) - 1;

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

	int code = graph(height, width, xmin, xmax, ymin, ymax, array, aoptions);

	if (array != NULL)
	{
		for (unsigned int i = 0; i < width; ++i)
			delete[] array[i];

		delete[] array;
	}

	return code;
}

// Convert single function to function array and output
template <typename T>
int graph(size_t height, size_t width, const long double xmin, const long double xmax, const long double ymin, const long double ymax, T afunction(T), const graphoptions &aoptions)
{
	T(*functions[])
	(T) = {afunction};

	return graph(height, width, xmin, xmax, ymin, ymax, 1, functions, aoptions);
}
