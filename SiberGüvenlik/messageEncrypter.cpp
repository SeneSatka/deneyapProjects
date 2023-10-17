#include <iostream>
#include <cstring>
using namespace std;
const char lowLetters[27] = "abcdefghijklmnopqrstuvwxyz", upLetters[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int main()
{

    // int k = 0;
    char message[1000] = "";
    cin >> message;
    // cin >> k;
    for (int j = 0; j < 26; j++)
    {
        for (int i = 0; i < strlen(message); i++)
        {
            cout << char(int(tolower(message[i])) - j);
        }
    }

    return 0;
}