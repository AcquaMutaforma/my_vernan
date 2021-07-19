//Author: Alessandro Pallotta - 102627
#include <stdlib.h>
#include "mycrypt.h"

char* Crypt(char* key, long keylength, char* input, long inputlength){
    char* toreturn;
    toreturn = calloc(inputlength, sizeof(char));
    int navkey = 0; //navigatore della key, da 0 a keyLength
    int navblocchi = 0; //contatore dei blocchi creati da N/K

    for(int i = 0; i < inputlength; i++){

        toreturn[i] = input[i] ^ key[((navkey+navblocchi)%keylength)];
        if(navkey == (keylength-1)){
            navkey = 0;
            navblocchi++;
        }else navkey++;
    }
    return toreturn;
}