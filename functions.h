// Adrian-Valeriu Croitoru, 312CA

#pragma once

#define MAX 255

typedef unsigned char UC;

typedef struct {
	UC **r, **g, **b;
	UC **mat;
	int lin, col;
	int max;
	int tip;
} image;

void swap(int *a, int *b);
int round_fc(double x);
int min(int max, double temp);

void init_poza(image *poza);
void free_memory(image *poza, int mod);
void matrix_copy(image *poza, image *poza2);

void load_op(int *cnt_load, image *poza, char *arg_op,
			 int *free_mode, int *x1, int *y1, int *x2, int *y2);
void save_op(char *save_type, char *save_path, image *poza,
			 int cnt_load, char *arg_op);
void select_op(int cnt_load, char *arg_op, image *poza,
			   int *x1, int *y1, int *x2, int *y2);
void grayscale_op(int cnt_load, image *poza, int x1, int y1, int x2, int y2);
void sepia_op(int cnt_load, image *poza, int x1, int y1, int x2, int y2);
void crop_op(int cnt_load, image *poza, image *poza2,
			 int *x1, int *y1, int *x2, int *y2);
void rotate_op(int cnt_load, char *arg_op, image *poza, image *poza2,
			   int *x1, int *y1, int *x2, int *y2);

int load(char *arg_op, image *poza);
UC **init_matrix_2(int lin, int col, char *arg_op);
UC **init_matrix_3(int lin, int col, char *arg_op, int index);
UC **init_matrix_5(int lin, int col, char *arg_op);
UC **init_matrix_6(int lin, int col, char *arg_op, int index);
int save_binar(image poza, char *save_path);
int save_ascii(image poza, char *save_path);
void grayscale(int x1, int y1, int x2, int y2, image *poza);
void sepia(int x1, int y1, int x2, int y2, image *poza);
void crop(image *poza2, image *poza, int x1, int y1, int x2, int y2);
void rotate_sq_transpose_all(image *poza, int x1, int y1, int x2, int y2);
void rotate_sq_reverse_all(image *poza, int x1, int y1, int y2);
void rotate_sq_all(image *poza, int x1, int y1, int x2, int y2);
void rotate_sq(image *poza, image *poza2, int x1, int y1, int x2, int y2);
void rotate_all(image *poza, image *poza2, int *x1, int *x2, int *y1, int *y2);
void rotate(image *poza, image *poza2, int angle,
			int *x1, int *y1, int *x2, int *y2);
