#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Teal Dulcet, CS546

from __future__ import division, print_function, unicode_literals
import sys
import math
import shutil
import textwrap
from wcwidth import wcswidth
from typing import List, Tuple, Optional, Sequence, Callable
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

colors = ["\033[39m", "\033[30m", "\033[31m", "\033[32m", "\033[33m", "\033[34m", "\033[35m", "\033[36m",
		  "\033[37m", "\033[90m", "\033[91m", "\033[92m", "\033[93m", "\033[94m", "\033[95m", "\033[96m", "\033[97m"]

dots = ["⠀", "⠁", "⠂", "⠃", "⠄", "⠅", "⠆", "⠇", "⠈", "⠉", "⠊", "⠋", "⠌", "⠍", "⠎", "⠏", "⠐", "⠑", "⠒", "⠓", "⠔", "⠕", "⠖", "⠗", "⠘", "⠙", "⠚", "⠛", "⠜", "⠝", "⠞", "⠟", "⠠", "⠡", "⠢", "⠣", "⠤", "⠥", "⠦", "⠧", "⠨", "⠩", "⠪", "⠫", "⠬", "⠭", "⠮", "⠯", "⠰", "⠱", "⠲", "⠳", "⠴", "⠵", "⠶", "⠷", "⠸", "⠹", "⠺", "⠻", "⠼", "⠽", "⠾", "⠿", "⡀", "⡁", "⡂", "⡃", "⡄", "⡅", "⡆", "⡇", "⡈", "⡉", "⡊", "⡋", "⡌", "⡍", "⡎", "⡏", "⡐", "⡑", "⡒", "⡓", "⡔", "⡕", "⡖", "⡗", "⡘", "⡙", "⡚", "⡛", "⡜", "⡝", "⡞", "⡟", "⡠", "⡡", "⡢", "⡣", "⡤", "⡥", "⡦", "⡧", "⡨", "⡩", "⡪", "⡫", "⡬", "⡭", "⡮", "⡯", "⡰", "⡱", "⡲", "⡳", "⡴", "⡵", "⡶", "⡷", "⡸", "⡹", "⡺", "⡻", "⡼", "⡽", "⡾",
		"⡿", "⢀", "⢁", "⢂", "⢃", "⢄", "⢅", "⢆", "⢇", "⢈", "⢉", "⢊", "⢋", "⢌", "⢍", "⢎", "⢏", "⢐", "⢑", "⢒", "⢓", "⢔", "⢕", "⢖", "⢗", "⢘", "⢙", "⢚", "⢛", "⢜", "⢝", "⢞", "⢟", "⢠", "⢡", "⢢", "⢣", "⢤", "⢥", "⢦", "⢧", "⢨", "⢩", "⢪", "⢫", "⢬", "⢭", "⢮", "⢯", "⢰", "⢱", "⢲", "⢳", "⢴", "⢵", "⢶", "⢷", "⢸", "⢹", "⢺", "⢻", "⢼", "⢽", "⢾", "⢿", "⣀", "⣁", "⣂", "⣃", "⣄", "⣅", "⣆", "⣇", "⣈", "⣉", "⣊", "⣋", "⣌", "⣍", "⣎", "⣏", "⣐", "⣑", "⣒", "⣓", "⣔", "⣕", "⣖", "⣗", "⣘", "⣙", "⣚", "⣛", "⣜", "⣝", "⣞", "⣟", "⣠", "⣡", "⣢", "⣣", "⣤", "⣥", "⣦", "⣧", "⣨", "⣩", "⣪", "⣫", "⣬", "⣭", "⣮", "⣯", "⣰", "⣱", "⣲", "⣳", "⣴", "⣵", "⣶", "⣷", "⣸", "⣹", "⣺", "⣻", "⣼", "⣽", "⣾", "⣿"]

values = [[0x1, 0x2, 0x4, 0x40], [0x8, 0x10, 0x20, 0x80]]

fractions = {
	"¼": 1.0 / 4.0,
	"½": 1.0 / 2.0,
	"¾": 3.0 / 4.0,
	"⅐": 1.0 / 7.0,
	"⅑": 1.0 / 9.0,
	"⅒": 1.0 / 10.0,
	"⅓": 1.0 / 3.0,
	"⅔": 2.0 / 3.0,
	"⅕": 1.0 / 5.0,
	"⅖": 2.0 / 5.0,
	"⅗": 3.0 / 5.0,
	"⅘": 4.0 / 5.0,
	"⅙": 1.0 / 6.0,
	"⅚": 5.0 / 6.0,
	"⅛": 1.0 / 8.0,
	"⅜": 3.0 / 8.0,
	"⅝": 5.0 / 8.0,
	"⅞": 7.0 / 8.0
}

constants = {
	"π": math.pi,
	"e": math.e
}


def strcol(str: str) -> int:
	"""Returns the number of columns that the given string would take up if printed."""
	width = wcswidth(str)
	if width == -1:
		print("\nError! wcswidth failed. Nonprintable wide character.", file=sys.stderr)
		sys.exit(1)
	return width
	# return len(str)


def outputlabel(label: float) -> Tuple[int, str]:
	"""Outputs a label in a nice, human readable format."""
	"""Convert fractions and constants to Unicode characters"""
	output = False

	fractionpart, intpart = math.modf(label)
	fractionpart = abs(fractionpart)

	strm = ""

	for fraction in fractions:
		if abs(fractionpart - fractions[fraction]) < sys.float_info.epsilon:
			if intpart != 0:
				strm += str(intpart)

			strm += fraction

			output = True
			break

	if abs(label) >= sys.float_info.epsilon and not output:
		for constant in constants:
			if not output and label % constants[constant] == 0:
				intpart = label / constants[constant]

				if intpart == -1:
					strm += "-"
				elif intpart != 1:
					strm += str(intpart)

				strm += constant

				output = True
				break

	if not output:
		strm += "{0:n}".format(label)

	length = strcol(strm)

	return length, strm


def graph(height: int, width: int, xmin: float, xmax: float, ymin: float, ymax: float, array: List[List[int]], border: bool=True, axislabel: bool=True, axisunitslabel: bool=True, style: int=2, title: Optional[str]=None) -> int:
	"""Output graph"""
	if not array:
		return 1

	if not (0 <= style < len(styles)):
		return 1

	if height == 0:
		return 1

	if width == 0:
		return 1

	w = shutil.get_terminal_size()

	aheight = height // 4
	awidth = width // 2

	if aheight > w.lines:
		print("The height of the graph ({0}) is greater then the height of the terminal ({1}).".format(
			aheight, w.lines), file=sys.stderr)
		return 1

	if awidth > w.columns:
		print("The width of the graph ({0}) is greater then the width of the terminal ({1}).".format(
			awidth, w.columns), file=sys.stderr)
		return 1

	if xmin >= xmax:
		print("xmin must be less than xmax.", file=sys.stderr)
		return 1

	if ymin >= ymax:
		print("ymin must be less than ymax.", file=sys.stderr)
		return 1

	xscl = width / (xmax - xmin)
	yscl = height / (ymax - ymin)
	xaxis = width - (xmax * xscl)
	yaxis = ymax * yscl
	divisor = 2 * 4 * ((width // 160) + 1 if (width / 160.0) > 1 else 1)

	if title:
		print(textwrap.fill(title, width=w.columns))

	strm = ""

	i = 0
	while i < height:
		ayaxis = i <= yaxis and (i + 4) > yaxis
		yaxislabel = i <= (yaxis + 4) and (i + 4) > (yaxis + 4)

		ylabelstrm = ""
		ylabellength = 0

		if border and axislabel and axisunitslabel:
			output = False
			label = 0.0
			adivisor = -divisor if i < yaxis else divisor

			k = yaxis + adivisor
			while ((i < yaxis and k >= i) or (i > yaxis and k < (i + 4))) and (i >= 4 or not axislabel) and not output:
				if (i <= k and (i + 4) > k):
					label = ymax - (k / yscl)

					output = True
				k += adivisor

			if (output):
				ylabellength, ylabelstrm = outputlabel(label)
				ylabellength *= 2

		j = 0
		while j < width:
			axaxis = j <= xaxis and (j + 2) > xaxis
			xaxislabel = j <= (xaxis - 2) and (j + 2) > (xaxis - 2)

			output = False

			if border:
				if axaxis and ayaxis:
					strm += styles[style][6]
					output = True
				elif axaxis:
					if axislabel and axisunitslabel:
						adivisor = -divisor if i < yaxis else divisor

						k = yaxis + adivisor
						while ((i < yaxis and k >= i) or (i > yaxis and k < (i + 4))) and (i >= 4 or not axislabel) and not output:
							if i <= k and (i + 4) > k:
								strm += styles[style][7]
								output = True
							k += adivisor
					if not output:
						if i == 0:
							strm += styles[style][4]
						elif i >= (height - 4):
							strm += styles[style][10]
						else:
							strm += styles[style][1]
						output = True
				elif ayaxis:
					if axislabel and axisunitslabel:
						adivisor = -divisor if j < xaxis else divisor

						k = xaxis + adivisor
						while ((j < xaxis and k >= j) or (j > xaxis and k < (j + 2))) and (j < (width - 4) or not axislabel) and not output:
							if j <= k and (j + 2) > k:
								strm += styles[style][3]
								output = True
							k += adivisor
					if not output:
						if j == 0:
							strm += styles[style][2]
						elif j >= (width - 2):
							strm += styles[style][4]
						else:
							strm += styles[style][0]
						output = True
				elif yaxislabel and xaxislabel and axislabel and axisunitslabel:
					strm += "0"
					output = True
				elif j >= (width - 2) and yaxislabel and axislabel:
					strm += "x"
					output = True
				elif yaxislabel and axislabel and axisunitslabel:
					label = 0.0
					adivisor = -divisor if j < xaxis else divisor
					if j < xaxis:
						j += 2

					k = xaxis + adivisor
					while ((j < xaxis and k >= j) or (j > xaxis and k < (j + 2))) and j < (width - 2) and not output:
						if j <= k and (j + 2) > k:
							label = (k / xscl) + xmin

							output = True
						k += adivisor

					if adivisor < 0:
						j -= 2

					if output:
						output = False

						length, astrm = outputlabel(label)
						length *= 2
						if (j >= xaxis or (j + length) < (xaxis - 4)) and (j + length) < (width - 2):
							strm += astrm

							if length > 2:
								j += length - 2

							if adivisor < 0:
								output = True
							else:
								j += 2
				elif i == 0 and xaxislabel and axislabel:
					strm += "y"
					output = True
				elif (j <= (xaxis - ylabellength) and (j + 2) > (xaxis - ylabellength)) and axislabel and axisunitslabel:
					strm += ylabelstrm
					output = True
					if ylabellength > 2:
						j += ylabellength - 2

			if not output:
				dot = 0
				color = 0

				for k in range(min(2, width - j)):
					for l in range(min(4, height - i)):
						dot += (1 if array[j + k][i + l] else 0) * values[k][l]
						if color:
							if array[j + k][i + l] and color != array[j + k][i + l]:
								color = 1
						else:
							color = array[j + k][i + l]

				if color:
					color -= 1

				if color:
					strm += colors[color]

				strm += "\033[1m" + dots[dot] + "\033[22m"

				if color:
					strm += colors[0]

			j += 2

		strm += "\n"
		i += 4

	print(strm)

	return 0


def arrays(height: int, width: int, xmin: float, xmax: float, ymin: float, ymax: float, aarrays: Sequence[Sequence[Sequence[float]]], border: bool=True, axislabel: bool=True, axisunitslabel: bool=True, style: int=2, color: int=2, title: Optional[str]=None) -> int:
	"""Convert one or more arrays to graph and output"""
	if not aarrays:
		return 1

	if not all(len(x) == 2 for aarray in aarrays for x in aarray):
		print("Error: The arrays must have two columns.")
		return 1

	if color < 0 or color >= len(colors):
		return 1

	w = shutil.get_terminal_size()

	aheight = height // 4
	awidth = width // 2

	if aheight > w.lines:
		print("The height of the graph ({0}) is greater then the height of the terminal ({1}).".format(
			aheight, w.lines), file=sys.stderr)
		return 1

	if awidth > w.columns:
		print("The width of the graph ({0}) is greater then the width of the terminal ({1}).".format(
			awidth, w.columns), file=sys.stderr)
		return 1

	if xmin == 0 and xmax == 0:
		xmin = min(i[0] for aarray in aarrays for i in aarray)
		xmax = max(i[0] for aarray in aarrays for i in aarray)

	if ymin == 0 and ymax == 0:
		ymin = min(i[1] for aarray in aarrays for i in aarray)
		ymax = max(i[1] for aarray in aarrays for i in aarray)

	if xmin >= xmax:
		print("xmin must be less than xmax.", file=sys.stderr)
		return 1

	if ymin >= ymax:
		print("ymin must be less than ymax.", file=sys.stderr)
		return 1

	xscl = width / (xmax - xmin)
	yscl = height / (ymax - ymin)
	xaxis = width - (xmax * xscl)
	yaxis = ymax * yscl

	aaarray = [[0 for j in range(height)] for i in range(width)]

	for j, aarray in enumerate(aarrays):
		acolor = color + 1 if len(aarrays) == 1 else (j % (len(colors) - 2)) + 3

		for i in aarray:
			if i[0] >= xmin and i[0] < xmax and i[1] >= ymin and i[1] < ymax:
				x = int((i[0] * xscl) + xaxis)
				y = int((yaxis - (i[1] * yscl)) - 1)

				if aaarray[x][y]:
					if aaarray[x][y] != acolor:
						aaarray[x][y] = 1
				else:
					aaarray[x][y] = acolor

	return graph(height, width, xmin, xmax, ymin, ymax, aaarray, border=border, axislabel=axislabel, axisunitslabel=axisunitslabel, style=style, title=title)


def array(height: int, width: int, xmin: float, xmax: float, ymin: float, ymax: float, aarray: Sequence[Sequence[float]], border: bool=True, axislabel: bool=True, axisunitslabel: bool=True, style: int=2, color: int=2, title: Optional[str]=None) -> int:
	"""Convert single array to graph and output"""
	return arrays(height, width, xmin, xmax, ymin, ymax, [aarray], border=border, axislabel=axislabel, axisunitslabel=axisunitslabel, style=style, color=color, title=title)


def functions(height: int, width: int, xmin: float, xmax: float, ymin: float, ymax: float, afunctions: Sequence[Callable[[float], float]], border: bool=True, axislabel: bool=True, axisunitslabel: bool=True, style: int=2, color: int=2, title: Optional[str]=None) -> int:
	"""Convert one or more functions to graph and output"""
	if color < 0 or color >= len(colors):
		return 1

	if len(afunctions) == 0:
		return 1

	w = shutil.get_terminal_size()

	if height == 0:
		height = w.lines * 4

	if width == 0:
		width = w.columns * 2

	aheight = height / 4
	awidth = width / 2

	if aheight > w.lines:
		print("The height of the graph ({0}) is greater then the height of the terminal ({1}).".format(
			aheight, w.lines), file=sys.stderr)
		return 1

	if awidth > w.columns:
		print("The width of the graph ({0}) is greater then the width of the terminal ({1}).".format(
			awidth, w.columns), file=sys.stderr)
		return 1

	if xmin >= xmax:
		print("xmin must be less than xmax.", file=sys.stderr)
		return 1

	if ymin >= ymax:
		print("ymin must be less than ymax.", file=sys.stderr)
		return 1

	rows = width

	xscl = width / (xmax - xmin)
	yscl = height / (ymax - ymin)
	xaxis = width - (xmax * xscl)
	yaxis = ymax * yscl

	array = [[0 for j in range(height)] for i in range(width)]

	for j, function in enumerate(afunctions):
		acolor = color + 1 if len(afunctions) == 1 else (j %
														 (len(colors) - 2)) + 3

		for i in (x / 2 for x in range(rows * 2)):
			x = (i / xscl) + xmin
			y = function(x)

			if x >= xmin and x < xmax and y >= ymin and y < ymax:
				ax = int((x * xscl) + xaxis)
				ay = int((yaxis - (y * yscl)) - 1)

				if array[ax][ay]:
					if array[ax][ay] != acolor:
						array[ax][ay] = 1
				else:
					array[ax][ay] = acolor

	return graph(height, width, xmin, xmax, ymin, ymax, array, border=border, axislabel=axislabel, axisunitslabel=axisunitslabel, style=style, title=title)


def function(height, width, xmin: float, xmax: float, ymin: float, ymax: float, afunction: Callable[[float], float], border: bool=True, axislabel: bool=True, axisunitslabel: bool=True, style: int=2, color: int=2, title: Optional[str]=None) -> int:
	"""Convert single function to function array and output"""
	return functions(height, width, xmin, xmax, ymin, ymax, [afunction], border=border, axislabel=axislabel, axisunitslabel=axisunitslabel, style=style, color=color, title=title)
