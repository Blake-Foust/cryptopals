#ifndef AES_C_H
#define AES_C_H
#include <string>
#include <bitset>

class AES_C
{
private:
	std::string key_AES, plainText, cipherText;
	std::vector<std::string> multInvVect;
	std::vector<std::bitset<9>> multInvTable;
	std::bitset<8> affine_gf28;
	const std::bitset<9> gf256{0b100011011};
	//fixed vector for affine transformation V;
	std::bitset<8> v_gf28{0b11000110};
public:
	//Constructors
	AES_C();
	AES_C(std::string& keyInput);
	AES_C(std::string& keyInput, std::string& pText, std::string& cText);

	//Methods
	std::vector<std::string> ByteString();
	void Affine_Transform();
	std::vector<std::bitset<9>> Mult_Inverse(std::string& byteHexString);
	void AES_C_Main();
};

#endif //AES_C_H
