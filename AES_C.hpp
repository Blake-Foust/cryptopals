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
	std::bitset<8> v_gf28{0b01100011};
	std::vector<int> S_BOX;
	int g_index = 3;
public:
	std::vector<std::string> w;
	//Constructors
	AES_C();
	AES_C(std::string& keyInput, std::string& pText);
	AES_C(std::string& keyInput);
	AES_C(std::string& keyInput, std::string& pText, std::string& cText);

	//Methods
	void WordVector(std::vector<std::string>& keyWordVector);
	std::vector<std::string> PlainByteStringV();
	std::vector<std::string> KeyByteStringV();
	void G();
	void KeyAddition();
	void KeySchedule();
	void Affine_Transform(std::vector<std::bitset<9>>& multInvTable, std::vector<int>& s_BoxVector);
	void Mult_Inverse(std::string& byteHexString, std::vector<std::bitset<9>>& returnVector);
	void Shift_Rows(std::vector<int>& s_BoxVector, std::vector<int>& shift_Rows_V);
	void AES_C_S_BOX();
	void PracticeRun();
};

#endif //AES_C_H
