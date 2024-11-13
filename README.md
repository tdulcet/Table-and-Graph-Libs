[![Actions Status](https://github.com/tdulcet/Table-and-Graph-Libs/actions/workflows/ci.yml/badge.svg?branch=master)](https://github.com/tdulcet/Table-and-Graph-Libs/actions/workflows/ci.yml)

# Table and Graph Libraries

Console Table and Graph/Plot Libraries

Copyright © 2018 Teal Dulcet

These header only libraries use [box-drawing](https://en.wikipedia.org/wiki/Box-drawing_character#Unicode), [Braille](https://en.wikipedia.org/wiki/Braille_Patterns), [fraction](https://en.wikipedia.org/wiki/Number_Forms) and other Unicode characters and [terminal colors and formatting](https://misc.flogisoft.com/bash/tip_colors_and_formatting) to output tables and graphs/plots to the console. All the tables and graphs are created with a single (one) function call and they do not require any special data structures.

See the [python](python) directory for Python ports of the libraries.

For command-line tools using these respective libraries, see the [Tables and Graphs CLI](https://github.com/tdulcet/Tables-and-Graphs-CLI).

❤️ Please visit [tealdulcet.com](https://www.tealdulcet.com/) to support these libraries and my other software development.

## Table of Contents
* [Tables](#tables)
	* [Usage](#usage)
		* [Output char array as table](#output-char-array-as-table)
		* [Output array as table with separate header row and column](#output-array-as-table-with-separate-header-row-and-column)
		* [Output array as table](#output-array-as-table)
		* [Output sorted array as table](#output-sorted-array-as-table)
		* [Output single function as table](#output-single-function-as-table)
		* [Output multiple functions as table](#output-multiple-functions-as-table)
	* [Options](#options)
* [Graphs/Plots](#graphsplots)
	* [Usage](#usage-1)
		* [Output array as histogram](#output-array-as-histogram)
		* [Output single array as plot](#output-single-array-as-plot)
		* [Output multiple arrays as plot](#output-single-array-as-plot)
		* [Output single function as graph](#output-single-function-as-graph)
		* [Output multiple functions as graph](#output-multiple-functions-as-graph)
	* [Options](#options-1)
* [Contributing](#contributing)

## Tables

### Usage

Requires support for C++17. See the [tables.hpp](tables.hpp) file for full usage information.

Complete versions of all of the examples below and more can be found in the [tables.cpp](tables.cpp) file.

Compile with:
* GCC: `g++ -std=c++17 -Wall -g -O3 tables.cpp -o tables`
* Clang: `clang++ -std=c++17 -Wall -g -O3 tables.cpp -o tables`

Other compilers should work as well, but are not (yet) tested.

Run with: `./tables`

#### Output char array as table

##### C style char array

```cpp
#include "tables.hpp"

using namespace std;

int main()
{
	size_t rows = 5;
	size_t columns = 5;

	char ***array;

	// Allocate and set array

	tables::options aoptions = {.headerrow = true, .headercolumn = true};

	tables::array(rows, columns, array, nullptr, nullptr, aoptions);

	// Deallocate array

	return 0;
}
```

##### C++ string array

```cpp
#include "tables.hpp"

using namespace std;

int main()
{
	size_t rows = 5;
	size_t columns = 5;

	vector<vector<string>> array(rows, vector<string>(columns));

	// Set array

	string *headerrow = nullptr;
	string *headercolumn = nullptr;

	tables::options aoptions = {.headerrow = true, .headercolumn = true};

	tables::array(array, headerrow, headercolumn, aoptions);

	return 0;
}
```

Table cells can contain [Unicode characters](https://en.wikipedia.org/wiki/List_of_Unicode_characters) and formatted text with [ANSI escape sequences](https://en.wikipedia.org/wiki/ANSI_escape_code), but not newlines and tabs.

![](images/char%20array%20to%20table.png)

#### Output array as table with separate header row and column

##### C style char array

```cpp
#include "tables.hpp"

using namespace std;

int main()
{
	size_t rows = 4;
	size_t columns = 4;

	const char* headerrow[] = {"Header row/column 1", "Header row 2", "Header row 3", "Header row 4", "Header row 5"};
	const char* headercolumn[] = {"Header column 2", "Header column 3", "Header column 4", "Header column 5"};

	char ***array;

	// Allocate and set array

	tables::options aoptions = {.headerrow = true, .headercolumn = true};

	tables::array(rows, columns, array, headerrow, headercolumn, aoptions);

	// Deallocate array

	return 0;
}
```

##### C++ string array

```cpp
#include "tables.hpp"

using namespace std;

int main()
{
	size_t rows = 5;
	size_t columns = 5;

	string headerrow[] = {"Header row/column 1", "Header row 2", "Header row 3", "Header row 4", "Header row 5"};
	string headercolumn[] = {"Header column 2", "Header column 3", "Header column 4", "Header column 5"};

	vector<vector<string>> array(rows, vector<string>(columns));

	// Set array

	tables::options aoptions = {.headerrow = true, .headercolumn = true};

	tables::array(array, headerrow, headercolumn, aoptions);

	return 0;
}
```

Output same as example above.

#### Output array as table

##### C style pointer

```cpp
#include "tables.hpp"

using namespace std;

int main()
{
	size_t rows = 5;
	size_t columns = 5;

	double **array; // array can be any data type

	// Allocate and set array

	tables::array(rows, columns, array);

	// Deallocate array

	return 0;
}
```

##### C++ array/vector

```cpp
#include "tables.hpp"

using namespace std;

int main()
{
	size_t rows = 5;
	size_t columns = 5;

	vector<vector<double>> array(rows, vector<double>(columns)); // array can be any data type

	// Set array

	tables::array(array);

	return 0;
}
```

![](images/array%20to%20table.png)

#### Output sorted array as table

##### C style pointer

```cpp
#include <algorithm>
#include "tables.hpp"

using namespace std;

int dimensions; // Number of columns
int sortdimension; // Column to sort by

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
	size_t rows = 5;
	size_t columns = 5;

	int **array; // array can be any data type

	// Allocate and set array

	dimensions = columns;
	sortdimension = 0;

	sort(array, array + rows, compare<int *>);

	tables::array(rows, columns, array);

	// Deallocate array

	return 0;
}
```

##### C++ array/vector

```cpp
#include <algorithm>
#include "tables.hpp"

using namespace std;

int sortdimension; // Column to sort by

template <typename T>
bool compare(const T &a, const T &b)
{
	if (a[sortdimension] == b[sortdimension])
		for (int i = 0; i < tables::size(a); ++i)
			if (sortdimension != i and a[i] != b[i])
				return a[i] < b[i];

	return a[sortdimension] < b[sortdimension];
}

int main()
{
	size_t rows = 5;
	size_t columns = 5;

	vector<vector<int>> array(rows, vector<int>(columns)); // array can be any data type

	// Set array

	sortdimension = 0;

	sort(array.begin(), array.end(), compare<vector<int>>);

	tables::array(array);

	return 0;
}
```

![](images/sorted%20array%20to%20table.png)

#### Output single function as table

##### C style function pointer

```cpp
#include "tables.hpp"

using namespace std;

double afunction(double x)
{
	return x + 1;
}

int main()
{
	double xmin = -10;
	double xmax = 10;
	double xstep = 0.5;

	tables::options aoptions = {.headerrow = true};

	tables::function(xmin, xmax, xstep, afunction, aoptions);

	return 0;
}
```

##### C++ lambda function

```cpp
#include "tables.hpp"

using namespace std;

int main()
{
	double xmin = -10;
	double xmax = 10;
	double xstep = 0.5;

	function<double(double)> afunction = [](auto x)
	{ return x + 1; };

	tables::options aoptions = {.headerrow = true};

	tables::function(xmin, xmax, xstep, afunction, aoptions);

	return 0;
}
```

![](images/function%20to%20table.png)

#### Output multiple functions as table

##### C style function pointer

```cpp
#include <cmath>
#include "tables.hpp"

using namespace std;

double function1(double x)
{
	return 2 * x;
}

double function2(double x)
{
	return pow(x, 2);
}

int main()
{
	double xmin = -10;
	double xmax = 10;
	double xstep = 0.5;

	size_t numfunctions = 2;

	// Function parameter and return value can be any data type, as long as they are the same
	function<double(double)> functions[] = {function1, function2};

	tables::options aoptions = {.headerrow = true};

	tables::functions(xmin, xmax, xstep, numfunctions, functions, aoptions);

	return 0;
}
```

##### C++ lambda function

```cpp
#include <cmath>
#include "tables.hpp"

using namespace std;

int main()
{
	double xmin = -10;
	double xmax = 10;
	double xstep = 0.5;

	size_t numfunctions = 2;

	// Function parameter and return value can be any data type, as long as they are the same
	function<double(double)> functions[] = {[](auto x)
											{ return 2 * x; },
											[](auto x)
											{ return pow(x, 2); }};

	tables::options aoptions = {.headerrow = true};

	tables::functions(xmin, xmax, xstep, numfunctions, functions, aoptions);

	return 0;
}
```

![](images/multiple%20functions%20to%20table.png)

### Options

#### Header row

Option: `headerrow`\
Default value: `false`

Header rows are bolded, centered and have a border.

#### Header column

Option: `headercolumn`\
Default value: `false`

Header columns are bolded, centered and have a border.

#### Table border

Option: `tableborder`\
Default value: `true`

#### Cell border

Option: `cellborder`\
Default value: `false`

#### Cell padding

Option: `padding`\
Default value: `1`

#### Alignment

Option: `alignment`\
Values:

* `nullptr`
* `left` (default)
* `right`
* `internal` (integer and floating-point types only)

#### bool to alpha

Option: `boolalpha`\
Default value: `false`

#### Title

Option: `title`\
Default value: `nullptr`

The title is output at the top of the table. It is word wrapped based on the current width of the terminal, using [this](https://gist.github.com/tdulcet/819821ca69501822ad3f84a060c640a0) solution. Handles newlines, tabs and [Unicode characters](https://en.wikipedia.org/wiki/List_of_Unicode_characters).

#### Border style

Option: `style`\
Values:

0. `style_ASCII`: ASCII
	![](images/ASCII%20table.png)
1. `style_basic`: Basic
	![](images/basic%20table.png)
2. `style_light`: Light (default)
	![](images/light%20table.png)
3. `style_heavy`: Heavy
	![](images/heavy%20table.png)
4. `style_double`: Double
	![](images/double%20table.png)
5. `style_arc`: Light Arc
	![](images/light%20arc%20table.png)
6. `style_light_dashed`: Light Dashed
	![](images/light%20dashed%20table.png)
7. `style_heavy_dashed`: Heavy Dashed
	![](images/heavy%20dashed%20table.png)

#### Check size

Option: `check`\
Default value: `true`

Check that the width of the table is not greater then the width of the terminal.

### Other C++ Console Tables Libraries

* [C++ Text Table](https://github.com/haarcuba/cpp-text-table) (must specify every cell individually in their data structure, limited options, no Unicode support, no header row or column support)
* [Cpp Console Table](https://github.com/Oradle/CppConsoleTable) (must specify every cell individually in their data structure, no Unicode support, no header row or column support)
* [ConsoleTable](https://github.com/766F6964/ConsoleTable) (requires C++11, must specify entire row at once in their data structure, no header column support)

## Graphs/Plots

### Usage

Requires support for C++17. See the [graphs.hpp](graphs.hpp) file for full usage information.

Complete versions of all of the examples below and more can be found in the [graphs.cpp](graphs.cpp) file.

Compile with:
* GCC: `g++ -std=c++17 -Wall -g -O3 graphs.cpp -o graphs`
* Clang: `clang++ -std=c++17 -Wall -g -O3 graphs.cpp -o graphs`

Other compilers should work as well, but are not (yet) tested.

Run with: `./graphs`

If `height` is `0`, it will be set to the current height of the terminal (number of rows times four). If `width` is `0`, it will be set to the current width of the terminal (number of columns times two).

#### Output array as histogram

##### C style pointer

```cpp
#include "graphs.hpp"

using namespace std;

int main()
{
	size_t height = 160;
	size_t width = 160;

	long double xmin = -20;
	long double xmax = 20;
	long double ymin = -20;
	long double ymax = 20;

	size_t rows = 100;

	double *array; // array can be any data type

	// Allocate and set array

	graphs::histogram(height, width, xmin, xmax, ymin, ymax, rows, array);

	// Deallocate array

	return 0;
}
```

##### C++ array/vector

```cpp
#include "graphs.hpp"

using namespace std;

int main()
{
	size_t height = 160;
	size_t width = 160;

	long double xmin = -20;
	long double xmax = 20;
	long double ymin = -20;
	long double ymax = 20;

	size_t rows = 100;

	vector<double> array(rows); // array can be any data type

	// Set array

	graphs::histogram(height, width, xmin, xmax, ymin, ymax, array);

	return 0;
}
```

If `xmin` and `xmax` are both `0`, they will be set to the respective minimum and maximum values of x in the array. If `ymin` and `ymax` are both `0`, they will be set to the respective minimum and maximum values of y in the resulting histogram.

![](images/array%20to%20histogram.png)

#### Output single array as plot

##### C style pointer

```cpp
#include "graphs.hpp"

using namespace std;

int main()
{
	size_t height = 160;
	size_t width = 160;

	long double xmin = -20;
	long double xmax = 20;
	long double ymin = -20;
	long double ymax = 20;

	size_t rows = 10;

	double **array; // array can be any data type, but must have exactly two columns

	// Allocate and set array

	graphs::plot(height, width, xmin, xmax, ymin, ymax, rows, array);

	// Deallocate array

	return 0;
}
```

##### C++ array/vector

```cpp
#include "graphs.hpp"

using namespace std;

int main()
{
	size_t height = 160;
	size_t width = 160;

	long double xmin = -20;
	long double xmax = 20;
	long double ymin = -20;
	long double ymax = 20;

	size_t rows = 10;

	vector<vector<double>> array(rows, vector<double>(2)); // array can be any data type, but must have exactly two columns

	// Set array

	graphs::plot(height, width, xmin, xmax, ymin, ymax, array);

	return 0;
}
```

If `xmin` and `xmax` are both `0`, they will be set to the respective minimum and maximum values of x in the array. If `ymin` and `ymax` are both `0`, they will be set to the respective minimum and maximum values of y in the array.

![](images/array%20to%20plot.png)

Use `graphs::plots()` to plot multiple arrays, which can be of different sizes.

#### Output single function as graph

##### C style function pointer

```cpp
#include "graphs.hpp"

using namespace std;

double afunction(double x)
{
	return x + 1;
}

int main()
{
	size_t height = 160;
	size_t width = 160;

	long double xmin = -20;
	long double xmax = 20;
	long double ymin = -20;
	long double ymax = 20;

	graphs::function(height, width, xmin, xmax, ymin, ymax, afunction);

	return 0;
}
```

##### C++ lambda function

```cpp
#include "graphs.hpp"

using namespace std;

int main()
{
	size_t height = 160;
	size_t width = 160;

	long double xmin = -20;
	long double xmax = 20;
	long double ymin = -20;
	long double ymax = 20;

	function<double(double)> afunction = [](auto x)
	{ return x + 1; };

	graphs::function(height, width, xmin, xmax, ymin, ymax, afunction);

	return 0;
}
```

![](images/function%20to%20graph.png)

#### Output multiple functions as graph

##### C style function pointer

```cpp
#include "graphs.hpp"

using namespace std;

double function1(double x)
{
	return 2 * x;
}

double function2(double x)
{
	return pow(x, 2);
}

int main()
{
	size_t height = 160;
	size_t width = 160;

	long double xmin = -20;
	long double xmax = 20;
	long double ymin = -20;
	long double ymax = 20;

	size_t numfunctions = 2;

	// Function parameter and return value can be any data type, as long as they are the same
	function<double(double)> functions[] = {function1, function2};

	graphs::functions(height, width, xmin, xmax, ymin, ymax, numfunctions, functions);

	return 0;
}
```

##### C++ lambda function

```cpp
#include "graphs.hpp"

using namespace std;

int main()
{
	size_t height = 160;
	size_t width = 160;

	long double xmin = -20;
	long double xmax = 20;
	long double ymin = -20;
	long double ymax = 20;

	size_t numfunctions = 2;

	// Function parameter and return value can be any data type, as long as they are the same
	function<double(double)> functions[] = {[](auto x)
											{ return 2 * x; },
											[](auto x)
											{ return pow(x, 2); }};

	graphs::functions(height, width, xmin, xmax, ymin, ymax, numfunctions, functions);

	return 0;
}
```

![](images/multiple%20functions%20to%20graph.png)

### Options

#### Border

Option: `border`\
Default value: `false`

#### Axis

Option: `axis`\
Default value: `true`

#### Axis labels

Option: `axislabel`\
Default value: `true`

Requires `axis` to be `true`.

#### Axis tick marks

Option: `axistick`\
Default value: `true`

Requires `axis` to be `true`.

#### Axis units labels

Option: `axisunitslabel`\
Default value: `true`

Requires `axis` and `axistick` to be `true`.

#### X-axis units format

Option: `xunits`\
Values:

1. `units_number`: Locale number format
2. `units_scale_none`: Locale number format with full precision
3. `units_scale_SI`: Auto-scale to the SI standard
4. `units_scale_IEC`: Auto-scale to the IEC standard
5. `units_scale_IEC_I`: Auto-scale to the IEC standard
6. `units_fracts`: Locale number format, but convert fractions and mathematical constants to Unicode characters (default)
6. `units_percent`: Percentage format
7. `units_date`: Locale date format
8. `units_time`: Locale time format
9. `units_monetary`: Locale monetary/currency format

Formats 2-5 are similar to the respective `--to` options with the [numfmt](https://www.gnu.org/software/coreutils/manual/html_node/numfmt-invocation.html) command from GNU Coreutils, but with [more precision](https://github.com/tdulcet/Numbers-Tool#comparison-of---to-option).

#### Y-axis units format

Option: `yunits`\
Values: Same as above.

#### Type

Option: `type`\
Values:

1. `type_braille`: Braille (default)
	![](images/type%20braille%20graph.png)
2. `type_block`: Block
	![](images/type%20block%20graph.png)

The Braille type has the highest resolution of 2×4 pixels per character, while the block type uses 2×2. This option is only used for plots and graphs. Histograms use 1×8 pixels per character.

#### Mark type

Option: `mark`\
Values:

1. `mark_dot`: Dot (default)
	![](images/mark%20dot%20graph.png)
2. `mark_plus`: Plus
	![](images/mark%20plus%20graph.png)
3. `mark_square`: Square
	![](images/mark%20square%20graph.png)

The dot mark type uses a single pixel per mark, the plus uses five pixels and the square uses eight pixels. This option is only used for plots and graphs.

#### Title

Option: `title`\
Default value: `nullptr`

The title is output at the top of the graph. It is word wrapped based on the current width of the terminal, using [this](https://gist.github.com/tdulcet/819821ca69501822ad3f84a060c640a0) solution. Handles newlines, tabs and [Unicode characters](https://en.wikipedia.org/wiki/List_of_Unicode_characters).

#### Axis/Border style

Option: `style`\
Values:

0. `style_ASCII`: ASCII
	![](images/ASCII%20graph.png)
1. `style_basic`: Basic
	![](images/basic%20graph.png)
2. `style_light`: Light (default)
	![](images/light%20graph.png)
3. `style_heavy`: Heavy
	![](images/heavy%20graph.png)
4. `style_double`: Double
	![](images/double%20graph.png)
5. `style_arc`: Light Arc
	![](images/light%20arc%20graph.png)
6. `style_light_dashed`: Light Dashed
	![](images/light%20dashed%20graph.png)
7. `style_heavy_dashed`: Heavy Dashed
	![](images/heavy%20dashed%20graph.png)

#### Graph/Plot Color

Option: `color`\
Values:

0. `color_default`: System default
1. `color_black`: Black
2. `color_red`: Red (default)
3. `color_green`: Green
4. `color_yellow`: Yellow
5. `color_blue`: Blue
6. `color_magenta`: Magenta
7. `color_cyan`: Cyan
8. `color_white`: White
9. `color_gray`: Gray
10. `color_bright_red`: Bright Red
11. `color_bright_green`: Bright Green
12. `color_bright_yellow`: Bright Yellow
13. `color_bright_blue`: Bright Blue
14. `color_bright_magenta`: Bright Magenta
15. `color_bright_cyan`: Bright Cyan
16. `color_bright_white`: Bright White

See here for [examples of the colors](https://misc.flogisoft.com/bash/tip_colors_and_formatting#foreground_text).

This option is only used when plotting a single array and when graphing a single function. When plotting multiple arrays or graphing multiple functions, colors 2 - 16 are used inorder. The system default color is used where the plots cross.

##### Plot

![](images/plot%20colors.png)

##### Graph

![](images/graph%20colors.png)

#### Check size

Option: `check`\
Default value: `true`

Check that the width and height of the graph are not greater then the respective width and height of the terminal.

### Other C++ Console Graphs/Plots Libraries

* [C++ terminal plotting library](https://github.com/fbbdev/plot) (requires C++14, based on [UnicodePlots.jl](https://github.com/Evizero/UnicodePlots.jl), no documentation and very difficult to use, although supports animations)

## Contributing

Pull requests welcome! Ideas for contributions:

Both:
* Add more options
	* Add options to word wrap and truncate long text in table cells
	* Add option to center text in table cells
* Add more examples
* Improve the performance
* Handle newlines and tabs in the tables
* Handle formatted text in the table and graph/plot titles
* Support more graph/plot colors
	* Support 256 and 24-bit color
	* Support combining/blending colors when functions cross
* Update the `-t, --table` options of column command from [util-linux](https://en.wikipedia.org/wiki/Util-linux) to use the Table library
* Port to other languages (C, Java, Rust, etc.)

C++:
* Update the CI to test with more compilers
* Support tables with the `wchar_t`, `char16_t` and `char32_t` C data types and the `wstring`, `u16string` and `u32string` C++ data types.
