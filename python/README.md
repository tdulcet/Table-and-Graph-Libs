## Tables

### Usage

Requires Python 3.5 or greater and the [wcwidth library](https://pypi.org/project/wcwidth/), which users can install with: `pip3 install wcwidth`. See the [tables.py](tables.py) file for full usage information.

Complete versions of all of the examples below and more can be found in the [test.py](test.py) file.

Run with: `python3 test.py`.

#### Output str array as table

```py
import tables

# Set array

tables.array(array, headerrow=True, headercolumn=True)
```

Table cells can contain [Unicode characters](https://en.wikipedia.org/wiki/List_of_Unicode_characters), but not newlines and tabs.

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
xscl = 2

tables.function(xmin, xmax, xscl, afunction, headerrow=True)
```

![](../images/function%20to%20table.png)

#### Output lambda function as table

```py
import tables

xmin = -10
xmax = 10
xscl = 2

afunction = lambda x: x + 1

tables.function(xmin, xmax, xscl, afunction, headerrow=True)
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
xscl = 2

# Function parameter and return value can be any data type, as long as they are the same
functions = [function1, function2]

tables.functions(xmin, xmax, xscl, functions, headerrow=True)
```

![](../images/multiple%20functions%20to%20table.png)

#### Output multiple lambda functions as table

```py
import tables

xmin = -10
xmax = 10
xscl = 2

# Function parameter and return value can be any data type, as long as they are the same
functions = [lambda x: 2 * x, lambda x: x ** 2]

tables.functions(xmin, xmax, xscl, functions, headerrow=True)
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
Default value: `False`

#### Cell border

Option: `cellborder`\
Default value: `False`

#### Cell padding

Option: `padding`\
Default value: `1`

#### Alignment

Option: `alignment`\
Values:

* `False` (left, default)
* `True` (right)

#### Title

Option: `title`\
Default value: `None`

The title is word wrapped based on the current width of the terminal. Handles newlines, tabs and [Unicode characters](https://en.wikipedia.org/wiki/List_of_Unicode_characters).

#### Border style

Option: `style`\
Values:

0. ASCII

	![](../images/ASCII%20table.png)
1. Basic

	![](../images/basic%20table.png)
2. Light (default)

	![](../images/light%20table.png)
3. Heavy

	![](../images/heavy%20table.png)
4. Double

	![](../images/double%20table.png)
5. Light Dashed

	![](../images/light%20dashed%20table.png)
6. Heavy Dashed

	![](../images/heavy%20dashed%20table.png)

## Graphs/Plots

### Usage

Requires Python 3.5 or greater and the [wcwidth library](https://pypi.org/project/wcwidth/), which users can install with: `pip3 install wcwidth`. See the [graphs.py](graphs.py) file for full usage information.

Complete versions of all of the examples below and more can be found in the [test.py](test.py) file.

Run with: `python3 test.py`.

If `height` is `0`, it will be set to the current height of the terminal (number of rows times four). If `width` is `0`, it will be set to the current width of the terminal (number of columns times two).

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

graphs.array(height, width, xmin, xmax, ymin, ymax, array)
```

If `xmin` and `xmax` are both `0`, they will be set to the respective minimum and maximum values of x in the array. If `ymin` and `ymax` are both `0`, they will be set to the respective minimum and maximum values of y in the array.

![](../images/array%20to%20plot.png)

Use `graphs.arrays()` to plot multiple arrays, which can be of different sizes.

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

#### Border/Axis

Option: `border`\
Default value: `False`

#### Axis labels

Option: `axislabel`\
Default value: `False`

Requires `border` to be `False`.

#### Axis units labels

Option: `axisunitslabel`\
Default value: `False`

Requires `border` and `axislabel` to be `False`.

#### Title

Option: `title`\
Default value: `None`

The title is word wrapped based on the current width of the terminal. Handles newlines, tabs and [Unicode characters](https://en.wikipedia.org/wiki/List_of_Unicode_characters).

#### Axis/Border style

Option: `style`\
Values:

0. ASCII

	![](../images/ASCII%20graph.png)
1. Basic

	![](../images/basic%20graph.png)
2. Light (default)

	![](../images/light%20graph.png)
3. Heavy

	![](../images/heavy%20graph.png)
4. Double

	![](../images/double%20graph.png)
5. Light Dashed

	![](../images/light%20dashed%20graph.png)
6. Heavy Dashed

	![](../images/heavy%20dashed%20graph.png)

#### Graph/Plot Color

Option: `color`\
Values:

0. System default
1. Black
2. Red (default)
3. Green
4. Yellow
5. Blue
6. Cyan
7. Light gray
8. Dark gray
9. Light red
10. Light green
11. Light yellow
12. Light blue
13. Light cyan
14. White

See [here](https://misc.flogisoft.com/bash/tip_colors_and_formatting#foreground_text) for examples of the colors.

Only used for plots and when graphing a single function.

When graphing multiple functions, colors `2` - `14` are used inorder. Color `0` is used where the functions cross.

##### Plot

![](../images/plot%20colors.png)

##### Graph

![](../images/graph%20colors.png)
