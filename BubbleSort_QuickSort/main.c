#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS //wylaczenie ostrzezen visuala aby nie uzywac scanf

unsigned int iteracje = 0; //liczba iteracji sortowania babelkowego
unsigned int zamiany = 0;// liczba zamian sortowania bablkowego
unsigned int porownania = 0;//liczba porownan sortowania babelkowego
unsigned int iteracje2 = 0; //liczba iteracji quicksorta
unsigned int porownania2 = 0; //liczba porownan quicksorta
unsigned int zamiany2 = 0; //liczba zamian quickosorta



void rand_num(unsigned int* tab, unsigned int n) //Generowanie liczb pseduolosowych to tablicy
{
	srand(time(0)); // inicjuje ziarno generatora liczb pseudolosowych aktualnym czasem
	int i; //iterator petli for
	for (i = 0; i < n; i++)
	{
		tab[i] = 1 + rand() % 100000; //generowanie liczby z zakresu 1-100000

	}
}

wyswietlanie_tablicy(unsigned int* tab, unsigned int n) // wyswietlenie zawartosci tablicy
{
	int i; //iterator petli for
	for (i = 0; i < n; i++)
	{
		printf("[%d] = %d\n", i, tab[i]);

	}
}

void sortowanie_babelkowe(unsigned int* tab, unsigned int n) //sortowanie babelkowe
{
	int i, j; //iteratory petli for
	int zamiana; //zmienna pomocnicza sluzaca do zamiany miejsc

	for (i = 0; i < n; i++)
	{
		iteracje++;

		for (j = 1; j < n - i; j++)
		{ //pêtla wewnêtrzna
			porownania++;
			iteracje++;
			if (tab[j - 1] > tab[j])
			{
				//zamiana miejscami sortowanych liczb
				zamiana = tab[j - 1];
				tab[j - 1] = tab[j];
				tab[j] = zamiana;
				zamiany++;
			}
		}
	}
}


void quick_sort(int* tab, int lewy, int prawy) // sortowanie quick sort
{
	int zamiana; //zmienna pomocnicza sluzaca do zamiany miejsc
	if (prawy <= lewy) return;

	int i = lewy - 1, j = prawy + 1,
		pivot = tab[(lewy + prawy) / 2]; //punkt odniesienia - srodkowy element tablicy
	porownania2++; // zwiekszanie licznika liczby porownan - sortowanie quick sort
	while (1) //petla glowna quicksorta
	{
		iteracje2++;

		while (pivot > tab[++i]); //szukanie elementu wiekszego lub rownego piwot stojacego po prawej stronie wartosci pivot
		iteracje2++;


		while (pivot < tab[--j]);//szukanie elementu mniejszego lub rownego pivot stojacego po lewej stronie wartosci pivot
		iteracje2++;


		if (i <= j)//zamieñ elementy ze soba ktore stoja po niewlasciwej stronie wzgledem elementu pivot
		{
			zamiana = tab[j];
			tab[j] = tab[i];
			tab[i] = zamiana;
			zamiany2++;
		}

		else

			break;
	}

	if (j > lewy)
		quick_sort(tab, lewy, j);
	if (i < prawy)
		quick_sort(tab, i, prawy);
}


int main()
{
	unsigned int rozmiar; //deklaracja rozmiaru tablicy
	unsigned int* tab, * tab2; //deklaracja tablicy
	printf("Podaj ile elementow chcesz umiescic w tablicy tablicy:");
	scanf("%d", &rozmiar);
	tab = (unsigned int*)malloc(sizeof(unsigned int) * rozmiar);
	tab2 = (unsigned int*)malloc(sizeof(unsigned int) * rozmiar);

	int wybor; //wybor opcji w menu
	rand_num(tab, rozmiar);
	tab2 = tab;

	puts("Trwa inicjalizacja progamu... Prosze czekac");
	time_t begin = clock(); //zaczecie liczenia czasu dla sortowania babelkowego
	sortowanie_babelkowe(tab, rozmiar);
	time_t end = clock(); //koniec liczenia czasu dla sortowania babelkowego

	time_t begin2 = clock(); //zaczecie liczenia czasu dla sortowania quick sort
	quick_sort(tab2, 0, rozmiar - 1);
	time_t end2 = clock(); //koniec liczenia czasu dla sortowania quick sort
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC; //czas wykonania sortowania babelkowego
	double time_spent2 = (double)(end2 - begin2) / CLOCKS_PER_SEC; //czas wykonania quickosort
	time_spent = time_spent * 1000; // zamiana na milisekundy czasu sortowania babelkowego
	time_spent2 = time_spent2 * 1000; // zamiana na milisekundy czasu quicksort
	while (1) //petla glowna
	{
		puts("Wybierz jakiego sortowania chcesz uzyc");
		puts("1. Sortowanie babelkowe");
		puts("2. Quicksort");
		puts("3. Chce porownac oba");
		scanf("%d", &wybor);


		switch (wybor)
		{

		case(1):
			puts("\nWybrales sortowanie babelkowe!");
			printf("\nCzas wykonania sortowania babelkowego wynosi: %f milisekund\n", time_spent);
			printf("\nWykonano lacznie %u iteracji\n", iteracje);
			printf("\nWykonano %u zamian liczb\n", zamiany);
			printf("\nWykonano %u porownan liczb\n", porownania);

			FILE* plik1; //plik zawierajacy dane wydajnosciowe z sortowania babelkowego
			plik1 = fopen("sortowanie_babelkowe.txt", "w");
			fprintf(plik1, "Iteracje: %d\n", iteracje);
			fprintf(plik1, "Zamiany: %d\n", zamiany);
			fprintf(plik1, "Porownania: %d\n", porownania);
			fprintf(plik1, "Czas %f\n", time_spent);
			fclose(plik1);
			return 0;

			break;
		case(2):
			puts("Wybrales sortowanie metoda quicksort!\n");
			printf("\n Czas wykonania quicksort wynosi: %f milisekund\n", time_spent2);
			printf("\nWykonano lacznie %u iteracji\n", iteracje2);
			printf("\nWykonano %u zamian liczb\n", zamiany2);
			printf("\nWykonano %u porownan liczb\n", porownania2);

			FILE* plik2; //plik zawierajacy dane wydajnosciowe z quicksort
			plik2 = fopen("quicksort.txt", "w");
			fprintf(plik2, "Iteracje %d\n", iteracje);
			fprintf(plik2, "Zamiany %d\n", zamiany);
			fprintf(plik2, "Porownania %d\n", porownania);
			fprintf(plik2, "Czas %f\n", time_spent2);
			fclose(plik2);

			break;
		case(3):
			puts("Wybrales porownanie obu metod sortowania!\n");
			puts("SORTOWANIE BABELKOWE START");
			if ((time_spent) <= 0)
				printf("\nCzas wykonania sortowania babelkowego wynosi: <1 milisekundy\n");
			else
			{
				printf("\nCzas wykonania sortowania babelkowego wynosi: %f milisekund\n", (time_spent));
			}
			printf("\nWykonano lacznie %u iteracji\n", iteracje);
			printf("\nWykonano %u zamian liczb\n", zamiany);
			printf("\nWykonano %u porownan liczb\n", porownania);
			puts("\nSORTOWANIE BABELKOWE STOP");
			puts("\nQUICKSORT START");
			printf("\nCzas wykonania quicksort wynosi: %f milisekund\n", time_spent2);


			printf("\nWykonano lacznie %u iteracji\n", iteracje2);
			printf("\nWykonano %u zamian liczb\n", zamiany2);
			printf("\nWykonano %u porownan liczb\n", porownania2);
			puts("\nQUICKSORT STOP\n");

			FILE* plik3; //plik zawierajacy dane wydajnosciowe z obu sortowan
			plik3 = fopen("obie_metody.txt", "a");
			fprintf(plik3, "\n\nRozmiar tablicy %d\n\n", rozmiar);
			fprintf(plik3, "Sortowanie babelkowe : \n");
			fprintf(plik3, "Iteracje %d\n", iteracje);
			fprintf(plik3, "Zamiany %d\n", zamiany);
			fprintf(plik3, "Porownania %d\n", porownania);
			fprintf(plik3, "Czas %f\n", time_spent);
			fprintf(plik3, " \n");
			fprintf(plik3, "Quick sort : \n");
			fprintf(plik3, "Iteracje %d\n", iteracje2);
			fprintf(plik3, "Zamiany %d\n", zamiany2);
			fprintf(plik3, "Porownania %d\n", porownania2);
			fprintf(plik3, "Czas %f\n", time_spent2);
			fclose(plik3);

			if (time_spent2 < time_spent)
			{
				printf("\nW tym wypadku quicksort byl szybszy o %f milisekund\n ", time_spent - time_spent2);
			}

			else if (time_spent < time_spent2)
			{
				printf("\nW tym wypadku quicksort byl szybszy o %f milisekund\n ", time_spent2 - time_spent);
			}

			else
				printf(" \n W tym wypadku czasy quicksort i bubble sort byly mniejsze niz 1 milisekunda\n\n");


			break;
		default:
			printf("\nMusisz wybrac jedna z 3 opcji: ");
			break;
		}

	}
	/*
	* \author Konrad Sochacki
	* \author Piotr Skuta
	*/
	return 0;
}
