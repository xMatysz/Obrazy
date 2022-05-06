#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "biblioteka.h"

int main(void)
{
	int nr = 0, prog = 0,i;
	char nazwa[20];
	struct OBRAZ* str = NULL;

	while (1)
	{
		switch (nr)
		{
		case 0:
			printf("1.Generuj gradient kolowy\n2.Wczytaj\n3.Przetwarzaj\n4.Zapisz\n5.Wyjdz\n\nTwoja opcja: ");
			scanf("%d", &nr);

			system("cls");
			break;

		case 1: // Gradient
			do {

				printf("Podaj rozmiar obrazu (mniejszy niz 256,  wiekszy niz 11 i liczbe nieparzysta)\n");
				scanf("%d", &prog);

			} while (prog > 256 || prog < 11 || prog % 2 == 0);
			
			str = Gradient(prog, prog);

			system("cls");
			printf("Utworzono gradient kolowy\n\n");
			nr = 0;
			break;

		case 2: // Odczyt
			printf("Podaj nazwe: ");
			scanf("%s", &nazwa);

			if (wczytaj(nazwa) == NULL)
			{
				system("cls");
				printf("Plik nie istnieje\n");

				nr = 0;
				break;
			}
			else
			{
				system("cls");
				str = wczytaj(nazwa);

				printf("Plik: %s wczytano pomyslnie.\n\n", nazwa);
				nr = 0;
				break;
			}

		case 3: // Przetwarzanie
			if (str == NULL)
			{
				system("cls");
				printf("Brak wczytanej grafiki\n\n");

				nr = 0;
				break;
			}
			else
			{
				printf("Co chcesz przetworzyc?\n\n1.Kolor\n2.Geometria\n3.Filtry\n4.Wroc do menu\n\nTwoja opcja: ");
				scanf("%d", &nr);

				nr += 30;
				system("cls");
				break;
			}

		case 31: // Przetwarzanie kolorow
			printf("Co chcesz zrobic?\n\n1.Progowanie\n2.Negatyw\n3.Kontrast\n4.Jasnosc\n5.Sol i pieprz\n6.Powrot\n\nTwoja opcja: ");
			scanf("%d", &nr);

			nr += 310;
			system("cls");
			break;

		case 311: // Progowanie
			printf("Podaj prog: ");
			scanf("%d", &prog);

			Progowanie(prog, str);

			system("cls");
			printf("Obraz poddano progowaniu.\n\n");
			nr = 0;
			break;

		case 312: // Negatyw
			Negatyw(str);

			system("cls");
			printf("Nalozono negatyw.\n\n");
			nr = 0;
			break;

		case 313: // Kontrast
			printf("Podaj prog: ");
			scanf("%d", &prog);

			Kontrast(prog, str);

			system("cls");
			printf("Nalozono kontrasto.\n\n");
			nr = 0;
			break;

		case 314: // Jasnosc
			printf("Podaj o ile %c zmienic jasnosc: ",37);
			scanf("%d", &prog);

			Jasnosc(prog, str);

			system("cls");
			printf("Obraz poddano zmianie jasnosci.\n\n");
			nr = 0;
			break;

		case 315: //Ziarno 
			printf("Podaj z jaka moca %c nadac ziarno: ",37);
			scanf("%d", &prog);

			Ziarno(prog, str);

			system("cls");
			printf("Nalozono ziarno.\n\n");
			nr = 0;
			break;

		case 316: // Powrot
			system("cls");
			nr = 3;
			break;

		case 32: // Przetwarzanie geometrii
			printf("Co chcesz zrobic?\n\n1.Odbicie lustrzane\n2.Rotacja\n3.Zoom\n4.Powrot\n\nTwoja opcja: ");
			scanf("%d", &nr);

			nr += 320;
			system("cls");
			break;

		case 321: // Odbicie lustrzane
			printf("1. Os X\n2. Os Y\n\nPodaj w jakiej osi odbic: ");
			do {

				scanf("%d", &prog);
			} while (prog != 1 && prog != 2);

			Lustro(prog, str);

			system("cls");
			printf("Odbito lustrzanie.\n\n");
			nr = 0;
			break;

		case 322: // Rotacja
			printf("1. 90%c\n2. 180%c\n3. 270%c\n\nPodaj o ile stopni wykonac obrot: ", 248, 248, 248);
			do {

				scanf("%d", &prog);
			} while (prog != 1 && prog != 2 && prog != 3);

			nr += 3220;
			system("cls");
			break;

		case 3221: // rotacja 90
			str = Rotacja(str);

			system("cls");
			printf("Zrotowano Obraz o 90%c.\n\n", 248);
			nr = 0;
			break;

		case 3222: // rotacja 180
			Lustro(1, str);
			Lustro(2, str);

			system("cls");
			printf("Zrotowano Obraz o 180%c.\n\n", 248);
			nr = 0;
			break;

		case 3223: // rotacja 270
			str = Rotacja(str);
			Lustro(1, str);
			Lustro(2, str);

			system("cls");
			printf("Zrotowano Obraz o 270%c.\n\n", 248);
			nr = 0;
			break;
			
		case 323: // zoom
			printf("Podaj ilokrotnie ma sie powiekszyc obraz(1 = x2, 2 = x4, itd): ");
			scanf("%d", &prog);

			for ( i = 0; i < prog; i++)
				str = powieksz(str);

			system("cls");
			printf("Powiekszono\n\n");
			nr = 0;
			break;

		case 324: // Powrót
			system("cls");
			nr = 3;
			break;

		case 33: // Przetwarzanie filtrow
			printf("Jaki filtr zastosowac?\n\n1.Dolnoprzepustowy\n2.Gornoprzepustowy\n3.Przesuwania i odejmowania\n4.Gradientowy kierunkowy\n5.Wypoklajacy\n6.Laplace'a\n7.Konturowy\n\nTwoj wybor: ");
			scanf("%d", &nr);
			
			nr += 330;
			system("cls");
			break;

		case 331:
			printf("Filtr usredniajacy (n01)\n");
			printf("Filtr kwadratowy (n02)\n");
			printf("Filtr kolowy (n03)\n");
			printf("Filtr LP1 (n04)\n");
			printf("Filtr LP2 (n05)\n");
			printf("Filtr LP3 (n06)\n");
			printf("Filtr Piramidalny (n07)\n");
			printf("Filtr Stozkowy (n08)\n");
			printf("Filtr Gauss 1 (n09)\n");
			printf("Filtr Gauss 2 (n10)\n");
			printf("Filtr Gauss 3 (n11)\n");
			printf("Filtr Gauss 4 (n12)\n");
			printf("Filtr Gauss 5 (n13)\n\n");
			scanf("%s", &nazwa);

			str = odczyt_fitr(str, nazwa);
			system("cls");
			printf("Nalozono filtr\n\n");
			nr = 0;
			break;

		case 332:
			printf("Filtr usun srednia (n14)\n");
			printf("Filtr HP1 (n15)\n");
			printf("Filtr HP2 (n16)\n");
			printf("Filtr HP3 (n17)\n\n");
			scanf("%s", &nazwa);

			str = odczyt_fitr(str, nazwa);
			system("cls");
			printf("Nalozono filtr\n\n");
			nr = 0;
			break;

		case 333:
			printf("Filtr poziomy (n18)\n");
			printf("Filtr pionowy (n19)\n");
			printf("Filtr ukosny L (n20)\n");
			printf("Filtr ukosny P (n21)\n\n");
			scanf("%s", &nazwa);

			str = odczyt_fitr(str, nazwa);
			system("cls");
			printf("Nalozono filtr\n\n");
			nr = 0;
			break;

		case 334:
			printf("Filtr wschod (n22)\n");
			printf("Filtr poludniowy-wschod (n23)\n");
			printf("Filtr poludnie (n24)\n");
			printf("Filtr poludniowy-zachod (n25)\n");
			printf("Filtr zachod (n26)\n");
			printf("Filtr polnocny-zachod (n27)\n");
			printf("Filtr polnoc (n28)\n");
			printf("Filtr polnocny-wschod (n29)\n\n");
			scanf("%s", &nazwa);

			str = odczyt_fitr(str, nazwa);
			system("cls");
			printf("Nalozono filtr\n\n");
			nr = 0;
			break;

		case 335:
			printf("Filtr wschod (n30)\n");
			printf("Filtr poludniowy-wschod (n31)\n");
			printf("Filtr poludnie (n32)\n");
			printf("Filtr poludniowy-zachod (n33)\n");
			printf("Filtr zachod (n34)\n");
			printf("Filtr polnocny-zachod (n35)\n");
			printf("Filtr polnoc (n36)\n");
			printf("Filtr polnocny-wschod (n37)\n\n");
			scanf("%s", &nazwa);

			str = odczyt_fitr(str, nazwa);
			system("cls");
			printf("Nalozono filtr\n\n");
			nr = 0;
			break;

		case 336:
			printf("Filtr LAPL1 (n38)\n");
			printf("Filtr LAPL2 (n39)\n");
			printf("Filtr LAPL3 (n40)\n");
			printf("Filtr Laplace'a ukosny (n41)\n");
			printf("Filtr Laplace'a poziomy (n42)\n");
			printf("Filtr Laplace'a pionowy (n43)\n");
			scanf("%s", &nazwa);

			str = odczyt_fitr(str, nazwa);
			system("cls");
			printf("Nalozono filtr\n\n");
			nr = 0;
			break;

		case 337:
			printf("Filtr poziomy Sobel'a (n44)\n");
			printf("Filtr pionowy Sobel'a (n45)\n");
			printf("Filtr poziomy Prewitt'a (n45)\n");
			printf("Filtr pionowy Prewitt'a (n45)\n");
			scanf("%s", &nazwa);

			str = odczyt_fitr(str, nazwa);
			system("cls");
			printf("Nalozono filtr\n\n");
			nr = 0;
			break;

		case 338:

			system("cls");
			nr = 33;
			break;

		case 34: // Powrot do menu
			system("cls");
			nr = 0;
			break;

		case 4: // Odczyt
			if (str == NULL)
			{
				system("cls");
				printf("Brak wczytanej grafiki\n\n");

				nr = 0;
				break;
			}
			else
			{
				printf("Podaj nazwe: ");
				scanf("%s", nazwa);

				zapis(str, nazwa);
				system("cls");

				printf("Zapisano pomyslnie, pod nazwa: %s.\n\n", nazwa);
				nr = 0;
				break;
			}

		case 5: // Wyjscie
			exit(1);

		default:
			nr = 0;
			printf("Blad!\n\n");
			break;
		}
	}

}

