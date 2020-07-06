#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

int main(int argc, char *args[]) 
{
    ofstream outfile("test.txt");

    for (int i = 0; i < 409700; i++)
    {
        outfile << 'a';
    }

    // system("PAUSE");
    getchar();
    outfile << 'b';

    // system("PAUSE");
    getchar();

    return 0;
}