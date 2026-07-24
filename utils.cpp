#include "utils.h"

void printCenter(string text)
{
    int width = 80;
    int padding = (width - text.length()) / 2;

    for(int i = 0; i < padding; i++)
        cout << " ";

    cout << text << endl;
}
