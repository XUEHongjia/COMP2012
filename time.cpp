#include <iostream>
#include <ctime>
using namespace std;

int main()
{
    time_t seconds;
    seconds = time(NULL);
    cout << seconds << endl;
    return 0;
}
