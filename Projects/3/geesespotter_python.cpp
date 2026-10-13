#include "geesespotter_lib.h"
#include "defs.h"
#include <iostream>

_markedValue = 0x10;
_hiddenValue = 0x20;
_revealedValue = 0x0F;
_D

def _create_board(_x, _y) {
	_board = new char[x*y]{};
	return(board)
}

def _clean_board(_board) {
	del board;
}

def _print_board(_board, _x, _y) {
	for_j_in_range(y) {
		for_i_in_range(x)
			if (board[j*x+i] & markedValue)
				print('M')
			elif (board[j*x+i] & hiddenValue)
				print('*')
			else
				print(int(board[j*x+i] & revealedValue))
		print("\n")
	}
}

def _hide_board(_board, _x, _y) {
	for_i_in_range(x*y)
		board[i] |= hiddenValue;
}

def _mark(_board, _x, _y, _i, _j) {
	if (not(board[j*x+i] & hiddenValue))
		return(2)
	board[j*x+i] ^= markedValue;
	return(0)
}

def _compute_neighbours(_board, _x, _y) {
	for_i_in_range(y)
		for_j_in_range(x)
			if ((board[j*x+i] & revealedValue) == 9)
				for_d_in_D
					if (i + d[0] < x and j + d[1] < y)
						board[(j + d[1])*x + i + d[0]] += 1;
}

def _is_game_won(_board, _x, _y) {
	for_i_in_range(x*y)
		if ((board[i] & hiddenValue) and (board[i] & revealedValue) != 9)
			return(0)
	return(1)
}

def _reveal(_board, _x, _y, _i, _j) {
	if (board[y*x + i] & markedValue)
		return(1)
	elif (not(board[j*x + i] & hiddenValue))
		return(2)

	board[j*x+i] &= ~hiddenValue;

	if ((board[j*x+i] & revealedValue) == 9)
		return(9)
	elif ((board[j*x+i] & revealedValue) == 0)
		for_d_in_D
			if (i + d[0] < x and j + d[1] < y and (board[(j + d[1])*x + i + d[0]] & revealedValue) != 9)
				board[(j + d[1])*x + i + d[0]] &= ~hiddenValue;

	return(0)
}
