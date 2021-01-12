OBJS = mainCrypto.o base64_C.o 
CXX = g++
CXXFLAGS = -Wall -std=c++17
#LDLIBS 

CryptProgram: $(OBJS)
	$(CXX) $(OBJS) -o CryptProgram $(CXXFLAGS)

mainCrypto.o: base64_C.hpp
base64_C.o: base64_C.hpp


#mainCrypto.o:	mainCrypto.cpp base64_C.hpp 
#	$(CXX) -c mainCrypto.cpp 

#base64_C.o: base64_C.cpp base64_C.hpp
#	$(CXX) -c base64_C.cpp 

#$(OBJS): base64_C.hpp 

clean:
	$(RM) CryptProgram $(OBJS)


#target: dependencies
#	command(s)
