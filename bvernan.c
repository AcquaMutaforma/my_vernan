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
    FILE *fdkey;
    long keylength;
    char* key;

    FILE * fdinput;
    long inputlength;
    char* input;

    FILE * fdoutput;
    int nblocchi;

    /* Controllo input */
    if(argc < 3){
        printf("\n[0] Argomenti inseriti sono meno di 3!\n");
        exit(0);
    }
    if(fdkey = fopen(k, "r") == NULL){
        printf("\n[1] Errore Apertura Key File!\n");
        exit(0);
    }
    if(fdinput = fopen(i,"r") == NULL){
        printf("\n[1] Errore Apertura Input File!\n");
        exit(0);
    }
    fdoutput = fopen(o, O_TRUNC|O_CREAT);

    /* Misuro la grandezza del file e quindi della Key */
    fseek( fdkey , 0L , SEEK_END);
    keylength = ftell( fdkey );
    rewind( fdkey );

    /* Alloco la memoria della chiave e leggo il key file */
    key = calloc(1, keylength+1);
    if(!key){
        ChiudiTuttiFiles(fdkey, fdinput, fdoutput);
        printf("\n[2] Errore allocazione memoria key!\n");
        exit(0);
    }
    
    if( fread(key, keylength, 1, fdkey =! 1)){
        ChiudiTuttiFiles(fdkey, fdinput, fdoutput);
        printf("\n[3] Errore lettura key file!\n");
        exit(0);
    }

    /* Misuro la grandezza del file input */
    fseek( fdinput , 0L , SEEK_END);
    inputlength = ftell( fdinput );
    rewind( fdinput );

    /* Leggo il file di input e lo alloco in memoria */
    char ch;
    int i = 0;
    input = calloc(1, inputlength+1);
    if(!input){
        ChiudiTuttiFiles(fdkey, fdinput, fdoutput);
        printf("\n[2] Errore allocazione memoria key!\n");
        exit(0);
    }
    while((ch = fgetc(fdinput)) != EOF){    //TODO test se funziona senno copi quello della key, chissa perche lo hai fatto diverso x)
      *(input+*i) = ch;
      i++;
    }

    //TODO chiedere crypt o decrypt
    int risultato = -1;
    if(1){
        risultato = fputs( Crypt(key, keylength, input, inputlength), fdoutput);
    }else{
        risultato = fputs( Decrypt(key, keylength, input, inputlength), fdoutput);
    }
    
    if(risultato){
        printf("\n[Ok] Operazione completata!\n");
    }else{ printf("\n[Error] Operazione non eseguita correttamente :<\n");
    }

    ChiudiTuttiFiles(fdkey, fdinput, fdoutput);
    //free(fdkey);
    //free(fdinput);
    //free(fdoutput);
    free(key);
    free(input);
}

void ChiudiTuttiFiles(FILE * key, FILE * input, FILE * output ){
    fclose(key);
    fclose(input);
    fclose(output);
}