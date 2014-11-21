package com.yanjun.ascilltobin;

import com.yanjun.ascilltobin.gui.ConversionViewController;
import com.yanjun.ascilltobin.gui.DefineLayoutParams;
import com.yanjun.ascilltobin.gui.TutorialViewController;
import com.yanjun.ascilltobin.math.StringConverter;

import android.app.Activity;
import android.view.View;
import android.widget.RelativeLayout;
import android.widget.ViewFlipper;

public class AsciiToBin_Main {
	
	private Activity hAct;
	private View mvMainView;
	private ViewFlipper mvRootViewFlipper; 
	
	private ConversionViewController mvConversionViewController;
	private TutorialViewController mvTutorialViewController;
	private RelativeLayout mvRootRL;
	
	private StringConverter mvConverter;
	
	public AsciiToBin_Main(Activity act){
		hAct = act;
		
		mvConverter = new StringConverter(this);
		
		mvRootRL = new RelativeLayout(hAct);
		hAct.addContentView(mvRootRL, DefineLayoutParams.getParams(DefineLayoutParams.getMM()));
		//hAct.setContentView(mvRootRL);
		///hAct.setContentView(R.layout.conversion_layout);
	}
	
	public void init(){
		
		//Add the viewgroup subclass viewflipper to the rootRL
		mvRootViewFlipper = new ViewFlipper(hAct);
		mvRootRL.addView(mvRootViewFlipper);
		
		
		//Instantiate our conversion view controller
		mvConversionViewController = new ConversionViewController(this);
		mvTutorialViewController = new TutorialViewController(this);
		
		//Fire up the conversion view
		mvConversionViewController.initGUI();
		mvConversionViewController.initSpinnerElements();
		
		//Fire up the tutorial view
		mvTutorialViewController.initGUI();	
		
	}
	
	public RelativeLayout getRootRL(){
		return mvRootRL;
	}
	
	public ViewFlipper getRootViewFlipper(){
		return mvRootViewFlipper;
	}
	
	
	public View getMainView(){
		return mvMainView;
	}
	public Activity getAct(){
		return hAct;
	}
	public void setMainView(View v){
		mvMainView = v;
	}
	public void setActivity(Activity a){
		hAct = a;
	}
	public StringConverter getConverter(){
		return mvConverter;
	}
	public void setConverter(StringConverter sc){
		mvConverter = sc;
	}
}
