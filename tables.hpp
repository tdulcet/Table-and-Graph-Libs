// Teal Dulcet, CS546

#include <iostream>
#include <sstream>
#include <cstring>
#include <iomanip>
#include <cwchar>
#include <clocale>
#include <cstdlib>
#include <vector>
#include <iterator>
#include <sys/ioctl.h>
#include <unistd.h>
#include <regex>

using namespace std;

const char *const styles[][11] = {
	{"-", "|", "+", "+", "+", "+", "+", "+", "+", "+", "+"}, // ASCII
	{"—", "|", "+", "+", "+", "+", "+", "+", "+", "+", "+"}, // Basic
	{"─", "│", "┌", "┬", "┐", "├", "┼", "┤", "└", "┴", "┘"}, // Light
	{"━", "┃", "┏", "┳", "┓", "┣", "╋", "┫", "┗", "┻", "┛"}, // Heavy
	{"═", "║", "╔", "╦", "╗", "╠", "╬", "╣", "╚", "╩", "╝"}, // Double
	{"╌", "╎", "┌", "┬", "┐", "├", "┼", "┤", "└", "┴", "┘"}, // Light Dashed
	{"╍", "╏", "┏", "┳", "┓", "┣", "╋", "┫", "┗", "┻", "┛"}	 // Heavy Dashed
};
// {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "}};//No border

regex ansi(R"(\x1B\[(?:[0-9]+(?:;[0-9]+)*)?m)");

struct tableoptions
{
	bool headerrow = false;
	bool headercolumn = false;
	bool tableborder = true;
	bool cellborder = false;
	unsigned int padding = 1;
	ios_base &(*alignment)(ios_base &) = left;
	bool boolalpha = false;
	const char *title = nullptr;
	unsigned int style = 2;
};

const tableoptions defaultoptions;

// Number of columns needed to represent the string
// Adapted from: https://stackoverflow.com/a/31124065
int strcol(const char *str)
{
	const string astr = regex_replace(str, ansi, "");
	str = astr.c_str();

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

	wchar_t *wcstring = new wchar_t[length];

	if (mbstowcs(wcstring, str, length) == static_cast<size_t>(-1))
	{
		if (wcstring != nullptr)
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

	if (wcstring != nullptr)
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

// Output char array as table
template <typename T>
int table(const vector<vector<basic_string<T>>> &array, const tableoptions &aoptions)
{
	if (!size(array))
		return 1;

	const bool headerrow = aoptions.headerrow;
	const bool headercolumn = aoptions.headercolumn;
	const bool tableborder = aoptions.tableborder;
	const bool cellborder = aoptions.cellborder;
	const unsigned int padding = aoptions.padding;
	const char *const title = aoptions.title;
	const unsigned int style = aoptions.style;

	if (style >= size(styles))
		return 1;

	const size_t rows = array.size();
	const size_t columns = array[0].size();

	int columnwidth[columns];
	for (unsigned int j = 0; j < columns; ++j)
		columnwidth[j] = 0;

	int width = 0;

	setlocale(LC_CTYPE, "");

	for (unsigned int j = 0; j < columns; ++j)
	{
		for (unsigned int i = 0; i < rows; ++i)
		{
			int cellwidth = strcol(array[i][j].c_str());
			if (cellwidth > columnwidth[j])
				columnwidth[j] = cellwidth;
		}

		width += columnwidth[j];
	}

	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	if (tableborder or cellborder or headerrow or headercolumn)
		width += (((2 * padding) + 1) * columns) + (tableborder ? 1 : -1);
	else
		width += (2 * padding) * columns;

	if (width > w.ws_col)
	{
		cerr << "The width of the table (" << width << ") is greater then the width of the terminal (" << w.ws_col << ").\n";
		return 1;
	}

	if (title != nullptr and title[0] != '\0')
		cout << wrap(title, w.ws_col) << "\n";

	if (tableborder)
	{
		cout << styles[style][2];

		for (unsigned int j = 0; j < columns; ++j)
		{
			for (unsigned int k = 0; k < (2 * padding) + columnwidth[j]; ++k)
				cout << styles[style][0];

			if (j == (columns - 1))
				cout << styles[style][4] << "\n";
			else if (cellborder or headerrow or (j == 0 and headercolumn))
				cout << styles[style][3];
			else
				cout << styles[style][0];
		}
	}

	for (unsigned int i = 0; i < rows; ++i)
	{
		for (unsigned int j = 0; j < columns; ++j)
		{
			if ((j == 0 and tableborder) or (j > 0 and cellborder) or (i == 0 and j > 0 and headerrow) or (j == 1 and headercolumn))
				cout << styles[style][1];
			else if (tableborder or (i > 0 and j > 0 and headerrow) or (j > 1 and headercolumn))
				cout << " ";

			const int difference = columnwidth[j] - strcol(array[i][j].c_str());

			if ((i == 0 and headerrow) or (j == 0 and headercolumn))
			{
				const int apadding = (difference / 2);

				cout << string(padding + apadding, ' ');

				cout << "\e[1m" << array[i][j] << "\e[22m";

				cout << string(padding + (difference - apadding), ' ');
			}
			else
			{
				cout << string(padding, ' ');

				cout << aoptions.alignment << setw(difference + array[i][j].length()) << array[i][j];

				cout << string(padding, ' ');
			}
		}

		if (tableborder)
			cout << styles[style][1];

		cout << "\n";

		if (tableborder)
		{
			if (i == (rows - 1))
				cout << styles[style][8];
			else if (cellborder or (i == 0 and headerrow) or headercolumn)
				cout << styles[style][5];
		}

		if ((i == (rows - 1) and tableborder) or (i < (rows - 1) and cellborder) or (i == 0 and headerrow) or (i < (rows - 1) and headercolumn))
		{
			for (unsigned int j = 0; j < columns; ++j)
			{
				if ((i == (rows - 1) and tableborder) or (i < (rows - 1) and cellborder) or (i == 0 and headerrow) or (i < (rows - 1) and j == 0 and headercolumn))
					for (unsigned int k = 0; k < (2 * padding) + columnwidth[j]; ++k)
						cout << styles[style][0];
				else if (i < (rows - 1) and headercolumn)
					cout << string((2 * padding) + columnwidth[j], ' ');

				if (j == (columns - 1))
				{
					if (tableborder)
					{
						if (i == (rows - 1))
							cout << styles[style][10];
						else if (cellborder or (i == 0 and headerrow))
							cout << styles[style][7];
						else if (headercolumn)
							cout << styles[style][1];
					}

					cout << "\n";
				}
				else
				{
					if (i == (rows - 1) and tableborder)
					{
						if (cellborder or (j == 0 and headercolumn))
							cout << styles[style][9];
						else
							cout << styles[style][0];
					}
					else if ((i < (rows - 1) and cellborder) or ((i == 0 and headerrow) and (j == 0 and headercolumn)))
						cout << styles[style][6];
					else if (i == 0 and headerrow)
						cout << styles[style][9];
					else if (i < (rows - 1) and headercolumn)
					{
						if (j == 0)
							cout << styles[style][7];
						else
							cout << " ";
					}
				}
			}
		}
	}

	cout << endl;

	return 0;
}

// Convert array to char array and output as table
template <typename T1, typename T2>
int table(const T1 &aarray, T2 headerrow[] = nullptr, T2 headercolumn[] = nullptr, const tableoptions &aoptions = defaultoptions)
{
	if (!size(aarray))
		return 1;

	unsigned int i = 0;
	unsigned int j = 0;

	size_t rows = size(aarray);
	size_t columns = size(aarray[0]);

	if (!all_of(begin(aarray), end(aarray), [columns](auto &x)
				{ return size(x) == columns; }))
	{
		cerr << "Error: The rows of the array must have the same number of columns.";
		return 1;
	}

	if (headerrow != nullptr)
		++rows;

	if (headercolumn != nullptr)
		++columns;

	vector<vector<string>> aaarray(rows, vector<string>(columns));

	if (headerrow != nullptr)
	{
		for (unsigned int j = 0; j < columns; ++j)
		{
			aaarray[i][j] = headerrow[j];
		}

		++i;
	}

	for (unsigned int ii = 0; i < rows; ++i)
	{
		if (headercolumn != nullptr)
		{
			unsigned int ii = i;

			if (headerrow != nullptr)
				--ii;

			aaarray[i][j] = headercolumn[ii];

			++j;
		}

		for (unsigned int jj = 0; j < columns; ++j)
		{
			ostringstream strm;

			if (aoptions.boolalpha)
				strm << boolalpha;

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
int table(const size_t rows, const size_t columns, T **aarray, const char *const headerrow[] = nullptr, const char *const headercolumn[] = nullptr, const tableoptions &aoptions = defaultoptions)
{
	vector<vector<T>> aaarray(rows, vector<T>(columns));
	for (unsigned int i = 0; i < rows; ++i)
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

	return table(aaarray, aheaderrow, aheadercolumn, aoptions);
}

// Convert one or more functions to array and output as table
template <typename T>
int table(const long double xmin, const long double xmax, const long double xscl, const size_t numfunctions, function<T(T)> functions[], const tableoptions &aoptions = defaultoptions)
{
	if (numfunctions == 0)
		return 1;

	if (xmin >= xmax)
	{
		cerr << "xmin must be less than xmax.\n";
		return 1;
	}

	if (xscl <= 0)
	{
		cerr << "xscl must be greater than zero.\n";
		return 1;
	}

	const size_t rows = ((xmax - xmin) * xscl) + 1;
	const size_t columns = numfunctions + 1;

	const char *const aheaderrow[] = {"x", "y"};
	// const char* const aheaderrow[] = {"", "x", "y"};

	const size_t length = size(aheaderrow);

	string *headerrow = new string[columns];

	for (unsigned int j = 0; j < columns; ++j)
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
	// headercolumn = new string[rows + 1];

	// for (unsigned int i = 0; i < rows + 1; ++i)
	// {
	// ostringstream strm;
	// strm << i + 1;
	// headercolumn[i] = strm.str();
	// }

	vector<vector<T>> aarray(rows, vector<T>(columns));

	for (unsigned int i = 0; i < rows; ++i)
	{
		aarray[i][0] = (i / xscl) + xmin;

		for (unsigned int j = 0; j < numfunctions; ++j)
			aarray[i][j + 1] = (functions[j])(aarray[i][0]);
	}

	int code = table(aarray, headerrow, headercolumn, aoptions);

	if (headerrow != nullptr)
	{
		delete[] headerrow;
	}

	// if (headercolumn != nullptr)
	// {
	// delete[] headercolumn;
	// }

	return code;
}

// Convert single function to array and output as table
template <typename T>
int table(const long double xmin, const long double xmax, const long double xscl, const function<T(T)> &afunction, const tableoptions &aoptions = defaultoptions)
{
	std::function<T(T)> afunctions[] = {afunction};

	return table(xmin, xmax, xscl, 1, afunctions, aoptions);
}

// Convert single function to array and output as table
template <typename T>
int table(const long double xmin, const long double xmax, const long double xscl, T afunction(T), const tableoptions &aoptions = defaultoptions)
{
	std::function<T(T)> afunctions[] = {afunction};

	return table(xmin, xmax, xscl, 1, afunctions, aoptions);
}
