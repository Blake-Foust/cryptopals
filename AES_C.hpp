#ifndef AES_C_H
#define AES_C_H
#include <string>
#include <bitset>
#include <list>

class AES_C
{
private:
	std::vector<uint8_t> round_Constants{0x01,0x02,0x04,0x06,0x08,0x10,0x20,0x40,0x80,0x1b,0x36};
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
	std::list<uint8_t> RCON();
	void Left_Shift(std::vector<std::string>& wordVector);
	void ADD_ROUND_CON(std::vector<int>& s_BoxVector);
	std::vector<std::string> PlainByteStringV();
	std::vector<std::string> KeyByteStringV(std::string& inputVector);
	void G(std::vector<std::string>& wordVector);
	void KeyAddition(std::vector<int>& s_BoxVector, int& index);
	void KeySchedule();
	void Affine_Transform(std::vector<std::bitset<9>>& multInvTable, std::vector<int>& s_BoxVector);
	void Mult_Inverse(std::string& byteHexString, std::vector<std::bitset<9>>& returnVector);
	void Shift_Rows(std::vector<int>& s_BoxVector, std::vector<int>& shift_Rows_V);
	void AES_C_S_BOX();
	void PracticeRun();
};

#endif //AES_C_H
