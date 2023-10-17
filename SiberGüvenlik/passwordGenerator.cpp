
#include <iostream>

using namespace std;
const char letters[53] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char ozelKarakter[33] = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
const char numbers[11] = "1234567890";
string generatePassword(int passwordLength = 0)
{
	char password[1000] = "";
	bool includeUpper = false, includeLower = false, includeSpecialCharacter = false, includeNumber = false;
	for (int i = 0; i < passwordLength; i++)
	{
		int randNumber = rand() % 3;
		if (randNumber == 1)
			password[i] = letters[rand() % 51 + 1];
		else if (randNumber == 2)
			password[i] = ozelKarakter[rand() % 31 + 1];
		else
			password[i] = numbers[rand() % 9 + 1];
	}

	for (int i = 0; i < passwordLength; i++)
		for (int j = 0; j < 24; j++)
		{
			if (password[i] == ozelKarakter[j])
				includeSpecialCharacter = true;
			if (isupper(password[i]))
				includeUpper = true;
			if (islower(password[i]))
				includeLower = true;
			if (isdigit(password[i]))
				includeNumber = true;
		}

	if (!includeLower || !includeUpper || !includeSpecialCharacter || !includeNumber)
		return generatePassword(passwordLength);
	else
		return password;
};
void generate()
{
	int passwordLength = 0;
	cout << "\x1B[36mUzunluk belirle(min-4 max-1000):\x1B[35m ";
	cin >> passwordLength;
	if (passwordLength < 4 || passwordLength > 1000)
	{
		cout << "\x1B[31mŞifrenin uzunluğu en az 4 en fazla 1000 olmalıdır!\033[0m" << endl;
		generate();
	}
	string password = generatePassword(passwordLength);
	cout << "\x1B[33mParola Uzunluğu: \x1B[32m" << password.length() << "\033[0m\n"
		 << "\x1B[33mParola: \x1B[31m" << password << "\033[0m" << endl;
	generate();
}
int main()
{
	srand(time(0));
	generate();
	return 0;
}
