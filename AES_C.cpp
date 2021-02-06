#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <string>
#include <cstddef>
#include "AES_C.hpp"

AES_C::AES_C(){};

AES_C::AES_C(std::string& keyInput, std::string& pText, std::string& cText)
	: key_AES(keyInput), plainText(pText), cipherText(cText){};

void AES_C::Mult_Inverse()
{
	//x^8+x^4+x^3+x+1 galois field of 2^8
	std::string binaryString;
	std::cout << "Enter binary String " << std::endl;
	std::getline(std::cin, binaryString);
	std::bitset<9> hexBit(binaryString);
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
                                std::cout << b2 << ": b2 " << b1 << ": b1" << std::endl;

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

        std::cout << "Multiplicative Inverse: " << tNEW << std::endl;
        std::cout << std::hex << tNEW.to_ulong() << std::endl;

 

	
	
};
