#ifndef CRYPTO_FUNCTIONS_H
#define CRYPTO_FUNCTIONS_H
#include <string>

class Crypto_Functions
{
private:
	std::string xorReturnString;
	std::string userValue1, userValue2;
public:
	Crypto_Functions();
	Crypto_Functions(std::string& userInput1);
	Crypto_Functions(std::string& userInput1,std::string& userInput2);
	template <typename T1, typename T2>
	bool equal_size(T1 var1, T2 var2);
	std::string xorHexS(std::string& hexString1, std::string& hexString2);
	void Hex_Check(std::string& hexString);
};



#endif //CRYPTO_FUNCTIONS_H
