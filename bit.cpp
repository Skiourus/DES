#include "bit.hpp"

#include <iostream>

std::bitset<64> sToBit(std::string msg){ //convert string to a Bitset
	
	std::bitset<64> msg_bitset;
	int M(0);
	for(size_t i = 0; i < 8; i++){
		M = msg[i];
		std::string s = "";
		s = std::to_string(M / 128); M %= 128;
		s = s + std::to_string(M / 64); M%= 64;
		s = s + std::to_string(M / 32); M %= 32;
		s = s + std::to_string(M / 16); M %= 16;
		s = s + std::to_string(M / 8); M %= 8;
		s = s + std::to_string(M / 4); M %= 4;
		s = s + std::to_string(M / 2) + std::to_string(M % 2);

		for(size_t j = 0; j < 8; j++) {
			if(s[7-j] == '1') msg_bitset[(7-i) * 8 + j] = 1;
		}
	}
	return msg_bitset;
}

std::bitset<64> HextoBit(std::string msg){ //convert string to hexastring
	std::bitset<64> msg_bitset;
	int M(0);
	for(size_t i=0;i<16;i++){
		M=msg[i];
		std::string s= "";
		if(M=='a'){M=10;}
		if(M=='b'){M=11;}
		if(M=='c'){M=12;}
		if(M=='d'){M=13;}
		if(M=='e'){M=14;}
		if(M=='f'){M=15;}
		if(M=='9'){M=9;}
		if(M=='8'){M=8;}
		if(M=='7'){M=7;}
		if(M=='6'){M=6;}
		if(M=='5'){M=5;}
		if(M=='4'){M=4;}
		if(M=='3'){M=3;}
		if(M=='2'){M=2;}
		if(M=='1'){M=1;}
		if(M=='0'){M=0;}
		s = s + std::to_string(M/8); M %= 8;
		s = s + std::to_string(M/4); M %= 4;
		s = s + std::to_string(M/2) + std::to_string(M % 2);

		for(size_t j = 0; j < 4 ; j++ ){
			if( s[3-j]=='1' ) msg_bitset[(15-i)*4 + j]=1;
		}
	}
	return msg_bitset;
}

std::vector<std::string> byBlock(std::string msg){ //divide the message in some block which are stored in a vector
	
	size_t final = (msg.length() - 1) / 16 + 1;
	//size_t final = (msg.length()-1)/8 +1;
	std::vector<std::string> block(final);          // creates a vector of string of size "final"
//	cout << final<< endl;
	for(size_t i = 0; i < final; i++){
		std::string s = "";
		for(size_t j = 0; j < 16; j++){
			s = s + msg[i * 16 + j];
	//	for(size_t j = 0; j < 8; j++){
	//		s = s + msg[i * 8 + j];
		}
		block[i] = s;
	}

	return block;
}

std::string bToString(std::bitset<64> bitset){ //convert a bitset into string readable for humans
	
	std::string str = "";

	for(size_t i = 0; i < 8; i++)
		str += bitset[63-i*8]*128 + bitset[62-i*8]*64 + bitset[61-i*8]*32 + bitset[60-i*8]*16 + bitset[59-i*8]*8 + bitset[58-i*8]*4 + bitset[57-i*8]*2 + bitset[56-i*8];

	return str;
}

std::string bToHex(std::bitset<64> bitset){ //convert a bitset into Hexadecimal visualization
	std::string str = "";

	for(size_t i = 0; i < 16; i++){
		int val = bitset[63-i*4]*8 + bitset[62-i*4]*4 + bitset[61-i*4]*2 + bitset[60-i*4];
		if(val == 15) str += "f";
		if(val == 14) str += "e";
		if(val == 13) str += "d";
		if(val == 12) str += "c";
		if(val == 11) str += "b";
		if(val == 10) str += "a";
		if(val < 10)  str += val + 48;
	}
	return str;
}

void printBitset(std::vector<std::bitset<64>> bitset, size_t final,int ch){ //print a bitset with the chosen visualiation Hex or String
	for(size_t i = 0; i < final; i++){
		if(ch==0){std::cout << bToHex(bitset[i]);} //Hex is more convenient as sometimes there the ciphertext is not printable in ASCII mode
		if(ch==1){std::cout << bToString(bitset[i]);}
	}

	std::cout << std::endl;
}


