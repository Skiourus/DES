#include "DES.hpp"
#include "bit.hpp"

#include <iostream>

void crypt(std::string msg, size_t final, std::string Key){
	std::vector<std::string> b(final);
	std::vector<std::bitset<64>> bit(final);
	size_t i;
	std::bitset<64> KKey;
	//KKey=sToBit(Key);
	//std::cout << bToHex(KKey) << std::endl;
	//std::cout << bToHex(sToBit(msg)) << std::endl;

	KKey=HextoBit(Key);
	b=byBlock(msg); //message decoupé par block
	//std::cout << "Message\t" << msg << "\n";
	//std::cout << "Key\t" << Key << "\n" << "Key\t" << KKey <<"\n";

	for(i=0;i<final;i++){ //ECB
		//bit[i]=sToBit(b[i]); //block transformé en bitset	
		bit[i]=HextoBit(b[i]);
		bit[i]=DESdecrypt(bit[i],KKey);// block crypté
	}

	printBitset(bit,final,0);
	/*
	for(i=0;i<final;i++){
		bit[i]=DESdecrypt(bit[i],KKey);
	}

	printBitset(bit,final,0);*/
}


int main(int argc, char const *argv[])
{
	if(argc!=3){
		std::cout << "./main.exe [message hexa] [key hexa]" << std:: endl;
		exit(255);
	}
	std::string msg = argv[1]; //4d455353414745
	std::string Key = argv[2]; //4b4559
	size_t final = (msg.length()-1)/16 +1;
	//size_t final = (msg.length()-1)/8 +1;
	crypt(msg,final,Key);
	return 0;
}


