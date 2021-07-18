#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "mycrypt.h"

void main(int argc, char* k, char* i, char* o){
    /*
    1 verificare file chiave, file da criptare e file output se esiste, per l'output in caso si crea (qua potrebbe essere carino 
     chiedere se salvare un'altro nuovo oppure sovrascrivere)
    2 dal file chiave si prende la key 
    3 il file di input viene preso a blocchi di key-byte e mandati al metodo di crypt
    4 quello restituito dal metodo di crypt viene mandato in output
    */
    FILE *fpkey;
    long keylength;
    char* key;

    FILE * fpinput;
    long inputlength;
    char* input;

    FILE * fpoutput;
    int nblocchi;

    /* Controllo input */
    if(argc < 3){
        printf("\n[0] Argomenti inseriti sono meno di 3!\n");
        exit(0);
    }
    if(fpkey = fopen(k, "r") == NULL){
        printf("\n[1] Errore Apertura Key File!\n");
        exit(0);
    }
    if(fpinput = fopen(i,"r") == NULL){
        printf("\n[1] Errore Apertura Input File!\n");
        exit(0);
    }
    fpoutput = fopen(o, O_TRUNC|O_CREAT);

    /* Misuro la grandezza del file per la Key e lo alloco in memoria */
    keylength = CalcolaLunghezza(fpkey);
    key = LeggiFile(fpkey, keylength);

    /* Misuro la grandezza del file in input e lo alloco in memoria */
    inputlength = CalcolaLunghezza(fpinput);
    input = LeggiFile(fpinput, inputlength);

    /* Controllo che l'allocazione di key e input sia corretta */
    if( key == NULL || input == NULL){
        printf("\n[2] Errore Lettura Files!\n");
        ChiudiTuttiFiles(fpkey, fpinput, fpoutput);
        free(key);
        free(input);
        exit(1);
    }
    
    /* Utilizzo la funzione Crypt per criptare o decriptare il file in input con la key 
    allo stesso tempo scrivo il risultato con fputs nel file di output */
    int risultato = fputs( Crypt(key, keylength, input, inputlength), fpoutput);

    if(risultato != EOF){
        printf("\n[Ok] Operazione completata!\n");
    }else printf("\n[Error] Operazione non eseguita correttamente :<\n");

    ChiudiTuttiFiles(fpkey, fpinput, fpoutput);
    free(key);
    free(input);
}

void ChiudiTuttiFiles(FILE * key, FILE * input, FILE * output ){
    fclose(key);
    fclose(input);
    fclose(output);
}

char* LeggiFile(FILE* f, int lungfile){
    char* contenuto = calloc(1, lungfile+1);
    if(!contenuto){
        return NULL;
    }
    if( fread(contenuto, lungfile, 1, f =! 1)){
        return NULL;
    }
    /* alternativa per la lettura
    while((ch = fgetc(fpinput)) != EOF){
      *(input+*i) = ch;
      i++;
    }
    */
    return contenuto;
}

int CalcolaLunghezza(FILE* f){
    int lunghezza = 0;
    fseek( f , 0L , SEEK_END);
    lunghezza = ftell( f );
    rewind( f );
    return lunghezza;
}