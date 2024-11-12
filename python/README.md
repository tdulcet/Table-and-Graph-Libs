## Table of Contents
* [Tables](#tables)
	* [Usage](#usage)
		* [Output str array as table](#output-str-array-as-table)
		* [Output array as table with separate header row and column](#output-array-as-table-with-separate-header-row-and-column)
		* [Output array as table](#output-array-as-table)
		* [Output sorted array as table](#output-sorted-array-as-table)
		* [Output single function as table](#output-single-function-as-table)
		* [Output lambda function as table](#output-lambda-function-as-table)
		* [Output multiple functions as table](#output-multiple-functions-as-table)
		* [Output multiple lambda functions as table](#output-multiple-lambda-functions-as-table)
	* [Options](#options)
* [Graphs/Plots](#graphsplots)
	* [Usage](#usage-1)
		* [Output array as histogram](#output-array-as-histogram)
		* [Output single array as plot](#output-single-array-as-plot)
		* [Output multiple arrays as plot](#output-single-array-as-plot)
		* [Output single function as graph](#output-single-function-as-graph)
		* [Output lambda function as graph](#output-lambda-function-as-graph)
		* [Output multiple functions as graph](#output-multiple-functions-as-graph)
		* [Output multiple lambda functions as graph](#output-multiple-lambda-functions-as-graph)
	* [Options](#options-1)

## Tables

### Usage

Requires Python 3.6 or greater and if not on Linux or macOS, the [wcwidth library](https://pypi.org/project/wcwidth/), which users can install with:
```bash
pip3 install wcwidth
# or
python3 -m pip install wcwidth
```
See the [tables.py](tables.py) file for full usage information.

Complete versions of all of the examples below and more can be found in the [test.py](test.py) file.

Run with: `python3 -OO test.py`.

#### Output str array as table

```py
import tables

# Set array

tables.array(array, headerrow=True, headercolumn=True)
```

Table cells can contain [Unicode characters](https://en.wikipedia.org/wiki/List_of_Unicode_characters) and formatted text with [ANSI escape sequences](https://en.wikipedia.org/wiki/ANSI_escape_code), but not newlines and tabs.

![](../images/char%20array%20to%20table.png)

#### Output array as table with separate header row and column

```py
import tables

headerrow = ["Header row/column 1", "Header row 2", "Header row 3", "Header row 4", "Header row 5"]
headercolumn = ["Header column 2", "Header column 3", "Header column 4", "Header column 5"]

# Set array

tables.array(array, headerrow, headercolumn, headerrow=True, headercolumn=True)
```

Output same as example above.

#### Output array as table

```py
import tables

# Set array, can be any sequence data type

tables.array(array)
```

![](../images/array%20to%20table.png)

#### Output sorted array as table

```py
import tables

# Set array

sortdimension = 0  # Column to sort by

array = sorted(array, key=lambda x: x[sortdimension])

tables.array(array)
```

![](../images/sorted%20array%20to%20table.png)

#### Output single function as table

```py
import tables

def afunction(x):
	return x + 1

xmin = -10
xmax = 10
xstep = 0.5

tables.function(xmin, xmax, xstep, afunction, headerrow=True)
```

![](../images/function%20to%20table.png)

#### Output lambda function as table

```py
import tables

xmin = -10
xmax = 10
xstep = 0.5

afunction = lambda x: x + 1

tables.function(xmin, xmax, xstep, afunction, headerrow=True)
```

Output same as example above.

#### Output multiple functions as table

```py
import tables

def function1(x):
	return 2 * x

def function2(x):
	return x ** 2

xmin = -10
xmax = 10
xstep = 0.5

# Function parameter and return value can be any data type, as long as they are the same
functions = [function1, function2]

tables.functions(xmin, xmax, xstep, functions, headerrow=True)
```

![](../images/multiple%20functions%20to%20table.png)

#### Output multiple lambda functions as table

```py
import tables

xmin = -10
xmax = 10
xstep = 0.5

# Function parameter and return value can be any data type, as long as they are the same
functions = [lambda x: 2 * x, lambda x: x ** 2]

tables.functions(xmin, xmax, xstep, functions, headerrow=True)
```

Output same as example above.

### Options

#### Header row

Option: `headerrow`\
Default value: `False`

Header rows are bolded, centered and have a border.

#### Header column

Option: `headercolumn`\
Default value: `False`

Header columns are bolded, centered and have a border.

#### Table border

Option: `tableborder`\
Default value: `True`

#### Cell border

Option: `cellborder`\
Default value: `False`

#### Cell padding

Option: `padding`\
Default value: `1`

#### Alignment

Option: `alignment`\
Values:

* `None` (default)
* `False` (left)
* `True` (right)

#### Title

Option: `title`\
Default value: `None`

The title is output at the top of the table. It is word wrapped based on the current width of the terminal. Handles newlines, tabs and [Unicode characters](https://en.wikipedia.org/wiki/List_of_Unicode_characters).

#### Border style

Option: `style`\
Values:

0. `style_types.ASCII`: ASCII
	![](../images/ASCII%20table.png)
1. `style_types.basic`: Basic
	![](../images/basic%20table.png)
2. `style_types.light`: Light (default)
	![](../images/light%20table.png)
3. `style_types.heavy`: Heavy
	![](../images/heavy%20table.png)
4. `style_types.double`: Double
	![](../images/double%20table.png)
5. `style_types.arc`: Light Arc
	![](../images/light%20arc%20table.png)
6. `style_types.light_dashed`: Light Dashed
	![](../images/light%20dashed%20table.png)
7. `style_types.heavy_dashed`: Heavy Dashed
	![](../images/heavy%20dashed%20table.png)

#### Check size

Option: `check`\
Default value: `True`

Check that the width of the table is not greater then the width of the terminal.

## Graphs/Plots

### Usage

Requires Python 3.6 or greater and if not on Linux or macOS, the [wcwidth library](https://pypi.org/project/wcwidth/), which users can install with:
```bash
pip3 install wcwidth
# or
python3 -m pip install wcwidth
```
See the [graphs.py](graphs.py) file for full usage information.

Complete versions of all of the examples below and more can be found in the [test.py](test.py) file.

Run with: `python3 -OO test.py`.

If `height` is `0`, it will be set to the current height of the terminal (number of rows times four). If `width` is `0`, it will be set to the current width of the terminal (number of columns times two).

#### Output array as histogram

```py
import graphs

height = 160
width = 160

xmin = -20
xmax = 20
ymin = -20
ymax = 20

# Set array, can be any sequence data type

graphs.histogram(height, width, xmin, xmax, ymin, ymax, array)
```

If `xmin` and `xmax` are both `0`, they will be set to the respective minimum and maximum values of x in the array. If `ymin` and `ymax` are both `0`, they will be set to the respective minimum and maximum values of y in the resulting histogram.

![](../images/array%20to%20histogram.png)

#### Output single array as plot

```py
import graphs

height = 160
width = 160

xmin = -20
xmax = 20
ymin = -20
ymax = 20

# Set array, can be any sequence data type, but must have exactly two columns

graphs.plot(height, width, xmin, xmax, ymin, ymax, array)
```

If `xmin` and `xmax` are both `0`, they will be set to the respective minimum and maximum values of x in the array. If `ymin` and `ymax` are both `0`, they will be set to the respective minimum and maximum values of y in the array.

![](../images/array%20to%20plot.png)

Use `graphs.plots()` to plot multiple arrays, which can be of different sizes.

#### Output single function as graph

```py
import graphs

def afunction(x):
	return x + 1

height = 160
width = 160

xmin = -20
xmax = 20
ymin = -20
ymax = 20

graphs.function(height, width, xmin, xmax, ymin, ymax, afunction)
```

![](../images/function%20to%20graph.png)

#### Output lambda function as graph

```py
import graphs

height = 160
width = 160

xmin = -20
xmax = 20
ymin = -20
ymax = 20

afunction = lambda x: x + 1

graphs.function(height, width, xmin, xmax, ymin, ymax, afunction)
```

Output same as example above.

#### Output multiple functions as graph

```py
import graphs

def function1(x):
	return 2 * x

def function2(x):
	return x ** 2

height = 160
width = 160

xmin = -20
xmax = 20
ymin = -20
ymax = 20

# Function parameter and return value can be any data type, as long as they are the same
functions = [function1, function2]

graphs.functions(height, width, xmin, xmax, ymin, ymax, functions)
```

![](../images/multiple%20functions%20to%20graph.png)

#### Output multiple lambda functions as graph

```py
import graphs

height = 160
width = 160

xmin = -20
xmax = 20
ymin = -20
ymax = 20

# Function parameter and return value can be any data type, as long as they are the same
functions = [lambda x: 2 * x, lambda x: x ** 2]

graphs.functions(height, width, xmin, xmax, ymin, ymax, functions)
```

Output same as example above.

### Options

#### Border

Option: `border`\
Default value: `False`

#### Axis

Option: `axis`\
Default value: `True`

#### Axis labels

Option: `axislabel`\
Default value: `True`

Requires `axis` to be `True`.

#### Axis tick marks

Option: `axistick`\
Default value: `True`

Requires `axis` to be `True`.

#### Axis units labels

Option: `axisunitslabel`\
Default value: `True`

Requires `axis` and `axistick` to be `True`.

#### X-axis units format

Option: `xunits`\
Values:

1. `units_types.number`: Locale number format
2. `units_types.scale_none`: Locale number format with full precision
3. `units_types.scale_SI`: Auto-scale to the SI standard
4. `units_types.scale_IEC`: Auto-scale to the IEC standard
5. `units_types.scale_IEC_I`: Auto-scale to the IEC standard
6. `units_types.fracts`: Locale number format, but convert fractions and mathematical constants to Unicode characters (default)
7. `units_types.percent`: Percentage format
8. `units_types.date`: Locale date format
9. `units_types.time`: Locale time format
10. `units_types.monetary`: Locale monetary/currency format

Formats 2-5 are similar to the respective `--to` options with the [numfmt](https://www.gnu.org/software/coreutils/manual/html_node/numfmt-invocation.html) command from GNU Coreutils, but with [more precision](https://github.com/tdulcet/Numbers-Tool#comparison-of---to-option).

#### Y-axis units format

Option: `yunits`\
Values: Same as above.

#### Type

Option: `type`\
Values:

1. `type_types.braille`: Braille (default)
	![](../images/type%20braille%20graph.png)
2. `type_types.block`: Block
	![](../images/type%20block%20graph.png)

The Braille type has the highest resolution of 2×4 pixels per character, while the block type uses 2×2. This option is only used for plots and graphs. Histograms use 1×8 pixels per character.

#### Mark type

Option: `mark`\
Values:

1. `mark_types.dot`: Dot (default)
	![](../images/mark%20dot%20graph.png)
2. `mark_types.plus`: Plus
	![](../images/mark%20plus%20graph.png)
3. `mark_types.square`: Square
	![](../images/mark%20square%20graph.png)

The dot mark type uses a single pixel per mark, the plus uses five pixels and the square uses eight pixels. This option is only used for plots and graphs.

#### Title

Option: `title`\
Default value: `None`

The title is output at the top of the graph. It is word wrapped based on the current width of the terminal. Handles newlines, tabs and [Unicode characters](https://en.wikipedia.org/wiki/List_of_Unicode_characters).

#### Axis/Border style

Option: `style`\
Values:

0. `style_types.ASCII`: ASCII
	![](../images/ASCII%20graph.png)
1. `style_types.basic`: Basic
	![](../images/basic%20graph.png)
2. `style_types.light`: Light (default)
	![](../images/light%20graph.png)
3. `style_types.heavy`: Heavy
	![](../images/heavy%20graph.png)
4. `style_types.double`: Double
	![](../images/double%20graph.png)
5. `style_types.arc`: Light Arc
	![](../images/light%20arc%20graph.png)
6. `style_types.light_dashed`: Light Dashed
	![](../images/light%20dashed%20graph.png)
7. `style_types.heavy_dashed`: Heavy Dashed
	![](../images/heavy%20dashed%20graph.png)

#### Graph/Plot Color

Option: `color`\
Values:

0. `color_types.default`: System default
1. `color_types.black`: Black
2. `color_types.red`: Red (default)
3. `color_types.green`: Green
4. `color_types.yellow`: Yellow
5. `color_types.blue`: Blue
6. `color_types.magenta`: Magenta
7. `color_types.cyan`: Cyan
8. `color_types.white`: White
9. `color_types.gray`: Gray
10. `color_types.bright_red`: Bright Red
11. `color_types.bright_green`: Bright Green
12. `color_types.bright_yellow`: Bright Yellow
13. `color_types.bright_blue`: Bright Blue
14. `color_types.bright_magenta`: Bright Magenta
15. `color_types.bright_cyan`: Bright Cyan
16. `color_types.bright_white`: Bright White

See here for [examples of the colors](https://misc.flogisoft.com/bash/tip_colors_and_formatting#foreground_text).

This option is only used when plotting a single array and when graphing a single function. When plotting multiple arrays or graphing multiple functions, colors 2 - 16 are used inorder. The system default color is used where the plots cross.

##### Plot

![](../images/plot%20colors.png)

##### Graph

![](../images/graph%20colors.png)

#### Check size

Option: `check`\
Default value: `True`

Check that the width and height of the graph are not greater then the respective width and height of the terminal.
