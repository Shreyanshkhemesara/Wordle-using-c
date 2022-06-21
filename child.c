#include<stdio.h>
#include<stdlib.h>
char finalArr[5];
void reset () {
  printf("\033[0m");
}
void print(char a){
    if(a == 'g'){
        printf("\033[0;32m");
    } else if (a == 'y') {
        printf("\033[0;33m");
    } else if (a == 'w' ) {
        printf("\033[0;37m");
    }
}
char present(int k, char s, char w[]) {
    /*  this function return the status of letter in word. */
    // printf("k : %d, w[%d] : %c, s: %c\n", k, k, w[k], s);
    if(w[k] == s) return 'g';
    else{
        for(int i = 0 ; i < 5; i ++) {
            if(s==w[i]){
                if(i==k) {  /* same place => green */
                    return 'g';
                } else {    /* present in the word, but different place */
                    return 'y';
                }
            }
        }
    }
    /* not present in the word at all */
    return 'w';
}

void printColors(){   /* function to print an array */
    for(int i =0; i < 5; i++) {
        print(finalArr[i]);
        printf("[]");
        reset();
    }
    printf("\n");
}
void check() {
    int cnt = 0;
    for(int i = 0 ;  i < 5; i++) {
        if(finalArr[i] == 'g') cnt ++;
    }
    if(cnt == 5) {
        exit(2);
    }
}
//w=grey, g=green, y=yellow
// not there, correct pos, there but not correct pos
void  getColorCode(char* s, char w[]){
    /* This function uses present function mentioned above to check the position and color of a letter and stores it. */
    for(int i=0; i <5; i++) {
        finalArr[i]=present(i, s[i], w);
    }
    printColors();
    check();
}

void checkCorrectness(char *s, FILE* f) {
    /* Getting the word from the check_name.txt file */
    fgetc(f);
    char word[5];
    for(int i = 0 ; i < 5; i++) {
        word[i]=fgetc(f);
    }
    char a[5];
    getColorCode(s, word);
}


int main(int argc, char * argv[]) {
    int day=2;
    FILE * f = fopen("./check_name.txt", "r");
    if (f == NULL) {
        return 0;
    } else {
        do {
            char c = fgetc(f);
            if (feof(f))
                break;
            if(c=='\n'){
                int k = 0;
                int i = 0;
                int m=1;
                while(c != '.' && i < 2) {
                    c=fgetc(f);
                    i++;
                    if(c=='.' ) break;
                    k += m*(int)(c-'0');
                    m=10*m;
                }
                if(k==day) {
                    checkCorrectness(argv[0], f);
                    break;
                }
            }
        } while (1);

    }
    fclose(f);
    exit(0);
}
