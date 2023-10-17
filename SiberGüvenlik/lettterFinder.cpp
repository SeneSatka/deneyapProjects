#include <iostream>
#include <cstring>
#include <locale>
using namespace std;
const wstring alfabe = L"abcçdefgğhıijklmnoöprsştuüvyz";

int main()
{
    locale::global(locale("tr_TR.UTF-8"));
    wcout.imbue(locale());
    wstring input;
    getline(std::wcin, input);

    for (int i = 0; i < alfabe.length(); i++)
    {
        int count = 0;
        for (int j = 0; j < input.length(); j++)
            if (alfabe[i] == tolower(input[j]))
                count++;
        if (count != 0)
            wcout << alfabe[i] << " harfinden " << count << " adet var" << endl;
    }

    return 0;
}