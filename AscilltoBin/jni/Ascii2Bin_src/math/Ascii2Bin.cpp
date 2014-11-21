#include "Ascii2Bin.h"


Ascii2Bin::Ascii2Bin(){
	asciiString = "";
	binaryString = "";
}

Ascii2Bin::~Ascii2Bin(){

}

//Accessors
std::string Ascii2Bin::getAsciiString(){
	return asciiString;
}
void Ascii2Bin::setAsciiString(std::string s){
	asciiString = s;
}
std::string Ascii2Bin::getBinaryString(){
	return binaryString;
}
void Ascii2Bin::setBinaryString(std::string b){
	binaryString = b;
}

//Control and Mutation functions

//This function takes an ascii character string and converts it to
//a binary string of equivalent value
std::string Ascii2Bin::calculateBinFromAsciiString(std::string s){
	std::string binStringSegments;//[s.length()]; //each char will converted to a binary string, and these strings will be cat'd together and returned
	char temp8Bits[8]; //will hold our 8 bits of either 0 or 1 depending on the decimal value to represent and the char array index

	//If the user did not supply a string argument,
	//then we'll use the stored member asciiStrin
	//which is guaranteed to be at least the empty string when this
	//function is invoked
	if(s.length() == 0){
		s = asciiString;
	}
	LOGI("s.length is %i\n",s.length());
	int asciiVals[s.length()]; //container for the decimal ascii char values
	int incTracker = 0;
	///double integralSegment = 0.0;
	////double* integralSegment_ptr = (double*)malloc(sizeof(double));
	int maxInt;
	///double fractionSegment = 0.0;

	for(int y=0;y<s.length();y++){
		asciiVals[y] = (int)s[y];
		incTracker = 0;

		maxInt = asciiVals[y];
		for(int x=7;x>=0;x--){//remember, we're working left to right, so our 8th index is 2^7

			if(maxInt<pow(2.0,x)){
				temp8Bits[incTracker] = '0';
			}
			else{
				temp8Bits[incTracker] = '1';
				maxInt -= pow(2.0,x);
			}

			///fractionSegment = modf((double)asciiVals[y],integralSegment_ptr);
			printf("temp8Bits at %i is %c\n",incTracker,temp8Bits[incTracker]);

			incTracker++;
		}

		//Now our char[] should hold the binary string segment.  COnvert to std::string and append to binStringSegments
		binStringSegments.append(temp8Bits,8);//[y] = temp8Bits;

	}

	//DEBUG
	printf("\nDEBUG\n");
	for(int i=0;i<s.length();i++){
		printf("The decimal char val of character %c at index %i is %i\n",s[i],i,asciiVals[i]);
	}



	//std::cout << binStringSegments;
	printf("\n");
	LOGI("%s",binStringSegments.c_str());
	return binStringSegments;
}

//This function takes a binary string and converts it to
//an ascii character string of equivalent value
std::string Ascii2Bin::calculateAsciiFromBinString(std::string s){
	//First thing we need to do here is check for valid value range in binary string
			//this would be, ideally, 65 through 122 base 10 (inclusive) but could be allowed to be
			//32 through 126 base 10 (inclusive) so check for the latter
			//UPDATE: we validate input value range for each char below... if any are illegal, we sey bIsIllegal flag to true

			//local control vars
			int bIsIllegal = 0;
			std::string debugString;

			//First validation is to ensure our input string is divisible evenly by 8
			if(strlen(s.c_str())%8 != 0){
				bIsIllegal = 1;
				debugString = "Please only enter 8-tuple binary strings.  Powers of 2 are gr(1<<3)!";
			}
			else{

			std::string asciiStringSegments;//[s.length()]; //each char will converted to a binary string, and these strings will be cat'd together and returned
			char temp8Bits[8]; //will hold our 8 bits of either 0 or 1 depending on the decimal value to represent and the char array index

			//If the user did not supply a string argument,
			//then we'll use the stored member asciiStrin
			//which is guaranteed to be at least the empty string when this
			//function is invoked
			if(s.length() == 0){
				s = asciiString;
			}
			printf("s.length is %i\n",s.length());
			int asciiVals[s.length()]; //container for the decimal ascii char values
			int incTracker = 0;
			///double integralSegment = 0.0;
			////double* integralSegment_ptr = (double*)malloc(sizeof(double));
			int cumInt = 0;
			///double fractionSegment = 0.0;

			for(int y=0;y<s.length();y+=8){ //s is comprised of s.length()/8 8-tuple binary substrings
				cumInt = 0;
				for(int x=7;x>=0;x--){
					temp8Bits[x] = s[y+(7-x)];
					printf("temp8Bits at x = %i is %c and s at y = %i + x = %i = %i is %c \n",x,temp8Bits[x],y,x,y+x,s[y+x]);
					if(temp8Bits[x] == '1'){
						printf("We hit a 1!  cumInt is currently: %i before the addition of 2^%i\n",cumInt,x);
						cumInt+= pow(2.0,x);
						printf("after adding 2^%i, cumInt is %i\n",x,cumInt);
					}
					//asciiStringSegments.append(temp8Bits,8);
				}

				if (cumInt < 32 || cumInt > 126){
					printf("Unsupported char value from bin string elements at index %i through %i  Please enter a binary string which resolves to a decimal value from the set 32 through 126 inclusive",y,(y+7));
					std::stringstream ss(std::stringstream::in | std::stringstream::out);
					ss << "Unsupported char value from bin string elements at index ";
					ss<< y;
					ss << " through ";
					ss<< y+7;
					ss<<" Please enter a binary string which resolves to a decimal value from the set 32 through 126 inclusive";
					LOGI("\nTesting ss: %s\n",ss.str().c_str());
					debugString.append(ss.str());


					bIsIllegal = 1;
				}

				//cumInt now holds our decimal value for this binary substring
				//convert to a char and append to asciiString
				char c = (char)cumInt;
				printf("Checking cumInt cast to char: cumInt is %i and after cast is %c\n",cumInt,c);
				asciiStringSegments.append(&c,1);

			}

				if(!bIsIllegal){
					//std::cout << asciiStringSegments;
					printf("\n");
					LOGI("%s",asciiStringSegments.c_str());
					return asciiStringSegments;
				}
				else{
					return debugString;
				}
			}//end else condition of s.length%8 != 0 check


			//if we're returning here, its because the input string was not evenly divisible by 8
			return debugString;

}



