#include <stdio.h>
#include <stdlib.h>
#include "board.h"

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

	board_print_degree(board);
	State *state_1 = board_get_state(board);
	board_shoot(board, 2, 1);
	board_shoot(board, 1, 1);
	board_shoot(board, 2, 1);
	board_shoot(board, 1, 1);
	
	board_print_degree(board);
	
	board_set_state(board, state_1);
	
	board_print_degree(board);
	board_print_asteroids(board);
	return 0;
}
