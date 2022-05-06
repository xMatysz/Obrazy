#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "biblioteka.h"

void Progowanie(int prog, struct OBRAZ* str)
{
	int i, j;

	str->skala = 1;

	for (j = 0; j < str->y; j++)
		for (i = 0; i < str->x; i++) {

			if (str->pixel[j][i] > prog)
				str->pixel[j][i] = 1;
			else
				str->pixel[j][i] = 0;
		}
}
void Negatyw(struct OBRAZ* str)
{
	int i, j;

	for (j = 0; j < str->y; j++)
		for (i = 0; i < str->x; i++)
			str->pixel[j][i] = str->skala - str->pixel[j][i];
}

void Kontrast(int prog, struct OBRAZ* str)
{
	int i, j, temp = str->skala / 2;

	for (j = 0; j < str->y; j++)
		for (i = 0; i < str->x; i++) {

			if (str->pixel[j][i] > temp) {

				str->pixel[j][i] += prog;
				if (str->pixel[j][i] > str->skala)
					str->pixel[j][i] = str->skala;
			}

			else {

				str->pixel[j][i] -= prog;
				if (str->pixel[j][i] < 0)
					str->pixel[j][i] = 0;
			}
		}
}

void Jasnosc(int prog, struct OBRAZ* str)
{
	int i, j;
	float temp;

	for (j = 0; j < str->y; j++)
		for (i = 0; i < str->x; i++) {

			temp = (float)prog / 100 + 1;
			(int)ceil(temp *= str->pixel[j][i]);
			str->pixel[j][i] = temp;

			if (str->pixel[j][i] > str->skala)
				str->pixel[j][i] = str->skala;
			if (str->pixel[j][i] < 0)
				str->pixel[j][i] = 0;
		}
}

void Ziarno(int prog, struct OBRAZ* str)
{
	int i, j, random;
	float temp;
	srand(time(NULL));

	for (j = 0; j < str->y; j++)
		for (i = 0; i < str->x; i++) {

			random = (rand() % prog + 1) - (prog / 2);
			temp = (float)random / 100 + 1;
			(int)ceil(temp *= str->pixel[j][i]);
			str->pixel[j][i] = temp;

			if (str->pixel[j][i] > str->skala)
				str->pixel[j][i] = str->skala;
			if (str->pixel[j][i] < 0)
				str->pixel[j][i] = 0;
		}
}
