// Adrian-Valeriu Croitoru, 312CA

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

void swap(int *a, int *b)
{
	if (*a > *b) {
		int aux = *a;
		*a = *b;
		*b = aux;
	}
}

UC **init_matrix_2(int lin, int col, char *arg_op)
{
	FILE *fptr2;
	fptr2 = fopen(arg_op, "r");
	if (!fptr2)
		printf("EROARE\n");

	char c[MAX];
	fgets(c, MAX, fptr2);
	fgets(c, MAX, fptr2);
	fgets(c, MAX, fptr2);

	UC **mat = NULL;
	mat = (UC **)malloc(lin * sizeof(UC *));
	if (!mat) {
		free(mat);
		exit(1);
	}

	for (int i = 0; i < lin; i++) {
		mat[i] = (UC *)malloc(col * sizeof(UC));
		if (!mat[i]) {
			free(mat[i]);
			exit(1);
		}

		for (int j = 0; j < col; j++)
			fscanf(fptr2, "%hhd", &mat[i][j]);
	}

	fclose(fptr2);

	return mat;
}

UC **init_matrix_3(int lin, int col, char *arg_op, int index)
{
	UC temp;
	FILE *fptr3;
	fptr3 = fopen(arg_op, "r");
	if (!fptr3)
		printf("EROARE\n");

	rewind(fptr3);

	char c[MAX];
	fgets(c, MAX, fptr3);
	fgets(c, MAX, fptr3);
	fgets(c, MAX, fptr3);

	UC **mat = NULL;
	mat = (UC **)malloc(lin * sizeof(UC *));
	if (!mat) {
		free(mat);
		exit(1);
	}

	for (int i = 0; i < lin; i++) {
		mat[i] = (UC *)malloc((col) * sizeof(UC));
		if (!mat[i]) {
			free(mat[i]);
			exit(1);
		}

		int cnt = 0;
		for (int j = 0; j < 3 * col; j++) {
			cnt++;
			fscanf(fptr3, "%hhu", &temp);
			if (cnt % 3 == index && index != 3)
				mat[i][cnt / 3] = temp;
			else if (cnt % 3 == 0 && index == 3)
				mat[i][cnt / 3 - 1] = temp;
		}
	}

	fclose(fptr3);

	return mat;
}

UC **init_matrix_5(int lin, int col, char *arg_op)
{
	FILE *fptr5;
	fptr5 = fopen(arg_op, "r");
	if (!fptr5)
		printf("EROARE\n");

	char c[MAX];
	fgets(c, MAX, fptr5);
	fgets(c, MAX, fptr5);
	fgets(c, MAX, fptr5);

	UC **mat = NULL;
	mat = (UC **)malloc(lin * sizeof(UC *));
	if (!mat) {
		free(mat);
		exit(1);
	}

	for (int i = 0; i < lin; i++) {
		mat[i] = (UC *)malloc(col * sizeof(UC));
		if (!mat[i]) {
			free(mat[i]);
			exit(1);
		}

		for (int j = 0; j < col; j++)
			fread(&mat[i][j], sizeof(UC), 1, fptr5);
	}

	fclose(fptr5);

	return mat;
}

UC **init_matrix_6(int lin, int col, char *arg_op, int index)
{
	UC temp;
	FILE *fptr6;
	fptr6 = fopen(arg_op, "r");
	if (!fptr6)
		printf("EROARE\n");

	rewind(fptr6);

	char c[MAX];
	fgets(c, MAX, fptr6);
	fgets(c, MAX, fptr6);
	fgets(c, MAX, fptr6);

	UC **mat = NULL;
	mat = (UC **)malloc(lin * sizeof(UC *));
	if (!mat) {
		free(mat);
		exit(1);
	}

	for (int i = 0; i < lin; i++) {
		mat[i] = (UC *)malloc((col) * sizeof(UC) + 1);
		if (!mat[i]) {
			free(mat[i]);
			exit(1);
		}

		int cnt = 0;
		for (int j = 0; j < 3 * col; j++) {
			cnt++;
			fread(&temp, sizeof(UC), 1, fptr6);
			if (cnt % 3 == index && index != 3)
				mat[i][cnt / 3] = temp;
			else if (cnt % 3 == 0 && index == 3)
				mat[i][cnt / 3 - 1] = temp;
		}
	}

	fclose(fptr6);

	return mat;
}

int load(char *arg_op, image *poza)
{
	FILE *fptr;
	fptr = fopen(arg_op, "r");
	if (!fptr) {
		poza->tip = 0;
		return 0;
	}

	char temp, c[MAX];
	fscanf(fptr, "%c%d", &temp, &poza->tip);
	fscanf(fptr, "%[^\n]", c);
	fscanf(fptr, "%d %d", &poza->col, &poza->lin);
	fscanf(fptr, "%[^\n]", c);
	fscanf(fptr, "%d", &poza->max);
	fscanf(fptr, "%[^\n]", c);
	fclose(fptr);

	if (poza->tip == 2) {
		poza->mat = init_matrix_2(poza->lin, poza->col, arg_op);
	} else if (poza->tip == 3) {
		poza->r = init_matrix_3(poza->lin, poza->col, arg_op, 1);
		poza->g = init_matrix_3(poza->lin, poza->col, arg_op, 2);
		poza->b = init_matrix_3(poza->lin, poza->col, arg_op, 3);
	} else if (poza->tip == 5) {
		poza->mat = init_matrix_5(poza->lin, poza->col, arg_op);
	} else if (poza->tip == 6) {
		poza->r = init_matrix_6(poza->lin, poza->col, arg_op, 1);
		poza->g = init_matrix_6(poza->lin, poza->col, arg_op, 2);
		poza->b = init_matrix_6(poza->lin, poza->col, arg_op, 3);
	}

	return 1;
}

void free_memory(image *poza, int mod)
{
	for (int i = 0; i < poza->lin; i++) {
		if (mod == 1) {
			free(poza->mat[i]);
		} else if (mod == 2) {
			free(poza->r[i]);
			free(poza->g[i]);
			free(poza->b[i]);
		} else if (mod > 2) {
			free(poza->r[i]);
			free(poza->g[i]);
			free(poza->b[i]);
			free(poza->mat[i]);
		}
	}

	if (mod == 1) {
		free(poza->mat);
	} else if (mod == 2) {
		free(poza->r);
		free(poza->g);
		free(poza->b);
	} else if (mod > 2) {
		free(poza->r);
		free(poza->g);
		free(poza->b);
		free(poza->mat);
	}
}

int save_binar(image poza, char *save_path)
{
	FILE *fptr_save_bin;
	fptr_save_bin = fopen(save_path, "wb");
	if (!fptr_save_bin)
		return 0;

	if (poza.tip == 2)
		poza.tip = 5;
	if (poza.tip == 3)
		poza.tip = 6;

	fprintf(fptr_save_bin, "P%d\n", poza.tip);
	fprintf(fptr_save_bin, "%d %d\n", poza.col, poza.lin);
	fprintf(fptr_save_bin, "%d\n", poza.max);

	if (poza.tip == 5) {
		for (int i = 0; i < poza.lin; i++)
			for (int j = 0; j < poza.col; j++)
				fwrite(&poza.mat[i][j], sizeof(UC), 1, fptr_save_bin);
	} else if (poza.tip == 6) {
		for (int i = 0; i < poza.lin; i++) {
			for (int j = 0; j < poza.col; j++) {
				fwrite(&poza.r[i][j], sizeof(UC), 1, fptr_save_bin);
				fwrite(&poza.g[i][j], sizeof(UC), 1, fptr_save_bin);
				fwrite(&poza.b[i][j], sizeof(UC), 1, fptr_save_bin);
			}
		}
	}
	fclose(fptr_save_bin);

	return 0;
}

int save_ascii(image poza, char *save_path)
{
	FILE *fptr_save_asc;
	fptr_save_asc = fopen(save_path, "w");
	if (!fptr_save_asc)
		return 0;

	if (poza.tip == 5)
		poza.tip = 2;
	if (poza.tip == 6)
		poza.tip = 3;

	fprintf(fptr_save_asc, "P%d\n", poza.tip);
	fprintf(fptr_save_asc, "%d %d\n", poza.col, poza.lin);
	fprintf(fptr_save_asc, "%d\n", poza.max);

	if (poza.tip == 2) {
		for (int i = 0; i < poza.lin; i++) {
			for (int j = 0; j < poza.col; j++)
				fprintf(fptr_save_asc, "%d ", poza.mat[i][j]);
			fprintf(fptr_save_asc, "\n");
		}
	} else if (poza.tip == 3) {
		for (int i = 0; i < poza.lin; i++) {
			for (int j = 0; j < poza.col; j++)
				fprintf(fptr_save_asc, "%d %d %d ",
						poza.r[i][j], poza.g[i][j], poza.b[i][j]);
			fprintf(fptr_save_asc, "\n");
		}
	}

	fclose(fptr_save_asc);

	return 0;
}

void init_poza(image *poza)
{
	poza->mat = NULL;
	poza->r = NULL;
	poza->g = NULL;
	poza->b = NULL;
}

int round_fc(double x)
{
	if (x - (int)x >= 0.5)
		return (int)x + 1;
	return (int)x;
}

void grayscale(int x1, int y1, int x2, int y2, image *poza)
{
	for (int i = y1; i <= y2; i++) {
		for (int j = x1; j <= x2; j++) {
			UC temp_r = poza->r[i][j];
			UC temp_g = poza->g[i][j];
			UC temp_b = poza->b[i][j];
			poza->r[i][j] = round_fc((double)((temp_r + temp_g + temp_b) / 3));
			poza->g[i][j] = round_fc((double)((temp_r + temp_g + temp_b) / 3));
			poza->b[i][j] = round_fc((double)((temp_r + temp_g + temp_b) / 3));
		}
	}
}

int min(int max, double temp)
{
	if (max >= temp)
		return temp;
	return max;
}

void sepia(int x1, int y1, int x2, int y2, image *poza)
{
	for (int i = y1; i <= y2; i++) {
		for (int j = x1; j <= x2; j++) {
			double temp_r = round_fc((double)(0.393 * poza->r[i][j] +
				0.769 * poza->g[i][j] + 0.189 * poza->b[i][j]));
			double temp_g = round_fc((double)(0.349 * poza->r[i][j] +
				0.686 * poza->g[i][j] + 0.168 * poza->b[i][j]));
			double temp_b = round_fc((double)(0.272 * poza->r[i][j] +
				0.534 * poza->g[i][j] + 0.131 * poza->b[i][j]));
			poza->r[i][j] = (UC)min(poza->max, temp_r);
			poza->g[i][j] = (UC)min(poza->max, temp_g);
			poza->b[i][j] = (UC)min(poza->max, temp_b);
		}
	}
}

void matrix_copy(image *poza, image *poza2)
{
	if (poza2->tip == 2 || poza2->tip == 5) {
		poza->mat = (UC **)malloc(poza2->lin * sizeof(UC *));
		if (!poza->mat) {
			free(poza->mat);
			exit(1);
		}

		for (int i = 0; i < poza2->lin; i++) {
			poza->mat[i] = (UC *)malloc(poza2->col * sizeof(UC));
			if (!poza->mat[i]) {
				free(poza->mat[i]);
				exit(1);
			}
		}

		for (int i = 0; i < poza2->lin; i++)
			for (int j = 0; j < poza2->col; j++)
				poza->mat[i][j] = poza2->mat[i][j];
	} else if (poza2->tip == 3 || poza2->tip == 6) {
		poza->r = (UC **)malloc(poza2->lin * sizeof(UC *));
		if (!poza->r) {
			free(poza->r);
			exit(1);
		}

		for (int i = 0; i < poza2->lin; i++) {
			poza->r[i] = (UC *)malloc(poza2->col * sizeof(UC));
			if (!poza->r[i]) {
				free(poza->r[i]);
				exit(1);
			}
		}

		for (int i = 0; i < poza2->lin; i++)
			for (int j = 0; j < poza2->col; j++)
				poza->r[i][j] = poza2->r[i][j];

		poza->g = (UC **)malloc(poza2->lin * sizeof(UC *));
		if (!poza->g) {
			free(poza->g);
			exit(1);
		}

		for (int i = 0; i < poza2->lin; i++) {
			poza->g[i] = (UC *)malloc(poza2->col * sizeof(UC));
			if (!poza->g[i]) {
				free(poza->g[i]);
				exit(1);
			}
		}

		for (int i = 0; i < poza2->lin; i++)
			for (int j = 0; j < poza2->col; j++)
				poza->g[i][j] = poza2->g[i][j];

		poza->b = (UC **)malloc(poza2->lin * sizeof(UC *));
		if (!poza->b) {
			free(poza->b);
			exit(1);
		}

		for (int i = 0; i < poza2->lin; i++) {
			poza->b[i] = (UC *)malloc(poza2->col * sizeof(UC));
			if (!poza->b[i]) {
				free(poza->b[i]);
				exit(1);
			}
		}

		for (int i = 0; i < poza2->lin; i++)
			for (int j = 0; j < poza2->col; j++)
				poza->b[i][j] = poza2->b[i][j];
	}
}

void crop(image *poza2, image *poza, int x1, int y1, int x2, int y2)
{
	init_poza(poza2);
	poza2->tip = poza->tip;
	poza2->lin = y2 - y1 + 1;
	poza2->col = x2 - x1 + 1;
	poza2->max = poza->max;
	if (poza2->tip == 2 || poza2->tip == 5) {
		poza2->mat = (UC **)malloc((y2 - y1 + 1) * sizeof(UC *));
		if (!poza2->mat) {
			free(poza2->mat);
			exit(1);
		}
		for (int i = 0; i < y2 - y1 + 1; i++) {
			poza2->mat[i] = (UC *)malloc((x2 - x1 + 1) * sizeof(UC));
			if (!poza2->mat[i]) {
				free(poza2->mat[i]);
				exit(1);
			}

			for (int j = 0; j < x2 - x1 + 1; j++)
				poza2->mat[i][j] = poza->mat[y1 + i][x1 + j];
		}
		free_memory(poza, 1);
		poza->lin = poza2->lin;
		poza->col = poza2->col;
		matrix_copy(poza, poza2);
		free_memory(poza2, 1);
	} else if (poza2->tip == 3 || poza2->tip == 6) {
		poza2->r = (UC **)malloc((y2 - y1 + 1) * sizeof(UC *));
		if (!poza2->r) {
			free(poza2->r);
			exit(1);
		}
		for (int i = 0; i < y2 - y1 + 1; i++) {
			poza2->r[i] = (UC *)malloc((x2 - x1 + 1) * sizeof(UC));
			if (!poza2->r[i]) {
				free(poza2->r[i]);
				exit(1);
			}
			for (int j = 0; j < x2 - x1 + 1; j++)
				poza2->r[i][j] = poza->r[y1 + i][x1 + j];
		}

		poza2->g = (UC **)malloc((y2 - y1 + 1) * sizeof(UC *));
		if (!poza2->g) {
			free(poza2->g);
			exit(1);
		}
		for (int i = 0; i < y2 - y1 + 1; i++) {
			poza2->g[i] = (UC *)malloc((x2 - x1 + 1) * sizeof(UC));
			if (!poza2->g[i]) {
				free(poza2->g[i]);
				exit(1);
			}
			for (int j = 0; j < x2 - x1 + 1; j++)
				poza2->g[i][j] = poza->g[y1 + i][x1 + j];
		}

		poza2->b = (UC **)malloc((y2 - y1 + 1) * sizeof(UC *));
		if (!poza2->b) {
			free(poza2->b);
			exit(1);
		}
		for (int i = 0; i < y2 - y1 + 1; i++) {
			poza2->b[i] = (UC *)malloc((x2 - x1 + 1) * sizeof(UC));
			if (!poza2->b[i]) {
				free(poza2->b[i]);
				exit(1);
			}
			for (int j = 0; j < x2 - x1 + 1; j++)
				poza2->b[i][j] = poza->b[y1 + i][x1 + j];
		}
		free_memory(poza, 2);
		poza->lin = poza2->lin;
		poza->col = poza2->col;
		matrix_copy(poza, poza2);
		free_memory(poza2, 2);
	}
}

void rotate_sq_transpose_all(image *poza, int x1, int y1, int x2, int y2)
{
	for (int i = y1; i <= y2; i++) {
		for (int j = i - y1 + x1; j <= x2 - x1; j++) {
			if (poza->tip == 2 || poza->tip == 5) {
				UC aux = poza->mat[i][j];
				poza->mat[i][j] = poza->mat[j][i];
				poza->mat[j][i] = aux;
			} else if (poza->tip == 3 || poza->tip == 6) {
				UC aux_r = poza->r[i][j];
				poza->r[i][j] = poza->r[j][i];
				poza->r[j][i] = aux_r;

				UC aux_g = poza->g[i][j];
				poza->g[i][j] = poza->g[j][i];
				poza->g[j][i] = aux_g;

				UC aux_b = poza->b[i][j];
				poza->b[i][j] = poza->b[j][i];
				poza->b[j][i] = aux_b;
			}
		}
	}
}

void rotate_sq_reverse_all(image *poza, int x1, int y1, int y2)
{
	int k;
	for (int i = y1; i <= y2 - y1; i++) {
		k = y2 - y1;
		for (int j = x1; j <= k; j++) {
			if (poza->tip == 2 || poza->tip == 5) {
				UC aux = poza->mat[i][j];
				poza->mat[i][j] = poza->mat[i][k];
				poza->mat[i][k] = aux;
			} else if (poza->tip == 3 || poza->tip == 6) {
				UC aux_r = poza->r[i][j];
				poza->r[i][j] = poza->r[i][k];
				poza->r[i][k] = aux_r;

				UC aux_g = poza->g[i][j];
				poza->g[i][j] = poza->g[i][k];
				poza->g[i][k] = aux_g;

				UC aux_b = poza->b[i][j];
				poza->b[i][j] = poza->b[i][k];
				poza->b[i][k] = aux_b;
			}
			k--;
		}
	}
}

void rotate_sq_all(image *poza, int x1, int y1, int x2, int y2)
{
	rotate_sq_transpose_all(poza, x1, y1, x2, y2);
	rotate_sq_reverse_all(poza, x1, y1, y2);
}

void rotate_sq(image *poza, image *poza2, int x1, int y1, int x2, int y2)
{
	init_poza(poza2);
	poza2->tip = poza->tip;
	poza2->lin = y2 - y1 + 1;
	poza2->col = y2 - y1 + 1;
	poza2->max = poza->max;

	if (poza->tip == 2 || poza->tip == 5) {
		poza2->mat = (UC **)malloc((y2 - y1 + 1) * sizeof(UC *));
		if (!poza2->mat) {
			free(poza2->mat);
			exit(1);
		}
		for (int i = 0; i <= y2 - y1; i++) {
			poza2->mat[i] = (UC *)malloc((y2 - y1 + 1) * sizeof(UC));
			if (!poza2->mat[i]) {
				free(poza2->mat[i]);
				exit(1);
			}
		}
		for (int i = 0; i <= y2 - y1; i++)
			for (int j = 0; j <= x2 - x1; j++)
				poza2->mat[i][j] = poza->mat[i + y1][j + x1];
		rotate_sq_all(poza2, 0, 0, y2 - y1, y2 - y1);
		for (int i = 0; i <= y2 - y1; i++)
			for (int j = 0; j <= x2 - x1; j++)
				poza->mat[i + y1][j + x1] = poza2->mat[i][j];
		free_memory(poza2, 1);
	} else if (poza->tip == 3 || poza->tip == 6) {
		poza2->r = (UC **)malloc((y2 - y1 + 1) * sizeof(UC *));
		if (!poza2->r) {
			free(poza2->r);
			exit(1);
		}
		for (int i = 0; i <= y2 - y1; i++) {
			poza2->r[i] = (UC *)malloc((y2 - y1 + 1) * sizeof(UC));
			if (!poza2->r[i]) {
				free(poza2->r[i]);
				exit(1);
			}
		}
		poza2->g = (UC **)malloc((y2 - y1 + 1) * sizeof(UC *));
		if (!poza2->g) {
			free(poza2->g);
			exit(1);
		}
		for (int i = 0; i <= y2 - y1; i++) {
			poza2->g[i] = (UC *)malloc((y2 - y1 + 1) * sizeof(UC));
			if (!poza2->g[i]) {
				free(poza2->g[i]);
				exit(1);
			}
		}
		poza2->b = (UC **)malloc((y2 - y1 + 1) * sizeof(UC *));
		if (!poza2->b) {
			free(poza2->b);
			exit(1);
		}
		for (int i = 0; i <= y2 - y1; i++) {
			poza2->b[i] = (UC *)malloc((y2 - y1 + 1) * sizeof(UC));
			if (!poza2->b[i]) {
				free(poza2->b[i]);
				exit(1);
			}
		}
		for (int i = 0; i <= y2 - y1; i++)
			for (int j = 0; j <= x2 - x1; j++) {
				poza2->r[i][j] = poza->r[i + y1][j + x1];
				poza2->g[i][j] = poza->g[i + y1][j + x1];
				poza2->b[i][j] = poza->b[i + y1][j + x1];
			}
		rotate_sq_all(poza2, 0, 0, y2 - y1, y2 - y1);
		for (int i = 0; i <= y2 - y1; i++)
			for (int j = 0; j <= x2 - x1; j++) {
				poza->r[i + y1][j + x1] = poza2->r[i][j];
				poza->g[i + y1][j + x1] = poza2->g[i][j];
				poza->b[i + y1][j + x1] = poza2->b[i][j];
			}
		free_memory(poza2, 2);
	}
}

//void rotate_all_2

void rotate_all(image *poza, image *poza2, int *x1, int *x2, int *y1, int *y2)
{
	int maxim = poza->lin, caz = 2;
	if (poza->lin < poza->col)
		caz = 1, maxim = poza->col;
	init_poza(poza2);
	poza2->tip = poza->tip; poza2->max = poza->max;
	poza2->lin = maxim; poza2->col = maxim;
	if (poza2->tip == 2 || poza2->tip == 5) {
		poza2->mat = (UC **)malloc(maxim * sizeof(UC *));
		if (!poza2->mat)
			free(poza2->mat), exit(1);
		for (int i = 0; i < maxim; i++) {
			poza2->mat[i] = (UC *)malloc(maxim * sizeof(UC));
			if (!poza2->mat[i])
				free(poza2->mat[i]), exit(1);
		}
		for (int i = 0; i < poza2->lin; i++) {
			for (int j = 0; j < poza2->col; j++) {
				if (i >= poza->lin || j >= poza->col)
					poza2->mat[i][j] = 0;
				else
					poza2->mat[i][j] = poza->mat[i][j];
			}
		}
		rotate_sq_all(poza2, 0, 0, maxim - 1, maxim - 1);
		free_memory(poza, 1);
		int lin_init = poza->lin, col_init = poza->col;
		poza->lin = poza2->lin; poza->col = poza2->col;
		matrix_copy(poza, poza2);
		free_memory(poza2, 1);
		if (caz == 1)
			crop(poza2, poza, maxim - lin_init, 0, maxim - 1, maxim - 1);
		else if (caz == 2)
			crop(poza2, poza, 0, 0, maxim - 1, col_init - 1);
	} else if (poza2->tip == 3 || poza2->tip == 6) {
		poza2->r = (UC **)malloc(maxim * sizeof(UC *));
		poza2->g = (UC **)malloc(maxim * sizeof(UC *));
		poza2->b = (UC **)malloc(maxim * sizeof(UC *));
		if (!poza2->r)
			free(poza2->r), exit(1);
		if (!poza2->g)
			free(poza2->g), exit(1);
		if (!poza2->b)
			free(poza2->b), exit(1);
		for (int i = 0; i < maxim; i++) {
			poza2->r[i] = (UC *)malloc(maxim * sizeof(UC));
			poza2->g[i] = (UC *)malloc(maxim * sizeof(UC));
			poza2->b[i] = (UC *)malloc(maxim * sizeof(UC));
			if (!poza2->r[i])
				free(poza2->r[i]), exit(1);
			if (!poza2->g[i])
				free(poza2->g[i]), exit(1);
			if (!poza2->b[i])
				free(poza2->b[i]), exit(1);
		}
		for (int i = 0; i < poza2->lin; i++) {
			for (int j = 0; j < poza2->col; j++) {
				if (i >= poza->lin || j >= poza->col) {
					poza2->r[i][j] = 0; poza2->g[i][j] = 0; poza2->b[i][j] = 0;
				} else {
					poza2->r[i][j] = poza->r[i][j];
					poza2->g[i][j] = poza->g[i][j];
					poza2->b[i][j] = poza->b[i][j];
				}
			}
		}
		rotate_sq_all(poza2, 0, 0, maxim - 1, maxim - 1);
		free_memory(poza, 2);
		int lin_init = poza->lin, col_init = poza->col;
		poza->lin = poza2->lin; poza->col = poza2->col;
		matrix_copy(poza, poza2);
		free_memory(poza2, 2);
		if (caz == 1)
			crop(poza2, poza, maxim - lin_init, 0, maxim - 1, maxim - 1);
		else if (caz == 2)
			crop(poza2, poza, 0, 0, maxim - 1, col_init - 1);
	}
	*x1 = 0; *y1 = 0; *x2 = poza->col - 1; *y2 = poza->lin - 1;
}

void rotate(image *poza, image *poza2, int angle,
			int *x1, int *y1, int *x2, int *y2)
{
	if (*y2 - *y1 == *x2 - *x1) {
		if (angle == 360 || angle == 0 || angle == -360) {
			printf("Rotated %d\n", angle);
		} else if (angle == -90 || angle == 270) {
			rotate_sq(poza, poza2, *x1, *y1, *x2, *y2);
			rotate_sq(poza, poza2, *x1, *y1, *x2, *y2);
			rotate_sq(poza, poza2, *x1, *y1, *x2, *y2);
			printf("Rotated %d\n", angle);
		} else if (angle == -180 || angle == 180) {
			rotate_sq(poza, poza2, *x1, *y1, *x2, *y2);
			rotate_sq(poza, poza2, *x1, *y1, *x2, *y2);
			printf("Rotated %d\n", angle);
		} else if (angle == 90 || angle == -270) {
			rotate_sq(poza, poza2, *x1, *y1, *x2, *y2);
			printf("Rotated %d\n", angle);
		} else {
			printf("Unsupported rotation angle\n");
		}
	} else if ((*y2 - *y1 + 1 == poza->lin) && (*x2 - *x1 + 1 == poza->col)) {
		if (angle == 360 || angle == 0 || angle == -360) {
			printf("Rotated %d\n", angle);
		} else if (angle == -90 || angle == 270) {
			rotate_all(poza, poza2, x1, x2, y1, y2);
			rotate_all(poza, poza2, x1, x2, y1, y2);
			rotate_all(poza, poza2, x1, x2, y1, y2);
			printf("Rotated %d\n", angle);
		} else if (angle == -180 || angle == 180) {
			rotate_all(poza, poza2, x1, x2, y1, y2);
			rotate_all(poza, poza2, x1, x2, y1, y2);
			printf("Rotated %d\n", angle);
		} else if (angle == 90 || angle == -270) {
			rotate_all(poza, poza2, x1, x2, y1, y2);
			printf("Rotated %d\n", angle);
		} else {
			printf("Unsupported rotation angle\n");
		}
	} else {
		printf("The selection must be square\n");
	}
}

void load_op(int *cnt_load, image *poza, char *arg_op,
			 int *free_mode, int *x1, int *y1, int *x2, int *y2)
{
	if (*cnt_load >= 1)
		free_memory(poza, *free_mode);

	int load_check = load(arg_op, poza);

	if (poza->tip == 2 || poza->tip == 5)
		*free_mode = 1;
	else if (poza->tip == 3 || poza->tip == 6)
		*free_mode = 2;

	if (load_check == 0) {
		*cnt_load = 0;
		printf("Failed to load %s\n", arg_op);
	} else {
		(*cnt_load)++;
		printf("Loaded %s\n", arg_op);
	}

	*x1 = 0; *y1 = 0; *x2 = poza->col - 1; *y2 = poza->lin - 1;
}

void save_op(char *save_type, char *save_path, image *poza,
			 int cnt_load, char *arg_op)
{
	save_type[0] = '\0';
	if (cnt_load == 0) {
		printf("No image loaded\n");
	} else {
		int ver = sscanf(arg_op, "%s %s", save_path, save_type);
		if (ver == 0) {
			printf("Invalid command\n");
		} else {
			if (strcmp(save_type, "ascii") != 0)
				save_binar(*poza, save_path);
			else
				save_ascii(*poza, save_path);
			printf("Saved %s\n", save_path);
		}
		save_type[0] = '\0';
	}
}

void select_op(int cnt_load, char *arg_op, image *poza,
			   int *x1, int *y1, int *x2, int *y2)
{
	if (cnt_load == 0) {
		printf("No image loaded\n");
	} else {
		if (strcmp(arg_op, "ALL") == 0 || strcmp(arg_op, "ALL ") == 0) {
			*x1 = 0; *y1 = 0; *x2 = poza->col - 1; *y2 = poza->lin - 1;
			printf("Selected ALL\n");
		} else {
			int x1_t = -5, y1_t = -5, x2_t = -5, y2_t = -5;
			int ver;
			ver = sscanf(arg_op, "%d %d %d %d",
						 &x1_t, &y1_t, &x2_t, &y2_t);
			if (ver == 0)
				printf("Invalid command\n");
			if (x1_t > x2_t)
				swap(&x1_t, &x2_t);
			if (y1_t > y2_t)
				swap(&y1_t, &y2_t);
			if (x1_t == -5 || x2_t == -5 || y1_t == -5 || y2_t == -5) {
				printf("Invalid command\n");
			} else {
				if (x1_t < 0 || x1_t > poza->col ||
					y1_t < 0 || y1_t > poza->lin) {
					printf("Invalid set of coordinates\n");
				} else if (x2_t < 0 || x2_t > poza->col ||
					y2_t < 0 || y2_t > poza->lin) {
					printf("Invalid set of coordinates\n");
				} else if (x1_t == x2_t || y1_t == y2_t) {
					printf("Invalid set of coordinates\n");
				} else {
					*x1 = x1_t; *y1 = y1_t; *x2 = x2_t - 1; *y2 = y2_t - 1;
					printf("Selected %d %d %d %d\n",
						   *x1, *y1, (*x2) + 1, (*y2) + 1);
				}
			}
		}
	}
}

void grayscale_op(int cnt_load, image *poza, int x1, int y1, int x2, int y2)
{
	if (cnt_load == 0) {
		printf("No image loaded\n");
	} else {
		if (poza->tip == 2 || poza->tip == 5) {
			printf("Grayscale filter not available\n");
		} else {
			grayscale(x1, y1, x2, y2, poza);
			printf("Grayscale filter applied\n");
		}
	}
}

void sepia_op(int cnt_load, image *poza, int x1, int y1, int x2, int y2)
{
	if (cnt_load == 0) {
		printf("No image loaded\n");
	} else {
		if (poza->tip == 2 || poza->tip == 5) {
			printf("Sepia filter not available\n");
		} else {
			sepia(x1, y1, x2, y2, poza);
			printf("Sepia filter applied\n");
		}
	}
}

void crop_op(int cnt_load, image *poza, image *poza2,
			 int *x1, int *y1, int *x2, int *y2)
{
	if (cnt_load == 0) {
		printf("No image loaded\n");
	} else {
		crop(poza2, poza, *x1, *y1, *x2, *y2);
		*x1 = 0; *y1 = 0; *x2 = poza->col - 1; *y2 = poza->lin - 1;
		printf("Image cropped\n");
	}
}

void rotate_op(int cnt_load, char *arg_op, image *poza, image *poza2,
			   int *x1, int *y1, int *x2, int *y2)
{
	if (cnt_load == 0) {
		printf("No image loaded\n");
	} else {
		int angle, ver;
		ver = sscanf(arg_op, "%d", &angle);
		if (ver == 0)
			printf("Invalid command\n");
		rotate(poza, poza2, angle, x1, y1, x2, y2);
	}
}
