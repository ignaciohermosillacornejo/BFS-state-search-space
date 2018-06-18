#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "board.h"

#define MIN(A, B) (((A) < (B)) ? (A) : (B))
#define MAX(A, B) (((A) > (B)) ? (A) : (B))

void board_print_cell(Cell *cell);
void board_set_priority(Board *board, Cell *cell, int priority);

/* Helper function that returns the a pointer to the cell of row and col  */
Cell *board_get_cell(Board *board, int row, int col)
{
    if (row >= 0 && row <= board->height - 1 && col >= 0 && col <= board->width - 1)
    {
        return (board->cells) + (board->width) * row + col;
    }
    else
    {
        printf("ERROR, accesing an out of bound cell!\n");
        exit(1);
    }
}

/* Helper function to return left neighbour, returns NULL if it doesn't have one */
Cell *board_left_neighbour(Board *board, Cell *cell)
{
    Cell *neighbour = NULL;
    if (cell->col > 0)
    {
        neighbour = board_get_cell(board, cell->row, cell->col - 1);
    }
    return neighbour;
}

/* Helper function to return right neighbour, returns NULL if it doesn't have one */
Cell *board_right_neighbour(Board *board, Cell *cell)
{
    Cell *neighbour = NULL;
    if (cell->col < board->width - 1)
    {
        neighbour = board_get_cell(board, cell->row, cell->col + 1);
    }
    return neighbour;
}

/* Helper function to return upper neighbour, returns NULL if it doesn't have one */
Cell *board_upper_neighbour(Board *board, Cell *cell)
{
    Cell *neighbour = NULL;
    if (cell->row > 0)
    {
        neighbour = board_get_cell(board, cell->row - 1, cell->col);
    }
    return neighbour;
}

/* Helper function to return bottom neighbour, returns NULL if it doesn't have one */
Cell *board_bottom_neighbour(Board *board, Cell *cell)
{
    Cell *neighbour = NULL;
    if (cell->row < board->height - 1)
    {
        neighbour = board_get_cell(board, cell->row + 1, cell->col);
    }
    return neighbour;
}

/* Helper function to return corresponding neighbour accoring to int direction */
Cell *board_get_neighbour(Board *board, Cell *cell, int direction)
{
    /* The idea is to always call this function to transition states
    * 0: get upper neighbour
    * 1: get right neighbour
    * 2: get bottom neighbour
    * 3: get left neighbour
    */
    if (direction == 0)
    {
        return board_upper_neighbour(board, cell);
    }
    else if (direction == 1)
    {
        return board_right_neighbour(board, cell);
    }
    else if (direction == 2)
    {
        return board_bottom_neighbour(board, cell);
    }
    else if (direction == 3)
    {
        return board_left_neighbour(board, cell);
    }
    else
    {
        printf("Error, invalid direction!\n");
        exit(1);
    }
}

/* Helper function to rotate a ship */
void board_rotate_ship(Board *board, Cell *cell)
{
    cell->degree = (cell->degree + 1) % 4;
}

/* Helper function to destroy an asteroid  TODO: asteroid count and other things */
void board_destroy_asteroid(Board *board, Cell *cell)
{
    cell->degree = 5;
    board->count_asteroids -= 1;
}

void board_shoot_direction(Board *board, Cell *cell, int direction)
{
    Cell *target_cell = board_get_neighbour(board, cell, direction);
    while (target_cell)
    {
        if (target_cell->degree <= 3)
        {
            board_rotate_ship(board, target_cell);
            return;
        }
        else if (target_cell->degree == 4)
        {
            board_destroy_asteroid(board, target_cell);
            board->total_asteroids -= 1;
            return;
        }
        else
        {
            target_cell = board_get_neighbour(board, target_cell, direction);
        }
    }
}

/* Helper funcion, returns a neighbour based on the cell and and int */
void board_shoot(Board *board, int row, int col)
{
    /* The idea is to always call this function to transition states
    * 0: shoot up
    * 1: shoot right
    * 2: shoot down
    * 3: shoot left
    */
    Cell *cell = board_get_cell(board, row, col);
    if (cell->degree >= 0 && cell->degree <= 3)
    {
        board_shoot_direction(board, cell, cell->degree);
    }
    else
    {
        printf("Error, trying to shoot from cell that is not a ship!\n");
        board_print_cell(cell);
        exit(1);
    }
}
/*
State *board_get_state(Board *board)//, State * parent, int parent_x, int parent_y)
{
    State * state = malloc(sizeof(State));
    state->ships = arraylist_init();
    state->asteroids = arraylist_init();
    state->count_asteroids = board->count_asteroids;
    //state->parent = parent;
    //state->parent_x = parent_x;
    //state->parent_y = parent_y;

    for (int i = 0; i < board->total_ships; i++)
    {
        arraylist_append(state->ships, board->ships[i]->degree);
    }
    for (int i = 0; i < board->total_asteroids; i++)
    {
        arraylist_append(state->asteroids, board->asteroids[i]->degree);
    }
    return state;
}

void board_set_state(Board *board, State * state)
{
    board->count_asteroids = state->count_asteroids;
    for (int i = 0; i < board->total_ships; i++)
    {
        board->ships[i]->degree = arraylist_get(state->ships, i);
    }
    for (int i = 0; i < board->total_ships; i++)
    {
        board->asteroids[i]->degree = arraylist_get(state->asteroids, i);
    }
}
*/
/* Create our board and return a pointer to our object */
Board *board_init(int height, int width)
{
    Board *board = malloc(sizeof(Board));
    board->height = height;
    board->width = width;
    board->total_ships = 0;
    board->total_asteroids = 0;
    /* We allocate enough memory for the cells in our board
     * we store a simple array of pointers and use basic arithmetic two get the correct cell
     */
    board->cells = (Cell *)malloc(board->height * board->width * sizeof(Cell));
    //board->ships =     (Cell *)malloc(1 * sizeof(Cell *));
    //board->asteroids = (Cell *)malloc(1 * sizeof(Cell *));

    /* We set the initial values of the cells in our board
     * on the first pass we just create an empty board
     */
    for (int row = 0; row < board->height; row++)
    {
        for (int col = 0; col < board->width; col++)
        {
            Cell *cell = board_get_cell(board, row, col);
            cell->row = row;
            cell->col = col;
            cell->degree = 0;
        }
    }
    return board;
}

/* Used to free the memory of a board and all associated cells */
void board_destroy(Board *board)
{
    free(board->cells);
    free(board);
}

/* Get the degree of a given cell */
int board_get_degree(Board *board, int row, int col)
{
    Cell *cell = board_get_cell(board, row, col);
    return cell->degree;
}

/* Used when creating out board, we set the apropiate info */
void board_set_degree(Board *board, int row, int col, int degree)
{
    Cell *cell = board_get_cell(board, row, col);
    if (degree >= 0 && degree <= 3)
    {
        cell->degree = degree;
        board->ships[board->total_ships] = cell;
        board->total_ships += 1;
    }
    else if (degree == 4)
    {
        cell->degree = degree;
        //board->asteroids[board->total_asteroids] = cell;
        board->total_asteroids += 1;
    }
    else if (degree == 5)
    {
        cell->degree = degree;
    }
    else
    {
        printf("[%d, %d] Error, incorrect set degree call!\n", row, col);
        exit(1);
    }
}

/* Debuging function */
void board_print_degree(Board *board)
{
    for (int row = 0; row < board->height; row++)
    {
        for (int col = 0; col < board->width; col++)
        {
            printf("%d ", board_get_degree(board, row, col));
        }
        printf("\n");
    }
    printf("\n");
}

/* Debuging function */
void board_print_cell(Cell *cell)
{
    printf("[%d, %d] degree: %d\n", cell->row, cell->col, cell->degree);
}

/* Debuging function */
void board_print_ships(Board *board)
{
    printf("Printing all ship\n");
    for (int i = 0; i < board->total_ships; i++)
    {
        board_print_cell(board->ships[i]);
    }
}

/* Debuging function */
void board_print_asteroids(Board *board)
{
    printf("Printing all asteroids\n");
    for (int i = 0; i < board->total_asteroids; i++)
    {
        board_print_cell(board->asteroids[i]);
    }
}