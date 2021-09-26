//=============================================================================
// snake.c
// A game of snake that plays in the linux terminal written in C using Ncurses
//
// Written by:	Tom Reid <tom.reid.2018@gmail.com>
// Created on:	25/9/21
//
// Copyright (c) 2021 Tom Reid.	Released under the MIT License.
// See LICENSE.txt for Details.
//=============================================================================
// Libaries
//=============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>


//=============================================================================
// Defines
//=============================================================================

// Objects
#define SNAKE		ACS_CKBOARD
#define FRUIT		ACS_DIAMOND
#define BORDER		ACS_HLINE

typedef struct location {
	int x;
	int y;
} LOC;

//=============================================================================
// Function Prototypes
//=============================================================================

void draw_fruit(LOC *a, int rows, int cols);

void details(int rows, int cols);

//=============================================================================
// Main Function
//=============================================================================

int main(void) {

	// Initialise Ncurses
	initscr();				// Initialise window
	noecho();				// Disable echo of user input
	cbreak();				// Dont wait for a newline
	keypad(stdscr, TRUE);	// Enable key input
	curs_set(FALSE);		// Disable cursor

	// Get terminal dimensions.
	int t_rows = 0, t_cols = 0;
	getmaxyx(stdscr, t_rows, t_cols);

	// Calculate dimensions of playfield
	int g_rows = t_rows - 2,
		g_cols = t_cols;

	// Initialise fruit location
	LOC fruit;

	// Print Score
	//mvprintw(t_rows, t_cols,"SCORE");

	int ch;
	while ((ch = getchar()) != 'q') {
		draw_fruit(&fruit, g_rows, g_cols);
		details(t_rows, t_cols);
		refresh();
	}

	endwin();
	return 0;
}

//=============================================================================
// Draw Fruit
//=============================================================================

void draw_fruit(LOC *a, int rows, int cols) {
	// Generate random num for x & y.
	a->x = rand() % rows;
	a->y = rand() % cols;

	// Print a diamond symbol.
	mvaddch(a->x, a->y, FRUIT);
}

//=============================================================================
// Details (Score, Command help)
//=============================================================================

void details(int rows, int cols) {
	// Seperation Line
	for (int i = 0; i <= cols; i++) {
		mvaddch((rows - 2), i, BORDER);
	}

	// Display Score
	mvprintw((rows - 1), 0,"SCORE:"); 
}