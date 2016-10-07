#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void ispisi_tablicu(int **tablica, int broj_stvari, int max_tezina)
{
    int i, j;
    for(i=0; i<broj_stvari+1; ++i)
    {
        for(j=0; j<max_tezina+1; ++j)
            printf("%d ", tablica[i][j] );
        printf("\n");

    }
}

void ispisi_vektore(int *vrijednosti, int *tezine, int broj_stvari)
{
    int i;
    printf("Tezine: [");
    for(i=0; i<broj_stvari; ++i)
        printf("%d ", tezine[i]);
    printf("]\n");

    printf("Vrijed: [");
    for(i=0; i<broj_stvari; ++i)
        printf("%d ", vrijednosti[i]);
    printf("]\n\n");

}

void ucitaj (int duljina, char *ime_datoteke, int *x, int *y)
{
    int i;
    FILE *file;
    file = fopen(ime_datoteke, "r");
    if(file == NULL)
    	printf("Greska pri otvaranju datoteke %s\n", ime_datoteke);
    for (i=0; i<duljina; ++i)
        fscanf(file, "%d", x+i);
    for (i=0; i<duljina; ++i)
        fscanf(file, "%d", y+i);
    fclose(file);
}


//RJESENJE REKURZIJOM
int nadi_optimalan(int *vrijednosti, int *tezine, int broj_stvari, int max_tezina)
{
    if(broj_stvari == 0 || max_tezina <=0)
        return 0;

    if(tezine[broj_stvari-1] > max_tezina)
        return nadi_optimalan(vrijednosti, tezine, broj_stvari-1, max_tezina);
    else
    {
        int a, b;
        a = nadi_optimalan(vrijednosti, tezine, broj_stvari-1, max_tezina);
        b = nadi_optimalan(vrijednosti, tezine, broj_stvari-1, max_tezina-tezine[broj_stvari-1]) + vrijednosti[broj_stvari-1];
        return ( a > b ) ? a : b;
    }
}

//RJESENJE PUNJENJEM TABLICE
void ispuni_tablicu(int **tablica, int *tezine, int *vrijednosti, int max_tezina, int broj_stvari)
{
    int i, j;
    for(i=0; i<max_tezina+1; ++i)
        tablica[0][i] = 0;

    for(i=1; i<broj_stvari+1; ++i)
        for(j=0; j<max_tezina+1; ++j)
        {
            tablica[i][j] = tablica[i-1][j];
            if(tezine[i-1] <= j && tablica[i][j] < tablica[i-1][j-tezine[i-1]]+vrijednosti[i-1])
                tablica[i][j] = tablica[i-1][j-tezine[i-1]]+vrijednosti[i-1];
        }
}

//RJESENJE PUNJENJEM TABLICE SA SAMO 2 REDA
void ispuni_tablicu_stednja(int **tablica_stednja, int *tezine, int *vrijednosti, int max_tezina, int broj_stvari)
{

    int i, j;
    for(i=0; i<max_tezina+1; ++i)
        tablica_stednja[0][i] = 0;

    for(i=1; i<broj_stvari+1; ++i)
        for(j=0; j<max_tezina+1; ++j)
        {
            tablica_stednja[i%2][j] = tablica_stednja[(i-1)%2][j];
            if(tezine[i-1] <= j && tablica_stednja[i%2][j] < tablica_stednja[(i-1)%2][j-tezine[i-1]]+vrijednosti[i-1])
                tablica_stednja[i%2][j] = tablica_stednja[(i-1)%2][j-tezine[i-1]]+vrijednosti[i-1];
        }
}

int main(void)
{
    int max_tezina, broj_stvari, i, j, *tezine, *vrijednosti, **tablica, **tablica_stednja;
    char ime[50];
    clock_t trajanje_rek, trajanje_din, trajanje_sted;

    printf("Upisi broj stvari\n");
    scanf("%d", &broj_stvari);
    printf("Upisi maksimalnu tezinu\n");
    scanf("%d", &max_tezina);
    printf("Upisi ime datoteke za ucitavanje\nDatoteka mora sadrzati bar 2n intova.\nPrvo se ucitava n tezina, pa n vrijdnosti za te tezine\n");
    scanf("%s", ime);
    printf("\n");

    tezine = (int*)malloc(broj_stvari*sizeof(int));
    vrijednosti = (int*)malloc(broj_stvari*sizeof(int));

    tablica = (int**)malloc((broj_stvari+1)*sizeof(int));
    for(i=0; i<broj_stvari+1; ++i){
	if(tablica == NULL)
		printf("Greska kod alokacije\n");
        tablica[i] = (int*)malloc((max_tezina+1)*sizeof(int));
	if(tablica[i] == NULL)
		printf("Greska kod alokacije mali niz\n");

}

    tablica_stednja = (int**)malloc(2*sizeof(int));
    for(i=0; i<2; ++i)
        tablica_stednja[i] = (int*)malloc((max_tezina+1)*sizeof(int));

    ucitaj(broj_stvari, ime, tezine, vrijednosti);
    ispisi_vektore(vrijednosti, tezine, broj_stvari);

    trajanje_rek = clock();
    printf("Rekurzijom: %d \n", nadi_optimalan(vrijednosti, tezine, broj_stvari, max_tezina) );
    trajanje_rek -= clock();

    trajanje_din = clock();
	printf("nesto");
    ispuni_tablicu(tablica, tezine, vrijednosti, max_tezina, broj_stvari);
    trajanje_din -= clock();
    printf("Tablicom: %d \n", tablica[broj_stvari][max_tezina] );

    trajanje_sted = clock();
    ispuni_tablicu_stednja(tablica_stednja, tezine, vrijednosti, max_tezina, broj_stvari);
    printf("Tablicom sa stednjom: %d \n", tablica_stednja[broj_stvari%2][max_tezina] );
    trajanje_sted -= clock();

    
    //ispisi_tablicu(tablica, broj_stvari, max_tezina);	//ISPISIVANJE TABLICA ZA PROVJERU
    //printf("\n\n");
    //ispisi_tablicu(tablica_stednja, 1, max_tezina);

    printf("\n");
    printf("Racunanje rekurzijom treba  %f   sekundi\n", ((float)-trajanje_rek)/CLOCKS_PER_SEC);
    printf("Racunanje dinamickim programiranjem treba  %f   sekundi\n", ((float)-trajanje_din)/CLOCKS_PER_SEC);
    printf("Racunanje dinamickim programiranjem sa stednjom treba  %f   sekundi\n", ((float)-trajanje_sted)/CLOCKS_PER_SEC);



    free(tezine);
    free(vrijednosti);
    for(i=0;i<broj_stvari+1;++i)
        free(tablica[i]);
    free(tablica);
    for(i=0;i<2;++i)
        free(tablica_stednja[i]);
    free(tablica_stednja);


    return 0;
}
