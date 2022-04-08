#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS //wylaczenie ostrzezen visuala aby nie uzywac scanf

unsigned int iteracje = 0;
unsigned int zamiany = 0;
unsigned int porownania = 0;
unsigned int iteracje2 = 0;
unsigned int porownania2 = 0;
unsigned int zamiany2 = 0;


void rand_num(unsigned int* tab, unsigned int n) //Generowanie liczb pseduolosowych to tablicy
{
	srand(time(0));
	int i;
	for (i = 0; i < n; i++)
	{
		tab[i] = 1 + rand() % 100;

	}
}

	wyswietlanie_tablicy(unsigned int *tab, unsigned int n) // wyswietlenie zawartosci tablicy
	{
		int i;
		for (i = 0; i < n; i++)
		{
			printf("[%d] = %d\n", i, tab[i]);
			
		}
	}


	void sortowanie_babelkowe(unsigned int* tab, unsigned int n) //sortowanie babelkowe
	{
		int i, j, zamiana;

		for (i = 0; i < n; i++)
		{
			iteracje++;

			for (j = 1; j < n - i; j++)
			{ //pêtla wewnêtrzna
				porownania++;
				iteracje++;
				if (tab[j - 1] > tab[j])
				{
					//zamiana miejscami
					zamiana = tab[j - 1];
					tab[j - 1] = tab[j];
					tab[j] = zamiana;
					zamiany++;
				}
			}
		}
	}
	

	void quick_sort(int* tab, int lewy, int prawy)
	{
		int zamiana;
		if (prawy <= lewy) return;
		
			int i = lewy - 1, j = prawy + 1,
			pivot = tab[(lewy + prawy) / 2]; //punkt odniesienia - srodkowy element tablicy
			porownania2++;
		while (1)
		{
			iteracje2++;
			//szukanie elementu wiekszego lub rownego piwot stojacego po prawej stronie wartosci pivot
			while (pivot > tab[++i]);
			iteracje2++;

			//szukam elementu mniejszego lub rownego pivot stojacego po lewej stronie wartosci pivot
			while (pivot < tab[--j]);
			iteracje2++;

			//zamieñ elementy ze soba ktore stoja po niewlasciwej stronie wzgledem elementu pivot
			if (i <= j)
			{
				//funkcja swap zamienia wartosciami tab[i] z tab[j]
				
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
		unsigned int *tab,*tab2,*zerowanie; //deklaracja tablicy
		printf("Podaj ile elementow chcesz umiescic w tablicy tablicy:");
		scanf("%d", &rozmiar);
		tab = (unsigned int*)malloc(sizeof(unsigned int)* rozmiar);
		tab2 = (unsigned int*)malloc(sizeof(unsigned int) * rozmiar);
		
		int wybor;
		rand_num(tab,rozmiar);
		tab2 = tab;
		
		puts("Trwa inicjalizacja progamu... Prosze czekac");
		time_t begin = time(NULL); //zaczecie liczenia czasu
		sortowanie_babelkowe(tab, rozmiar);
		time_t end = time(NULL); //koniec liczenia czasu
		
		time_t begin2 = time(NULL);
		quick_sort(tab2, 0, rozmiar - 1);
		time_t end2 = time(NULL);
		
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
				printf("\nCzas wykonania sortowania babelkowego wynosi: %d sekund\n", (end - begin));
				printf("\nWykonano lacznie %u iteracji\n", iteracje);
				printf("\nWykonano %u zamian liczb\n", zamiany);
				printf("\nWykonano %u porownan liczb\n", porownania);
				break;
			case(2):
				puts("Wybrales sortowanie metoda quicksort!\n");
				printf("\n Czas wykonania quicksort wynosi: %d sekund\n", (end2 - begin2));
				printf("\nWykonano lacznie %u iteracji\n", iteracje2);
				printf("\nWykonano %u zamian liczb\n", zamiany2);
				printf("\nWykonano %u porownan liczb\n", porownania2);

				break;
			case(3):
				puts("Wybrales porownanie obu metod sortowania!\n");
				//wyswietlanie_tablicy(tab2, rozmiar);
				//puts("SPACJA");
				//wyswietlanie_tablicy(tab, rozmiar);
				puts("SORTOWANIE BABELKOWE START");
				if ((end - begin) <= 0)
					printf("\nCzas wykonania sortowania babelkowego wynosi: <1 sekundy\n");
				else
				{
					printf("\nCzas wykonania sortowania babelkowego wynosi: %d sekund\n", (end - begin));
				}
				printf("\nWykonano lacznie %u iteracji\n", iteracje);
				printf("\nWykonano %u zamian liczb\n", zamiany);
				printf("\nWykonano %u porownan liczb\n", porownania);
				puts("\nSORTOWANIE BABELKOWE STOP");
				puts("\nQUICKSORT START");
				if ((end2 - begin2) <= 0)
					printf("\nCzas wykonania quicksort wynosi: <1 sekundy\n");
				else
				{
					printf("\nCzas wykonania quicksort wynosi: %d sekund\n", (end2 - begin2));
				}
			
				printf("\nWykonano lacznie %u iteracji\n", iteracje2);
				printf("\nWykonano %u zamian liczb\n", zamiany2);
				printf("\nWykonano %u porownan liczb\n", porownania2);
				puts("\nQUICKSORT STOP\n");

				//wyswietlanie_tablicy(tab2, rozmiar); //Wlaczyc zeby sprawdzilo czy sortuje

				if ((end2 - begin2) < (end - begin))
				{
					printf("\nW tym wypadku quicksort byl szybszy o %d sekund\n ", (end - begin) - (end2 - begin2));
				}

				else if ((end - begin) < (end2 - begin2))
				{
					printf("\nW tym wypadku quicksort byl szybszy o %d sekund\n ", (end2 - begin2) - (end - begin));
				}

				else
					printf(" \n W tym wypadku czasy quicksort i bubble sort byly mniejsze niz 1 sekunda\n\n");
				

				break;
			default:
				printf("\nMusisz wybrac jedna z 3 opcji: ");
				break;
			}

		} 
		
		//wyswietlanie_tablicy(tab, rozmiar); // tymczasowo wylaczone
		

		
		return 0;
	}