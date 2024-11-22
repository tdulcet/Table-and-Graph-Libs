// Teal Dulcet, CS546
#pragma once
#include <iostream>
#include <sstream>
#include <cstring>
#include <iomanip>
#include <cwchar>
#include <clocale>
#include <cstdlib>
#include <vector>
#include <iterator>
#include <numeric>
#include <sys/ioctl.h>
#include <unistd.h>
#include <regex>

#ifdef TGLIB_TABLES_NAMESPACE
namespace TGLIB_TABLES_NAMESPACE
{
#else
namespace tables
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

	const regex ansi(R"(\x1B\[(?:[0-9]+(?:;[0-9]+)*)?m)");

	struct options
	{
		bool headerrow = false;
		bool headercolumn = false;
		bool tableborder = true;
		bool cellborder = false;
		unsigned padding = 1;
		ios_base::fmtflags alignment;
		const char *title = nullptr;
		style_type style = style_light;
		ostream &ostr = cout;
		bool check = true;
	};

	// Number of columns needed to represent the string
	// Adapted from: https://stackoverflow.com/a/31124065
	inline int strcol(const string &astr)
	{
		const string str = regex_replace(astr, ansi, "");

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

	// Output char array as table
	template <typename T>
	int table(const vector<vector<basic_string<T>>> &array, const options &aoptions)
	{
		if (!size(array))
			return 1;

		const bool headerrow = aoptions.headerrow;
		const bool headercolumn = aoptions.headercolumn;
		const bool tableborder = aoptions.tableborder;
		const bool cellborder = aoptions.cellborder;
		const unsigned padding = aoptions.padding;
		const char *const title = aoptions.title;

		const size_t rows = array.size();
		const size_t columns = array[0].size();

		vector<int> columnwidth(columns);

		setlocale(LC_ALL, "");

		for (size_t j = 0; j < columns; ++j)
		{
			for (size_t i = 0; i < rows; ++i)
			{
				const int cellwidth = strcol(array[i][j]);
				if (cellwidth > columnwidth[j])
					columnwidth[j] = cellwidth;
			}
		}

		struct winsize w;
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

		size_t width = accumulate(columnwidth.cbegin(), columnwidth.cend(), 0ul);

		if (tableborder or cellborder or headerrow or headercolumn)
			width += (((2 * padding) + 1) * columns) + (tableborder ? 1 : -1);
		else
			width += (2 * padding) * columns;

		if (aoptions.check)
		{
			if (width > w.ws_col)
			{
				cerr << "The width of the table (" << width << ") is greater then the width of the terminal (" << w.ws_col << ").\n";
				return 1;
			}
		}

		if (title and title[0] != '\0')
			aoptions.ostr << wrap(title, width) << '\n';

		const char *const *astyle = styles[aoptions.style];

		ostringstream strm;
		strm << setiosflags(aoptions.alignment);

		if (tableborder)
		{
			strm << astyle[2];

			for (size_t j = 0; j < columns; ++j)
			{
				for (size_t k = 0; k < (2 * padding) + columnwidth[j]; ++k)
					strm << astyle[0];

				if (j < (columns - 1))
				{
					if (cellborder or headerrow or (!j and headercolumn))
						strm << astyle[3];
					else
						strm << astyle[0];
				}
			}

			strm << astyle[4] << '\n';
		}

		for (size_t i = 0; i < rows; ++i)
		{
			if (tableborder)
				strm << astyle[1];

			for (size_t j = 0; j < columns; ++j)
			{
				if ((j and cellborder) or (!i and j and headerrow) or (j == 1 and headercolumn))
					strm << astyle[1];
				else if (j and (tableborder or (i and headerrow) or headercolumn))
					strm << ' ';

				const int difference = columnwidth[j] - strcol(array[i][j]);

				if ((!i and headerrow) or (!j and headercolumn))
				{
					const int apadding = (difference / 2);

					strm << string(padding + apadding, ' ') << "\e[1m" << array[i][j] << "\e[22m" << string(padding + (difference - apadding), ' ');
				}
				else
				{
					strm << string(padding, ' ') << setw(difference + array[i][j].length()) << array[i][j] << string(padding, ' ');
				}
			}

			if (tableborder)
				strm << astyle[1];

			if (i < (rows - 1) or tableborder)
				strm << '\n';

			if ((i < (rows - 1) and cellborder) or (!i and headerrow) or (i < (rows - 1) and headercolumn))
			{
				if (tableborder)
				{
					if (cellborder or (!i and headerrow) or headercolumn)
						strm << astyle[5];
				}

				for (size_t j = 0; j < columns; ++j)
				{
					if (cellborder or (!i and headerrow) or (!j and headercolumn))
						for (size_t k = 0; k < (2 * padding) + columnwidth[j]; ++k)
							strm << astyle[0];
					else if (headercolumn)
						strm << string((2 * padding) + columnwidth[j], ' ');

					if (j < (columns - 1))
					{
						if (cellborder or ((!i and headerrow) and (!j and headercolumn)))
							strm << astyle[6];
						else if (!i and headerrow)
							strm << astyle[9];
						else if (headercolumn)
						{
							if (!j)
								strm << astyle[7];
							else
								strm << ' ';
						}
					}
				}

				if (tableborder)
				{
					if (cellborder or (!i and headerrow))
						strm << astyle[7];
					else if (headercolumn)
						strm << astyle[1];
				}

				strm << '\n';
			}
		}

		if (tableborder)
		{
			strm << astyle[8];

			for (size_t j = 0; j < columns; ++j)
			{
				for (size_t k = 0; k < (2 * padding) + columnwidth[j]; ++k)
					strm << astyle[0];

				if (j < (columns - 1))
				{
					if (cellborder or (!j and headercolumn))
						strm << astyle[9];
					else
						strm << astyle[0];
				}
			}

			strm << astyle[10];
		}

		strm << '\n';
		aoptions.ostr << strm.str();

		return 0;
	}

	// Convert array to char array and output as table
	template <typename T1, typename T2>
	int array(const T1 &aarray, T2 headerrow[] = nullptr, T2 headercolumn[] = nullptr, const options &aoptions = {})
	{
		if (!size(aarray))
			return 1;

		size_t i = 0;
		size_t j = 0;

		size_t rows = size(aarray);
		size_t columns = size(aarray[0]);

		if (!all_of(cbegin(aarray), cend(aarray), [&columns](const auto &x)
					{ return size(x) == columns; }))
		{
			cerr << "Error: The rows of the array must have the same number of columns.\n";
			return 1;
		}

		if (headerrow)
			++rows;

		if (headercolumn)
			++columns;

		vector<vector<string>> aaarray(rows, vector<string>(columns));

		if (headerrow)
		{
			for (size_t j = 0; j < columns; ++j)
			{
				aaarray[i][j] = headerrow[j];
			}

			++i;
		}

		for (size_t ii = 0; i < rows; ++i)
		{
			if (headercolumn)
			{
				size_t ii = i;

				if (headerrow)
					--ii;

				aaarray[i][j] = headercolumn[ii];

				++j;
			}

			for (size_t jj = 0; j < columns; ++j)
			{
				ostringstream strm;
				strm << setiosflags(aoptions.alignment);

				strm << aarray[ii][jj];
				aaarray[i][j] = strm.str();

				++jj;
			}

			j = 0;
			++ii;
		}

		return table(aaarray, aoptions);
	}

	template <typename T>
	int array(const size_t rows, const size_t columns, T **aarray, const char *const headerrow[] = nullptr, const char *const headercolumn[] = nullptr, const options &aoptions = {})
	{
		vector<vector<T>> aaarray(rows, vector<T>(columns));
		for (size_t i = 0; i < rows; ++i)
			copy(aarray[i], aarray[i] + columns, aaarray[i].begin());

		string *aheaderrow = nullptr;
		string *aheadercolumn = nullptr;

		if (headerrow and headercolumn)
		{
			vector<string> aaheaderrow(rows + 1);
			copy(headerrow, headerrow + rows + 1, aaheaderrow.begin());
			aheaderrow = aaheaderrow.data();

			vector<string> aaheadercolumn(columns);
			copy(headercolumn, headercolumn + columns, aaheadercolumn.begin());
			aheadercolumn = aaheadercolumn.data();
		}
		else if (headerrow)
		{
			vector<string> aaheaderrow(rows);
			copy(headerrow, headerrow + rows, aaheaderrow.begin());
			aheaderrow = aaheaderrow.data();
		}
		else if (headercolumn)
		{
			vector<string> aaheadercolumn(columns);
			copy(headercolumn, headercolumn + columns, aaheadercolumn.begin());
			aheadercolumn = aaheadercolumn.data();
		}

		return array(aaarray, aheaderrow, aheadercolumn, aoptions);
	}

	// Convert one or more functions to array and output as table
	template <typename T>
	int functions(const long double xmin, const long double xmax, const long double xstep, const size_t numfunctions, function<T(T)> functions[], const options &aoptions = {})
	{
		if (!numfunctions)
			return 1;

		if (xmin >= xmax)
		{
			cerr << "xmin must be less than xmax.\n";
			return 1;
		}

		if (xstep <= 0)
		{
			cerr << "xstep must be greater than zero.\n";
			return 1;
		}

		const size_t rows = ((xmax - xmin) / xstep) + 1;
		const size_t columns = numfunctions + 1;

		const char *const aheaderrow[] = {"x", "y"};
		// const char* const aheaderrow[] = {"", "x", "y"};

		const size_t length = size(aheaderrow);

		vector<string> headerrow(columns);

		for (size_t j = 0; j < columns; ++j)
		{
			if (j < (length - 1) or numfunctions == 1)
			{
				headerrow[j] = aheaderrow[j];
			}
			else
			{
				ostringstream strm;
				strm << aheaderrow[length - 1] << j - length + 2;
				headerrow[j] = strm.str();
			}
		}

		string *headercolumn = nullptr;
		// vector<string> headercolumn(rows + 1);

		// for (size_t i = 0; i < rows + 1; ++i)
		// {
		// ostringstream strm;
		// strm << i + 1;
		// headercolumn[i] = strm.str();
		// }

		vector<vector<T>> aarray(rows, vector<T>(columns));

		for (size_t i = 0; i < rows; ++i)
		{
			aarray[i][0] = (i * xstep) + xmin;

			for (size_t j = 0; j < numfunctions; ++j)
				aarray[i][j + 1] = (functions[j])(aarray[i][0]);
		}

		return array(aarray, headerrow.data(), headercolumn, aoptions);
	}

	// Convert single function to array and output as table
	template <typename T>
	int function(const long double xmin, const long double xmax, const long double xstep, const function<T(T)> &afunction, const options &aoptions = {})
	{
		std::function<T(T)> afunctions[] = {afunction};

		return functions(xmin, xmax, xstep, 1, afunctions, aoptions);
	}

	// Convert single function to array and output as table
	template <typename T>
	int function(const long double xmin, const long double xmax, const long double xstep, T afunction(T), const options &aoptions = {})
	{
		std::function<T(T)> afunctions[] = {afunction};

		return functions(xmin, xmax, xstep, 1, afunctions, aoptions);
	}
}
