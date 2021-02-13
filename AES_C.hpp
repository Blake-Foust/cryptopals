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
	std::vector<int> S_BOX, n_S_BOX;
	std::vector<int> shift_Rows_V;
public:
	//Constructors
	AES_C();
	AES_C(std::string& keyInput);
	AES_C(std::string& keyInput, std::string& pText, std::string& cText);

	//Methods
	std::vector<std::string> ByteString();
	void KeyAddition();
	void KeySchedule();
	void Affine_Transform();
	std::vector<std::bitset<9>> Mult_Inverse(std::string& byteHexString);
	void Shift_Rows();
	void AES_C_S_BOX();
};

#endif //AES_C_H
