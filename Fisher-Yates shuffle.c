#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 3		//velicina originalnog niza, pozitivan broj
#define M 1000	//koliko puta shufflamo originalni niz
#define NFAKT 6	//RUCNO IZRACUNAJ, N! broj svih mogucih permutacija, velicina niza ponavljanja

void Shuffle(int niz[N]);
int RandInRange(int min, int max);
int Faktorijel(int n);
void GenerirajOriginalniNiz(int niz[N]);
void GenerirajNizPermutacija(int* arr, int start, int end, int nizPerm[NFAKT]);
void IspisiPonavljanja(int nizPon[NFAKT], int nizPerm[NFAKT]);

int main()
{
	srand((unsigned)time(NULL));
	const int nFakt = Faktorijel(N); //iz nekog razloga ne moze biti velicina niza?
	int i, j, k, sum = 0;	

	if (nFakt != NFAKT)
	{
		printf("Krivi iznos faktorijela. Unesi tocan broj i ponovno pokreni program.\n%d! = %d\n\n", N, nFakt);
		return 1;
	}

	int originalniNiz[N] = { 0 };
	GenerirajOriginalniNiz(originalniNiz);
	int shuffleNiz[N] = { 0 };
	GenerirajOriginalniNiz(shuffleNiz);

	int nizPermutacija[NFAKT] = { 0 };
	GenerirajNizPermutacija(originalniNiz, 0, N - 1, nizPermutacija);

	int nizPonavljanja[NFAKT] = { 0 };

	for (i = 0; i < M; i++)
	{
		Shuffle(shuffleNiz);
		for (j = 0; j < N; j++)
		{
			sum += shuffleNiz[j] * pow(10, N - j - 1);
		}
		
		for (k = 0; k < NFAKT; k++)
		{
			if (sum == nizPermutacija[k])
			{
				nizPonavljanja[k] = nizPonavljanja[k] + 1;
				break;
			}
		}
		sum = 0;
		GenerirajOriginalniNiz(shuffleNiz);
	}

	printf("Na niz od %d elementa pozvan je Fisher-Yates shuffle algoritam %d puta.\n", N, M);
	printf("Niz od %d elementa ima %d permutacija.\n\n", N, NFAKT);
	
	IspisiPonavljanja(nizPonavljanja, nizPermutacija);

	return 0;
}

void Shuffle(int niz[N])
{
	int i, j, temp = 0;
	for (i = N - 1; i > 0; i--)
	{
		j = RandInRange(0, i);
		temp = niz[i];
		niz[i] = niz[j];
		niz[j] = temp;
	}
}

int RandInRange(int min, int max)
{
	int broj = 0;
	broj = rand() % (max - min + 1) + min;
	return broj;
}


int Faktorijel(int n)
{
	int i, fakt = 1;

	for (i = 1; i <= n; i++)
		fakt = fakt * i;

	return fakt;
}

void GenerirajOriginalniNiz(int niz[N])
{
	int i = 0;
	for (i = 0; i < N; i++)
	{
		niz[i] = i + 1;
	}
}

void IspisiPonavljanja(int nizPon[NFAKT], int nizPerm[NFAKT])
{
	int i = 0;
	printf("Perm.:\tBroj ponavljanja:\n");

	for (i = 0; i < NFAKT; i++)
		printf("%d\t%d\n", nizPerm[i], nizPon[i]);
}

void swap(int* a, int* b) {
	int t = *a;
	*a = *b;
	*b = t;
}

void GenerirajNizPermutacija(int* arr, int start, int end, int nizPerm[NFAKT])
{
	static int j = 0;
	if (start == end)
	{
		int i, sum = 0;
		for (i = 0; i < end + 1; i++)
		{
			sum += arr[i] * pow(10, end - i);
		}
		nizPerm[j] = sum;
		j++;
		return;
	}
	int i;
	for (i = start;i <= end;i++)
	{
		swap((arr + i), (arr + start));
		GenerirajNizPermutacija(arr, start + 1, end, nizPerm); //fixing one first digit and calling permutation on the rest
		swap((arr + i), (arr + start));
	}
}