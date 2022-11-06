#include <iostream>
#include <sstream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <string>
#include <cstddef>
#include <list>
#include "AES_C.hpp"


//Test
//Constructors
AES_C::AES_C(){};

AES_C::AES_C(std::string& pText)
	: plainText(pText){};

AES_C::AES_C(std::string& keyInput, std::string& pText)
	: plainText(pText), key_AES(keyInput){};


AES_C::AES_C(std::string& keyInput, std::string& pText, std::string& cText)
	: key_AES(keyInput), plainText(pText), cipherText(cText){};
//--------------------------------------------------------
//

//Seperates string into vectors of strings, length 2 for plaintext
std::vector<std::string> AES_C::PlainByteStringV()
{
	std::vector<std::string> pTextByteVector;
	std::string byteString;
	for(int i = 0; i < plainText.size(); i+=2)
	{
		byteString = plainText.substr(i,2);
		pTextByteVector.push_back(byteString);
	}
	return pTextByteVector;
};

//Seperates string into vectors of strings, length 2 for keyText
std::vector<std::string> AES_C::KeyByteStringV(std::string& inputVector)
{
	std::vector<std::string> kTextByteVector;
	std::string byteString;
	for(int i = 0; i < inputVector.size(); i += 2)
	{
		byteString = inputVector.substr(i, 2);
		kTextByteVector.push_back(byteString);
	}
	return kTextByteVector;
};
//--------------------------------------------------------

//Left shift vector string once, for G function
std::vector<std::string> AES_C::Left_Shift(std::vector<std::string>& wordVector)
{
	std::string w_buffer = wordVector[g_index];
	std::vector<std::string> leftShiftReturn = wordVector;
	leftShiftReturn[g_index].clear();
	for(int i = 2; i <= 6; i += 2)
	{
		leftShiftReturn[g_index].append(w_buffer.substr(i,2));
	}
	leftShiftReturn[g_index].append(w_buffer.substr(0,2));
	return leftShiftReturn;
};

//Function G for KeySchedule, 
//LEFT SHIFT
//Mult_Inverse for S_Box
//Affine_Transform for S_Box
//Key_Addition
std::vector<int> AES_C::G(std::vector<std::string>& wordVector)
{
	std::cout << "KeySchedule \n";
	//std::string w_buffer = wordVector[g_index];
	std::vector<std::bitset<9>> vectorGBuffer;
	std::vector<std::string> stringVector;
	std::vector<int> s_BoxVector;
	std::vector<std::string> lsVectString;

	//SHIFT ROW-------------
	lsVectString = Left_Shift(wordVector);
	//wordVector[g_index].append(w_buffer.substr(0,2));
	//----------------------
	std::cout << lsVectString[g_index] << std::endl;
	stringVector = KeyByteStringV(lsVectString[g_index]);
	int count = 0;
	for(auto& x : stringVector)
	{
		Mult_Inverse(x,vectorGBuffer);
	}
	Affine_Transform(vectorGBuffer, s_BoxVector);
	/*for(int i = 0; i < s_BoxVector.size(); ++i)
	{
		std::cout << s_BoxVector[i] << std::endl;
	}*/
	KeyAddition(s_BoxVector, index);
	index++;
	g_index += 4;
	return s_BoxVector;
};

//add round key constant
void AES_C::KeyAddition(std::vector<int>& s_BoxVector,int& index)
{
	std::vector<int> sboxBuffer = s_BoxVector;
	uint8_t xorValue = round_Constants[index] ^ sboxBuffer[0];
	s_BoxVector.clear();
	s_BoxVector.push_back(xorValue);
	for(int i = 1; i < sboxBuffer.size(); ++i)
	{
		s_BoxVector.push_back(sboxBuffer[i]);
	}
	/*
	for(auto& x : s_BoxVector)
		std::cout << x << std::endl;
	*/
	
};

//groups 32 into 4 groups of 8
void AES_C::WordVector(std::vector<std::string>& keyWordVector)
{
	for(int i = 0; i < key_AES.size(); i += 8)
		keyWordVector.push_back(key_AES.substr(i,8));
	/*
	for(auto& x : keyWordVector)
		std::cout << x << std::endl;
	*/
};

//Initial_Key Round 0
void AES_C::Initial_Key(std::vector<std::string>& w_String_Vector)
{
	std::cout << "Initial Key: \n";
	for(auto& x : w_String_Vector)
		std::cout << x << std::endl;
};

std::vector<int> AES_C::StringV_To_IntV(std::vector<std::string>& w_String_Vector)
{
	unsigned int x;
	std::vector<int> w_Int_V;
	std::stringstream ss;
	for(int i = 0; i < w_String_Vector.size(); ++i)
	{
		for(int j = 0; j < w_String_Vector[i].size()/8; ++j)
		{
			//std::cout << w_String_Vector[i].substr(j*2,2) << std::endl;
			
			ss << std::hex << w_String_Vector[i].substr(j*8,8);
			ss >> x;
			w_Int_V.push_back(x);
			ss.clear();
		}
	}
	return w_Int_V;
};

//Key Rounds 1-11
void AES_C::Key_Rounds(std::vector<std::string>& w_String_Vector, 
		std::vector<int>& w_Rounds_Vector)
{
	std::cout << "Round" << std::endl;
	std::vector<int> gReturn = G(w_String_Vector);
	for(auto& x : gReturn)
		std::cout << x << std::endl;
	std::vector<int> w_Int_V = StringV_To_IntV(w_String_Vector);
	std::stringstream ss;
	std::string wStringBuffer;
	unsigned int x;
	uint32_t xorBuffer;
	int count;
	for(std::vector<int>::iterator it = w_Int_V.begin(); it != w_Int_V.end(); ++it)
	{
		std::cout << *it << " " << count << std::endl;
		count++;
	}

	
	//xorBuffer = w_Int_V[0] ^ gReturn[3];
	
	std::cout << xorBuffer << std::endl;
	/*
	for(int i = 0; i < gReturn.size(); ++i)
	{
		
		ss << std::hex << w_String_Vector[0].substr(i*2,2);
		ss >> x;
		std::cout << "ROUND HERE" << std::endl;
		xorBuffer = (x ^ gReturn[i]);
		wStringBuffer.append(std::to_string(xorBuffer));
		ss.clear();*/
	//}
	

};

//The key schedule which creates all rounds of keys 0-11
void AES_C::KeySchedule()
{
	int key_Whitening_IDX = 0;
	int round_n = 0;
	std::vector<std::string> w_String_Buffer;
	std::vector<std::string> w_String_Vector;
	std::vector<int> w_Rounds_Vector;
	WordVector(w_String_Vector);
	Initial_Key(w_String_Vector);	
	Key_Rounds(w_String_Vector, w_Rounds_Vector);
	//G(w_String_Vector);		

};

//First level of the S_BOX, only takes 1 byte, two chars
void AES_C::Mult_Inverse(std::string& byteHexString, std::vector<std::bitset<9>>& returnVector)
{

	//x^8+x^4+x^3+x+1 galois field of 2^8
	//std::cout << byteHexString << std::endl;
	uint16_t hexString;
	std::istringstream ost(byteHexString);
	ost >> std::hex >> hexString; 
	std::cout << hexString << " hexString " << std::endl;	
	
	std::bitset<9> hexBit(hexString);
	std::bitset<9> gf{0b100011011};
	std::bitset<9> remainder, b1,b2,quotient, buffer;
	std::bitset<9> nullB{0b000000000};
	std::bitset<9> tL,tmp;

	std::vector<int> qV;

	std::bitset<9> tOLD{0b000000000};
	std::bitset<9> tI{0b000000001};
	std::bitset<9> tNEW;

	int idx1, idx2;
	b1 = gf;
	b2 = hexBit;

	if(b2 == 0b00000000)
                tNEW = 0b000000000;
        else if(b2 == 0b000000001)
                tNEW = 0b000000001;
        else
        {
                while(tmp != 0b000000001)
                {

                        idx1 = b1.size() - 1;
                        while(!(b1.test(idx1)) && (idx1 > 0))
                        {
                                --idx1;
                        }

                        idx2 = b2.size() - 1;
                        while(!(b2.test(idx2)))
                        {
                                --idx2;
                        }


                        idx2 = idx1 - idx2;

                        if(idx2 < 0)
                        {
                                tmp = b1;
                                b1 = b2;
                                b2 = tmp;
                                //std::cout << b2 << ": b2 " << b1 << ": b1" << std::endl;

                                for(int q = 0; q < quotient.size(); ++q)
                                {
                                        if(quotient[q] != 0 && q > 0)
                                        {
                                                qV.push_back(q);
                                        }
                                }
                                buffer = tI;
                                tI = 0b000000000;
                                for(std::vector<int>::iterator it = qV.begin(); it != qV.end(); ++it)
                                {
                                        tL = (buffer << *it);
                                        tI = tI ^ tL;
                                }
                                if(quotient.test(0))
                                        tI ^= buffer;
                                qV.clear();


                                tNEW = tOLD ^ tI;
                                tI = tNEW;
                                tOLD = buffer;
                                quotient = nullB;
			}
                        else if(idx2 == 0)
                        {
                                quotient.set(0);
                                b1 = b1 ^ (b2);
                        }
                        else
                        {
                                quotient.set(idx2);
                                b1 = b1^(b2 << idx2);
                        }
                }
        }

        //std::cout << "Multiplicative Inverse: " << tNEW << std::endl;
        std::cout << std::hex << tNEW.to_ulong() << std::endl;
	
	returnVector.push_back(tNEW);
	 
	//return returnVector;
	
	
};

//{a'} = M{a} xor {v}, second part of the S_BOX
void AES_C::Affine_Transform(std::vector<std::bitset<9>>& multInvTable, std::vector<int>& s_BoxVector)
{

	for(int i = 0; i < multInvTable.size(); ++i)
	{
		//std::cout << multInvTable[i] << std::endl;
		for(int j = 0; j < multInvTable[i].size()-1; ++j)
		{
			affine_gf28[j] = multInvTable[i][j] ^ multInvTable[i][(j+4)%8] 
				^ multInvTable[i][(j+5)%8] ^ multInvTable[i][(j+6)%8] 
				^ multInvTable[i][(j+7)%8] ^ v_gf28[j];	
		}
		s_BoxVector.push_back(static_cast<int>(affine_gf28.to_ulong()));
	}	
	//for(std::vector<int>::iterator it = S_BOX.begin(); it != S_BOX.end(); ++it)
	//		std::cout << *it << std::endl;

};

//Diffusion Layer
//using vector container for this specific algorithm 
void AES_C::Shift_Rows(std::vector<int>& s_BoxVector, std::vector<int>& shift_Rows_V)
{
	
	std::vector<int> n_S_BOX;
	for(int j = 0; j < 4; ++j)
	{
		for(int k = 0; k < 4; ++k)
		{
			n_S_BOX.push_back(s_BoxVector[k*4 + j]);
		}
	}
	//for(int pl = 0; pl < n_S_BOX.size(); ++pl)
	//	std::cout << n_S_BOX[pl] << std::endl;
	
	//std::cout << "AES SHIFT: \n";
	
	int five = 5;
	for(int i = 0; i < 16; i += 4)
	{
		for(int t = 0; t < 4; ++t)
		{
			shift_Rows_V.push_back(n_S_BOX[(i + five*t)%16]);
		}
	}	
	
	/*for(int lp = 0; lp < shift_Rows_V.size(); ++lp)
	{
		std::cout << shift_Rows_V[lp] << std::endl;
	}*/
};



//Put into constructor later?i
//
/*
void AES_C::AES_C_S_BOX()
{
	multInvVect = ByteString();
	for(int i = 0; i < multInvVect.size(); ++i)
	{
		std::cout << "Mult Inverse Vector[" << i << "] = "<< multInvVect[i] << std::endl;
		Mult_Inverse(multInvVect[i]);				
	}
	Affine_Transform();
	Shift_Rows();
	KeySchedule();
	multInvVect.clear();
};*/

void AES_C::PracticeRun()
{
	//std::vector<std::string> KeyVector = KeyByteStringV();
	KeySchedule();		
};
/*
void AES_C::Initial_Round()
{
        for(int i = 0; i < key_AES.size()+1; i += 8)
                wordVector.push_back(key_AES.substr(i, 8));
};

void AES_C::Main_Rounds()
{

	
};

void AES_C::Final_Round()
{

};

void AES_C::AES_ENCRYPT()
{


};*/
