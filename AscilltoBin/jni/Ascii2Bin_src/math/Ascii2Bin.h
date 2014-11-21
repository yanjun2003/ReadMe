/*
 * Ascii2Bin_Main.h
 *
 *  Created on: Jan 3, 2013
 *      Author: creswell
 */

#ifndef ASCII2BIN_MAIN_H_
#define ASCII2BIN_MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include <string.h>
#include <android/log.h>

using namespace std;

#define  TAG    "ascii2bin"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)

class Ascii2Bin{
private:
	std::string asciiString;
	std::string binaryString;

public:
	//Con/de 'structors
	Ascii2Bin();
	~Ascii2Bin();

	//Accessors
	std::string getAsciiString();
	void setAsciiString(std::string);
	std::string getBinaryString();
	void setBinaryString(std::string);

	//Control and Mutation function
	std::string calculateBinFromAsciiString(std::string);
	std::string calculateAsciiFromBinString(std::string);


};


#endif /* ASCII2BIN_MAIN_H_ */
