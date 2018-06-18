#pragma once
#include "arraylist.h"

typedef struct board Board;
typedef struct cell Cell;
typedef struct state State;



struct board
{
    int width;
    int height;
    int total_ships;
    int total_asteroids;
    int count_ships;
    int count_asteroids;
    Cell *ships[1000]; // array of pointers to our ships
    Cell *asteroids[1000]; // array of pointers to our asteroids
    Cell *cells; // Simple array of cells to represent a matrix
};

/* A simple struct to hold some properties */
struct cell
{
    int row;
    int col;
    int degree; // From 0 to 5
};

/* State to hold  */
struct state
{
    ArrayList * ships;
    ArrayList * asteroids;
    int count_asteroids;
    State * parent;
};

/* Board creation and destruction */
Board *board_init(int height, int width);
void board_destroy(Board *board); 
void board_shoot(Board * board, int row, int col);
State * board_get_state(Board *board);
void board_set_state(Board *board, State * state);
/* Setters and getters for our board */
int  board_get_degree        (Board *board, int row, int col             );
void board_set_degree        (Board *board, int row, int col, int  degree);
/* Debuging functions */
void board_print_degree(Board *board);
void board_print_cell(Cell *cell);
void board_print_ships(Board *board);
void board_print_asteroids(Board *board);