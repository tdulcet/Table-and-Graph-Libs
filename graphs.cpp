// Teal Dulcet, CS546

// Compile: g++ -Wall -g -O3 graphs.cpp -o graphs

// Run: ./graphs

#include <cctype>
#include "graphs.hpp"

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

long double function3(long double x)
{
	return sin(x);
}

long double function4(long double x)
{
	return cos(x);
}

long double function5(long double x)
{
	return tan(x);
}

int main()
{
	const size_t height = 160;
	const size_t width = 160;

	const long double xmin = -20;
	const long double xmax = 20;
	const long double ymin = -20;
	const long double ymax = 20;

	const size_t rows = 10;
	const size_t columns = 2;

	// Output array as plot
	cout << "\nOutput array as plot\n\n";
	{
		long double **array;
		array = new long double *[rows];
		for (unsigned int i = 0; i < rows; ++i)
			array[i] = new long double[columns];

		for (unsigned int i = 0; i < rows; ++i)
			for (unsigned int j = 0; j < columns; ++j)
				array[i][j] = i + j; //rand();

		graphoptions aoptions;

		for (unsigned int k = 0; k < (sizeof styles / sizeof styles[0]); ++k)
		{
			aoptions.style = k;

			graph(height, width, xmin, xmax, ymin, ymax, rows, array, aoptions);
		}

		if (array != NULL)
		{
			for (unsigned int i = 0; i < rows; ++i)
				delete[] array[i];

			delete[] array;
		}
	}
	// Output single function as graph
	cout << "\nOutput single function as graph\n\n";
	{
		graphoptions aoptions;

		for (unsigned int k = 0; k < (sizeof styles / sizeof styles[0]); ++k)
		{
			aoptions.style = k;

			graph(height, width, xmin, xmax, ymin, ymax, afunction, aoptions);
		}
	}
	// Output multiple functions as graph
	cout << "\nOutput multiple functions as graph\n\n";
	{
		long double (*functions[])(long double) = {function1, function2};

		graphoptions aoptions;

		for (unsigned int k = 0; k < (sizeof styles / sizeof styles[0]); ++k)
		{
			aoptions.style = k;

			graph(height, width, xmin, xmax, ymin, ymax, 2, functions, aoptions);
		}
	}
	{
		const long double xmin = -(2 * M_PI);
		const long double xmax = 2 * M_PI;
		const long double ymin = -4;
		const long double ymax = 4;

		long double (*functions[])(long double) = {function3, function4, function5};

		graphoptions aoptions;
		aoptions.axisunitslabel = false;

		for (unsigned int k = 0; k < (sizeof styles / sizeof styles[0]); ++k)
		{
			aoptions.style = k;

			graph(height, width, xmin, xmax, ymin, ymax, 3, functions, aoptions);
		}

		/*aoptions.style = 2;
		
		for (unsigned int k = 10; k < 300; ++k)
		{
			cout << "\e[1;1H" << "\e[2J";

			graph(k, k, xmin, xmax, ymin, ymax, 3, functions, aoptions);
			
			usleep(200000);
		}*/
	}

	return 0;
}
