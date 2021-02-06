OBJS = mainCrypto.o crypto_Functions.o base64_C.o AES_C.o
CXX = g++
CXXFLAGS = -Wall -std=c++17
#LDLIBS 

CryptProgram: $(OBJS)
	$(CXX) $(OBJS) -o CryptProgram $(CXXFLAGS)

crypto_Functions.o: crypto_Functions.hpp 
base64_C.o: base64_C.hpp crypto_Functions.hpp
AES_C.o: AES_C.hpp 
mainCrypto.o: base64_C.hpp crypto_Functions.hpp AES_C.hpp


#mainCrypto.o:	mainCrypto.cpp base64_C.hpp 
#	$(CXX) -c mainCrypto.cpp 

#base64_C.o: base64_C.cpp base64_C.hpp
#	$(CXX) -c base64_C.cpp 

#$(OBJS): base64_C.hpp 

clean:
	$(RM) CryptProgram $(OBJS)


#target: dependencies
#	command(s)
