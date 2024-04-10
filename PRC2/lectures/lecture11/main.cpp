//this is better for binary

#include "stdio.h"

const char* NAME = "data.txt";

void output()
{
    FILE* f = fopen(NAME, "w");
    if (!f){
        printf("Could not open file\n");
        return;
    }

    for (int i = 50000; i < 50015; ++i){
        fprintf(f, " Number: %5d\n", i);
    }
    fclose(f);
}

void output1()
{
    for (int i = 5; i < 15; ++i)
    {
        fprintf(stdout, " Number %5X\n", i); // small x converts numbers to hex (but outputed letters are in lower_case)
        fprintf(stdout, " Number %5x\n", i);  // X - converts to hex (outputed letters are in upper_case)
    }
}

void output2()
{
    double x = 3.14159265358979323;
    fprintf(stdout, " number %f\n", x);
}

void output3()
{
    // number in scientific notation
    double x = 3.14159265358979323;
    fprintf(stdout, " number %e\n", x);
    fprintf(stdout, " number %E\n", x);
}

void output4()
{
    // G g - chooses between f and e
    double x = 3.14159265358979323;
    fprintf(stdout, " number %g\n", x);
    x = 3.14159265358979323e11;
    fprintf(stdout, " number %g\n", x);
    fprintf(stdout, " number %G\n", x);
    fprintf(stdout, " number %10.9g\n", x); // for precision width. precision
    fprintf(stdout, " number %.2G\n", x); // without width

    // to write percentage
    fprintf(stdout, " number %.2f %%\n", x);
    fprintf(stdout, " number %.1f %%\n", x);
    fprintf(stdout, " number %.0f %%\n", x); // equivalent %.f
}



int main()
{
    output();
    output1();
    output2();
    output3();
    output4();
    return 0;
}
