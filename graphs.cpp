// Teal Dulcet, CS546

// Compile: g++ -std=c++14 -Wall -g -O3 graphs.cpp -o graphs

// Run: ./graphs

#include <cctype>
#include <array>
#include <vector>
#include <random>

#include "graphs.hpp"

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

constexpr long double function3(long double x)
{
	return sin(x);
}

constexpr long double function4(long double x)
{
	return cos(x);
}

constexpr long double function5(long double x)
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

	// Output array as histogram
	cout << "\nOutput array as histogram\n\n";
	{
		const size_t rows = 100;

		default_random_engine generator;
		normal_distribution<long double> distribution(0, 1);

		{
			long double *array;
			array = new long double[rows];

			for (unsigned i = 0; i < rows; ++i)
				array[i] = distribution(generator);

			graphs::options aoptions;

			for (const graphs::style_type style : graphs::style_types)
			{
				aoptions.style = style;

				graphs::histogram(height, width, xmin, xmax, ymin, ymax, rows, array, aoptions);
			}

			if (array)
				delete[] array;
		}
		{
			array<long double, rows> aarray;

			for (unsigned i = 0; i < rows; ++i)
				aarray[i] = distribution(generator);

			graphs::options aoptions;

			for (const graphs::style_type style : graphs::style_types)
			{
				aoptions.style = style;

				graphs::histogram(height, width, xmin, xmax, ymin, ymax, aarray, aoptions);
			}
		}
		{
			vector<long double> array(rows);

			for (unsigned i = 0; i < rows; ++i)
				array[i] = distribution(generator);

			graphs::options aoptions;

			for (const graphs::style_type style : graphs::style_types)
			{
				aoptions.style = style;

				graphs::histogram(height, width, xmin, xmax, ymin, ymax, array, aoptions);
			}
		}
	}

	// Output single array as plot
	cout << "\nOutput array as plot\n\n";
	{
		long double **array;
		array = new long double *[rows];
		for (unsigned i = 0; i < rows; ++i)
			array[i] = new long double[columns];

		for (unsigned i = 0; i < rows; ++i)
			for (unsigned j = 0; j < columns; ++j)
				array[i][j] = i + j; // rand();

		graphs::options aoptions;

		for (const graphs::type_type type : graphs::type_types)
		{
			aoptions.type = type;

			for (const graphs::mark_type mark : graphs::mark_types)
			{
				aoptions.mark = mark;

				for (const graphs::style_type style : graphs::style_types)
				{
					aoptions.style = style;

					graphs::plot(height, width, xmin, xmax, ymin, ymax, rows, array, aoptions);
				}
			}
		}

		if (array)
		{
			for (unsigned i = 0; i < rows; ++i)
				delete[] array[i];

			delete[] array;
		}
	}
	{
		array<array<long double, columns>, rows> aarray;

		for (unsigned i = 0; i < rows; ++i)
			for (unsigned j = 0; j < columns; ++j)
				aarray[i][j] = i + j; // rand();

		graphs::options aoptions;

		for (const graphs::type_type type : graphs::type_types)
		{
			aoptions.type = type;

			for (const graphs::mark_type mark : graphs::mark_types)
			{
				aoptions.mark = mark;

				for (const graphs::style_type style : graphs::style_types)
				{
					aoptions.style = style;

					graphs::plot(height, width, xmin, xmax, ymin, ymax, aarray, aoptions);
				}
			}
		}
	}
	{
		vector<vector<long double>> array(rows, vector<long double>(columns));

		for (unsigned i = 0; i < rows; ++i)
			for (unsigned j = 0; j < columns; ++j)
				array[i][j] = i + j; // rand();

		graphs::options aoptions;

		for (const graphs::type_type type : graphs::type_types)
		{
			aoptions.type = type;

			for (const graphs::mark_type mark : graphs::mark_types)
			{
				aoptions.mark = mark;

				for (const graphs::style_type style : graphs::style_types)
				{
					aoptions.style = style;

					graphs::plot(height, width, xmin, xmax, ymin, ymax, array, aoptions);
				}
			}
		}
	}
	// Output single function as graph
	cout << "\nOutput single function as graph\n\n";
	{
		graphs::options aoptions;

		for (const graphs::style_type style : graphs::style_types)
		{
			aoptions.style = style;

			graphs::function(height, width, xmin, xmax, ymin, ymax, afunction, aoptions);
		}
	}
	{
		const function<long double(long double)> afunction = [](auto x)
		{ return x + 1; };

		graphs::options aoptions;

		for (const graphs::style_type style : graphs::style_types)
		{
			aoptions.style = style;

			graphs::function(height, width, xmin, xmax, ymin, ymax, afunction, aoptions);
		}
	}
	// Output multiple functions as graph
	cout << "\nOutput multiple functions as graph\n\n";
	{
		function<long double(long double)> functions[] = {function1, function2};

		graphs::options aoptions;

		for (const graphs::style_type style : graphs::style_types)
		{
			aoptions.style = style;

			graphs::functions(height, width, xmin, xmax, ymin, ymax, graphs::size(functions), functions, aoptions);
		}
	}
	{
		function<long double(long double)> functions[] = {[](auto x)
														  { return 2 * x; },
														  [](auto x)
														  { return pow(x, 2); }};

		graphs::options aoptions;

		for (const graphs::style_type style : graphs::style_types)
		{
			aoptions.style = style;

			graphs::functions(height, width, xmin, xmax, ymin, ymax, graphs::size(functions), functions, aoptions);
		}
	}
	{
		const long double xmin = -(2 * M_PI);
		const long double xmax = 2 * M_PI;
		const long double ymin = -4;
		const long double ymax = 4;

		function<long double(long double)> functions[] = {function3, function4, function5};

		graphs::options aoptions;
		aoptions.axisunitslabel = false;
		// graphs::options aoptions{.axisunitslabel = false};

		for (const graphs::style_type style : graphs::style_types)
		{
			aoptions.style = style;

			graphs::functions(height, width, xmin, xmax, ymin, ymax, graphs::size(functions), functions, aoptions);
		}

		/* aoptions.style = 2;

		for (unsigned k = 10; k < 300; ++k)
		{
			cout << "\e[1;1H"
				 << "\e[2J";

			graphs::functions(k, k, xmin, xmax, ymin, ymax, graphs::size(functions), functions, aoptions);

			usleep(200000);
		} */
	}

	return 0;
}
