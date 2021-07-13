#include <stdio.h>
#include "mycrypt.h"
//#include libreria dei files

int main(){
    /*
    1 verificare file chiave, file da criptare e file output se esiste, per l'output in caso si crea (qua potrebbe essere carino 
     chiedere se salvare un'altro nuovo oppure sovrascrivere)
    2 dal file chiave si prende la key 
    3 il file di input viene preso a blocchi di key-byte e mandati al metodo di crypt
    4 quello restituito dal metodo di crypt viene mandato in output
    */
   char* key;
   int keylength;
   char* input;
   int inputlength;
   char* output;
   int nblocchi;

   nblocchi = (inputlength/keylength)+1;
   
   

}

/*
Libreria mycript.h

metodo per criptare un blocco utilizzando una chiave,
da ricordare che la key per l'ultimo blocco è più grande del blocco da cryptare
*/