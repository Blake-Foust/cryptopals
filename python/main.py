import argparse
import cryptoF as cf


def main():
    hex = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"
    
    cff = cf.CryptoF()
    s1c1 = cff.hex2b64(hex)

    h1 = '1c0111001f010100061a024b53535009181c'
    h2 = '686974207468652062756c6c277320657965'
    s1c2 = cff.xor2Hex(h1,h2)
    
    print(s1c1)
    print(s1c2)
    xorHexString = '1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736'
    file4 = open('4.txt','r')
    lines = file4.readlines()
    for line in lines:
        cff.byteXorHex(line)
        print(line)

    s1c3 = cff.byteXorHex(xorHexString)
    print(s1c3)

if __name__ == "__main__":
    main()