#include <iostream>
#include <cstring>
#include <locale>
using namespace std;
void letterChanger(wstring inputText)
{
    wstring text = inputText, letter, changeLetter, newText;
    wcout << L"Değiştirilecek Harfi gir: ";
    wcin >> letter;
    wcout << L"Harfin alacağı yeni değer: ";
    wcin >> changeLetter;

    for (int i = 0; i < text.length(); i++)
    {
        if (tolower(text.at(i)) == tolower(letter.at(0), locale()))
            text[i] = tolower(changeLetter.at(0), locale());
        else
            text[i] = tolower(text.at(i), locale());
    }
    wcout << text << endl;
    letterChanger(text);
}
int main()
{
    locale::global(locale("tr_TR.UTF-8"));
    wcout.imbue(locale());
    wstring text;
    wcout << "Metni gir: ";
    getline(std::wcin, text);
    letterChanger(text);

    return 0;
}