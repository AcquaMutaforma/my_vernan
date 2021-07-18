char* Crypt(char* key, long keylength, char* input, long inputlength){
    char toreturn[inputlength];
    int navkey = 0; //navigatore della key, da 0 a keyLength
    int navblocchi = 0; //contatore dei blocchi creati da N/K
    for(int i = 0; i < inputlength; i++){

        toreturn[i] = input[i] ^ key[((i+navblocchi)%keylength)];

        if(navkey == keylength){
            navkey = 0;
            navblocchi++;
        }else navkey++;
    }
    return toreturn;
}