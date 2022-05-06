#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "biblioteka.h"

void Lustro(int os, struct OBRAZ* str)
{
	int i, j, temp;

	if (os == 1){

		for (j = 0; j < (str->y / 2); j++)
			for (i = 0; i < str->x; i++) {

				temp = str->pixel[(str->y - 1) - j][i];
				str->pixel[(str->y - 1) - j][i] = str->pixel[j][i];
				str->pixel[j][i] = temp;
			}
	}

	else{

		for (j = 0; j < (str->y); j++)
			for (i = 0; i < (str->x / 2); i++) {

				temp = str->pixel[j][(str->x - 1) - i];
				str->pixel[j][(str->x - 1) - i] = str->pixel[j][i];
				str->pixel[j][i] = temp;
			}
	}
}

struct OBRAZ* Rotacja(struct OBRAZ* str) // o 90 stopni
{
	int i, j;
	struct OBRAZ* str2;

	str2 = (struct OBRAZ*)malloc(sizeof(struct OBRAZ));

	str2->x = str->y;
	str2->y = str->x;
	str2->skala = str->skala;

	str2->pixel = (int**)calloc(str2->y, sizeof(int*));

	for (i = 0; i < str2->y; i++)
		str2->pixel[i] = (int*)calloc(str2->x, sizeof(int));

	for (j = 0; j < str2->y; j++)
		for (i = 0; i < str2->x; i++)
			str2->pixel[j][(str2->x - 1) - i] = str->pixel[i][j];

	ZwalnianiePamieci(str);

	return str2;
}

struct OBRAZ* powieksz(struct OBRAZ* str)
{
	int i, j;
	struct OBRAZ* str2;
	int* tab;

	tab = (int*)malloc(4 * sizeof(int));

	str2 = (struct OBRAZ*)malloc(sizeof(struct OBRAZ));

	str2->x = (str->x * 2);
	str2->y = (str->y * 2);
	str2->skala = str->skala;

	str2->pixel = (int**)calloc(str2->y, sizeof(int*));

	for (i = 0; i < str2->y; i++)
		str2->pixel[i] = (int*)calloc(str2->x, sizeof(int));

	for (j = 0; j < str->y; j++)
		for (i = 0; i < str->x; i++)
			str2->pixel[j * 2][i * 2] = str->pixel[j][i];

	for (j = 1; j < str2->y; j += 2)
		for (i = 1; i < str2->x; i += 2) {

			if ((i != (str2->x - 1)) && (j != (str2->y - 1))) {

				tab[0] = str2->pixel[j - 1][i - 1];
				tab[1] = str2->pixel[j + 1][i + 1];
				tab[2] = str2->pixel[j - 1][i + 1];
				tab[3] = str2->pixel[j + 1][i - 1];
				str2->pixel[j][i] = sortowanie(tab, 4);
			}

			else if ((i == (str2->x - 1)) && (j == (str2->y - 1))) {

				tab[0] = str2->pixel[j - 2][i];
				tab[1] = str2->pixel[j - 1][i - 1];
				tab[2] = str2->pixel[j][i - 2];
				str2->pixel[j][i] = sortowanie(tab, 3);
			}

			else {

				if (j != (str2->y - 1))
					str2->pixel[j][i] = (str2->pixel[j - 1][i - 1] + str2->pixel[j + 1][i - 1]) / 2;
				else
					str2->pixel[j][i] = (str2->pixel[j - 1][i - 1] + str2->pixel[j - 1][i + 1]) / 2;
			}
		}

	for (j = 0; j < str2->y; j++)
		for (i = 0; i < str2->x; i++) {
			if ((i == 0) && (j % 2 != 0)) {

				if (j != (str2->y - 1)) {

					tab[0] = str2->pixel[j - 1][i];
					tab[1] = str2->pixel[j][i + 1];
					tab[2] = str2->pixel[j + 1][i];
					str2->pixel[j][i] = sortowanie(tab, 3);
				}

				else
					str2->pixel[j][i] = (str2->pixel[j - 1][i] + str2->pixel[j][i + 1]) / 2;
			}

			else if ((j == 0) && (i % 2 != 0)) {

				if (j != (str2->x - 1)) {

					tab[0] = str2->pixel[j][i - 1];
					tab[1] = str2->pixel[j + 1][i];
					tab[2] = str2->pixel[j][i + 1];
					str2->pixel[j][i] = sortowanie(tab, 3);
				}

				else
					str2->pixel[j][i] = (str2->pixel[j][i - 1] + str2->pixel[j + 1][i]) / 2;
			}

			else if ((i == (str2->x - 1)) && (j % 2 == 0)) {

				if (j != 0) {

					tab[0] = str2->pixel[j - 1][i];
					tab[1] = str2->pixel[j][i - 1];
					tab[2] = str2->pixel[j + 1][i];
					str2->pixel[j][i] = sortowanie(tab, 3);
				}
			}

			else if ((j == (str2->y - 1)) && (i % 2 == 0)) {

				if (i != 0) {

					tab[0] = str2->pixel[j][i - 1];
					tab[1] = str2->pixel[j - 1][i];
					tab[2] = str2->pixel[j][i + 1];
					str2->pixel[j][i] = sortowanie(tab, 3);
				}
			}

			else if (j % 2 == 0 && i % 2 != 0 && i != 0 && j != (str2->y - 1) && i != (str2->x - 1)) {

				tab[0] = str2->pixel[j - 1][i];
				tab[1] = str2->pixel[j + 1][i];
				tab[2] = (int)ceil(str2->pixel[j][i - 1] * 0.5);
				tab[3] = (int)ceil(str2->pixel[j][i + 1] * 0.5);
				str2->pixel[j][i] = sortowanie(tab, 4);
			}

			else if (j % 2 != 0 && i % 2 == 0 && j != 0 && i != 0 && j != (str2->y - 1) && i != (str2->x - 1)) {

				tab[0] = str2->pixel[j][i - 1];
				tab[1] = str2->pixel[j][i + 1];
				tab[2] = (int)ceil(str2->pixel[j + 1][i] * 0.5);
				tab[3] = (int)ceil(str2->pixel[j - 1][i] * 0.5);
				str2->pixel[j][i] = sortowanie(tab, 4);
			}
		}
	
	ZwalnianiePamieci(str);

	return str2;
}

int sortowanie(int* tab, int ile) {

	int i, j, temp, mediana;

	for (i = 0; i < ile; i++) {

		temp = tab[i];
		for (j = i + 1; j < ile; j++)
			if (tab[j] < temp) {

				temp = tab[j];
				tab[j] = tab[i];
				tab[i] = temp;
			}
	}

	if (ile % 2 == 0)
		mediana = (int)ceil((tab[1] + tab[2]) / 2);
	else
		mediana = tab[1];

	return mediana;
}