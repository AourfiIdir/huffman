#include"include/huffman.h"
#define LOOPING(x,l) for(int x=0; x<(l); x++)

typedef struct MapEntry{
    char c;
    int freq;
} MapEntry;


void getFreq(MapEntry map[26], char c, int *index){
    
    if (c == ' ' || c == '\n')
        return;

    for (int i = 0; i < *index; i++){
        if (map[i].c == c){
            map[i].freq++;
            return;
        }
    }

    if (*index < 26) {
        map[*index].c = c;
        map[*index].freq = 1;
        (*index)++;
    }
}

int main() {

    FILE *f = fopen("test.txt","r");
    if (!f){
        perror("cant open the file");
        exit(1);
    }

    int c;
    int index = 0;
    MapEntry buffer[26] = {0};

    while ((c = fgetc(f)) != EOF){
        putchar(c);
        getFreq(buffer, (char)c, &index);
    }

    LOOPING(i, index){
        printf("char %c freq %d\n", buffer[i].c, buffer[i].freq);
    }

    char buffer2[26];
    int fres[26];

    for (int i = 0; i < index; i++){
        buffer2[i] = buffer[i].c;
        fres[i] = buffer[i].freq;
    }

    HuffmanCodes(buffer2, fres, index,"result.txt");

    return 0;
}

