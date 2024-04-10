// this might be used if compiler gives us warning that fopen is unsafe
//#define _CRT_SECURE_NO_WARNNING
#include <stdio.h> //  mainly used for binary files


const char* NAME = "data.txt";
const int N = 10;

void write_to_file(const char* name)
{
    // w - write to text file; wb - write to binary;
    // r - read text file; rb - read binary;
    // a - append txt file; ab - append binary file
    FILE *f = fopen(name, "wb"); // w - text file; wb - write binary; rb - read binary
    if (!f){
        printf("Couldn't open file");
        return;
    }

    for (int i = 0; i <= N; ++i)
    {
        fwrite(&i, sizeof(int), 1, f); //params - (what, sizeof what, len [!= 1 if its array], file)
    }

    fclose(f);
}

void read_file(const char *name)
{
    FILE* f = fopen(name, "rb");
    if (!f){
        printf("Couldn't open file");
        return;
    }

    int i;
    while (fread(&i, sizeof(int), 1, f)){
        printf("%d ", i);
    }
    fclose(f);
}

void actualization(const char *name)
{
    FILE* f = fopen(name, "rb+"); // + means possibility with writing in
    //    FILE* f = fopen(name, "r+b"); // same as line above; different way to write it
    if (!f){
        printf("Couldn't open file");
        return;
    }

    int i;
    while (fread(&i, sizeof(int), 1, f)){
        if(i % 2 == 0){
            i = i/2; // if number is even we are going to write its half
            // https://en.cppreference.com/w/c/io/fgetpos
//            size_t position = ftell(f); //returns current position of file indicator
            fseek(f,  - (long) sizeof(int), SEEK_CUR); //without long we would make enormous file
            fwrite(&i, sizeof(int), 1, f);
            fseek(f, 0, SEEK_CUR);
        }
    }
}

int main() {
    write_to_file(NAME);
    read_file(NAME);
    printf("\n");
    actualization(NAME);
    read_file(NAME);
    return 0;
}
