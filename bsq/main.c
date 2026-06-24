/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:24:20 by fvizcaya          #+#    #+#             */
/*   Updated: 2026/05/16 19:56:26 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#if 1
  #define DEBUG
#endif

#define PRINT_ERR(str, err) fprintf(stderr, "ERROR: %s LINE: %d ERRNO: %d\n", str, __LINE__, err);

/*
ALLOWED FUNCTIONS AND GLOBALS:
malloc, calloc, realloc, free, fopen, fclose,
getline, fscanf, fputs, fprintf, stderr, stdout, stdin, errno
*/

static struct constraints_s {
    size_t height;
	size_t width;
    char empty;
    char obstacle;
    char full;
} limits;

static struct bsq_s {
	size_t size;
	size_t i;
	size_t j;
	char** map_original;
	size_t** map_bsq;
	FILE *fmap;
} bsq;

void copy_line_to_array(const char *src, char *dst, size_t size)
{
	size_t i;

    for (i = 0; i < size; i++) {
		if (src[i] != '\n') {
        	dst[i] = src[i];
		}
    }
	dst[size] = '\0';
}

size_t** map_bsq_malloc(void)
{
	size_t** res;

	res = (size_t**) malloc(limits.height * sizeof(size_t**));
	if (!res) {
		PRINT_ERR("Error. Malloc error.", errno);
		return NULL;
	}
	for(size_t i = 0; i < limits.height; i++) {
		res[i] = (size_t*) malloc(limits.width * sizeof(size_t));
		if (!res[i]) {
			PRINT_ERR("Error. Malloc error.", errno);
			for (size_t j = 0; j < i; j++) {
				free(res[j]);
			}
			free(res);
			return NULL;
		}
	}
	return res;
}

void print_map(char** map)
{
	for (size_t i = 0; i < limits.height; i++) {
		for (size_t j = 0; j < limits.width; j++) {
			fprintf(stdout, "%c", map[i][j]);
		}
		fprintf(stdout, "\n");
	}
}

void free_map(void** map, size_t h)
{
	for (size_t i = 0; i < h; i++) {
			free(map[i]);
		}
	free(map);
}

size_t lower_number(size_t i, size_t j, size_t k)
{
	size_t res;
	
	res = i < j ? i : j;
	res = res < k ? res : k;
	
	return res;
}

void do_bsq(char** map_original, size_t **map_bsq)
{
	for (size_t i = 0; i < limits.height; i++) {
		for (size_t j = 0; j < limits.width; j++) {
			if (i == 0 || j == 0) {
				if (map_original[i][j] == limits.empty) {
					map_bsq[i][j] = 1;
				} else {
					map_bsq[i][j] = 0;
				}
			} else {
				// Minor of [i][j - i], [i - i][j], [i - 1][j - 1]
				// We assign to map_bsq[i][j] minor + 1
				if (map_original[i][j] == limits.obstacle) {
					map_bsq[i][j] = 0;
				}
				else {
					map_bsq[i][j] = lower_number(map_bsq[i][j - 1], map_bsq[i - 1][j], map_bsq[i - 1][j - 1]) + 1;
					if (map_bsq[i][j] > bsq.size) {
						bsq.size = map_bsq[i][j];
						bsq.i = i;
						bsq.j = j;
					}
				}
			}
		}
	}
	for (long i = bsq.i; i > (long)(bsq.i - bsq.size); i--) {
		for (size_t j = bsq.j; j > (bsq.j - bsq.size); j--) {
			bsq.map_original[i][j] = limits.full;
		}
	}
}

int main(int argc, char **argv)
{	
    if (argc != 2) {
        PRINT_ERR("Error. Requieres file path as argument.", errno);
        return 0;
    }
    // Open file
    bsq.fmap = fopen(argv[1], "r");
    if (!bsq.fmap) {
        PRINT_ERR("Error. Could not open file for reading.", errno);
        return 1;
    }
    // Read number, empty, obstacle, full
	// char dummy is for reading last '\n' since we cannot use fseek()
	char dummy;
    if (fscanf(bsq.fmap, "%zu %c %c %c%c", &limits.height, &limits.empty, &limits.obstacle, &limits.full, &dummy) != 5) {
        PRINT_ERR("Error. Could not read constraints from file.", errno);
        fclose(bsq.fmap);
        return 1;
    }
#ifdef DEBUG
    printf("Constraints: %zu %c %c %c\n", limits.height, limits.empty, limits.obstacle, limits.full);
#endif
    bsq.map_original = (char **) malloc(limits.height * sizeof(char *));
	if (!bsq.map_original) {
		PRINT_ERR("Error. Malloc error.", errno);
		fclose(bsq.fmap);
		return 1;
	}
    char *buffer = NULL;  // For use of getline()
    size_t bufcap = 0, i = 0;
    long len = 0; // For use of getline()
    while ((len = getline(&buffer, &bufcap, bsq.fmap)) != -1 && i < limits.height) {
		if (!limits.width) {
			limits.width = len - 1;
		}
		if (!(bsq.map_original[i] = (char*) malloc(limits.width * sizeof(char) + 1))) {
			PRINT_ERR("Error. Malloc error.", errno);
			fclose(bsq.fmap);
			free_map((void**)bsq.map_original, i - 1);
		}
        copy_line_to_array(buffer, bsq.map_original[i], limits.width);
        i++;
    }
	free(buffer); // We need to free on buffer although it was internally allocated by getline()
    fclose(bsq.fmap);

	#ifdef DEBUG	
	printf("Limits height: %zu\n", limits.height);
	printf("Limits width: %zu\n", limits.width);
	printf("Original map:\n");
	print_map(bsq.map_original);
	#endif
	
	bsq.map_bsq = map_bsq_malloc();
	if (!bsq.map_bsq) {
		PRINT_ERR("Error. Malloc error.", errno);
		// Memory already freed in map_bsq_malloc()
		return 1;
	}
	do_bsq(bsq.map_original, bsq.map_bsq);
	
	#ifdef DEBUG
	fprintf(stdout, "Found square of size %zu at (%zu, %zu)\n", bsq.size, bsq.i, bsq.j);
	printf("BSQ map:\n");
	for (size_t i = 0; i < limits.height; i++) {
    	for(size_t j = 0; j < limits.width; j++) {
            printf("%zu", bsq.map_bsq[i][j]);
        }
        printf("\n");
    }
	#endif
	print_map(bsq.map_original);
	free_map((void**)bsq.map_original, limits.height);
	free_map((void**)bsq.map_bsq, limits.height);

	return 0;
} /* main() */
