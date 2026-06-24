/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 21:41:46 by fvizcaya          #+#    #+#             */
/*   Updated: 2026/06/24 13:25:04 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
Allowed functions: atoi, read, putchar, malloc, calloc, realloc, free
*/

static struct life_s {
		int width;
		int height;
		int iterations;
		int pencil_status;
		int i;
		int j;
		char** board;
		char** board_aux;
		char buffer[4096];
} life;
	
	
size_t ft_strlen(char *str)
{
	size_t i = 0;

	while (str[i]) {
		i++;
	}
	return i;
}

void print_output(char* str)
{
	for (size_t i = 0; i < ft_strlen(str); i++) {
		putchar(str[i]);
	}
}

char **create_array(void)
{
	char **res = (char**) malloc(life.height * sizeof(char*));
	if (!res) {
		return NULL;
	}

	for (int i = 0; i < life.height; i++) {
		res[i] = (char*) malloc(life.width * sizeof(char) + 1);
		if (!res[i]) {
			for (int j = 0; j < i; j++) {
				free(res[i]);
			}
			free(res);
			return NULL;
		}
	}
	return res;
}
void toggle_pencil(void) {
	
	life.pencil_status = !life.pencil_status;
}

void initialize_board(char** array)
{
	for (int i = 0; i < life.height; i++) {
		for (int j = 0; j < life.width; j++) {
			array[i][j] = ' ';
		}
	}
}

void init_game() {
	
	int i = 0;
	
	// Draw at initial position if pen is down
	if (life.pencil_status) {
		life.board[life.i][life.j] = 'O';
	}

	while(life.buffer[i]) {
		switch(life.buffer[i]) {
			case 'w':
				if (life.i > 0) {
					life.i--;
				}
				break;
			case 's':
				if(life.i < life.height - 1) {
					life.i++;
				}
				break;
			case 'a':
				if (life.j > 0) {
					life.j--;
				}
				break;
			case 'd':
				if (life.j < life.width - 1) {
					life.j++;
				}
				break;
			case 'x':
				toggle_pencil();
				break;
		}
		if (life.pencil_status) {
			life.board[life.i][life.j] = 'O';
		}
		i++;
	}
}

int count_neighbors(int i, int j)
{
	int res = 0;
	
	if (i - 1 >= 0 && j - 1 >=0 && life.board[i - 1][j - 1] == 'O') {
		res++;
	}
	if (j - 1 >=0 && life.board[i][j - 1] == 'O') {
		res++;
	}
	if (i + 1 < life.height && j - 1 >=0 && life.board[i + 1][j - 1] == 'O') {
		res++;
	}
	if (i + 1 < life.height && life.board[i + 1][j] == 'O') {
		res++;
	}
	if (i + 1 < life.height && j + 1 < life.width && life.board[i + 1][j + 1] == 'O') {
		res++;
	}
	if (j + 1 < life.width && life.board[i][j + 1] == 'O') {
		res++;
	}
	if (i - 1 >= 0 && j + 1 < life.width && life.board[i - 1][j + 1] == 'O') {
		res++;
	}
	if (i - 1 >= 0 && life.board[i - 1][j] == 'O') {
		res++;
	}
	return res;
}

void play_game(void) {
	
	int neighbors = 0;
	
	for (int i = 0; i < life.height; i++) {
		for (int j = 0; j < life.width; j++) {
			neighbors = count_neighbors(i, j);
			if (life.board[i][j] == 'O') {
				if (neighbors == 2 || neighbors == 3) {
					life.board_aux[i][j] = 'O';
				}
				else {
					life.board_aux[i][j] = ' ';
				}
			}
			else {
				if (neighbors == 3) {
					life.board_aux[i][j] = 'O';
				}
				else {
					life.board_aux[i][j] = ' ';
				}
			}	
		}
	}
}

void print_board(char** array)
{
	for (int i = 0; i < life.height; i++) {
		for (int j = 0; j < life.width; j++) {
			putchar(array[i][j]);
			}
	putchar('\n');
	}
}

int main(int argc, char** argv)
{
	if (argc != 4) {
		print_output("ERROR: required arguments: <width> <height> <iterations>\n");
		return 0;
	}
	
	life.width = atoi(argv[1]);
	life.height = atoi(argv[2]);
	life.iterations = atoi(argv[3]);
	life.pencil_status = 0;
	life.i = 0;
	life.j = 0;

	long num_read = read(0, life.buffer, sizeof(life.buffer));
	life.buffer[num_read] = '\0';

	// (void)num_read;

	life.board = create_array();
	if (!life.board) {
		// Memory was freed in create_array() in case of failure.
		return 1;
	}
	life.board_aux = create_array();
	if (!life.board) {
		// Memory was freed in create_array() in case of failure.
		return 1;
	}

	initialize_board(life.board);
	initialize_board(life.board_aux);
	init_game();
	
	int iteration_counter = 0;
	while (iteration_counter < life.iterations) {
		play_game();
		char** swap;
		swap = life.board;
		life.board = life.board_aux;
		life.board_aux = swap;
		iteration_counter++;
	}
	
	print_board(life.board);

	return 0;
}