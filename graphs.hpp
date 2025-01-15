// Teal Dulcet, CS546
#pragma once
#include <bitset>
#include <cassert>
#include <iostream>
#include <memory>
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
#include <chrono>
#include <sys/ioctl.h>
#include <unistd.h>

#ifdef TGLIB_GRAPHS_NAMESPACE
namespace TGLIB_GRAPHS_NAMESPACE
{
#else
namespace graphs
{
#endif
	using namespace std;

	enum style_type
	{
		style_ASCII,
		style_basic,
		style_light,
		style_heavy,
		style_double,
		style_arc,
		style_light_dashed,
		style_heavy_dashed
	};

	enum style_type const style_types[] = {style_ASCII, style_basic, style_light, style_heavy, style_double, style_arc, style_light_dashed, style_heavy_dashed};

	const char *const styles[][11] = {
		{"-", "|", "+", "+", "+", "+", "+", "+", "+", "+", "+"}, // ASCII
		{"—", "|", "+", "+", "+", "+", "+", "+", "+", "+", "+"}, // Basic
		{"─", "│", "┌", "┬", "┐", "├", "┼", "┤", "└", "┴", "┘"}, // Light
		{"━", "┃", "┏", "┳", "┓", "┣", "╋", "┫", "┗", "┻", "┛"}, // Heavy
		{"═", "║", "╔", "╦", "╗", "╠", "╬", "╣", "╚", "╩", "╝"}, // Double
		{"─", "│", "╭", "┬", "╮", "├", "┼", "┤", "╰", "┴", "╯"}, // Light Arc
		{"╌", "┊", "┌", "┬", "┐", "├", "┼", "┤", "└", "┴", "┘"}, // Light Dashed
		{"╍", "┋", "┏", "┳", "┓", "┣", "╋", "┫", "┗", "┻", "┛"}	 // Heavy Dashed
		// {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "}	 // No border
	};

	enum color_type: uint8_t
	{
		color_default,
		color_black,
		color_red,
		color_green,
		color_yellow,
		color_blue,
		color_magenta,
		color_cyan,
		color_white,
		color_gray,
		color_bright_red,
		color_bright_green,
		color_bright_yellow,
		color_bright_blue,
		color_bright_magenta,
		color_bright_cyan,
		color_bright_white
	};

	enum color_type const color_types[] = {color_default, color_black, color_red, color_green, color_yellow, color_blue, color_magenta, color_cyan, color_white, color_gray, color_bright_red, color_bright_green, color_bright_yellow, color_bright_blue, color_bright_magenta, color_bright_cyan, color_bright_white};

	const char *const colors[] = {"\e[39m", "\e[30m", "\e[31m", "\e[32m", "\e[33m", "\e[34m", "\e[35m", "\e[36m", "\e[37m", "\e[90m", "\e[91m", "\e[92m", "\e[93m", "\e[94m", "\e[95m", "\e[96m", "\e[97m"};

	const char *const dots[] = {"⠀", "⠁", "⠂", "⠃", "⠄", "⠅", "⠆", "⠇", "⠈", "⠉", "⠊", "⠋", "⠌", "⠍", "⠎", "⠏", "⠐", "⠑", "⠒", "⠓", "⠔", "⠕", "⠖", "⠗", "⠘", "⠙", "⠚", "⠛", "⠜", "⠝", "⠞", "⠟", "⠠", "⠡", "⠢", "⠣", "⠤", "⠥", "⠦", "⠧", "⠨", "⠩", "⠪", "⠫", "⠬", "⠭", "⠮", "⠯", "⠰", "⠱", "⠲", "⠳", "⠴", "⠵", "⠶", "⠷", "⠸", "⠹", "⠺", "⠻", "⠼", "⠽", "⠾", "⠿", "⡀", "⡁", "⡂", "⡃", "⡄", "⡅", "⡆", "⡇", "⡈", "⡉", "⡊", "⡋", "⡌", "⡍", "⡎", "⡏", "⡐", "⡑", "⡒", "⡓", "⡔", "⡕", "⡖", "⡗", "⡘", "⡙", "⡚", "⡛", "⡜", "⡝", "⡞", "⡟", "⡠", "⡡", "⡢", "⡣", "⡤", "⡥", "⡦", "⡧", "⡨", "⡩", "⡪", "⡫", "⡬", "⡭", "⡮", "⡯", "⡰", "⡱", "⡲", "⡳", "⡴", "⡵", "⡶", "⡷", "⡸", "⡹", "⡺", "⡻", "⡼", "⡽", "⡾", "⡿", "⢀", "⢁", "⢂", "⢃", "⢄", "⢅", "⢆", "⢇", "⢈", "⢉", "⢊", "⢋", "⢌", "⢍", "⢎", "⢏", "⢐", "⢑", "⢒", "⢓", "⢔", "⢕", "⢖", "⢗", "⢘", "⢙", "⢚", "⢛", "⢜", "⢝", "⢞", "⢟", "⢠", "⢡", "⢢", "⢣", "⢤", "⢥", "⢦", "⢧", "⢨", "⢩", "⢪", "⢫", "⢬", "⢭", "⢮", "⢯", "⢰", "⢱", "⢲", "⢳", "⢴", "⢵", "⢶", "⢷", "⢸", "⢹", "⢺", "⢻", "⢼", "⢽", "⢾", "⢿", "⣀", "⣁", "⣂", "⣃", "⣄", "⣅", "⣆", "⣇", "⣈", "⣉", "⣊", "⣋", "⣌", "⣍", "⣎", "⣏", "⣐", "⣑", "⣒", "⣓", "⣔", "⣕", "⣖", "⣗", "⣘", "⣙", "⣚", "⣛", "⣜", "⣝", "⣞", "⣟", "⣠", "⣡", "⣢", "⣣", "⣤", "⣥", "⣦", "⣧", "⣨", "⣩", "⣪", "⣫", "⣬", "⣭", "⣮", "⣯", "⣰", "⣱", "⣲", "⣳", "⣴", "⣵", "⣶", "⣷", "⣸", "⣹", "⣺", "⣻", "⣼", "⣽", "⣾", "⣿"};
	const int dotvalues[][4] = {{0x1, 0x2, 0x4, 0x40}, {0x8, 0x10, 0x20, 0x80}};

	const char *const blocks[] = {" ", "▖", "▗", "▄", "▘", "▌", "▚", "▙", "▝", "▞", "▐", "▟", "▀", "▛", "▜", "█"};
	const int blockvalues[][2] = {{4, 1}, {8, 2}};

	const char *const bars[] = {" ", "▁", "▂", "▃", "▄", "▅", "▆", "▇", "█"};

	enum type_type
	{
		type_braille,
		type_block,
		type_histogram // Set automatically by the histogram() function
	};

	enum type_type const type_types[] = {type_braille, type_block /* , type_histogram */};

	enum plot_type
	{
		plot_scatter,
		plot_line
	};

	enum plot_type const plot_types[] = {plot_scatter, plot_line};

	const short marks[][8][2] = {{{0, 0}}, {{0, 1}, {-1, 0}, {0, 0}, {1, 0}, {0, -1}}, {{-1, 1}, {0, 1}, {1, 1}, {-1, 0}, {1, 0}, {-1, -1}, {0, -1}, {1, -1}}};

	enum mark_type
	{
		mark_dot,
		mark_plus,
		mark_square
	};

	enum mark_type const mark_types[] = {mark_dot, mark_plus, mark_square};

	enum graph_type
	{
		graph_dot,
		graph_shade_above,
		graph_shade_below
	};

	enum graph_type const graph_types[] = {graph_dot, graph_shade_above, graph_shade_below};

	const char *const fractions[] = {"¼", "½", "¾", "⅐", "⅑", "⅒", "⅓", "⅔", "⅕", "⅖", "⅗", "⅘", "⅙", "⅚", "⅛", "⅜", "⅝", "⅞"};
	const long double fractionvalues[] = {1.0L / 4.0L, 1.0L / 2.0L, 3.0L / 4.0L, 1.0L / 7.0L, 1.0L / 9.0L, 1.0L / 10.0L, 1.0L / 3.0L, 2.0L / 3.0L, 1.0L / 5.0L, 2.0L / 5.0L, 3.0L / 5.0L, 4.0L / 5.0L, 1.0L / 6.0L, 5.0L / 6.0L, 1.0L / 8.0L, 3.0L / 8.0L, 5.0L / 8.0L, 7.0L / 8.0L};

	const char *const constants[] = {"π", "e"};
	const long double constantvalues[] = {M_PI, M_E};

	enum units_type
	{
		units_number,
		units_scale_none,
		units_scale_SI,
		units_scale_IEC,
		units_scale_IEC_I,
		units_fracts,
		units_percent,
		units_date,
		units_time,
		units_monetary
	};

	enum units_type const units_types[] = {units_number, units_scale_SI, units_scale_IEC, units_scale_IEC_I, units_fracts, units_percent, units_date, units_time, units_monetary};

	const char *const suffix_power_char[] = {"", "K", "M", "G", "T", "P", "E", "Z", "Y", "R", "Q"};

	const long double max_bit = scalbn(1.0L, LDBL_MANT_DIG - 1);
	const long double MAX = max_bit + (max_bit - 1);

	struct options
	{
		bool border = false;
		bool axis = true;
		bool axislabel = true;
		bool axistick = true;
		bool axisunitslabel = true;
		units_type xunits = units_fracts;
		units_type yunits = units_fracts;
		type_type type = type_braille;
		mark_type mark = mark_dot;
		const char *title = nullptr;
		style_type style = style_light;
		color_type color = color_red;
		ostream &ostr = cout;
		bool check = true;
	};

	// Number of columns needed to represent the string
	// Adapted from: https://stackoverflow.com/a/31124065
	inline int strcol(const string &str)
	{
		for (const char c : str)
			if (iscntrl(c))
			{
				cerr << "\nError: Control character in string.\n";
				cerr << "Control character: " << (int)c << '\n';
			}

		size_t length = mbstowcs(nullptr, str.c_str(), 0);
		if (length == static_cast<size_t>(-1))
			throw range_error("Error: mbstowcs failed. Invalid multibyte character.");
		++length;

		wstring wcstring(length, L'\0');

		if (mbstowcs(wcstring.data(), str.c_str(), length) == static_cast<size_t>(-1))
			throw range_error("Error: mbstowcs failed. Invalid multibyte character.");

		const int width = wcswidth(wcstring.c_str(), length);
		if (width == -1)
			throw range_error("Error: wcswidth failed. Nonprintable wide character.");

		return width;
	}

	// Word wrap
	// Source: https://gist.github.com/tdulcet/819821ca69501822ad3f84a060c640a0
	// Adapted from: https://stackoverflow.com/a/42016346 and https://stackoverflow.com/a/13094734
	inline string wrap(const string &str, const size_t line_length)
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

				const size_t width = strcol(words.substr(index - linelen, templinelen));

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

	// Auto-scale number to unit
	// Adapted from: https://github.com/coreutils/coreutils/blob/master/src/numfmt.c
	inline void outputunit(long double number, const units_type scale, ostringstream &strm)
	{
		unsigned x = 0;
		long double val = number;
		if (val >= -LDBL_MAX and val <= LDBL_MAX)
		{
			while (abs(val) >= 10)
			{
				++x;
				val /= 10;
			}
		}

		if (scale == units_scale_none)
		{
			if (x > LDBL_DIG)
				return;

			strm << setprecision(LDBL_DIG) << number;
			return;
		}

		if (x > 33 - 1)
			return;

		double scale_base;

		switch (scale)
		{
		case units_scale_IEC:
		case units_scale_IEC_I:
			scale_base = 1024;
			break;
		case units_scale_none:
		case units_scale_SI:
		default:
			scale_base = 1000;
			break;
		}

		unsigned power = 0;
		if (number >= -LDBL_MAX and number <= LDBL_MAX)
		{
			while (abs(number) >= scale_base)
			{
				++power;
				number /= scale_base;
			}
		}

		long double anumber = abs(number);
		anumber += anumber < 10 ? 0.0005 : anumber < 100 ? 0.005
									   : anumber < 1000	 ? 0.05
														 : 0.5;

		if (number and anumber < 1000 and power > 0)
		{
			strm << setprecision(LDBL_DIG) << number;
			const string str = strm.str();

			const unsigned length = 5 + (number < 0 ? 1 : 0);
			if (str.length() > length)
			{
				const int prec = anumber < 10 ? 3 : anumber < 100 ? 2
																  : 1;
				strm.str("");
				strm << setprecision(prec) << fixed << number;
			}
		}
		else
		{
			strm << setprecision(0) << fixed << number;
		}

		// power == 1 and scale == units_scale_SI ? "k" :
		strm << (power < size(suffix_power_char) ? suffix_power_char[power] : "(error)");

		if (scale == units_scale_IEC_I and power > 0)
			strm << "i";
	}

	// Convert fractions and constants to Unicode characters
	inline void outputfraction(const long double number, ostringstream &strm)
	{
		bool output = false;

		const long double n = abs(number);
		if (n <= MAX)
		{
			long double intpart = 0;
			const long double fractionpart = abs(modf(number, &intpart));

			for (size_t i = 0; i < size(fractions) and !output; ++i)
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
				for (size_t i = 0; i < size(constants) and !output; ++i)
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
	}

	inline size_t outputlabel(const long double label, const units_type units, ostringstream &strm)
	{
		strm.imbue(locale(""));

		switch (units)
		{
		case units_number:
			strm << label;
			break;
		case units_scale_none:
		case units_scale_SI:
		case units_scale_IEC:
		case units_scale_IEC_I:
			outputunit(label, units, strm);
			break;
		case units_fracts:
			outputfraction(label, strm);
			break;
		case units_percent:
			strm << label * 100 << '%';
			break;
		case units_date:
		{
			// const time_t t = chrono::system_clock::to_time_t(chrono::sys_seconds(chrono::duration_cast<chrono::seconds>(chrono::duration<double>(label))));
			const time_t t = chrono::system_clock::to_time_t(chrono::system_clock::time_point(chrono::duration_cast<chrono::seconds>(chrono::duration<long double>(label))));
			const tm atm = *localtime(&t);
			strm << put_time(&atm, "%x");
			break;
		}
		case units_time:
		{
			// const time_t t = chrono::system_clock::to_time_t(chrono::sys_seconds(chrono::duration_cast<chrono::seconds>(chrono::duration<double>(label))));
			const time_t t = chrono::system_clock::to_time_t(chrono::system_clock::time_point(chrono::duration_cast<chrono::seconds>(chrono::duration<long double>(label))));
			const tm atm = *localtime(&t);
			strm << put_time(&atm, "%X");
			break;
		}
		case units_monetary:
			strm << showbase << put_money(label);
			break;
		}

		const size_t length = strcol(strm.str());

		return length;
	}

	// Output graph
	inline int graph(const size_t height, const size_t width, const long double xmin, const long double xmax, const long double ymin, const long double ymax, const vector<vector<unsigned short>> &array, const options &aoptions)
	{
		if (!size(array))
			return 1;

		const bool border = aoptions.border;
		const bool axis = aoptions.axis;
		const bool axislabel = aoptions.axislabel;
		const bool axistick = aoptions.axistick;
		const bool axisunitslabel = aoptions.axisunitslabel;
		const type_type type = aoptions.type;
		const char *const title = aoptions.title;

		if (!height)
			return 1;

		if (!width)
			return 1;

		struct winsize w;
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

		const size_t ai = type == type_histogram ? 8 : type == type_block ? 2
																		  : 4;
		const size_t aj = type == type_histogram ? 1 : 2;

		const size_t aheight = height / ai;
		const size_t awidth = width / aj;

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
		const int xdivisor = 4 * aj * ((((2 * width) / aj) / 160) + 2);
		const int ydivisor = 2 * ai * ((((4 * height) / ai) / 160) + 2);

		setlocale(LC_ALL, "");

		if (title and title[0] != '\0')
			aoptions.ostr << wrap(title, awidth) << '\n';

		const char *const *astyle = styles[aoptions.style];

		ostringstream strm;

		if (border)
		{
			strm << astyle[2];

			for (size_t k = 0; k < awidth; ++k)
				strm << astyle[0];

			strm << astyle[4] << '\n';
		}

		for (size_t i = 0; i < height; i += ai)
		{
			const bool ayaxis = yaxis <= (height - ai) ? i <= yaxis and (i + ai) > yaxis : i < yaxis and (i + ai) >= yaxis;
			const bool yaxislabel = yaxis <= (height - ai) ? i <= (yaxis + ai) and (i + ai) > (yaxis + ai) : i < (yaxis - ai) and (i + ai) >= (yaxis - ai);

			ostringstream ylabelstrm;
			size_t ylabellength = 0;

			if (axis and axistick and axisunitslabel and yaxis >= 0 and yaxis <= height)
			{
				bool output = false;
				long double label = 0;
				const int adivisor = i < yaxis ? -ydivisor : ydivisor;

				for (long double k = yaxis + adivisor; (i < yaxis ? k >= i : k < (i + ai)) and i >= ai and !output; k += adivisor)
				{
					if (i <= k and (i + ai) > k)
					{
						label = ymax - ((k > height ? height : k) * ystep);

						output = true;
					}
				}

				if (output)
				{
					ylabellength = outputlabel(label, aoptions.yunits, ylabelstrm);
					ylabellength *= aj;
				}
			}

			if (border)
				strm << astyle[1];

			for (size_t j = 0; j < width; j += aj)
			{
				const bool axaxis = xaxis >= aj ? j < xaxis and (j + aj) >= xaxis : j <= xaxis and (j + aj) > xaxis;
				const bool xaxislabel = xaxis >= aj ? j < (xaxis - aj) and (j + aj) >= (xaxis - aj) : j <= (xaxis + aj) and (j + aj) > (xaxis + aj);

				bool output = false;

				if (axis)
				{
					if (axaxis and ayaxis)
					{
						strm << astyle[6];
						output = true;
					}
					else if (axaxis)
					{
						if (!i)
						{
							strm << astyle[4];
							output = true;
						}
						else if (i >= (height - ai))
						{
							strm << astyle[10];
							output = true;
						}
						else if (axistick)
						{
							const int adivisor = i < yaxis ? -ydivisor : ydivisor;

							for (long double k = yaxis + adivisor; (i < yaxis ? k >= i : k < (i + ai)) and i >= ai and !output; k += adivisor)
							{
								if (i <= k and (i + ai) > k)
								{
									strm << astyle[xaxis >= aj ? 7 : 5];
									output = true;
								}
							}
						}
						if (!output)
						{
							strm << astyle[1];
							output = true;
						}
					}
					else if (ayaxis)
					{
						if (!j)
						{
							strm << astyle[2];
							output = true;
						}
						else if (j >= (width - aj))
						{
							strm << astyle[4];
							output = true;
						}
						else if (axistick)
						{
							const int adivisor = j < xaxis ? -xdivisor : xdivisor;

							for (long double k = xaxis + adivisor; (j < xaxis ? k >= j : k < (j + aj)) and j < (width - (aj * 2)) and !output; k += adivisor)
							{
								if (j <= k and (j + aj) > k)
								{
									strm << astyle[yaxis <= (height - ai) ? 3 : 9];
									output = true;
								}
							}
						}
						if (!output)
						{
							strm << astyle[0];
							output = true;
						}
					}
					else if (yaxislabel and xaxislabel and axistick and axisunitslabel and ymin <= 0 and ymax >= 0 and xmin <= 0 and xmax >= 0)
					{
						strm << '0';
						output = true;
					}
					else if ((xaxis <= (width - aj) ? j >= (width - aj) : !j) and yaxislabel and axislabel)
					{
						strm << 'x';
						output = true;
					}
					else if (yaxislabel and axistick and axisunitslabel)
					{
						long double label = 0;
						const int adivisor = j < xaxis ? -xdivisor : xdivisor;
						if (j < xaxis)
							j += aj;

						for (long double k = xaxis + adivisor; (j < xaxis ? k >= j : k < (j + aj)) and j < (width - aj) and !output; k += adivisor)
						{
							if (j <= k and (j + aj) > k)
							{
								label = ((k > width ? width : k) * xstep) + xmin;

								output = true;
							}
						}

						if (adivisor < 0)
							j -= aj;

						if (output)
						{
							output = false;

							ostringstream astrm;
							size_t length = outputlabel(label, aoptions.xunits, astrm);
							length *= aj;
							if ((j >= xaxis or (j + length) < (ymin <= 0 and ymax >= 0 and xmin <= 0 and xmax >= 0 ? xaxis - ai : xaxis)) and (j + length) < (width - aj) and (xaxis <= (width - aj) or j > aj))
							{
								strm << astrm.str();

								if (length > aj)
									j += length - aj;

								if (adivisor < 0)
									output = true;
								else
									j += aj;
							}
						}
					}
					else if ((yaxis >= ai ? !i : i >= (height - ai)) and xaxislabel and axislabel)
					{
						strm << 'y';
						output = true;
					}
					else if (ylabellength and (xaxis < aj ? xaxislabel : j < (xaxis - ylabellength) and (j + aj) >= (xaxis - ylabellength)) and (yaxis >= ai or i < (height - ai)) and axistick and axisunitslabel)
					{
						strm << ylabelstrm.str();
						output = true;
						if (ylabellength > aj)
							j += ylabellength - aj;
					}
				}

				if (!output)
				{
					size_t dot = 0;
					unsigned short color = 0;

					for (size_t k = 0; k < aj and k < (width - j); ++k)
					{
						for (size_t l = 0; l < ai and l < (height - i); ++l)
						{
							const unsigned short value = array[j + k][i + l];
							if (value)
							{
								if (type == type_histogram)
								{
									if (!dot)
										dot = (size(bars) - l) - 1;
								}
								else if (type == type_block)
									dot += blockvalues[k][l];
								else
									dot += dotvalues[k][l];
							}
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
						strm << colors[color];

					strm << (type == type_histogram ? bars[dot] : type == type_block ? blocks[dot]
																					 : dots[dot]);

					if (color)
						strm << colors[0];
				}
			}

			if (border)
				strm << astyle[1];

			if (i < (height - ai) or border)
				strm << '\n';
		}

		if (border)
		{
			strm << astyle[8];

			for (size_t k = 0; k < awidth; ++k)
				strm << astyle[0];

			strm << astyle[10];
		}

		strm << '\n';
		aoptions.ostr << strm.str();

		return 0;
	}

	// EXPERIMENTAL BEG

	// Using the existing color_type enum for the 4-bit colors (not using std::variant due to its larger size)
	union Color {
		color_type col_4; // 4-bit color
		uint8_t col_8; // 8-bit color
		struct {
			uint8_t red;
			uint8_t green;
			uint8_t blue;
		} col_24; // 24-bit true color
	};
	enum class ColorBits: uint8_t { e4, e8, e24 };

	// Intermediate fragment representation potentially holding multiple pixels (e.g. 2x4 as braille)
	// most optimal representation possible with only 4 bytes in size, applicable for all types of characters
	struct Fragment {
		Color color;
		uint8_t data; // stores up to 8 data points or up to 255 values
	};
	// store fragments on temporary buffer to pass between draws
	using Texture = std::vector<Fragment>;
	struct Axis {
		long double min = 0;
		long double max = 0;
		bool labels = true;
		bool ticks = true;
		bool units_label = true;
		units_type units = units_fracts;
	};
	struct Options {
		size_t width = 0; // Width in terminal characters. Set to 0 for automatic size based on terminal.
		size_t height = 0; // Height in terminal characters. Set to 0 for automatic size based on terminal.

		Axis x = {};
		Axis y = {};

		type_type character_set = type_braille;
		plot_type plot = plot_scatter;
		style_type style = style_light;
		graph_type graph = graph_dot;

		std::string title;
		std::ostream &ostr = std::cout;

		ColorBits color_type = ColorBits::e4; // bit depth of color representation
		bool check = true; // validate sizes for graph draw
		bool border = false; // draw border around the graph
		bool draw_immediately = true; // draw graph immediately after creation. otherwise call draw/graph with the returned texture
	};
	// intermediate representation of a graph texture for ease of passing around
	struct Intermediate {
		// use a graph texture to draw into the terminal
		inline void draw() {
			// draw graph for experimental preview purposes only
			for (size_t y = 0; y < options.height; y++) {
				for (size_t x = 0; x < options.width; x++) {
					const size_t index = x + y * options.width;
					const auto& frag = texture[index];
					// draw Fragment
					cout << colors[frag.color.col_4];
					switch (options.character_set) {
						case type_braille:
							cout << dots[frag.data];
							break;
						case type_block:
							cout << blocks[frag.data];
							break;
						default: break;
					}
					cout << colors[0];
				}
				cout << '\n';
			}
		}

		Texture texture;
		const Options options;
	};

	// plot from single data set, drawn on top of existing graph
	template <typename T>
	void plot_experimental(const T &data, Intermediate &intermediate, const Color &color = {color_red}) {
		cout << "Experimental plot\n";

		// precalc spans
		const Options& options = intermediate.options;
		const long double x_span = options.x.max - options.x.min;
		const long double y_span = options.y.max - options.y.min;
		const long double x_span_recip = 1.0 / x_span;
		const long double y_span_recip = 1.0 / y_span;

		// insert draw plot data into texture
		for (const auto [x, y]: data) {
			// check if value is between limits
			if (x >= options.x.min && x < options.x.max && y >= options.y.min && y < options.y.max) {
				// calculate terminal character position
				const long double x_term = ((long double)x - options.x.min) * x_span_recip * (long double)options.width;
				const long double y_term = ((long double)y - options.y.min) * y_span_recip * (long double)options.height;

				// calculate sub-fragment position (2x4 for braille)
				size_t char_width = 0;
				size_t char_height = 0;
				// TODO: could put this in a separate function to avoid switch statement and reuse in other plot funcs
				switch (options.character_set) {
					case type_braille:
						char_width = 2;
						char_height = 4;
						break;
					case type_block:
						char_width = 2;
						char_height = 2;
						break;
					default: break;
				}
				size_t x_sub = (x_term - std::floor(x_term)) * char_width;
				size_t y_sub = (y_term - std::floor(y_term)) * char_height;
				// invert y_sub
				y_sub = char_height - 1 - y_sub;

				// draw Fragment
				const size_t index = (size_t)x_term + (options.height - 1 - (size_t)y_term) * options.width;
				intermediate.texture[index].color = color; // TODO: mix color here

				uint8_t value = 0;
				switch (options.character_set) {
					case type_braille:
						value = dotvalues[x_sub][y_sub];
						break;
					case type_block:
						value = blockvalues[x_sub][y_sub];
						break;
					default: break;
				}
				intermediate.texture[index].data |= value;
			}
		}
	}
	// plot from single data set
	template <typename T>
	auto plot_experimental(const T &data, const Options &options = {}, const Color &color = {color_red}) -> Intermediate {
		cout << "Experimental plot\n";

		// precalc spans
		const long double x_span = options.x.max - options.x.min;
		const long double y_span = options.y.max - options.y.min;
		const long double x_span_recip = 1.0 / x_span;
		const long double y_span_recip = 1.0 / y_span;

		// create new intermediate object for texture and options
		assert(options.width > 0 && options.height > 0); // enforce valid size for now
		Intermediate intermediate = { Texture(options.width * options.height), options };
		plot_experimental(data, intermediate, color);
		return intermediate;
	}
	// EXPERIMENTAL END

	template <typename T>
	int histogram(size_t height, size_t width, long double xmin, long double xmax, long double ymin, long double ymax, const T &aarray, const options &aoptions = {})
	{
		if (!size(aarray))
			return 1;

		const color_type color = aoptions.color;

		struct winsize w;
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

		if (!height)
			height = w.ws_row * 4;

		if (!width)
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

		height *= 2;
		width /= 2;

		if (!xmin and !xmax)
		{
			const auto &[amin, amax] = minmax_element(cbegin(aarray), cend(aarray));

			xmin = *amin;
			xmax = *amax;
		}

		if (xmin >= xmax)
		{
			cerr << "xmin must be less than xmax.\n";
			return 1;
		}

		vector<size_t> histogram(width, 0);

		const long double xstep = (xmax - xmin) / width;

		for (const auto &x : aarray)
		{
			if (x >= xmin and x < xmax)
			{
				const size_t index = (x - xmin) / xstep;
				++histogram[index];
			}
		}

		if (!ymin and !ymax)
		{
			const auto &[amin, amax] = minmax_element(histogram.cbegin(), histogram.cend());

			ymin = *amin;
			ymax = *amax;
		}

		if (ymin >= ymax)
		{
			cerr << "ymin must be less than ymax.\n";
			return 1;
		}

		const long double ystep = (ymax - ymin) / height;
		const long double yaxis = ymax / ystep;

		vector<vector<unsigned short>> aaarray(width, vector<unsigned short>(height, 0));

		const unsigned acolor = color + 1;

		for (size_t x = 0; x < size(histogram); ++x)
		{
			const size_t ay = histogram[x];

			for (size_t y = ay >= ymax ? 0 : yaxis - (ay / ystep); y < yaxis and y < height; ++y)
				aaarray[x][y] = acolor;
		}

		if (aoptions.type != type_histogram)
		{
			options hist_options = aoptions;
			hist_options.type = type_histogram;
			return graph(height, width, xmin, xmax, ymin, ymax, aaarray, hist_options);
		}
		return graph(height, width, xmin, xmax, ymin, ymax, aaarray, aoptions);
	}

	template <typename T>
	int histogram(size_t height, size_t width, long double xmin, long double xmax, long double ymin, long double ymax, const size_t rows, T *aarray, const options &aoptions = {})
	{
		if (!rows)
			return 1;

		vector<T> aaarray(rows);
		copy(aarray, aarray + rows, aaarray.begin());

		return histogram(height, width, xmin, xmax, ymin, ymax, aaarray, aoptions);
	}

	// Convert one or more arrays to graph and output
	template <typename T>
	int plots(size_t height, size_t width, long double xmin, long double xmax, long double ymin, long double ymax, const T &arrays, const options &aoptions = {})
	{
		if (!size(arrays))
			return 1;

		if (!all_of(cbegin(arrays), cend(arrays), [](const auto &array)
					{ return all_of(cbegin(array), cend(array), [](const auto &x)
									{ return size(x) == 2; }); }))
		{
			cerr << "Error: The arrays must have two columns.\n";
			return 1;
		}

		const color_type color = aoptions.color;

		struct winsize w;
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

		if (!height)
			height = w.ws_row * 4;

		if (!width)
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

		if (aoptions.type == type_block)
			height /= 2;

		if (!xmin and !xmax)
		{
			const auto compare = [](const auto &a, const auto &b)
			{ return a[0] < b[0]; };
			const auto &[amin, amax] = accumulate(cbegin(arrays), cend(arrays), make_pair(arrays[0][0], arrays[0][0]), [&compare](const auto &current, const auto &array)
												  { const auto &[amin, amax] = minmax_element(cbegin(array), cend(array), compare); return make_pair(min(current.first, *amin, compare), max(current.second, *amax, compare)); });
			xmin = amin[0];
			xmax = amax[0];
		}

		if (!ymin and !ymax)
		{
			const auto compare = [](const auto &a, const auto &b)
			{ return a[1] < b[1]; };
			const auto &[amin, amax] = accumulate(cbegin(arrays), cend(arrays), make_pair(arrays[0][0], arrays[0][0]), [&compare](const auto &current, const auto &array)
												  { const auto &[amin, amax] = minmax_element(cbegin(array), cend(array), compare); return make_pair(min(current.first, *amin, compare), max(current.second, *amax, compare)); });
			ymin = amin[1];
			ymax = amax[1];
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

		for (size_t j = 0; j < size(arrays); ++j)
		{
			const auto &array = arrays[j];
			const unsigned acolor = size(arrays) == 1 ? color + 1 : (j % (size(colors) - 2)) + 3;

			for (size_t i = 0; i < size(array); ++i)
			{
				const auto &x = array[i][0], &y = array[i][1];

				if (x >= xmin and x < xmax and y >= ymin and y < ymax)
				{
					const size_t ax = (x / xstep) + xaxis;
					const size_t ay = (yaxis - (y / ystep)) - 1;

					for (const auto &[ix, iy] : marks[aoptions.mark])
					{
						const size_t x = ax + ix;
						const size_t y = ay + iy;

						if (x < width and y < height)
						{
							if (aarray[x][y])
							{
								if (aarray[x][y] != acolor)
									aarray[x][y] = 1;
							}
							else
								aarray[x][y] = acolor;
						}
					}
				}
			}
		}

		return graph(height, width, xmin, xmax, ymin, ymax, aarray, aoptions);
	}

	// Convert single array to graph and output
	template <typename T>
	int plot(size_t height, size_t width, long double xmin, long double xmax, long double ymin, long double ymax, const T &aarray, const options &aoptions = {})
	{
		const std::array<T, 1> aaarray = {aarray};

		return plots(height, width, xmin, xmax, ymin, ymax, aaarray, aoptions);
	}

	// Convert single array to graph and output
	template <typename T>
	int plot(size_t height, size_t width, long double xmin, long double xmax, long double ymin, long double ymax, const size_t rows, T **aarray, const options &aoptions = {})
	{
		if (!rows)
			return 1;

		const size_t columns = 2;
		vector<std::array<T, columns>> aaarray(rows);
		for (size_t i = 0; i < rows; ++i)
			copy(aarray[i], aarray[i] + columns, aaarray[i].begin());

		return plot(height, width, xmin, xmax, ymin, ymax, aaarray, aoptions);
	}

	// Convert one or more functions to graph and output
	template <typename T>
	int functions(size_t height, size_t width, const long double xmin, const long double xmax, const long double ymin, const long double ymax, const size_t numfunctions, function<T(T)> functions[], const options &aoptions = {})
	{
		const color_type color = aoptions.color;

		if (!numfunctions)
			return 1;

		struct winsize w;
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

		if (!height)
			height = w.ws_row * 4;

		if (!width)
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

		if (aoptions.type == type_block)
			height /= 2;

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
			const unsigned short acolor = numfunctions == 1 ? color + 1 : (j % (size(colors) - 2)) + 3;

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
	int function(size_t height, size_t width, const long double xmin, const long double xmax, const long double ymin, const long double ymax, const function<T(T)> &afunction, const options &aoptions = {})
	{
		std::function<T(T)> afunctions[] = {afunction};

		return functions(height, width, xmin, xmax, ymin, ymax, 1, afunctions, aoptions);
	}

	// Convert single function to function array and output
	template <typename T>
	int function(size_t height, size_t width, const long double xmin, const long double xmax, const long double ymin, const long double ymax, T afunction(T), const options &aoptions = {})
	{
		std::function<T(T)> afunctions[] = {afunction};

		return functions(height, width, xmin, xmax, ymin, ymax, 1, afunctions, aoptions);
	}
}
