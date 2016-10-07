#include<stdio.h>

int main()
{
    int i;
    double sve2, sve3, sve4, S2, S3, S4, N;

    for(i=0; i<100; ++i)
    {
        scanf("%lg", &N);

        //za sve moguce kombinacije mozemo izabrati n+1 liniju i trebaju nam 2 da ogranicimo prostor i tako dim puta ovisno o dimenziji
        //to je n+1 povrh 2 i to na eksponent dim gdje je dim dimenzija
        sve2 = N*(N+1)*N*(N+1)/4;
        sve3 = N*(N+1)*N*(N+1)*N*(N+1)/8;
        sve4 = N*(N+1)*N*(N+1)*N*(N+1)*N*(N+1)/16;

        S2 = (N*(N+1)*(2*N+1))/6;
        S3 = N*N*(N+1)*(N+1)/4;
        S4 = N*(N+1)*(2*N+1)*(3*N*N+3*N-1)/30;

        //ono sto nisu kvadrati to su pravokutnici, analogno u visim dimenzijama
        printf("%lg %lg %lg %lg %lg %lg\n", S2, sve2-S2, S3, sve3-S3, S4 ,sve4-S4);


    }

    return 0;
}
