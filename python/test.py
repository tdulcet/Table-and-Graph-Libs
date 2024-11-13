#!/usr/bin/env python3

# Teal Dulcet, CS546

# Run: python3 -OO test.py

import math
import operator
import random
import sys

import graphs
import tables


def afunction(x: float) -> float:
	return x + 1


def function1(x: float) -> float:
	return 2 * x


def function2(x: float) -> float:
	return x ** 2


rows = 5
columns = 5

xmin = -10
xmax = 10
xstep = 0.5

print("\nOutput array as table\n")
array = [[random.randint(0, sys.maxsize)
		  for j in range(columns)] for i in range(rows)]
for style in tables.style_types:
	tables.array(array, None, None, style=style)

array = [[random.random() for j in range(columns)] for i in range(rows)]
for style in tables.style_types:
	tables.array(array, None, None, style=style)

print("\nOutput char array as table\n")
array = [["Header row/column 1", "Header row 2", "Header row 3", "Header row 4", "Header row 5"],
		 ["Header column 2", "Data 1", "Data 2", "Data 3", "Data 4"],
		 ["Header column 3", "Data 5", "Data 6", "Data 7", "Data 8"],
		 ["Header column 4", "Data 9", "Data 10", "Data 11", "Data 12"],
		 ["Header column 5", "Data 13", "Data 14", "Data 15", "Data 16"]]
for style in tables.style_types:
	tables.array(array, None, None, headerrow=True,
				 headercolumn=True, style=style)

print("\nOutput array as table with separate header row and column\n")
array = [[f"Data {i + j:n}" for j in range(4)]
		 for i in range(1, 4 * 4 + 1, 4)]
headerrow = ["Header row/column 1", "Header row 2",
			 "Header row 3", "Header row 4", "Header row 5"]
headercolumn = ["Header column 2", "Header column 3",
				"Header column 4", "Header column 5"]

for style in tables.style_types:
	tables.array(array, headerrow, headercolumn, headerrow=True,
				 headercolumn=True, cellborder=True, style=style)
	tables.array(array, headerrow, headercolumn,
				 headerrow=True, headercolumn=True, style=style)
	tables.array(array, headerrow[:-1], None, headerrow=True, style=style)
	tables.array(array, None, [headerrow[0]] +
				 headercolumn[:-1], headercolumn=True, style=style)
	tables.array(array, None, None, cellborder=True, style=style)
	tables.array(array, None, None, tableborder=False, style=style)
	tables.array(array, headerrow, headercolumn, tableborder=False,
				 headerrow=True, headercolumn=True, style=style)
	tables.array(array, headerrow[:-1], None,
				 tableborder=False, headerrow=True, style=style)
	tables.array(array, None, [headerrow[0]] + headercolumn[:-1],
				 tableborder=False, headercolumn=True, style=style)
	tables.array(array, None, None, tableborder=False,
				 cellborder=True, style=style)

array = [[bool(random.getrandbits(1)) for j in range(columns)]
		 for i in range(rows)]
for style in tables.style_types:
	tables.array(array, None, None, style=style)

print("\nOutput sorted array as table\n")
array = ([random.randint(0, sys.maxsize)
		  for j in range(columns)] for i in range(rows))
sortdimension = 0
array = sorted(array, key=operator.itemgetter(sortdimension))
for style in tables.style_types:
	tables.array(array, None, None, style=style)

print("\nOutput single function as table\n")
for style in tables.style_types:
	tables.function(xmin, xmax, xstep, afunction, headerrow=True, style=style)
for style in tables.style_types:
	tables.function(xmin, xmax, xstep, lambda x: x +
					1, headerrow=True, style=style)

print("\nOutput multiple functions as table\n")
for style in tables.style_types:
	tables.functions(xmin, xmax, xstep, [
		function1, function2], headerrow=True, style=style)
for style in tables.style_types:
	tables.functions(xmin, xmax, xstep, [
		lambda x: 2 * x, lambda x: x ** 2], headerrow=True, style=style)

height = 160
width = 160

xmin = -20
xmax = 20
ymin = -20
ymax = 20

print("\nOutput array as histogram\n")
array = [random.gauss(0, 1) for i in range(100)]
for style in graphs.style_types:
	graphs.histogram(height, width, xmin, xmax, ymin, ymax, array, style=style)

print("\nOutput single array as plot\n")
array = [range(i, i + 2) for i in range(10)]
for atype in graphs.atype_types:
	for mark in graphs.mark_types:
		for style in graphs.style_types:
			graphs.plot(height, width, xmin, xmax, ymin, ymax,
						array, atype=atype, mark=mark, style=style)

print("\nOutput single function as graph\n")
for style in graphs.style_types:
	graphs.function(height, width, xmin, xmax, ymin,
					ymax, afunction, style=style)
for style in graphs.style_types:
	graphs.function(height, width, xmin, xmax, ymin,
					ymax, lambda x: x + 1, style=style)

print("\nOutput multiple functions as graph\n")
for style in graphs.style_types:
	graphs.functions(height, width, xmin, xmax, ymin, ymax,
					 [function1, function2], style=style)
for style in graphs.style_types:
	graphs.functions(height, width, xmin, xmax, ymin, ymax, [
		lambda x: 2 * x, lambda x: x ** 2], style=style)

for style in graphs.style_types:
	graphs.functions(height, width, -(2 * math.pi), 2 * math.pi, -4, 4,
					 [math.sin, math.cos, math.tan], axisunitslabel=False, style=style)
