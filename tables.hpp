// Teal Dulcet, CS546

#include <iostream>
#include <sstream>
#include <cstring>
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

struct tableoptions
{
	bool headerrow;
	bool headercolumn;
	bool tableborder;
	bool cellborder;
	unsigned int padding;
	ios_base &(*alignment)(ios_base &);
	bool boolalpha;
	char *title;
	unsigned int style;
	tableoptions(void);
	~tableoptions(void);
};

tableoptions::tableoptions(void)
{
	headerrow = false;
	headercolumn = false;
	tableborder = true;
	cellborder = false;
	padding = 1;
	alignment = left;
	boolalpha = false;
	title = NULL;
	style = 2;
}

tableoptions::~tableoptions(void)
{
}

const tableoptions tabledefaultoptions;

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

// Output char array as table
int table(const size_t rows, const size_t columns, char ***array, const tableoptions &aoptions)
{
	if (array == NULL)
		return 1;

	const bool headerrow = aoptions.headerrow;
	const bool headercolumn = aoptions.headercolumn;
	const bool tableborder = aoptions.tableborder;
	const bool cellborder = aoptions.cellborder;
	const unsigned int padding = aoptions.padding;
	const char *const title = aoptions.title;
	const unsigned int style = aoptions.style;

	if (style >= (sizeof styles / sizeof styles[0]))
		return 1;

	int columnwidth[columns];
	for (unsigned int j = 0; j < columns; ++j)
		columnwidth[j] = 0;

	int width = 0;

	setlocale(LC_CTYPE, "");

	for (unsigned int j = 0; j < columns; ++j)
	{
		for (unsigned int i = 0; i < rows; ++i)
		{
			int cellwidth = strcol(array[i][j]);
			if (cellwidth > columnwidth[j])
				columnwidth[j] = cellwidth;
		}

		width += columnwidth[j];
	}

	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	if (tableborder and (cellborder or headerrow or headercolumn))
		width += (((2 * padding) + 1) * columns) + 1;
	else
		width += ((2 * padding) * columns) + 2;

	if (width > w.ws_col)
	{
		cerr << "The width of the table (" << width << ") is greater then the width of the terminal (" << w.ws_col << ").\n";
		return 1;
	}

	if (title != NULL and title[0] != '\0')
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
			if (tableborder)
			{
				if (j == 0 or cellborder or (i == 0 and headerrow) or (j == 1 and headercolumn))
					cout << styles[style][1];
				else
					cout << " ";
			}

			if ((i == 0 and headerrow) or (j == 0 and headercolumn))
			{
				int difference = columnwidth[j] - strcol(array[i][j]);
				int apadding = (difference / 2);

				for (unsigned int k = 0; k < padding + apadding; ++k)
					cout << " ";

				cout << "\e[1m" << array[i][j] << "\e[22m";

				for (unsigned int k = 0; k < padding + (difference - apadding); ++k)
					cout << " ";
			}
			else
			{
				for (unsigned int k = 0; k < padding; ++k)
					cout << " ";

				cout << aoptions.alignment << setw(columnwidth[j]) << array[i][j];

				for (unsigned int k = 0; k < padding; ++k)
					cout << " ";
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

			for (unsigned int j = 0; j < columns; ++j)
			{
				if (cellborder or i == (rows - 1) or (i == 0 and headerrow) or (j == 0 and headercolumn))
					for (unsigned int k = 0; k < (2 * padding) + columnwidth[j]; ++k)
						cout << styles[style][0];
				else if (headercolumn)
					for (unsigned int k = 0; k < (2 * padding) + columnwidth[j]; ++k)
						cout << " ";

				if (j == (columns - 1))
				{
					if (i == (rows - 1))
						cout << styles[style][10];
					else if (cellborder or (i == 0 and headerrow))
						cout << styles[style][7];
					else if (headercolumn)
						cout << styles[style][1];

					if (cellborder or (i == 0 and headerrow) or headercolumn)
						cout << "\n";
				}
				else
				{
					if (i == (rows - 1))
					{
						if (cellborder or (j == 0 and headercolumn))
							cout << styles[style][9];
						else
							cout << styles[style][0];
					}
					else if (cellborder or ((i == 0 and headerrow) and (j == 0 and headercolumn)))
						cout << styles[style][6];
					else if (i == 0 and headerrow)
						cout << styles[style][9];
					else if (headercolumn)
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
template <typename T>
int table(size_t rows, size_t columns, T **array, const char *const headerrow[], const char *const headercolumn[], const tableoptions &aoptions)
{
	if (array == NULL)
		return 1;

	unsigned int i = 0;
	unsigned int j = 0;

	if (headerrow != NULL)
		++rows;

	if (headercolumn != NULL)
		++columns;

	char ***aarray;
	aarray = new char **[rows];
	for (unsigned int i = 0; i < rows; ++i)
		aarray[i] = new char *[columns];

	if (headerrow != NULL)
	{
		for (unsigned int j = 0; j < columns; ++j)
		{
			aarray[i][j] = new char[strlen(headerrow[j]) + 1];
			strcpy(aarray[i][j], headerrow[j]);
		}

		++i;
	}

	for (unsigned int ii = 0; i < rows; ++i)
	{
		if (headercolumn != NULL)
		{
			unsigned int ii = i;

			if (headerrow != NULL)
				--ii;

			aarray[i][j] = new char[strlen(headercolumn[ii]) + 1];
			strcpy(aarray[i][j], headercolumn[ii]);

			++j;
		}

		for (unsigned int jj = 0; j < columns; ++j)
		{
			ostringstream strm;

			if (aoptions.boolalpha)
				strm << boolalpha;

			strm << array[ii][jj];
			string str = strm.str();
			aarray[i][j] = new char[str.length() + 1];
			strcpy(aarray[i][j], str.c_str());

			++jj;
		}

		j = 0;
		++ii;
	}

	int code = table(rows, columns, aarray, aoptions);

	if (aarray != NULL)
	{
		for (unsigned int i = 0; i < rows; ++i)
		{
			for (unsigned int j = 0; j < columns; ++j)
				delete[] aarray[i][j];

			delete[] aarray[i];
		}
		delete[] aarray;
	}

	return code;
}

// Convert one or more functions to array and output as table
template <typename T>
int table(const long double xmin, const long double xmax, const long double xscl, const size_t numfunctions, T (*functions[])(T), const tableoptions &aoptions)
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

	char **headerrow = new char *[columns];

	for (unsigned int j = 0; j < columns; ++j)
	{
		const size_t length = (sizeof aheaderrow / sizeof aheaderrow[0]);

		if (j < (length - 1) or numfunctions == 1)
		{
			headerrow[j] = new char[strlen(aheaderrow[j]) + 1];
			strcpy(headerrow[j], aheaderrow[j]);
		}
		else
		{
			ostringstream strm;
			strm << aheaderrow[length - 1] << j - length + 2;
			string str = strm.str();
			headerrow[j] = new char[str.length() + 1];
			strcpy(headerrow[j], str.c_str());
		}
	}

	char **headercolumn = NULL;
	// headercolumn = new char *[rows + 1];

	// for (unsigned int i = 0; i < rows + 1; ++i)
	// {
	// ostringstream strm;
	// strm << i + 1;
	// string str = strm.str();
	// headercolumn[i] = new char[str.length() + 1];
	// strcpy(headercolumn[i], str.c_str());
	// }

	T **array;
	array = new T *[rows];
	for (unsigned int i = 0; i < rows; ++i)
		array[i] = new T[columns];

	for (unsigned int i = 0; i < rows; ++i)
	{
		array[i][0] = (i / xscl) + xmin;

		for (unsigned int j = 0; j < numfunctions; ++j)
			array[i][j + 1] = (functions[j])(array[i][0]);
	}

	int code = table(rows, columns, array, headerrow, headercolumn, aoptions);

	if (array != NULL)
	{
		for (unsigned int i = 0; i < rows; ++i)
			delete[] array[i];

		delete[] array;
	}

	if (headerrow != NULL)
	{
		for (unsigned int j = 0; j < columns; ++j)
			delete[] headerrow[j];

		delete[] headerrow;
	}

	// if (headercolumn != NULL)
	// {
	// for (unsigned int i = 0; i < rows + 1; ++i)
	// delete[] headercolumn[i];

	// delete[] headercolumn;
	// }

	return code;
}

// Convert single function to array and output as table
template <typename T>
int table(const long double xmin, const long double xmax, const long double xscl, T afunction(T), const tableoptions &aoptions)
{
	T(*functions[])
	(T) = {afunction};

	return table(xmin, xmax, xscl, 1, functions, aoptions);
}
