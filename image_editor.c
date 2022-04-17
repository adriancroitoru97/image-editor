// Adrian-Valeriu Croitoru, 312CA

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

int main(void)
{
	image poza, poza2;
	init_poza(&poza);
	char arg[MAX];
	char save_type[MAX], save_path[MAX];
	int cnt_load = 0;
	int free_mode = 0;
	int x1, y1, x2, y2;

	while (1) {
		fgets(arg, MAX, stdin);
		if (arg[strlen(arg) - 1] == '\n')
			arg[strlen(arg) - 1] = '\0';

		if (strcmp(arg, "EXIT") == 0) {
			if (cnt_load == 0)
				printf("No image loaded\n");
			break;
		}

		char op[MAX];
		char arg_op[MAX];
		int dim = strlen(arg);
		int dim_arg;
		for (int i = 0; i < dim; i++) {
			if (arg[i] == ' ') {
				strcpy(arg_op, arg + i + 1);
				break;
			}
			dim_arg = i;
			op[i] = arg[i];
		}
		op[dim_arg + 1] = '\0';

		if (strcmp(op, "LOAD") == 0)
			load_op(&cnt_load, &poza, arg_op, &free_mode, &x1, &y1, &x2, &y2);
		else if (strcmp(op, "SAVE") == 0)
			save_op(save_type, save_path, &poza, cnt_load, arg_op);
		else if (strcmp(op, "SELECT") == 0)
			select_op(cnt_load, arg_op, &poza, &x1, &y1, &x2, &y2);
		else if (strcmp(op, "GRAYSCALE") == 0)
			grayscale_op(cnt_load, &poza, x1, y1, x2, y2);
		else if (strcmp(op, "SEPIA") == 0)
			sepia_op(cnt_load, &poza, x1, y1, x2, y2);
		else if (strcmp(op, "CROP") == 0)
			crop_op(cnt_load, &poza, &poza2, &x1, &y1, &x2, &y2);
		else if (strcmp(op, "ROTATE") == 0)
			rotate_op(cnt_load, arg_op, &poza, &poza2, &x1, &y1, &x2, &y2);
		else
			printf("Invalid command\n");
	}

	if (cnt_load)
		free_memory(&poza, free_mode);

	return 0;
}
