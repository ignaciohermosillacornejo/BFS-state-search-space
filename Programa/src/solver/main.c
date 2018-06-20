#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "queue.h"
#include "hash.h"

void print_answer(State * state)
{
	if (state->parent)
	{
		print_answer(state->parent);
		printf("%d,%d\n", state->parent_x, state->parent_y);
	}
}


void bfs(Board * board)
{
	Queue * queue = queue_init();
	Hashtable * hash = hashtable_init(board->total_ships, board->total_asteroids);
	int count = 0;
	
	queue_push(queue, board_get_state(board, NULL, -1, -1));

	while (queue->first)
	{
		State * current_state = queue_pop(queue);
		if (current_state->count_asteroids == 0)
		{
			//printf("number of states: %d\n", count);
			print_answer(current_state);
			hashtable_destroy(hash);
			break;
		}

		for (int i = 0; i < board->total_ships; i++)
		{
			board_set_state(board, current_state);
			if(board_shoot(board, board->ships[i]))
			{
				State * new_state = board_get_state(board, current_state, board->ships[i]->col, board->ships[i]->row);
				if (hashtable_insert(hash, new_state))
				{
					queue_push(queue, new_state);
				}
				count += 1;
			}
		}
	}


	queue_destroy(queue);
}


int main(int argc, char** argv)
{
	if (argc != 2)
	{
		printf("Modo de uso: ./solver test.txt\n");
		return 0;
	}

	FILE *input_file = fopen(argv[1], "r");

	if (!input_file)
	{
		printf("¡El archivo %s no existe!\n", argv[1]);
		return 2;
	}

	/* Our board dimensions */
	int height;
	int width;

	/* We read out width and height from the file */
	fscanf(input_file, "%d %d", &height, &width);

	/* Create our board instance */
	Board *board = board_init(height, width);

	/* Leemos el resto del archivo fila por fila */
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			/* El grado de la celda actual */
			int degree;
			/* We read the degree of the cell */
			fscanf(input_file, "%d", &degree);
			/* We set the degree of the board */
			board_set_degree(board, row, col, degree);
		}
	}

	bfs(board);  
	return 0;
}
