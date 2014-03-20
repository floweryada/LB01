#include <iostream>
#include <fstream>
#include "Finish.h"

using namespace std;

int main()
{
    const int n = 20;
    CandidatsList *List = new CandidatsList[n];
    myMenu( List, n);
    delete []List;
    return 0;
}
