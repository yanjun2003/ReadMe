package com.example.student.exception;

import java.util.List;

import com.example.student.R;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

public class ExceptionNDK extends Activity {
     TextView mTextView;
     Button mBtn01;
     Button mBtn02;
     Button mBtn03;
     Button mBtn04;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
	    setContentView(R.layout.activity_exception);
	    
	    mTextView =(TextView)findViewById(R.id.mTextView);
	    
	    mBtn01 =(Button)findViewById(R.id.mBtn01);
	    mBtn02 =(Button)findViewById(R.id.mBtn02);
	    mBtn03 =(Button)findViewById(R.id.mBtn03);
	    mBtn04 =(Button)findViewById(R.id.mBtn04);
	   
		mBtn01.setOnClickListener(mListener);
	    mBtn02.setOnClickListener(mListener);
	    mBtn03.setOnClickListener(mListener);
	    mBtn04.setOnClickListener(mListener);
	}
    
	 private OnClickListener mListener= new OnClickListener(){
         String mString = new String();
		@Override
		public void onClick(View view) {
			switch(view.getId()){
			case R.id.mBtn01:
				mString=showException(13); 
				mTextView.append(mString);
				break;
			case R.id.mBtn02:
				mString=showException(130); 
				mTextView.append(mString);
				break;
				
			case R.id.mBtn03:
				try{
				    doit();
				}catch (Exception e){
					mTextView.append("doit throw exception\n");
				}
				break;
				
				
			case R.id.mBtn04:
				mTextView.append("-------test()"+"\n");
				mTextView.append(test()+"\n");

				mTextView.append("-------testArray()"+"\n");
				String[] s1 = testArray();
				for (int i = 0; i < s1.length; i++) {
					mTextView.append(s1[i]+"\n");
				}

				mTextView.append("testObject()"+"\n");
				mTextView.append(testObject().ssid+"\n");
				mTextView.append(testObject().mac+"\n");
				mTextView.append(String.valueOf(testObject().level)+"\n");

				mTextView.append("-----getScanResultsA()"+"\n");
				ScanResult[] s2 = getScanResultsA();
				for (int i = 0; i < s2.length; i++) {
					mTextView.append("index"+ i +": \n");
					mTextView.append(s2[i].ssid+"\n");
					mTextView.append(s2[i].mac+"\n");
					mTextView.append(String.valueOf(s2[i].level)+"\n");
				}

				mTextView.append("-------getScanResults()"+"\n");
				List<ScanResult> list = getScanResults();
				mTextView.append(list.get(0).ssid+"\n");
				mTextView.append(list.get(0).mac+"\n");
				mTextView.append(String.valueOf(list.get(0).level)+"\n");
		
				break;	
				
			}
			
		}
		 
	 };
	
	public native String showException(int index);
	private native void doit() throws IllegalArgumentException;
	
	private void callback() throws   NullPointerException{
		throw new NullPointerException("CatchThrow.callback");
	} 
	
	
	private void jni_call_back(int index){
		Log.i("Student","In jni_call_back");
		if(index >100){
			throw new NullPointerException();
		}
	}
	
	
	public native static String test();
	public native static String[] testArray();
	public native static ScanResult testObject();
	public native static ScanResult[] getScanResultsA();
	public native static List<ScanResult> getScanResults();
	
}
