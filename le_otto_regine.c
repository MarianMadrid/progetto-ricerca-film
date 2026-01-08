#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N 8 // numero di righe
int euristica(int stato[N]){
    return verifica(stato);
}

//funzione per stampare la scacchiera
void stampa(int stato [N]) {
    //ciclo sulle righe da'allato verso il basso
    for (int riga = N; riga >=1; riga--) {
        printf("%d", riga); //stampa numero riga a sinistra

        //ciclo sulle colonne da 0 a 7
        for (int col = 0; col < N; col++ ) {

            //se la regina è IN QUESTA RIGA E COLONNA
            if (stato[col] == riga){
                printf(" Q");
            } else { //else stampa la casella vuota
                if((riga + col) % 2 == 0){
                    printf(" *");

                }else{
                    printf(" -");
                }
                
            }
        }
        printf("\n"); //a fine riga va a capo

        
    }
}

int verifica(int stato [N]){
    int conflitti =0;
    for(int i=0; i<N; i++){
        for (int j=i + 1; j<N; j++){
            //stessa riga
            if(stato[i] == stato[j]){
                conflitti++;
            }
            //stessa diagonale
            else if(abs(i - j)== abs(stato[i] - stato[j])){
                conflitti++;
            }
        }
    }
    return conflitti;

}

void carica(char *nomefile, int stato[N]){
    FILE *fp = fopen(nomefile, "r");
    if (fp == NULL){
        printf("file nn trovato\n");
        return;
    }

    for (int i=0; i<N; i++){
        fscanf (fp, "%d", &stato[i]);
    }
    fclose (fp);
}

// esercizio 2.2
int cerca(int stato[N], char colonna, int nuova_riga){
    int temp[N];
    //copia dello stato
    for (int i=0; i<N; i++){
        temp[i] = stato[i];
    }
    //conversione della collonna lettera in indice
    int col = colonna - 'a';
    //spostamento simulato
    temp[col] = nuova_riga;
    //calcolo euristica
    return verifica (temp);
} 

    


// main per testare
int main() {
    int stato[8] = {4, 3, 2, 5, 4, 3, 2, 3};  // esempio di stato
    
    /** esercizi 1 e 2 
     stampa(stato);  // chiama la funzione

    int conflitti = verifica(stato);


    if (conflitti == 0){
        printf("la scacchiera è una soluzione- conflitti: %d \n", conflitti);
    }else{
        printf("Non è una soluzione. Conflitti: %d\n", conflitti);
    }

    int euristica= conflitti;
    printf("Euristica: %d\n", euristica);

    //carica
    carica("stato.txt", stato);
    stampa(stato);

    int h=cerca(stato, 'g', 7);
    printf("Euristica dopo mossa di simulazione: %d\n", h);**/

    int scelta = -1;

    while (scelta !=0){
        printf("\n-----MENU-----\n");
        printf("1- Stampa scacchiera\n");
        printf("2- verifica soluzione\n");
        printf("3- Calcola euristica con il costo corrente\n");
        printf("4- Carica da file una array a scelta dall'utente\n");
        printf("5- Calcola euristica dopo mossa simulata\n");
        printf("6- essegui mossa e modidica lo stato corrente\n");
        printf("0- Esci\n");
        printf("scelta: ");
        scanf("%d", &scelta);

        switch (scelta){

            case 1:
                stampa(stato);  // chiama la funzione
                break;
            
            case 2:{
                int conflitti = verifica(stato);


                if (conflitti == 0){
                     printf("la scacchiera è una soluzione- conflitti: %d \n", conflitti);
                 }else{
                    printf("Non è una soluzione. Conflitti: %d\n", conflitti);
                }

                    int euristica= conflitti;
                    printf("Euristica: %d\n", euristica);
                    break;
            }

            case 3:{
                int h= euristica(stato);
                printf("Euristica: %d\n", h);
                break;
            }
            case 4:{
                char nomefile[100];
                printf("Nome file:");
                scanf("%s", nomefile);
                carica(nomefile, stato);
                break;
            }
            case 5:{
                char col;
                int riga;
                printf("Inserisci mossa (ex. A8): ");
                scanf(" %c%d", &col, &riga);
                col = tolower(col);

                int h= cerca(stato, col, riga);
                printf("costo dela mossa simulata: %d\n", h);
                break;
            }

            case 6:{
                char col;
                int riga;
                printf("Inserisci mossa (ex. A8): ");
                scanf(" %c%d", &col, &riga);
                col = tolower(col);

                int c= col-'a';
                stato[c]= riga;
                break;

            }
            case 0:
                printf("Uscita in corso...\n");
                break;
            default:
                printf("Scelta non valida. Riprova.\n");



        }
       
    }




    return 0;

}