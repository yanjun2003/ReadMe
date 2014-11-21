package com.yanjun.ascilltobin.gui;

import android.view.ViewGroup.LayoutParams;

public class DefineLayoutParams {
	//the controls
	private static final int MATCHMATCH = 1;
	private static final int WRAPMATCH = 2;
	private static final int MATCHWRAP = 3;
	private static final int WRAPWRAP = 4;

	//the ONE layoutparams object
	private static LayoutParams floatParams = new LayoutParams(0,0);

	public DefineLayoutParams(){

	}

	public static LayoutParams getParams(int type){
	if (type == MATCHMATCH){
	floatParams.width = LayoutParams.MATCH_PARENT;
	floatParams.height = LayoutParams.MATCH_PARENT;
	}
	else if(type == WRAPWRAP){
	floatParams.width = LayoutParams.WRAP_CONTENT;
	floatParams.height = LayoutParams.WRAP_CONTENT;
	}
	else if (type == WRAPMATCH){
	floatParams.width = LayoutParams.WRAP_CONTENT;
	floatParams.height = LayoutParams.MATCH_PARENT;
	}
	else if (type == MATCHWRAP){
	floatParams.width = LayoutParams.MATCH_PARENT;
	floatParams.height = LayoutParams.WRAP_CONTENT;
	}
	return floatParams;
	}

	public static LayoutParams getCustomParams(int w, int h){
	floatParams.width = w;
	floatParams.height = h;
	return floatParams;
	}

	public static int getMM(){
	return MATCHMATCH;
	}
	public static int getWW(){
	return WRAPWRAP;
	}
	public static int getWM(){
	return WRAPMATCH;
	}
	public static int getMW(){
	return MATCHWRAP;
	}
}
