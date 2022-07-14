// Teal Dulcet, CS546

// Compile: g++ -Wall -g -O3 -std=c++17 tables.cpp -o tables

// Run: ./tables

#include <cctype>
#include <cmath>
#include <algorithm>
#include <array>
#include <vector>
#include "tables.hpp"

using namespace std;

constexpr long double afunction(long double x)
{
	return x + 1;
}

constexpr long double function1(long double x)
{
	return 2 * x;
}

constexpr long double function2(long double x)
{
	return pow(x, 2);
}

int dimensions = 0;
int sortdimension = 0;

/* template <typename T>
int compare(const void *pa, const void *pb)
{
	const T a = *(const T *)pa;
	const T b = *(const T *)pb;

	if (a[sortdimension] == b[sortdimension])
	{
		for (int i = 0; i < dimensions; ++i)
		{
			if (sortdimension != i and a[i] != b[i])
			{
				if (a[i] > b[i])
					return 1;

				return -1;
			}
		}
	}

	if (a[sortdimension] > b[sortdimension])
		return 1;
	else if (a[sortdimension] == b[sortdimension])
		return 0;

	return -1;
} */

template <typename T>
bool compare(const T &a, const T &b)
{
	if (a[sortdimension] == b[sortdimension])
		for (int i = 0; i < dimensions; ++i)
			if (sortdimension != i and a[i] != b[i])
				return a[i] < b[i];

	return a[sortdimension] < b[sortdimension];
}

int main()
{
	const size_t rows = 5;
	const size_t columns = 5;

	const long double xmin = -10;
	const long double xmax = 10;
	const long double xscl = 2; // 80 / (xmax - xmin);

	string *headerrow = nullptr;
	string *headercolumn = nullptr;

	// Output array as table
	cout << "\nOutput array as table\n\n";
	{
		long long **array;
		array = new long long *[rows];
		for (unsigned int i = 0; i < rows; ++i)
			array[i] = new long long[columns];

		for (unsigned int i = 0; i < rows; ++i)
			for (unsigned int j = 0; j < columns; ++j)
				array[i][j] = rand();

		tables::options aoptions;

		for (unsigned int k = 0; k < size(tables::styles); ++k)
		{
			aoptions.style = k;

			tables::array(rows, columns, array, nullptr, nullptr, aoptions);
		}

		if (array != nullptr)
		{
			for (unsigned int i = 0; i < rows; ++i)
				delete[] array[i];

			delete[] array;
		}
	}
	{
		array<array<long long, columns>, rows> aarray;

		for (unsigned int i = 0; i < rows; ++i)
			for (unsigned int j = 0; j < columns; ++j)
				aarray[i][j] = rand();

		tables::options aoptions;

		for (unsigned int k = 0; k < size(tables::styles); ++k)
		{
			aoptions.style = k;

			tables::array(aarray, headerrow, headercolumn, aoptions);
		}
	}
	{
		vector<vector<long long>> array(rows, vector<long long>(columns));

		for (unsigned int i = 0; i < rows; ++i)
			for (unsigned int j = 0; j < columns; ++j)
				array[i][j] = rand();

		tables::options aoptions;

		for (unsigned int k = 0; k < size(tables::styles); ++k)
		{
			aoptions.style = k;

			tables::array(array, headerrow, headercolumn, aoptions);
		}
	}
	{
		long double **array;
		array = new long double *[rows];
		for (unsigned int i = 0; i < rows; ++i)
			array[i] = new long double[columns];

		for (unsigned int i = 0; i < rows; ++i)
			for (unsigned int j = 0; j < columns; ++j)
				array[i][j] = static_cast<long double>(rand()) / static_cast<long double>(RAND_MAX);

		tables::options aoptions;

		for (unsigned int k = 0; k < size(tables::styles); ++k)
		{
			aoptions.style = k;

			tables::array(rows, columns, array, nullptr, nullptr, aoptions);
		}

		if (array != nullptr)
		{
			for (unsigned int i = 0; i < rows; ++i)
				delete[] array[i];

			delete[] array;
		}
	}
	{
		array<array<long double, columns>, rows> aarray;

		for (unsigned int i = 0; i < rows; ++i)
			for (unsigned int j = 0; j < columns; ++j)
				aarray[i][j] = static_cast<long double>(rand()) / static_cast<long double>(RAND_MAX);

		tables::options aoptions;

		for (unsigned int k = 0; k < size(tables::styles); ++k)
		{
			aoptions.style = k;

			tables::array(aarray, headerrow, headercolumn, aoptions);
		}
	}
	{
		vector<vector<long double>> array(rows, vector<long double>(columns));

		for (unsigned int i = 0; i < rows; ++i)
			for (unsigned int j = 0; j < columns; ++j)
				array[i][j] = static_cast<long double>(rand()) / static_cast<long double>(RAND_MAX);

		tables::options aoptions;

		for (unsigned int k = 0; k < size(tables::styles); ++k)
		{
			aoptions.style = k;

			tables::array(array, headerrow, headercolumn, aoptions);
		}
	}
	// Output char array as table
	cout << "\nOutput char array as table\n\n";
	{
		const char *const array[rows][columns] = {
			{"Header row/column 1", "Header row 2", "Header row 3", "Header row 4", "Header row 5"},
			{"Header column 2", "Data 1", "Data 2", "Data 3", "Data 4"},
			{"Header column 3", "Data 5", "Data 6", "Data 7", "Data 8"},
			{"Header column 4", "Data 9", "Data 10", "Data 11", "Data 12"},
			{"Header column 5", "Data 13", "Data 14", "Data 15", "Data 16"}};

		tables::options aoptions;
		aoptions.headerrow = true;
		aoptions.headercolumn = true;
		// tables::options aoptions{.headerrow = true, .headercolumn = true};

		for (unsigned int k = 0; k < size(tables::styles); ++k)
		{
			aoptions.style = k;

			tables::array(array, headerrow, headercolumn, aoptions);
		}
	}
	{
		const array<array<string, columns>, rows> aarray = {{{"Header row/column 1", "Header row 2", "Header row 3", "Header row 4", "Header row 5"},
															 {"Header column 2", "Data 1", "Data 2", "Data 3", "Data 4"},
															 {"Header column 3", "Data 5", "Data 6", "Data 7", "Data 8"},
															 {"Header column 4", "Data 9", "Data 10", "Data 11", "Data 12"},
															 {"Header column 5", "Data 13", "Data 14", "Data 15", "Data 16"}}};

		tables::options aoptions;
		aoptions.headerrow = true;
		aoptions.headercolumn = true;
		// tables::options aoptions{.headerrow = true, .headercolumn = true};

		for (unsigned int k = 0; k < size(tables::styles); ++k)
		{
			aoptions.style = k;

			tables::array(aarray, headerrow, headercolumn, aoptions);
		}
	}
	// Output array as table with separate header row and column
	cout << "\nOutput array as table with separate header row and column\n\n";
	{
		const size_t rows = 4;
		const size_t columns = 4;

		const char *const array[rows][columns] = {
			{"Data 1", "Data 2", "Data 3", "Data 4"},
			{"Data 5", "Data 6", "Data 7", "Data 8"},
			{"Data 9", "Data 10", "Data 11", "Data 12"},
			{"Data 13", "Data 14", "Data 15", "Data 16"}};

		const char *const headerrow[] = {"Header row/column 1", "Header row 2", "Header row 3", "Header row 4", "Header row 5"};
		const char *const headercolumn[] = {"Header column 2", "Header column 3", "Header column 4", "Header column 5"};

		tables::options aoptions;
		aoptions.headerrow = true;
		aoptions.headercolumn = true;
		// tables::options aoptions{.headerrow = true, .headercolumn = true};

		for (unsigned int k = 0; k < size(tables::styles); ++k)
		{
			aoptions.style = k;

			tables::array(array, headerrow, headercolumn, aoptions);
		}
	}
	{
		const size_t rows = 4;
		const size_t columns = 4;

		const array<array<string, columns>, rows> aarray = {{{"Data 1", "Data 2", "Data 3", "Data 4"},
															 {"Data 5", "Data 6", "Data 7", "Data 8"},
															 {"Data 9", "Data 10", "Data 11", "Data 12"},
															 {"Data 13", "Data 14", "Data 15", "Data 16"}}};

		const string headerrow[] = {"Header row/column 1", "Header row 2", "Header row 3", "Header row 4", "Header row 5"};
		const string headercolumn[] = {"Header column 2", "Header column 3", "Header column 4", "Header column 5"};

		vector<string> aheaderrow(headerrow, headerrow + (rows + 1) - 1);
		vector<string> aheadercolumn(headerrow, headerrow + 1);
		aheadercolumn.insert(aheadercolumn.end(), headercolumn, headercolumn + columns - 1);

		for (unsigned int k = 0; k < size(tables::styles); ++k)
		{
			{
				tables::options aoptions;
				aoptions.headerrow = true;
				aoptions.headercolumn = true;
				aoptions.cellborder = true;
				aoptions.style = k;
				// tables::options aoptions{.headerrow = true, .headercolumn = true, .cellborder = true, .style = k};

				tables::array(aarray, headerrow, headercolumn, aoptions);
			}
			{
				tables::options aoptions;
				aoptions.headerrow = true;
				aoptions.headercolumn = true;
				aoptions.style = k;
				// tables::options aoptions{.headerrow = true, .headercolumn = true, .style = k};

				tables::array(aarray, headerrow, headercolumn, aoptions);
			}
			{
				string *headerrow = aheaderrow.data();
				string *headercolumn = nullptr;

				tables::options aoptions;
				aoptions.headerrow = true;
				aoptions.style = k;
				// tables::options aoptions{.headerrow = true, .style = k};

				tables::array(aarray, headerrow, headercolumn, aoptions);
			}
			{
				string *headerrow = nullptr;
				string *headercolumn = aheadercolumn.data();

				tables::options aoptions;
				aoptions.headercolumn = true;
				aoptions.style = k;
				// tables::options aoptions{.headercolumn = true, .style = k};

				tables::array(aarray, headerrow, headercolumn, aoptions);
			}
			{
				string *headerrow = nullptr;
				string *headercolumn = nullptr;

				tables::options aoptions;
				aoptions.cellborder = true;
				aoptions.style = k;
				// tables::options aoptions{.cellborder = true, .style = k};

				tables::array(aarray, headerrow, headercolumn, aoptions);
			}
			{
				string *headerrow = nullptr;
				string *headercolumn = nullptr;

				tables::options aoptions;
				aoptions.tableborder = false;
				aoptions.style = k;
				// tables::options aoptions{.tableborder = false, .style = k};

				tables::array(aarray, headerrow, headercolumn, aoptions);
			}
			{
				tables::options aoptions;
				aoptions.tableborder = false;
				aoptions.headerrow = true;
				aoptions.headercolumn = true;
				aoptions.style = k;
				// tables::options aoptions{.tableborder = false, .headerrow = true, .headercolumn = true, .style = k};

				tables::array(aarray, headerrow, headercolumn, aoptions);
			}
			{
				string *headerrow = aheaderrow.data();
				string *headercolumn = nullptr;

				tables::options aoptions;
				aoptions.tableborder = false;
				aoptions.headerrow = true;
				aoptions.style = k;
				// tables::options aoptions{.tableborder = false, .headerrow = true, .style = k};

				tables::array(aarray, headerrow, headercolumn, aoptions);
			}
			{
				string *headerrow = nullptr;
				string *headercolumn = aheadercolumn.data();

				tables::options aoptions;
				aoptions.tableborder = false;
				aoptions.headercolumn = true;
				aoptions.style = k;
				// tables::options aoptions{.tableborder = false, .headercolumn = true, .style = k};

				tables::array(aarray, headerrow, headercolumn, aoptions);
			}
			{
				string *headerrow = nullptr;
				string *headercolumn = nullptr;

				tables::options aoptions;
				aoptions.tableborder = false;
				aoptions.cellborder = true;
				aoptions.style = k;
				// tables::options aoptions{.tableborder = false, .cellborder = true, .style = k};

				tables::array(aarray, headerrow, headercolumn, aoptions);
			}
		}
	}
	{
		bool **array;
		array = new bool *[rows];
		for (unsigned int i = 0; i < rows; ++i)
			array[i] = new bool[columns];

		for (unsigned int i = 0; i < rows; ++i)
			for (unsigned int j = 0; j < columns; ++j)
				array[i][j] = rand() % 2;

		tables::options aoptions;
		aoptions.boolalpha = true;
		// tables::options aoptions{.boolalpha = true};

		for (unsigned int k = 0; k < size(tables::styles); ++k)
		{
			aoptions.style = k;

			tables::array(rows, columns, array, nullptr, nullptr, aoptions);
		}

		if (array != nullptr)
		{
			for (unsigned int i = 0; i < rows; ++i)
				delete[] array[i];

			delete[] array;
		}
	}
	// Output sorted array as table
	cout << "\nOutput sorted array as table\n\n";
	{
		int **array;
		array = new int *[rows];
		for (unsigned int i = 0; i < rows; ++i)
			array[i] = new int[columns];

		for (unsigned int i = 0; i < rows; ++i)
			for (unsigned int j = 0; j < columns; ++j)
				array[i][j] = rand();

		dimensions = columns;
		sortdimension = 0;

		// qsort(array, rows, sizeof(array[0]), compare<int *>);
		sort(array, array + rows, compare<int *>);

		tables::options aoptions;

		for (unsigned int k = 0; k < size(tables::styles); ++k)
		{
			aoptions.style = k;

			tables::array(rows, columns, array, nullptr, nullptr, aoptions);
		}

		if (array != nullptr)
		{
			for (unsigned int i = 0; i < rows; ++i)
				delete[] array[i];

			delete[] array;
		}
	}
	{
		array<array<int, columns>, rows> aarray;

		for (unsigned int i = 0; i < rows; ++i)
			for (unsigned int j = 0; j < columns; ++j)
				aarray[i][j] = rand();

		dimensions = columns;
		sortdimension = 0;

		sort(aarray.begin(), aarray.end(), compare<array<int, columns>>);

		tables::options aoptions;

		for (unsigned int k = 0; k < size(tables::styles); ++k)
		{
			aoptions.style = k;

			tables::array(aarray, headerrow, headercolumn, aoptions);
		}
	}
	{
		vector<vector<int>> array(rows, vector<int>(columns));

		for (unsigned int i = 0; i < rows; ++i)
			for (unsigned int j = 0; j < columns; ++j)
				array[i][j] = rand();

		dimensions = columns;
		sortdimension = 0;

		sort(array.begin(), array.end(), compare<vector<int>>);

		tables::options aoptions;

		for (unsigned int k = 0; k < size(tables::styles); ++k)
		{
			aoptions.style = k;

			tables::array(array, headerrow, headercolumn, aoptions);
		}
	}
	// Output single function as table
	cout << "\nOutput single function as table\n\n";
	{
		tables::options aoptions;
		aoptions.headerrow = true;
		// tables::options aoptions{.headerrow = true};

		for (unsigned int k = 0; k < size(tables::styles); ++k)
		{
			aoptions.style = k;

			tables::function(xmin, xmax, xscl, afunction, aoptions);
		}
	}
	{
		function<long double(long double)> afunction = [](auto x)
		{ return x + 1; };

		tables::options aoptions;
		aoptions.headerrow = true;
		// tables::options aoptions{.headerrow = true};

		for (unsigned int k = 0; k < size(tables::styles); ++k)
		{
			aoptions.style = k;

			tables::function(xmin, xmax, xscl, afunction, aoptions);
		}
	}
	// Output multiple functions as table
	cout << "\nOutput multiple functions as table\n\n";
	{
		function<long double(long double)> functions[] = {function1, function2};

		tables::options aoptions;
		aoptions.headerrow = true;
		// tables::options aoptions{.headerrow = true};

		for (unsigned int k = 0; k < size(tables::styles); ++k)
		{
			aoptions.style = k;

			tables::functions(xmin, xmax, xscl, 2, functions, aoptions);
		}
	}
	{
		function<long double(long double)> functions[] = {[](auto x)
														  { return 2 * x; },
														  [](auto x)
														  { return pow(x, 2); }};

		tables::options aoptions;
		aoptions.headerrow = true;
		// tables::options aoptions{.headerrow = true};

		for (unsigned int k = 0; k < size(tables::styles); ++k)
		{
			aoptions.style = k;

			tables::functions(xmin, xmax, xscl, 2, functions, aoptions);
		}
	}

	return 0;
}
