package com.yanjun.ascilltobin.math;

import com.yanjun.ascilltobin.AsciiToBin_Main;



public class StringConverter {

	private AsciiToBin_Main hMain;
	
	public StringConverter(AsciiToBin_Main main){
		hMain = main;
		
	}
	//Uncomment once the UI overlay issue is solved
	public native String calculateBinFromAsciiStringJNI(String s);
	public native String calculateAsciiFromBinStringJNI(String s);
	
	
	 static {
		 	//System.loadLibrary("stlport_shared");//this is a static lib now, built in.  See Application.k
	        System.loadLibrary("ascii2bin");
	    }
	
}
