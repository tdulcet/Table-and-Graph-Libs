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

if sys.platform != "win32":
	import ctypes
	from ctypes.util import find_library

	libc = ctypes.CDLL(find_library("c"))
	libc.wcwidth.argtypes = (ctypes.c_wchar,)
	libc.wcwidth.restype = ctypes.c_int
	libc.wcswidth.argtypes = (ctypes.c_wchar_p, ctypes.c_int)
	libc.wcswidth.restype = ctypes.c_int

	def wcswidth(astr: str) -> int:
		return libc.wcswidth(astr, len(astr))
else:
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


styles = (
	("-", "|", "+", "+", "+", "+", "+", "+", "+", "+", "+"),  # ASCII
	("—", "|", "+", "+", "+", "+", "+", "+", "+", "+", "+"),  # Basic
	("─", "│", "┌", "┬", "┐", "├", "┼", "┤", "└", "┴", "┘"),  # Light
	("━", "┃", "┏", "┳", "┓", "┣", "╋", "┫", "┗", "┻", "┛"),  # Heavy
	("═", "║", "╔", "╦", "╗", "╠", "╬", "╣", "╚", "╩", "╝"),  # Double
	("─", "│", "╭", "┬", "╮", "├", "┼", "┤", "╰", "┴", "╯"),  # Light Arc
	("╌", "┊", "┌", "┬", "┐", "├", "┼", "┤", "└", "┴", "┘"),  # Light Dashed
	("╍", "┋", "┏", "┳", "┓", "┣", "╋", "┫", "┗", "┻", "┛")  # Heavy Dashed
	# (" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ")) #No border
)


class color_types(IntEnum):
	default = 0
	black = auto()
	red = auto()
	green = auto()
	yellow = auto()
	blue = auto()
	magenta = auto()
	cyan = auto()
	white = auto()
	gray = auto()
	bright_red = auto()
	bright_green = auto()
	bright_yellow = auto()
	bright_blue = auto()
	bright_magenta = auto()
	bright_cyan = auto()
	bright_white = auto()


colors = ("\033[39m", "\033[30m", "\033[31m", "\033[32m", "\033[33m",
		  "\033[34m", "\033[35m", "\033[36m", "\033[37m", "\033[90m",
		  "\033[91m", "\033[92m", "\033[93m", "\033[94m", "\033[95m",
		  "\033[96m", "\033[97m")

dots = (
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
	"⣿")
dotvalues = ((0x1, 0x2, 0x4, 0x40), (0x8, 0x10, 0x20, 0x80))

blocks = (" ", "▖", "▗", "▄", "▘", "▌", "▚",
		  "▙", "▝", "▞", "▐", "▟", "▀", "▛", "▜", "█")
blockvalues = ((4, 1), (8, 2))

bars = (" ", "▁", "▂", "▃", "▄", "▅", "▆", "▇", "█")


class type_types(IntEnum):
	braille = 0
	block = auto()
	histogram = auto() # Set automatically by the histogram() function

atype_types = (type_types.braille, type_types.block)

marks = (((0, 0),), ((0, 1), (-1, 0), (0, 0), (1, 0), (0, -1)),
		 ((-1, 1), (0, 1), (1, 1), (-1, 0), (1, 0), (-1, -1), (0, -1), (1, -1)))


class mark_types(IntEnum):
	dot = 0
	plus = auto()
	square = auto()


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


suffix_power_char = ("", "K", "M", "G", "T", "P", "E", "Z", "Y", "R", "Q")

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

	if number and anumber < 1000 and power > 0:
		strm = f"{number:.{sys.float_info.dig}n}"

		length = 5 + (number < 0)
		if len(strm) > length:
			prec = 3 if anumber < 10 else 2 if anumber < 100 else 1
			strm = locale.format_string(f"%.{prec}f", number, grouping=True)
	else:
		strm = locale.format_string("%.0f", number, grouping=True)

	# "k" if power == 1 and scale == scale_SI else
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


def graph(height: int, width: int, xmin: float, xmax: float, ymin: float, ymax: float, array: List[List[int]], border: bool = False, axis: bool = True, axislabel: bool = True, axistick: bool = True, axisunitslabel: bool = True, xunits: units_types = units_types.fracts, yunits: units_types = units_types.fracts, atype: type_types = type_types.braille, style: style_types = style_types.light, title: Optional[str] = None, check: bool = True) -> int:
	"""Output graph."""
	if not array:
		return 1

	if height == 0:
		return 1

	if width == 0:
		return 1

	w = shutil.get_terminal_size()

	ai = 8 if atype == type_types.histogram else 2 if atype == type_types.block else 4
	aj = 1 if atype == type_types.histogram else 2

	aheight = height // ai
	awidth = width // aj

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
	xdivisor = 4 * aj * ((((2 * width) // aj) // 160) + 2)
	ydivisor = 2 * ai * ((((4 * height) // ai) // 160) + 2)

	if title:
		print(textwrap.fill(title, width=awidth))

	astyle = styles[style]

	strm = ""

	if border:
		strm += astyle[2] + (astyle[0] * awidth) + astyle[4] + "\n"

	i = 0
	while i < height:
		ayaxis = i <= yaxis < i + ai if yaxis <= height - ai else i < yaxis <= i + ai
		yaxislabel = i <= yaxis + ai < i + ai if yaxis <= height - ai else i < yaxis - ai <= i + ai

		ylabelstrm = ""
		ylabellength = 0

		if axis and axistick and axisunitslabel and 0 <= yaxis <= height:
			output = False
			label = 0.0
			adivisor = -ydivisor if i < yaxis else ydivisor

			k = yaxis + adivisor
			while (k >= i if i < yaxis else k < i + ai) and i >= ai and not output:
				if i <= k < i + ai:
					label = ymax - min(k, height) * ystep

					output = True
				k += adivisor

			if output:
				ylabellength, ylabelstrm = outputlabel(label, yunits)
				ylabellength *= aj

		if border:
			strm += astyle[1]

		j = 0
		while j < width:
			axaxis = j < xaxis <= j + aj if xaxis >= aj else j <= xaxis < j + aj
			xaxislabel = j < xaxis - aj <= j + aj if xaxis >= aj else j <= xaxis + aj < j + aj

			output = False

			if axis:
				if axaxis and ayaxis:
					strm += astyle[6]
					output = True
				elif axaxis:
					if i == 0:
						strm += astyle[4]
						output = True
					elif i >= height - ai:
						strm += astyle[10]
						output = True
					elif axistick:
						adivisor = -ydivisor if i < yaxis else ydivisor

						k = yaxis + adivisor
						while (k >= i if i < yaxis else k < i + ai) and i >= ai and not output:
							if i <= k < i + ai:
								strm += astyle[7 if xaxis >= aj else 5]
								output = True
							k += adivisor
					if not output:
						strm += astyle[1]
						output = True
				elif ayaxis:
					if j == 0:
						strm += astyle[2]
						output = True
					elif j >= width - aj:
						strm += astyle[4]
						output = True
					elif axistick:
						adivisor = -xdivisor if j < xaxis else xdivisor

						k = xaxis + adivisor
						while (k >= j if j < xaxis else k < j + aj) and j < width - ai and not output:
							if j <= k < j + aj:
								strm += astyle[3 if yaxis <= height - ai else 9]
								output = True
							k += adivisor
					if not output:
						strm += astyle[0]
						output = True
				elif yaxislabel and xaxislabel and axistick and axisunitslabel and ymin <= 0 <= ymax and xmin <= 0 <= xmax:
					strm += "0"
					output = True
				elif (j >= width - aj if xaxis <= width - aj else j == 0) and yaxislabel and axislabel:
					strm += "x"
					output = True
				elif yaxislabel and axistick and axisunitslabel:
					label = 0.0
					adivisor = -xdivisor if j < xaxis else xdivisor
					if j < xaxis:
						j += aj

					k = xaxis + adivisor
					while (k >= j if j < xaxis else k < j + aj) and j < width - aj and not output:
						if j <= k < j + aj:
							label = min(k, width) * xstep + xmin

							output = True
						k += adivisor

					if adivisor < 0:
						j -= aj

					if output:
						output = False

						length, astrm = outputlabel(label, xunits)
						length *= aj
						if (j >= xaxis or j + length < xaxis - ai) and j + length < width - aj:
							strm += astrm

							if length > aj:
								j += length - aj

							if adivisor < 0:
								output = True
							else:
								j += aj
				elif (i == 0 if yaxis >= ai else i >= height - ai) and xaxislabel and axislabel:
					strm += "y"
					output = True
				elif ylabellength and (xaxislabel if xaxis < aj else j < xaxis - ylabellength and j + aj >= xaxis - ylabellength) and (yaxis >= ai or i < height - ai) and axistick and axisunitslabel:
					strm += ylabelstrm
					output = True
					if ylabellength > aj:
						j += ylabellength - aj

			if not output:
				dot = 0
				color = 0

				for k in range(min(aj, width - j)):
					for l in range(min(ai, height - i)):
						value = array[j + k][i + l]
						if value:
							if atype == type_types.histogram:
								if not dot:
									dot = (len(bars) - l) - 1
							elif atype == type_types.block:
								dot += blockvalues[k][l]
							else:
								dot += dotvalues[k][l]
						if color:
							if value and color != value:
								color = 1
						else:
							color = value

				if color:
					color -= 1

				if color:
					strm += colors[color]

				strm += bars[dot] if atype == type_types.histogram else blocks[dot] if atype == type_types.block else dots[dot]

				if color:
					strm += colors[0]

			j += aj

		if border:
			strm += astyle[1]

		if i < height - ai or border:
			strm += "\n"
		i += ai

	if border:
		strm += astyle[8] + (astyle[0] * awidth) + astyle[10]

	print(strm)

	return 0


def histogram(height: int, width: int, xmin: float, xmax: float, ymin: float, ymax: float, aarray: Sequence[float], border: bool = False, axis: bool = True, axislabel: bool = True, axistick: bool = True, axisunitslabel: bool = True, xunits: units_types = units_types.fracts, yunits: units_types = units_types.fracts, style: style_types = style_types.light, color: color_types = color_types.red, title: Optional[str] = None, check: bool = True) -> int:
	"""Convert one or more arrays to graph and output."""
	if not aarray:
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

	height *= 2
	width //= 2

	if xmin == xmax == 0:
		xmin = min(aarray)
		xmax = max(aarray)

	if xmin >= xmax:
		print("xmin must be less than xmax.", file=sys.stderr)
		return 1

	histogram = [0 for i in range(width)]

	xstep = (xmax - xmin) / width

	for x in aarray:
		if xmin <= x < xmax:
			index = int((x - xmin) / xstep)
			histogram[index] += 1

	if ymin == ymax == 0:
		ymin = min(histogram)
		ymax = max(histogram)

	if ymin >= ymax:
		print("ymin must be less than ymax.", file=sys.stderr)
		return 1

	ystep = (ymax - ymin) / height
	yaxis = ymax / ystep

	aaarray = [[0 for j in range(height)] for i in range(width)]

	acolor = color + 1

	for x, ay in enumerate(histogram):
		y = 0 if ay >= ymax else int(yaxis - (ay / ystep))
		while y < yaxis and y < height:
			aaarray[x][y] = acolor
			y += 1

	return graph(height, width, xmin, xmax, ymin, ymax, aaarray, border, axis, axislabel, axistick, axisunitslabel, xunits, yunits, type_types.histogram, style, title)


def plots(height: int, width: int, xmin: float, xmax: float, ymin: float, ymax: float, aarrays: Sequence[Sequence[Sequence[float]]], border: bool = False, axis: bool = True, axislabel: bool = True, axistick: bool = True, axisunitslabel: bool = True, xunits: units_types = units_types.fracts, yunits: units_types = units_types.fracts, atype: type_types = type_types.braille, mark: mark_types = mark_types.dot, style: style_types = style_types.light, color: color_types = color_types.red, title: Optional[str] = None, check: bool = True) -> int:
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

	if atype == type_types.block:
		height //= 2

	if xmin == xmax == 0:
		xmin = min(x for aarray in aarrays for x, y in aarray)
		xmax = max(x for aarray in aarrays for x, y in aarray)

	if ymin == ymax == 0:
		ymin = min(y for aarray in aarrays for x, y in aarray)
		ymax = max(y for aarray in aarrays for x, y in aarray)

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

		for x, y in aarray:
			if xmin <= x < xmax and ymin <= y < ymax:
				ax = int(x / xstep + xaxis)
				ay = int(yaxis - y / ystep - 1)

				for ix, iy in marks[mark]:
					x = ax + ix
					y = ay + iy

					if x < width and y < height:
						if aaarray[x][y]:
							if aaarray[x][y] != acolor:
								aaarray[x][y] = 1
						else:
							aaarray[x][y] = acolor

	return graph(height, width, xmin, xmax, ymin, ymax, aaarray, border, axis, axislabel, axistick, axisunitslabel, xunits, yunits, atype, style, title)


def plot(height: int, width: int, xmin: float, xmax: float, ymin: float, ymax: float, aarray: Sequence[Sequence[float]], border: bool = False, axis: bool = True, axislabel: bool = True, axistick: bool = True, axisunitslabel: bool = True, xunits: units_types = units_types.fracts, yunits: units_types = units_types.fracts, atype: type_types = type_types.braille, mark: mark_types = mark_types.dot, style: style_types = style_types.light, color: color_types = color_types.red, title: Optional[str] = None) -> int:
	"""Convert single array to graph and output."""
	return plots(height, width, xmin, xmax, ymin, ymax, [aarray], border, axis, axislabel, axistick, axisunitslabel, xunits, yunits, atype, mark, style, color, title)


def functions(height: int, width: int, xmin: float, xmax: float, ymin: float, ymax: float, afunctions: Sequence[Callable[[float], float]], border: bool = False, axis: bool = True, axislabel: bool = True, axistick: bool = True, axisunitslabel: bool = True, xunits: units_types = units_types.fracts, yunits: units_types = units_types.fracts, atype: type_types = type_types.braille, style: style_types = style_types.light, color: color_types = color_types.red, title: Optional[str] = None, check: bool = True) -> int:
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

	if atype == type_types.block:
		height //= 2

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

	return graph(height, width, xmin, xmax, ymin, ymax, array, border, axis, axislabel, axistick, axisunitslabel, xunits, yunits, atype, style, title)


def function(height: int, width: int, xmin: float, xmax: float, ymin: float, ymax: float, afunction: Callable[[float], float], border: bool = False, axis: bool = True, axislabel: bool = True, axistick: bool = True, axisunitslabel: bool = True, xunits: units_types = units_types.fracts, yunits: units_types = units_types.fracts, atype: type_types = type_types.braille, style: style_types = style_types.light, color: color_types = color_types.red, title: Optional[str] = None) -> int:
	"""Convert single function to function array and output."""
	return functions(height, width, xmin, xmax, ymin, ymax, [afunction], border, axis, axislabel, axistick, axisunitslabel, xunits, yunits, atype, style, color, title)
