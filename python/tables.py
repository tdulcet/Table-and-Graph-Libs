#!/usr/bin/env python3

# Teal Dulcet, CS546

import locale
import re
import shutil
import sys
import textwrap
from enum import IntEnum, auto
from typing import Any, Callable, List, Optional, Sequence

from wcwidth import wcswidth

locale.setlocale(locale.LC_ALL, "")


class style_types(IntEnum):
	ASCII = 0
	basic = auto()
	light = auto()
	heavy = auto()
	double = auto()
	arc = auto()
	light_dashed = auto()
	heavy_dashed = auto()


styles = [
	["-", "|", "+", "+", "+", "+", "+", "+", "+", "+", "+"],  # ASCII
	["—", "|", "+", "+", "+", "+", "+", "+", "+", "+", "+"],  # Basic
	["─", "│", "┌", "┬", "┐", "├", "┼", "┤", "└", "┴", "┘"],  # Light
	["━", "┃", "┏", "┳", "┓", "┣", "╋", "┫", "┗", "┻", "┛"],  # Heavy
	["═", "║", "╔", "╦", "╗", "╠", "╬", "╣", "╚", "╩", "╝"],  # Double
	["─", "│", "╭", "┬", "╮", "├", "┼", "┤", "╰", "┴", "╯"],  # Light Arc
	["╌", "┊", "┌", "┬", "┐", "├", "┼", "┤", "└", "┴", "┘"],  # Light Dashed
	["╍", "┋", "┏", "┳", "┓", "┣", "╋", "┫", "┗", "┻", "┛"]  # Heavy Dashed
	# [" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "]] #No border
]

ansi = re.compile(r"\x1B\[(?:[0-9]+(?:;[0-9]+)*)?m")


def strcol(astr: str) -> int:
	"""Returns the number of columns that the given string would take up if printed."""
	astr = ansi.sub("", astr)
	width = wcswidth(astr)
	if width == -1:
		print(
			"\nError! wcswidth failed. Nonprintable wide character.",
			file=sys.stderr)
		sys.exit(1)
	return width
	# return len(astr)


def table(array: List[List[str]], headerrow: bool = False, headercolumn: bool = False, tableborder: bool = True, cellborder: bool = False,
		  padding: int = 1, alignment: Optional[bool] = None, title: Optional[str] = None, style: style_types = style_types.light, check: bool = True) -> int:
	"""Output char array as table."""
	if not array:
		return 1

	rows = len(array)
	columns = len(array[0])

	columnwidth = [max(strcol(i) for i in j) for j in zip(*array)]

	width = sum(columnwidth)

	w = shutil.get_terminal_size()

	if tableborder or cellborder or headerrow or headercolumn:
		width += (2 * padding + 1) * columns + (1 if tableborder else -1)
	else:
		width += 2 * padding * columns

	if check:
		if width > w.columns:
			print(
				f"The width of the table ({width}) is greater then the width of the terminal ({w.columns}).", file=sys.stderr)
			return 1

	if title:
		print(textwrap.fill(title, width=width))

	strm = ""

	if tableborder:
		strm += styles[style][2]

		for j in range(columns):
			strm += styles[style][0] * (2 * padding + columnwidth[j])

			if j < columns - 1:
				if cellborder or headerrow or (j == 0 and headercolumn):
					strm += styles[style][3]
				else:
					strm += styles[style][0]

		strm += styles[style][4] + "\n"

	for i in range(rows):
		if tableborder:
			strm += styles[style][1]

		for j in range(columns):
			if (j > 0 and cellborder) or (i == 0 and j > 0 and headerrow) or (j == 1 and headercolumn):
				strm += styles[style][1]
			elif j > 0 and (tableborder or (i > 0 and headerrow) or headercolumn):
				strm += " "

			awidth = columnwidth[j] - (strcol(array[i][j]) - len(array[i][j]))

			if (i == 0 and headerrow) or (j == 0 and headercolumn):
				strm += " " * padding

				strm += "\033[1m" + array[i][j].center(awidth) + "\033[22m"

				strm += " " * padding
			else:
				strm += " " * padding

				if alignment is None:
					strm += f"{array[i][j]:{awidth}}"
				elif alignment:
					strm += array[i][j].rjust(awidth)
				else:
					strm += array[i][j].ljust(awidth)

				strm += " " * padding

		if tableborder:
			strm += styles[style][1]

		if i < rows - 1 or tableborder:
			strm += "\n"

		if (i < rows - 1 and cellborder) or (i == 0 and headerrow) or (i < rows - 1 and headercolumn):
			if tableborder and (cellborder or (i == 0 and headerrow) or headercolumn):
				strm += styles[style][5]

			for j in range(columns):
				if cellborder or (i == 0 and headerrow) or (j == 0 and headercolumn):
					strm += styles[style][0] * (2 * padding + columnwidth[j])
				elif headercolumn:
					strm += " " * (2 * padding + columnwidth[j])

				if j < columns - 1:
					if cellborder or ((i == 0 and headerrow) and (j == 0 and headercolumn)):
						strm += styles[style][6]
					elif i == 0 and headerrow:
						strm += styles[style][9]
					elif headercolumn:
						if j == 0:
							strm += styles[style][7]
						else:
							strm += " "

			if tableborder:
				if cellborder or (i == 0 and headerrow):
					strm += styles[style][7]
				elif headercolumn:
					strm += styles[style][1]

			strm += "\n"

	if tableborder:
		strm += styles[style][8]

		for j in range(columns):
			strm += styles[style][0] * (2 * padding + columnwidth[j])

			if j < columns - 1:
				if cellborder or (j == 0 and headercolumn):
					strm += styles[style][9]
				else:
					strm += styles[style][0]

		strm += styles[style][10]

	print(strm)

	return 0


def array(aarray: Sequence[Sequence[Any]], aheaderrow: Optional[Sequence[Any]] = None, aheadercolumn: Optional[Sequence[Any]] = None, headerrow: bool = False, headercolumn: bool = False, tableborder: bool = True, cellborder: bool = False, padding: int = 1, alignment: Optional[bool] = None, title: Optional[str] = None, style: style_types = style_types.light) -> int:
	"""Convert array to char array and output as table."""
	if not aarray:
		return 1

	rows = len(aarray)
	columns = len(aarray[0])

	if not all(len(x) == columns for x in aarray):
		print(
			"Error: The rows of the array must have the same number of columns.",
			file=sys.stderr)
		return 1

	if aheaderrow:
		rows += 1

	if aheadercolumn:
		columns += 1

	if aheaderrow and len(aheaderrow) != columns:
		print(
			"Error: The header row must have the same number of columns as the array.",
			file=sys.stderr)
		return 1

	if aheadercolumn and len(aheadercolumn) != (rows - 1 if aheaderrow else rows):
		print(
			"Error: The header column must have the same number of rows as the array.",
			file=sys.stderr)
		return 1

	aaarray = [["" for j in range(columns)] for i in range(rows)]

	if aheaderrow:
		aaarray[0] = aheaderrow[:columns]

	for i in range(1 if aheaderrow else 0, rows):
		ii = i - 1 if aheaderrow else i

		if aheadercolumn:
			aaarray[i][0] = aheadercolumn[ii]

		j = 1 if aheadercolumn else 0
		aaarray[i][j:] = map(str, aarray[ii][:columns - j])

	return table(aaarray, headerrow, headercolumn, tableborder, cellborder, padding, alignment, title, style)


def functions(xmin: float, xmax: float, xstep: float, afunctions: Sequence[Callable[[float], float]], headerrow: bool = False, headercolumn: bool = False, tableborder: bool = True, cellborder: bool = False, padding: int = 1, alignment: Optional[bool] = None, title: Optional[str] = None, style: style_types = style_types.light) -> int:
	"""Convert one or more functions to array and output as table."""
	if not afunctions:
		return 1

	if xmin >= xmax:
		print("xmin must be less than xmax.", file=sys.stderr)
		return 1

	if xstep <= 0:
		print("xstep must be greater than zero.", file=sys.stderr)
		return 1

	rows = int((xmax - xmin) / xstep) + 1
	columns = len(afunctions) + 1

	aaheaderrow = ["x", "y"]
	length = len(aaheaderrow)

	aheaderrow = [""] * columns

	if len(afunctions) == 1:
		aheaderrow = aaheaderrow
	else:
		aheaderrow = aaheaderrow[:-1] + [aaheaderrow[-1] +
										 str(j - length + 2) for j in range(1, columns)]

	aarray = [[0 for j in range(columns)] for i in range(rows)]

	for i in range(rows):
		temp = aarray[i][0] = i * xstep + xmin

		aarray[i][1:] = [function(temp) for function in afunctions]

	return array(aarray, aheaderrow, None, headerrow, headercolumn, tableborder, cellborder, padding, alignment, title, style)


def function(xmin: float, xmax: float, xstep: float, afunction: Callable[[float], float], headerrow: bool = False, headercolumn: bool = False, tableborder: bool = True, cellborder: bool = False, padding: int = 1, alignment: Optional[bool] = None, title: Optional[str] = None, style: style_types = style_types.light) -> int:
	"""Convert single function to array and output as table."""
	return functions(xmin, xmax, xstep, [afunction], headerrow, headercolumn, tableborder, cellborder, padding, alignment, title, style)
