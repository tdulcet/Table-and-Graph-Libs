#!/usr/bin/env python3

# Teal Dulcet, CS546

import locale
import math
import shutil
import sys
import textwrap
from datetime import datetime, timezone
from enum import Enum, IntEnum, auto
from fractions import Fraction
from typing import Callable, List, Optional, Sequence, Tuple

from wcwidth import wcswidth

locale.setlocale(locale.LC_ALL, "")


class style_types(IntEnum):
	ASCII = 0
	basic = auto()
	light = auto()
	heavy = auto()
	double = auto()
	light_dashed = auto()
	heavy_dashed = auto()


styles = [
	["-", "|", "+", "+", "+", "+", "+", "+", "+", "+", "+"],  # ASCII
	["—", "|", "+", "+", "+", "+", "+", "+", "+", "+", "+"],  # Basic
	["─", "│", "┌", "┬", "┐", "├", "┼", "┤", "└", "┴", "┘"],  # Light
	["━", "┃", "┏", "┳", "┓", "┣", "╋", "┫", "┗", "┻", "┛"],  # Heavy
	["═", "║", "╔", "╦", "╗", "╠", "╬", "╣", "╚", "╩", "╝"],  # Double
	["╌", "┊", "┌", "┬", "┐", "├", "┼", "┤", "└", "┴", "┘"],  # Light Dashed
	["╍", "┋", "┏", "┳", "┓", "┣", "╋", "┫", "┗", "┻", "┛"]  # Heavy Dashed
	# [" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "]] #No border
]


class color_types(IntEnum):
	default = 0
	black = auto()
	red = auto()
	green = auto()
	yellow = auto()
	blue = auto()
	magenta = auto()
	cyan = auto()
	light_gray = auto()
	dark_gray = auto()
	light_red = auto()
	light_green = auto()
	light_yellow = auto()
	light_blue = auto()
	light_magenta = auto()
	light_cyan = auto()
	white = auto()


colors = ["\033[39m", "\033[30m", "\033[31m", "\033[32m", "\033[33m",
		  "\033[34m", "\033[35m", "\033[36m", "\033[37m", "\033[90m",
		  "\033[91m", "\033[92m", "\033[93m", "\033[94m", "\033[95m",
		  "\033[96m", "\033[97m"]

dots = [
	"⠀", "⠁", "⠂", "⠃", "⠄", "⠅", "⠆", "⠇", "⠈", "⠉", "⠊", "⠋", "⠌", "⠍", "⠎",
	"⠏", "⠐", "⠑", "⠒", "⠓", "⠔", "⠕", "⠖", "⠗", "⠘", "⠙", "⠚", "⠛", "⠜", "⠝",
	"⠞", "⠟", "⠠", "⠡", "⠢", "⠣", "⠤", "⠥", "⠦", "⠧", "⠨", "⠩", "⠪", "⠫", "⠬",
	"⠭", "⠮", "⠯", "⠰", "⠱", "⠲", "⠳", "⠴", "⠵", "⠶", "⠷", "⠸", "⠹", "⠺", "⠻",
	"⠼", "⠽", "⠾", "⠿", "⡀", "⡁", "⡂", "⡃", "⡄", "⡅", "⡆", "⡇", "⡈", "⡉", "⡊",
	"⡋", "⡌", "⡍", "⡎", "⡏", "⡐", "⡑", "⡒", "⡓", "⡔", "⡕", "⡖", "⡗", "⡘", "⡙",
	"⡚", "⡛", "⡜", "⡝", "⡞", "⡟", "⡠", "⡡", "⡢", "⡣", "⡤", "⡥", "⡦", "⡧", "⡨",
	"⡩", "⡪", "⡫", "⡬", "⡭", "⡮", "⡯", "⡰", "⡱", "⡲", "⡳", "⡴", "⡵", "⡶", "⡷",
	"⡸", "⡹", "⡺", "⡻", "⡼", "⡽", "⡾", "⡿", "⢀", "⢁", "⢂", "⢃", "⢄", "⢅", "⢆",
	"⢇", "⢈", "⢉", "⢊", "⢋", "⢌", "⢍", "⢎", "⢏", "⢐", "⢑", "⢒", "⢓", "⢔", "⢕",
	"⢖", "⢗", "⢘", "⢙", "⢚", "⢛", "⢜", "⢝", "⢞", "⢟", "⢠", "⢡", "⢢", "⢣", "⢤",
	"⢥", "⢦", "⢧", "⢨", "⢩", "⢪", "⢫", "⢬", "⢭", "⢮", "⢯", "⢰", "⢱", "⢲", "⢳",
	"⢴", "⢵", "⢶", "⢷", "⢸", "⢹", "⢺", "⢻", "⢼", "⢽", "⢾", "⢿", "⣀", "⣁", "⣂",
	"⣃", "⣄", "⣅", "⣆", "⣇", "⣈", "⣉", "⣊", "⣋", "⣌", "⣍", "⣎", "⣏", "⣐", "⣑",
	"⣒", "⣓", "⣔", "⣕", "⣖", "⣗", "⣘", "⣙", "⣚", "⣛", "⣜", "⣝", "⣞", "⣟", "⣠",
	"⣡", "⣢", "⣣", "⣤", "⣥", "⣦", "⣧", "⣨", "⣩", "⣪", "⣫", "⣬", "⣭", "⣮", "⣯",
	"⣰", "⣱", "⣲", "⣳", "⣴", "⣵", "⣶", "⣷", "⣸", "⣹", "⣺", "⣻", "⣼", "⣽", "⣾",
	"⣿"]

values = [[0x1, 0x2, 0x4, 0x40], [0x8, 0x10, 0x20, 0x80]]

fractions = {
	"¼": Fraction(1, 4),
	"½": Fraction(1, 2),
	"¾": Fraction(3, 4),
	"⅐": Fraction(1, 7),
	"⅑": Fraction(1, 9),
	"⅒": Fraction(1, 10),
	"⅓": Fraction(1, 3),
	"⅔": Fraction(2, 3),
	"⅕": Fraction(1, 5),
	"⅖": Fraction(2, 5),
	"⅗": Fraction(3, 5),
	"⅘": Fraction(4, 5),
	"⅙": Fraction(1, 6),
	"⅚": Fraction(5, 6),
	"⅛": Fraction(1, 8),
	"⅜": Fraction(3, 8),
	"⅝": Fraction(5, 8),
	"⅞": Fraction(7, 8)
}

constants = {
	"π": math.pi,
	"e": math.e
}


class units_types(Enum):
	number = auto()
	scale_none = auto()
	scale_SI = auto()
	scale_IEC = auto()
	scale_IEC_I = auto()
	fracts = auto()
	percent = auto()
	date = auto()
	time = auto()
	monetary = auto()


suffix_power_char = ["", "K", "M", "G", "T", "P", "E", "Z", "Y", "R", "Q"]

MAX = sys.float_info.radix ** sys.float_info.mant_dig - 1


def strcol(astr: str) -> int:
	"""Returns the number of columns that the given string would take up if printed."""
	width = wcswidth(astr)
	if width == -1:
		print(
			"\nError! wcswidth failed. Nonprintable wide character.",
			file=sys.stderr)
		sys.exit(1)
	return width
	# return len(astr)


def outputunit(number: float, scale: units_types) -> str:
	x = 0
	val = number
	if -sys.float_info.max <= val <= sys.float_info.max:
		while abs(val) >= 10:
			x += 1
			val /= 10

	if scale == units_types.scale_none:
		if x > sys.float_info.dig:
			return ""

		return f"{number:.{sys.float_info.dig}n}"

	if x > 33 - 1:
		return ""

	if scale in {units_types.scale_IEC, units_types.scale_IEC_I}:
		scale_base = 1024
	elif scale == units_types.scale_SI:
		scale_base = 1000

	power = 0
	if -sys.float_info.max <= number <= sys.float_info.max:
		while abs(number) >= scale_base:
			power += 1
			number /= scale_base

	anumber = abs(number)
	anumber += 0.0005 if anumber < 10 else 0.005 if anumber < 100 else 0.05 if anumber < 1000 else 0.5

	strm = ""

	if number != 0 and anumber < 1000 and power > 0:
		strm = f"{number:.{sys.float_info.dig}n}"

		length = 5 + (number < 0)
		if len(strm) > length:
			prec = 3 if anumber < 10 else 2 if anumber < 100 else 1
			strm = locale.format_string(f"%.{prec}f", number, grouping=True)
	else:
		strm = locale.format_string("%.0f", number, grouping=True)

	strm += suffix_power_char[power] if power < len(
		suffix_power_char) else "(error)"

	if scale == units_types.scale_IEC_I and power > 0:
		strm += "i"

	return strm


def outputfraction(number: float) -> str:
	"""Convert fractions and constants to Unicode characters."""
	output = False

	strm = ""

	n = abs(number)

	if n <= MAX:
		# fractionpart, intpart = math.modf(number)
		# fractionpart = abs(fractionpart)
		intpart, fractionpart = divmod(Fraction(number).limit_denominator(), 1)

		for fraction, value in fractions.items():
			if abs(fractionpart - value) <= sys.float_info.epsilon * n:
				if intpart == 0 and number < 0:
					strm += "-"
				elif intpart != 0:
					strm += f"{intpart:n}"

				strm += fraction

				output = True
				break

		if n > sys.float_info.epsilon and not output:
			for constant, value in constants.items():
				if not output and number % value <= sys.float_info.epsilon * n:
					intpart = number / value

					if intpart == -1:
						strm += "-"
					elif intpart != 1:
						strm += f"{intpart:.{sys.float_info.dig}n}"

					strm += constant

					output = True
					break

	if not output:
		strm += f"{number:n}"

	return strm


def outputlabel(label: float, units: units_types) -> Tuple[int, str]:
	"""Outputs a label in a nice, human readable format."""
	if units == units_types.number:
		strm = f"{label:n}"
	elif units in {units_types.scale_none, units_types.scale_SI, units_types.scale_IEC, units_types.scale_IEC_I}:
		strm = outputunit(label, units)
	elif units == units_types.fracts:
		strm = outputfraction(label)
	elif units == units_types.percent:
		strm = f"{label:%}"
	elif units == units_types.date:
		strm = datetime.fromtimestamp(label, timezone.utc).strftime("%x")
	elif units == units_types.time:
		strm = datetime.fromtimestamp(label, timezone.utc).strftime("%X")
	elif units == units_types.monetary:
		strm = locale.currency(label, grouping=True)

	length = strcol(strm)

	return length, strm


def graph(height: int, width: int, xmin: float, xmax: float, ymin: float, ymax: float, array: List[List[int]], border: bool = False, axis: bool = True, axislabel: bool = True, axistick: bool = True,
		  axisunitslabel: bool = True, xunits: units_types = units_types.fracts, yunits: units_types = units_types.fracts, style: style_types = style_types.light, title: Optional[str] = None, check: bool = True) -> int:
	"""Output graph."""
	if not array:
		return 1

	if height == 0:
		return 1

	if width == 0:
		return 1

	w = shutil.get_terminal_size()

	aheight = height // 4
	awidth = width // 2

	if check:
		if aheight > w.lines:
			print(
				f"The height of the graph ({aheight}) is greater then the height of the terminal ({w.lines}).", file=sys.stderr)
			return 1

		if awidth > w.columns:
			print(
				f"The width of the graph ({awidth}) is greater then the width of the terminal ({w.columns}).", file=sys.stderr)
			return 1

	if xmin >= xmax:
		print("xmin must be less than xmax.", file=sys.stderr)
		return 1

	if ymin >= ymax:
		print("ymin must be less than ymax.", file=sys.stderr)
		return 1

	xstep = (xmax - xmin) / width
	ystep = (ymax - ymin) / height
	xaxis = 0 if xmin > 0 else width if xmax < 0 else width - xmax / xstep
	yaxis = height if ymin > 0 else 0 if ymax < 0 else ymax / ystep
	xdivisor = 2 * 4 * (width // 160 + 2)
	ydivisor = 2 * 4 * (height // 160 + 2)

	if title:
		print(textwrap.fill(title, width=awidth))

	strm = ""

	if border:
		strm += styles[style][2]

		strm += styles[style][0] * awidth

		strm += styles[style][4] + "\n"

	i = 0
	while i < height:
		ayaxis = i <= yaxis < i + 4 if yaxis <= height - 4 else i < yaxis <= i + 4
		yaxislabel = i <= yaxis + 4 < i + 4 if yaxis <= height - 4 else i < yaxis - 4 <= i + 4

		ylabelstrm = ""
		ylabellength = 0

		if axis and axistick and axisunitslabel and 0 <= yaxis <= height:
			output = False
			label = 0.0
			adivisor = -ydivisor if i < yaxis else ydivisor

			k = yaxis + adivisor
			while (k >= i if i < yaxis else k < i + 4) and i >= 4 and not output:
				if i <= k < i + 4:
					label = ymax - (height if k > height else k) * ystep

					output = True
				k += adivisor

			if output:
				ylabellength, ylabelstrm = outputlabel(label, yunits)
				ylabellength *= 2

		if border:
			strm += styles[style][1]

		j = 0
		while j < width:
			axaxis = j < xaxis <= j + 2 if xaxis >= 2 else j <= xaxis < j + 2
			xaxislabel = j < xaxis - 2 <= j + 2 if xaxis >= 2 else j <= xaxis + 2 < j + 2

			output = False

			if axis:
				if axaxis and ayaxis:
					strm += styles[style][6]
					output = True
				elif axaxis:
					if i == 0:
						strm += styles[style][4]
						output = True
					elif i >= height - 4:
						strm += styles[style][10]
						output = True
					elif axistick:
						adivisor = -ydivisor if i < yaxis else ydivisor

						k = yaxis + adivisor
						while (k >= i if i < yaxis else k < i + 4) and i >= 4 and not output:
							if i <= k < i + 4:
								strm += styles[style][7 if xaxis >= 2 else 5]
								output = True
							k += adivisor
					if not output:
						strm += styles[style][1]
						output = True
				elif ayaxis:
					if j == 0:
						strm += styles[style][2]
						output = True
					elif j >= width - 2:
						strm += styles[style][4]
						output = True
					elif axistick:
						adivisor = -xdivisor if j < xaxis else xdivisor

						k = xaxis + adivisor
						while (k >= j if j < xaxis else k < j + 2) and j < width - 4 and not output:
							if j <= k < j + 2:
								strm += styles[style][3 if yaxis <=
													  height - 4 else 9]
								output = True
							k += adivisor
					if not output:
						strm += styles[style][0]
						output = True
				elif yaxislabel and xaxislabel and axistick and axisunitslabel and ymin <= 0 <= ymax and xmin <= 0 <= xmax:
					strm += "0"
					output = True
				elif (j >= width - 2 if xaxis <= width - 2 else j == 0) and yaxislabel and axislabel:
					strm += "x"
					output = True
				elif yaxislabel and axistick and axisunitslabel:
					label = 0.0
					adivisor = -xdivisor if j < xaxis else xdivisor
					if j < xaxis:
						j += 2

					k = xaxis + adivisor
					while (k >= j if j < xaxis else k < j + 2) and j < width - 2 and not output:
						if j <= k < j + 2:
							label = (width if k > width else k) * xstep + xmin

							output = True
						k += adivisor

					if adivisor < 0:
						j -= 2

					if output:
						output = False

						length, astrm = outputlabel(label, xunits)
						length *= 2
						if (j >= xaxis or j + length < xaxis - 4) and j + length < width - 2:
							strm += astrm

							if length > 2:
								j += length - 2

							if adivisor < 0:
								output = True
							else:
								j += 2
				elif (i == 0 if yaxis >= 4 else i >= height - 4) and xaxislabel and axislabel:
					strm += "y"
					output = True
				elif ylabellength and (xaxislabel if xaxis < 2 else j < xaxis - ylabellength and j + 2 >= xaxis - ylabellength) and (yaxis >= 4 or i < height - 4) and axistick and axisunitslabel:
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

				strm += dots[dot]

				if color:
					strm += colors[0]

			j += 2

		if border:
			strm += styles[style][1]

		if i < height - 4 or border:
			strm += "\n"
		i += 4

	if border:
		strm += styles[style][8]

		strm += styles[style][0] * awidth

		strm += styles[style][10]

	print(strm)

	return 0


def arrays(height: int, width: int, xmin: float, xmax: float, ymin: float, ymax: float, aarrays: Sequence[Sequence[Sequence[float]]], border: bool = False, axis: bool = True, axislabel: bool = True, axistick: bool = True, axisunitslabel: bool = True,
		   xunits: units_types = units_types.fracts, yunits: units_types = units_types.fracts, style: style_types = style_types.light, color: color_types = color_types.red, title: Optional[str] = None, check: bool = True) -> int:
	"""Convert one or more arrays to graph and output."""
	if not aarrays:
		return 1

	if not all(len(x) == 2 for aarray in aarrays for x in aarray):
		print("Error: The arrays must have two columns.")
		return 1

	w = shutil.get_terminal_size()

	if height == 0:
		height = w.lines * 4

	if width == 0:
		width = w.columns * 2

	if check:
		aheight = height // 4
		awidth = width // 2

		if aheight > w.lines:
			print(
				f"The height of the graph ({aheight}) is greater then the height of the terminal ({w.lines}).", file=sys.stderr)
			return 1

		if awidth > w.columns:
			print(
				f"The width of the graph ({awidth}) is greater then the width of the terminal ({w.columns}).", file=sys.stderr)
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

	xstep = (xmax - xmin) / width
	ystep = (ymax - ymin) / height
	xaxis = width - xmax / xstep
	yaxis = ymax / ystep

	aaarray = [[0 for j in range(height)] for i in range(width)]

	for j, aarray in enumerate(aarrays):
		acolor = color + 1 if len(aarrays) == 1 else j % (len(colors) - 2) + 3

		for i in aarray:
			if i[0] >= xmin and i[0] < xmax and i[1] >= ymin and i[1] < ymax:
				x = int(i[0] / xstep + xaxis)
				y = int(yaxis - i[1] / ystep - 1)

				if aaarray[x][y]:
					if aaarray[x][y] != acolor:
						aaarray[x][y] = 1
				else:
					aaarray[x][y] = acolor

	return graph(height, width, xmin, xmax, ymin, ymax, aaarray, border=border, axis=axis, axislabel=axislabel,
				 axistick=axistick, axisunitslabel=axisunitslabel, xunits=xunits, yunits=yunits, style=style, title=title)


def array(height: int, width: int, xmin: float, xmax: float, ymin: float, ymax: float, aarray: Sequence[Sequence[float]], border: bool = False, axis: bool = True, axislabel: bool = True, axistick: bool = True,
		  axisunitslabel: bool = True, xunits: units_types = units_types.fracts, yunits: units_types = units_types.fracts, style: style_types = style_types.light, color: color_types = color_types.red, title: Optional[str] = None) -> int:
	"""Convert single array to graph and output."""
	return arrays(height, width, xmin, xmax, ymin, ymax, [aarray], border=border, axis=axis, axislabel=axislabel,
				  axistick=axistick, axisunitslabel=axisunitslabel, xunits=xunits, yunits=yunits, style=style, color=color, title=title)


def functions(height: int, width: int, xmin: float, xmax: float, ymin: float, ymax: float, afunctions: Sequence[Callable[[float], float]], border: bool = False, axis: bool = True, axislabel: bool = True, axistick: bool = True,
			  axisunitslabel: bool = True, xunits: units_types = units_types.fracts, yunits: units_types = units_types.fracts, style: style_types = style_types.light, color: color_types = color_types.red, title: Optional[str] = None, check: bool = True) -> int:
	"""Convert one or more functions to graph and output."""
	if not afunctions:
		return 1

	w = shutil.get_terminal_size()

	if height == 0:
		height = w.lines * 4

	if width == 0:
		width = w.columns * 2

	if check:
		aheight = height // 4
		awidth = width // 2

		if aheight > w.lines:
			print(
				f"The height of the graph ({aheight}) is greater then the height of the terminal ({w.lines}).", file=sys.stderr)
			return 1

		if awidth > w.columns:
			print(
				f"The width of the graph ({awidth}) is greater then the width of the terminal ({w.columns}).", file=sys.stderr)
			return 1

	if xmin >= xmax:
		print("xmin must be less than xmax.", file=sys.stderr)
		return 1

	if ymin >= ymax:
		print("ymin must be less than ymax.", file=sys.stderr)
		return 1

	rows = width

	xstep = (xmax - xmin) / width
	ystep = (ymax - ymin) / height
	xaxis = width - xmax / xstep
	yaxis = ymax / ystep
	xres = 2

	array = [[0 for j in range(height)] for i in range(width)]

	for j, function in enumerate(afunctions):
		acolor = color + \
			1 if len(afunctions) == 1 else j % (len(colors) - 2) + 3

		for i in (x / xres for x in range(rows * xres)):
			x = i * xstep + xmin
			y = function(x)

			if xmin <= x < xmax and ymin <= y < ymax:
				ax = int(x / xstep + xaxis)
				ay = int(yaxis - y / ystep - 1)

				if array[ax][ay]:
					if array[ax][ay] != acolor:
						array[ax][ay] = 1
				else:
					array[ax][ay] = acolor

	return graph(height, width, xmin, xmax, ymin, ymax, array, border=border, axis=axis, axislabel=axislabel,
				 axistick=axistick, axisunitslabel=axisunitslabel, xunits=xunits, yunits=yunits, style=style, title=title)


def function(height: int, width: int, xmin: float, xmax: float, ymin: float, ymax: float, afunction: Callable[[float], float], border: bool = False, axis: bool = True, axislabel: bool = True, axistick: bool = True,
			 axisunitslabel: bool = True, xunits: units_types = units_types.fracts, yunits: units_types = units_types.fracts, style: style_types = style_types.light, color: color_types = color_types.red, title: Optional[str] = None) -> int:
	"""Convert single function to function array and output."""
	return functions(height, width, xmin, xmax, ymin, ymax, [afunction], border=border, axis=axis, axislabel=axislabel,
					 axistick=axistick, axisunitslabel=axisunitslabel, xunits=xunits, yunits=yunits, style=style, color=color, title=title)
