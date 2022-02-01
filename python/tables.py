#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Teal Dulcet, CS546

from __future__ import division, print_function, unicode_literals
import sys
import shutil
import re
import textwrap
from wcwidth import wcswidth
from typing import List, Optional, Any, Sequence, Callable
import locale

locale.setlocale(locale.LC_ALL, '')

styles = [
	["-", "|", "+", "+", "+", "+", "+", "+", "+", "+", "+"],  # ASCII
	["—", "|", "+", "+", "+", "+", "+", "+", "+", "+", "+"],  # Basic
	["─", "│", "┌", "┬", "┐", "├", "┼", "┤", "└", "┴", "┘"],  # Light
	["━", "┃", "┏", "┳", "┓", "┣", "╋", "┫", "┗", "┻", "┛"],  # Heavy
	["═", "║", "╔", "╦", "╗", "╠", "╬", "╣", "╚", "╩", "╝"],  # Double
	["╌", "╎", "┌", "┬", "┐", "├", "┼", "┤", "└", "┴", "┘"],  # Light Dashed
	["╍", "╏", "┏", "┳", "┓", "┣", "╋", "┫", "┗", "┻", "┛"]  # Heavy Dashed
]
# [" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "]] #No border

ansi = re.compile(r'\x1B\[(?:[0-9]+(?:;[0-9]+)*)?m')


def strcol(str: str) -> int:
	"""Returns the number of columns that the given string would take up if printed."""
	str = ansi.sub('', str)
	width = wcswidth(str)
	if width == -1:
		print("\nError! wcswidth failed. Nonprintable wide character.", file=sys.stderr)
		sys.exit(1)
	return width
	# return len(str)


def table(array: List[List[str]], headerrow: bool=False, headercolumn: bool=False, tableborder: bool=True, cellborder: bool=False, padding: int=1, alignment: bool=False, title: Optional[str]=None, style: int=2) -> int:
	"""Output char array as table"""
	if not array:
		return 1

	if not (0 >= style > len(styles)):
		return 1

	rows = len(array)
	columns = len(array[0])

	columnwidth = [max(strcol(i) for i in j) for j in zip(*array)]

	width = sum(columnwidth)

	w = shutil.get_terminal_size()

	if tableborder or cellborder or headerrow or headercolumn:
		width += (((2 * padding) + 1) * columns) + (1 if tableborder else -1)
	else:
		width += (2 * padding) * columns

	if width > w.columns:
		print("The width of the table ({0}) is greater then the width of the terminal ({1}).".format(
			width, w.columns), file=sys.stderr)
		return 1

	if title:
		print(textwrap.fill(title, width=w.columns))

	strm = ""

	if tableborder:
		strm += styles[style][2]

		for j in range(columns):
			strm += styles[style][0] * ((2 * padding) + columnwidth[j])

			if j == (columns - 1):
				strm += styles[style][4] + "\n"
			elif cellborder or headerrow or (j == 0 and headercolumn):
				strm += styles[style][3]
			else:
				strm += styles[style][0]

	for i in range(rows):
		for j in range(columns):
			if (j == 0 and tableborder) or (j > 0 and cellborder) or (i == 0 and j > 0 and headerrow) or (j == 1 and headercolumn):
				strm += styles[style][1]
			elif tableborder or (i > 0 and j > 0 and headerrow) or (j > 1 and headercolumn):
				strm += " "

			awidth = columnwidth[j] - (strcol(array[i][j]) - len(array[i][j]))

			if (i == 0 and headerrow) or (j == 0 and headercolumn):
				strm += " " * padding

				strm += "\033[1m" + array[i][j].center(awidth) + "\033[22m"

				strm += " " * padding
			else:
				strm += " " * padding

				if alignment:
					strm += array[i][j].rjust(awidth)
				else:
					strm += array[i][j].ljust(awidth)

				strm += " " * padding

		if tableborder:
			strm += styles[style][1]

		strm += "\n"

		if tableborder:
			if i == (rows - 1):
				strm += styles[style][8]
			elif cellborder or (i == 0 and headerrow) or headercolumn:
				strm += styles[style][5]

		if (i == (rows - 1) and tableborder) or (i < (rows - 1) and cellborder) or (i == 0 and headerrow) or (i < (rows - 1) and headercolumn):
			for j in range(columns):
				if (i == (rows - 1) and tableborder) or (i < (rows - 1) and cellborder) or (i == 0 and headerrow) or (i < (rows - 1) and j == 0 and headercolumn):
					strm += styles[style][0] * ((2 * padding) + columnwidth[j])
				elif i < (rows - 1) and headercolumn:
					strm += " " * ((2 * padding) + columnwidth[j])

				if j == (columns - 1):
					if tableborder:
						if i == (rows - 1):
							strm += styles[style][10]
						elif cellborder or (i == 0 and headerrow):
							strm += styles[style][7]
						elif headercolumn:
							strm += styles[style][1]

					strm += "\n"
				else:
					if i == (rows - 1) and tableborder:
						if cellborder or (j == 0 and headercolumn):
							strm += styles[style][9]
						else:
							strm += styles[style][0]
					elif (i < (rows - 1) and cellborder) or ((i == 0 and headerrow) and (j == 0 and headercolumn)):
						strm += styles[style][6]
					elif i == 0 and headerrow:
						strm += styles[style][9]
					elif i < (rows - 1) and headercolumn:
						if j == 0:
							strm += styles[style][7]
						else:
							strm += " "

	print(strm)

	return 0


def array(aarray: Sequence[Sequence[Any]], aheaderrow: Optional[Sequence[Any]], aheadercolumn: Optional[Sequence[Any]], headerrow: bool=False, headercolumn: bool=False, tableborder: bool=True, cellborder: bool=False, padding: int=1, alignment: bool=False, title: Optional[str]=None, style: int=2) -> int:
	"""Convert array to char array and output as table"""
	if not aarray:
		return 1

	rows = len(aarray)
	columns = len(aarray[0])

	if not all(len(x) == columns for x in aarray):
		print("Error: The rows of the array must have the same number of columns.", file=sys.stderr)
		return 1

	if aheaderrow:
		rows += 1

	if aheadercolumn:
		columns += 1

	if aheaderrow and len(aheaderrow) != columns:
		print("Error: The header row must have the same number of columns as the array.", file=sys.stderr)
		return 1

	if aheadercolumn and len(aheadercolumn) != (rows - 1 if aheaderrow else rows):
		print("Error: The header column must have the same number of rows as the array.", file=sys.stderr)
		return 1

	aaarray = [["" for j in range(columns)] for i in range(rows)]

	i = 0

	if aheaderrow:
		for j in range(columns):
			aaarray[i][j] = aheaderrow[j]

		i += 1

	j = 0

	ii = 0
	for i in range(i, rows):
		if aheadercolumn:
			aii = i

			if aheaderrow:
				aii -= 1

			aaarray[i][j] = aheadercolumn[aii]

			j += 1

		jj = 0
		for j in range(j, columns):
			aaarray[i][j] = str(aarray[ii][jj])

			jj += 1

		j = 0
		ii += 1

	return table(aaarray, headerrow=headerrow, headercolumn=headercolumn, tableborder=tableborder, cellborder=cellborder, padding=padding, alignment=alignment, title=title, style=style)


def functions(xmin: float, xmax: float, xscl: float, afunctions: Sequence[Callable[[float], float]], headerrow: bool=False, headercolumn: bool=False, tableborder: bool=True, cellborder: bool=False, padding: int=1, alignment: bool=False, title: Optional[str]=None, style: int=2) -> int:
	"""Convert one or more functions to array and output as table"""
	if len(afunctions) == 0:
		return 1

	if xmin >= xmax:
		print("xmin must be less than xmax.", file=sys.stderr)
		return 1

	if xscl <= 0:
		print("xscl must be greater than zero.", file=sys.stderr)
		return 1

	rows = int(((xmax - xmin) * xscl)) + 1
	columns = len(afunctions) + 1

	aaheaderrow = ["x", "y"]
	length = len(aaheaderrow)

	aheaderrow = [""] * columns

	for j in range(columns):
		if j < (length - 1) or len(afunctions) == 1:
			aheaderrow[j] = aaheaderrow[j]
		else:
			aheaderrow[j] = aaheaderrow[length - 1] + str(j - length + 2)

	aarray = [[0 for j in range(columns)] for i in range(rows)]

	for i in range(rows):
		aarray[i][0] = (i / xscl) + xmin

		for j, function in enumerate(afunctions):
			aarray[i][j + 1] = function(aarray[i][0])

	return array(aarray, aheaderrow, None, headerrow=headerrow, headercolumn=headercolumn, tableborder=tableborder, cellborder=cellborder, padding=padding, alignment=alignment, title=title, style=style)


def function(xmin: float, xmax: float, xscl: float, afunction: Callable[[float], float], headerrow: bool=False, headercolumn: bool=False, tableborder: bool=True, cellborder: bool=False, padding: int=1, alignment: bool=False, title: Optional[str]=None, style: int=2) -> int:
	"""Convert single function to array and output as table"""
	return functions(xmin, xmax, xscl, [afunction], headerrow=headerrow, headercolumn=headercolumn, tableborder=tableborder, cellborder=cellborder, padding=padding, alignment=alignment, title=title, style=style)
