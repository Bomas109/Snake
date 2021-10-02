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
#include <stdbool.h>
#include <time.h>

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

void details(int rows, int cols, int score);

void draw_snake(LOC snake[255], int snake_length, int direction);

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

	// Set seed for rand().
	srand(time(NULL));

	// Stores the snakes direction.
	// Up = 1 | Down = 2 | Left = 3 | Right = 4
	int direction = 4;

	// Stores snake length.
	int snake_length = 5;

	// Stores the Score.
	int score = 0;

	// Initialise fruit location
	LOC fruit;

	// Initialise snake array
	LOC snake[255];

	// Snake starting position (center).
	snake[0].x = g_rows / 2;
	snake[0].y = g_cols / 2;

	bool game_over = false;
	int ch;
	while (!game_over) {
		draw_snake(snake, snake_length, direction);
		draw_fruit(&fruit, g_rows, g_cols);
		details(t_rows, t_cols, score);
		refresh();

		// Input
		ch = getch();
		switch(ch) {

			case KEY_UP:
				direction = 1;
				break;

			case KEY_DOWN:
				direction = 2;
				break;

			case KEY_LEFT:
				direction = 3;
				break;

			case KEY_RIGHT:
				direction = 4;
				break;

			case 'q':
				game_over = true;
				break;

		}
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

void details(int rows, int cols, int score) {
	// Seperation Line
	for (int i = 0; i <= cols; i++) {
		mvaddch((rows - 2), i, BORDER);
	}

	// Display Score
	mvprintw((rows - 1), 0,"SCORE: %d", score);

	// Display Credits
	mvprintw((rows - 1), ((cols - 17) / 2), "Snake By Tom Reid");
}

//=============================================================================
// Draw Snake
//=============================================================================

void draw_snake(LOC snake[255], int snake_length, int direction) {

	// Movement
	LOC snake_next;

	if (direction == 1) { // Up = 1
		snake_next.x = snake[0].x - 1;
		snake_next.y = snake[0].y;
	} else if (direction == 2) { // Down = 2
		snake_next.x = snake[0].x + 1;
		snake_next.y = snake[0].y;

	} else if (direction == 3) { // Left = 3
		snake_next.x = snake[0].x;
		snake_next.y = snake[0].y - 1;

	} else if (direction == 4) { // Right = 4
		snake_next.x = snake[0].x;
		snake_next.y = snake[0].y + 1;
	}

	snake[0] = snake_next;

	// Display Snake.
	for(int i = 0; i < snake_length; i++) {
		mvaddch(snake[i].x, snake[i].y, SNAKE);
	}
}
