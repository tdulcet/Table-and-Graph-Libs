#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Teal Dulcet, CS546

from __future__ import division, print_function, unicode_literals
import random
import sys
import math
import graphs
import tables


def afunction(x): return x + 1
def function1(x): return 2 * x
def function2(x): return x ** 2


rows = 5
columns = 5

xmin = -10
xmax = 10
xscl = 2

print("\nOutput array as table\n")
array = [[random.randint(0, sys.maxsize)
		  for j in range(columns)] for i in range(rows)]
for k in range(len(tables.styles)):
	tables.array(array, None, None, style=k)

array = [[random.random() for j in range(columns)] for i in range(rows)]
for k in range(len(tables.styles)):
	tables.array(array, None, None, style=k)

print("\nOutput char array as table\n")
array = [["Header row/column 1", "Header row 2", "Header row 3", "Header row 4", "Header row 5"],
		 ["Header column 2", "Data 1", "Data 2", "Data 3", "Data 4"],
		 ["Header column 3", "Data 5", "Data 6", "Data 7", "Data 8"],
		 ["Header column 4", "Data 9", "Data 10", "Data 11", "Data 12"],
		 ["Header column 5", "Data 13", "Data 14", "Data 15", "Data 16"]]
for k in range(len(tables.styles)):
	tables.array(array, None, None, headerrow=True, headercolumn=True, style=k)

print("\nOutput array as table with separate header row and column\n")
array = [["Data {0:n}".format(i + j) for j in range(4)]
		 for i in range(1, 4 * 4 + 1, 4)]
headerrow = ["Header row/column 1", "Header row 2",
			 "Header row 3", "Header row 4", "Header row 5"]
headercolumn = ["Header column 2", "Header column 3",
				"Header column 4", "Header column 5"]

for k in range(len(tables.styles)):
	tables.array(array, headerrow, headercolumn, headerrow=True, headercolumn=True, cellborder=True, style=k)
	tables.array(array, headerrow, headercolumn, headerrow=True, headercolumn=True, style=k)
	tables.array(array, headerrow[:-1], None, headerrow=True, style=k)
	tables.array(array, None, [headerrow[0]] + headercolumn[:-1], headercolumn=True, style=k)
	tables.array(array, None, None, cellborder=True, style=k)
	tables.array(array, None, None, tableborder=False, style=k)
	tables.array(array, headerrow, headercolumn, tableborder=False, headerrow=True, headercolumn=True, style=k)
	tables.array(array, headerrow[:-1], None, tableborder=False, headerrow=True, style=k)
	tables.array(array, None, [headerrow[0]] + headercolumn[:-1], tableborder=False, headercolumn=True, style=k)
	tables.array(array, None, None, tableborder=False, cellborder=True, style=k)

array = [[bool(random.getrandbits(1)) for j in range(columns)]
		 for i in range(rows)]
for k in range(len(tables.styles)):
	tables.array(array, None, None, style=k)

print("\nOutput sorted array as table\n")
array = ([random.randint(0, sys.maxsize)
		  for j in range(columns)] for i in range(rows))
sortdimension = 0
array = sorted(array, key=lambda x: x[sortdimension])
for k in range(len(tables.styles)):
	tables.array(array, None, None, style=k)

print("\nOutput single function as table\n")
for k in range(len(tables.styles)):
	tables.function(xmin, xmax, xscl, afunction, headerrow=True, style=k)

print("\nOutput multiple functions as table\n")
for k in range(len(tables.styles)):
	tables.functions(xmin, xmax, xscl, [
					 function1, function2], headerrow=True, style=k)

height = 160
width = 160

xmin = -20
xmax = 20
ymin = -20
ymax = 20

print("\nOutput array as plot\n")
array = [[i + j for j in range(2)] for i in range(10)]
for k in range(len(graphs.styles)):
	graphs.array(height, width, xmin, xmax, ymin, ymax, array, style=k)

print("\nOutput single function as graph\n")
for k in range(len(graphs.styles)):
	graphs.function(height, width, xmin, xmax, ymin, ymax, afunction, style=k)

print("\nOutput multiple functions as graph\n")
for k in range(len(graphs.styles)):
	graphs.functions(height, width, xmin, xmax, ymin,
					 ymax, [function1, function2], style=k)

for k in range(len(graphs.styles)):
	graphs.functions(height, width, -(2 * math.pi), 2 *
					 math.pi, -4, 4, [math.sin, math.cos, math.tan], style=k)
