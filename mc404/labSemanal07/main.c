//#include <stdio.h>

#define MAX_WIDTH 3072

void read(short *height){
    /*
    scanf("%hd", height);
    */
}

void write(int hex){
    /*
    for(int i =0; current[i] != 0 ; i++){
        printf("%08X ", current[i]);
    }
    printf("\n");
    */
}

void print(int *current){
    int i;
    for(i = 0; current[i] != 0 ; i++){
        write(current[i]);
    }
    write('\n');
}

void _start(int args, char **argc){
    short height;
    int current[MAX_WIDTH] = {0};
    int i, j;
    read(&height);
    if(height == 0){
        return;
    }
    current[0] = 1;
    print(current);
    for(i = 1; i <= height; i++){
        for(j = i; j > 0; j--){
            current[j] += current[j-1];
        }
        print(current);
    }
}

