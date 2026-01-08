#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

void cifra(char *caratteri, int k){ //riceve una stringa e una chiave intera k
    int i=0;

    while(caratteri[i]!='\0'){ //'\0' perfche indics la fine di una stringa
        if (caratteri[i]>='A' && caratteri[i]<='Z'){ //il caraattere è una lettera maiuscola?
            
            caratteri[i]=((caratteri[i]- 'A'+k)%26) + 'A'; //cifra il carattere mantenendo la maiuscola

        }
        i ++;
    }
}


void decifra(char *caratteri, int k){
    int i=0;

    while(caratteri[i]!='\0'){ //'\0' perfche indics la fine di una stringa
        if (caratteri[i]>='A' && caratteri[i]<='Z'){ //il caraattere è una lettera maiuscola?
            
            caratteri[i]=((caratteri[i]- 'A'-k+26 )%26) + 'A'; //cifra il carattere mantenendo la maiuscola
            //cambia il 'A'-k+26 per evitare numeri negativi nel modulo
        }
        i ++;
    }
}

//esercizio 2
typedef struct{
    char *testo; //stringa allocata dinamicmìamente
    int lunghezza; //lunghezza stringa senza \'0'

} riga;

riga leggiRiga(FILE *fp, int n){ //n è la lunghezza massima della riga (dal file)
    riga r;
    char *buffer; //apoggio temporaneo per leggere la riga
    int length=0;

    //se non legge nulla exit
    buffer=(char *)malloc((n+1)* sizeof(char));
    if(buffer==NULL){
        exit(1);
    }


    if(fgets(buffer, n+1, fp)== NULL){
        r.testo= NULL;
        r.lunghezza=0;
        free(buffer);
        return r;
    }
    length= strlen(buffer);

    //togliamo il \n
    if(buffer[length -1]=='\n'){
        buffer[length -1]='\0';
        length--;
    }

    //allochiamo memoria per la stringa fi lunghezza scelta
    r.testo=(char *)malloc((length+1)* sizeof(char));
    if(r.testo==NULL){
        exit(1); //da errore se è nullo
    }

 //copiamo testo in riga
    strcpy(r.testo, buffer);
    r.lunghezza=length;

    free(buffer);
    return r;

} 

//main per testare
int main(){

    FILE *fp;
    riga r;
    int k=3;
    char mode= 'd'; //per cifrare

     // 1. controlli iniziali

    // 2. apertura file
    fp=fopen("input.txt", "r");
    if(fp== NULL){
        printf("file non trovato");
        return 1;
    }
    // 3. ciclo di lettura
    while(1){
        r=leggiRiga(fp, 200);

        if(r.testo==NULL){//se non  legge piu esce
            break;
        }
        printf("stringa originale: %s\n", r.testo);
 // 4. cifratura / decifratura
        if (mode== 'd'){
            cifra(r.testo, k);
        }else{
            decifra(r.testo, k);
        }
// 5. stampa

        printf("%s\n", r.testo);

        free(r.testo);
    }
    
    // 6. chiusura
    fclose(fp);

   /* char stringa[]="CIAO MONDO"; //stringa di test
    int k=10; //chiave di test

    printf("stringa originale: %s\n", stringa);

    cifra(stringa, k);
    printf("stringa cifrata: %s\n", stringa);*/


    
    return 0;
}