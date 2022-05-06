#ifndef biblioteka 
#define biblioteka

struct OBRAZ
{
	int x, y, skala;
	int** pixel;
};

struct OBRAZ* Gradient(int, int);
void ZwalnianiePamieci(struct OBRAZ*);
struct OBRAZ* wczytaj(char*);
void zapis(struct OBRAZ*, char*);
void Progowanie(int, struct OBRAZ*);
void Negatyw(struct OBRAZ*);
void Kontrast(int, struct OBRAZ*);
void Jasnosc(int, struct OBRAZ*);
void Ziarno(int, struct OBRAZ*);
void Lustro(int, struct OBRAZ*);
struct OBRAZ* Rotacja(struct OBRAZ*); // o 90 stopni
struct OBRAZ* powieksz(struct OBRAZ*);
int sortowanie(int*, int);
struct OBRAZ* odczyt_fitr(struct OBRAZ*, char*);
#endif
