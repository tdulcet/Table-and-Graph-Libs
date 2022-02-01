// Teal Dulcet, CS546

// Compile: g++ -Wall -g -O3 tables.cpp -o tables

// Run: ./tables

#include <cctype>
#include <cmath>
#include <algorithm>
#include "tables.hpp"

using namespace std;

long double afunction(long double x)
{
	return x + 1;
}

long double function1(long double x)
{
	return 2 * x;
}

long double function2(long double x)
{
	return pow(x, 2);
}

int dimensions = 0;
int sortdimension = 0;

/* template <typename T>
int compare(const void *pa, const void *pb)
{
	const T *a = *(const T **)pa;
	const T *b = *(const T **)pb;

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
bool compare(const T *a, const T *b)
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

		tableoptions aoptions;

		for (unsigned int k = 0; k < (sizeof styles / sizeof styles[0]); ++k)
		{
			aoptions.style = k;

			table(rows, columns, array, NULL, NULL, aoptions);
		}

		if (array != NULL)
		{
			for (unsigned int i = 0; i < rows; ++i)
				delete[] array[i];

			delete[] array;
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

		tableoptions aoptions;

		for (unsigned int k = 0; k < (sizeof styles / sizeof styles[0]); ++k)
		{
			aoptions.style = k;

			table(rows, columns, array, NULL, NULL, aoptions);
		}

		if (array != NULL)
		{
			for (unsigned int i = 0; i < rows; ++i)
				delete[] array[i];

			delete[] array;
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

		tableoptions aoptions;
		aoptions.headerrow = true;
		aoptions.headercolumn = true;

		for (unsigned int k = 0; k < (sizeof styles / sizeof styles[0]); ++k)
		{
			aoptions.style = k;

			table(rows, columns, array, NULL, NULL, aoptions);
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

		tableoptions aoptions;
		aoptions.headerrow = true;
		aoptions.headercolumn = true;

		for (unsigned int k = 0; k < (sizeof styles / sizeof styles[0]); ++k)
		{
			aoptions.style = k;

			table(rows, columns, array, headerrow, headercolumn, aoptions);
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

		tableoptions aoptions;
		aoptions.boolalpha = true;

		for (unsigned int k = 0; k < (sizeof styles / sizeof styles[0]); ++k)
		{
			aoptions.style = k;

			table(rows, columns, array, NULL, NULL, aoptions);
		}

		if (array != NULL)
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

		// qsort(array, rows, sizeof(array[0]), compare<int>);
		sort(array, array + rows, compare<int>);

		tableoptions aoptions;

		for (unsigned int k = 0; k < (sizeof styles / sizeof styles[0]); ++k)
		{
			aoptions.style = k;

			table(rows, columns, array, NULL, NULL, aoptions);
		}

		if (array != NULL)
		{
			for (unsigned int i = 0; i < rows; ++i)
				delete[] array[i];

			delete[] array;
		}
	}
	// Output single function as table
	cout << "\nOutput single function as table\n\n";
	{
		tableoptions aoptions;
		aoptions.headerrow = true;

		for (unsigned int k = 0; k < (sizeof styles / sizeof styles[0]); ++k)
		{
			aoptions.style = k;

			table(xmin, xmax, xscl, afunction, aoptions);
		}
	}
	// Output multiple functions as table
	cout << "\nOutput multiple functions as table\n\n";
	{
		long double (*functions[])(long double) = {function1, function2};

		tableoptions aoptions;
		aoptions.headerrow = true;

		for (unsigned int k = 0; k < (sizeof styles / sizeof styles[0]); ++k)
		{
			aoptions.style = k;

			table(xmin, xmax, xscl, 2, functions, aoptions);
		}
	}

	return 0;
}
