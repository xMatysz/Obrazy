#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "biblioteka.h"

struct OBRAZ* Gradient(int szer, int wys)
{
	struct OBRAZ* str;
	int i, j, wyn, szar;
	float odleglosc;
	szar = szer / 2;

	str = (struct OBRAZ*)malloc(sizeof(struct OBRAZ));

	str->x = szer;
	str->y = wys;
	str->skala = szar;

	str->pixel = (int**)calloc(str->y, sizeof(int*));

	for (i = 0; i < str->y; i++)
		str->pixel[i] = (int*)calloc(str->x, sizeof(int));

	for (j = 0; j < str->y; j++)
		for (i = 0; i < str->x; i++) {

			odleglosc = sqrt(pow(((szer / 2) - i), 2) + pow((wys / 2) - j, 2));
			wyn = (int)round(odleglosc);
			wyn = szar - wyn;
			if (wyn < 0)
				wyn = 0;
			str->pixel[j][i] = wyn;
		}
	return str;
}
void ZwalnianiePamieci(struct OBRAZ* str) {

	int i;

	for (i = 0; i < str->y; i++)
		free(str->pixel[i]);

	free(str->pixel);
	free(str);
}

void zapis(struct OBRAZ* do_zapisu, char* nazwa)
{
	FILE* zapis;
	int i, j;

	zapis = fopen(nazwa, "w");

	fprintf(zapis, "%s\n", "P2");
	fprintf(zapis, "%s\n", "# komentarz");
	fprintf(zapis, "%d %d\n", do_zapisu->x, do_zapisu->y);
	fprintf(zapis, "%d\n", do_zapisu->skala);
	for (j = 0; j < do_zapisu->y; j++)
	{
		for (i = 0; i < do_zapisu->x; i++)
			fprintf(zapis, "%d ", do_zapisu->pixel[j][i]);

		fprintf(zapis, "\n");
	}
	fclose(zapis);
	system(nazwa);
}

struct OBRAZ* wczytaj(char* nazwa)
{
	int i, j;
	struct OBRAZ* str;
	char bufor[100];
	FILE* odczyt;

	odczyt = fopen(nazwa, "r");
	if (odczyt == NULL)
		return NULL;

	fgets(bufor, 100, odczyt);
	fgets(bufor, 100, odczyt);

	str = (struct OBRAZ*)malloc(sizeof(struct OBRAZ));

	fscanf(odczyt, "%d%d%d", &str->x, &str->y, &str->skala);

	str->pixel = (int**)calloc(str->y, sizeof(int*));

	for (i = 0; i < str->y; i++)
		str->pixel[i] = (int*)calloc(str->x, sizeof(int));

	for (j = 0; j < str->y; j++)
		for (i = 0; i < str->x; i++)
			fscanf(odczyt, "%d", &str->pixel[j][i]);

	fclose(odczyt);

	return str;
}

struct OBRAZ* odczyt_fitr(struct OBRAZ* str, char *nazwa){

	int i,j,rozmiar = 0, suma_waz = 0, suma_wag = 0, wynik = 0,k,a;
	int* tab = NULL;
	char poszukiwacz[255];
	FILE* odczyt;

	odczyt = fopen("filtry.txt", "r");
	
	while (fscanf(odczyt, "%s", &poszukiwacz)!=EOF){

		if (!strcmp(nazwa, poszukiwacz)){

			fscanf(odczyt, "%d",&rozmiar);
			tab = (int*)malloc((rozmiar*rozmiar) * sizeof(int));

			for (i = 0; i < rozmiar*rozmiar; i++)
				fscanf(odczyt, "%d,", &tab[i]);

			break;
		}
	}
	
	fclose(odczyt);

	struct OBRAZ* str2;

	str2 = (struct OBRAZ*)malloc(sizeof(struct OBRAZ));

	str2->x = str->x - 2*(rozmiar/2);
	str2->y = str->y - 2*(rozmiar/2);
	str2->skala = str->skala;

	str2->pixel = (int**)calloc(str2->y, sizeof(int*));

	for (i = 0; i < str2->y; i++)
		str2->pixel[i] = (int*)calloc(str2->x, sizeof(int));

	for (k = 0; k < (rozmiar*rozmiar); k++)
		suma_wag += tab[k];

	if (suma_wag == 0)
		suma_wag = 1;

	for (j = (rozmiar/2); j < str->y - (rozmiar/2); j++)
		for (i = (rozmiar/2); i < str->x - (rozmiar/2); i++) {

			suma_waz = 0;
			a = 0;

			if (rozmiar == 3) {

				for (k = -1; k <= 1; k++){

					suma_waz += (str->pixel[j+k][i - 1] * tab[a++]);
					suma_waz += (str->pixel[j+k][i] * tab[a++]);
					suma_waz += (str->pixel[j+k][i + 1] * tab[a++]);
				}
			}

			else if (rozmiar == 5) {

				for (k = -2; k <= 2; k++){

					suma_waz += (str->pixel[j + k][i - 2] * tab[a++]);
					suma_waz += (str->pixel[j + k][i - 1] * tab[a++]);
					suma_waz += (str->pixel[j + k][i] * tab[a++]);
					suma_waz += (str->pixel[j + k][i + 1] * tab[a++]);
					suma_waz += (str->pixel[j + k][i + 2] * tab[a++]);
				}
			}

			else if (rozmiar == 7) {

				for (k = -2; k <= 2; k++){

					suma_waz += (str->pixel[j + k][i - 3] * tab[a++]);
					suma_waz += (str->pixel[j + k][i - 2] * tab[a++]);
					suma_waz += (str->pixel[j + k][i - 1] * tab[a++]);
					suma_waz += (str->pixel[j + k][i] * tab[a++]);
					suma_waz += (str->pixel[j + k][i + 1] * tab[a++]);
					suma_waz += (str->pixel[j + k][i + 2] * tab[a++]);
					suma_waz += (str->pixel[j + k][i + 3] * tab[a++]);
				}
			}

			wynik = suma_waz / suma_wag;

			if (wynik > str->skala)
				wynik = str->skala;
			else if (wynik < 0)
				wynik = 0;

			str2->pixel[j-1][i-1] = abs(wynik);
		}
	free(tab);

	return str2;
}
