#include <iostream>
#include <cstring>
#include <locale>
using namespace std;
string lowLetters = "abc.defg-h_ijlmno*prs?tu,vyz";
string upperLetters = "ABC.DEFG-HI_JKLMNO*RS?TU,VYZ";
void function()
{
    locale::global(locale("tr_TR.UTF-8"));
    wcout.imbue(locale());

    int k = 0;
    wstring message;
    wcin >> message;
    wcin >> k;

    for (int i = 0; i < message.length(); i++)
    {
        wcout << Lchar(int(tolower(message.at(i))) - k);
    }
    wcout << endl;
    function();
}

int main()
{
    locale::global(locale("tr_TR.UTF-8"));
    wcout.imbue(locale());

    function();
    return 0;
}
// using namespace std;
// void letterChanger(wstring inputText)
// {
//     wstring text = inputText, letter, changeLetter, newText;
//     wcout << L"Değiştirilecek Harfi gir: ";
//     wcin >> letter;
//     wcout << L"Harfin alacağı yeni değer: ";
//     wcin >> changeLetter;

//     for (int i = 0; i < text.length(); i++)
//     {
//         if (tolower(text.at(i)) == tolower(letter.at(0), locale()))
//             text[i] = tolower(changeLetter.at(0), locale());
//         else
//             text[i] = tolower(text.at(i), locale());
//     }
//     wcout << text << endl;
//     letterChanger(text);
// }
// int main()
// {

//     wstring text;
//     wcout << "Metni gir: ";
//     getline(std::wcin, text);
//     letterChanger(text);

//     return 0;
// }