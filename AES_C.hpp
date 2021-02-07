#ifndef AES_C_H
#define AES_C_H
#include <string>
#include <bitset>

class AES_C
{
private:
	std::string key_AES, plainText, cipherText;
	std::vector<std::string> multInvVect;
	const std::bitset<9> gf256{0b100011011};
	uint8_t S = 0, newS, oldS = 1, quotient, remainder, T = 1, newT, oldT = 0;
public:
	//Constructors
	AES_C();
	AES_C(std::string& keyInput);
	AES_C(std::string& keyInput, std::string& pText, std::string& cText);

	//Methods
	std::vector<std::string> ByteString();
	void Mult_Inverse(std::string& byteHexString);
	void AES_C_Main();
};

#endif //AES_C_H
