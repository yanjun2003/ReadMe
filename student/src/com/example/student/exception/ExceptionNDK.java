package com.example.student.exception;

import java.util.List;

import com.example.student.R;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ScrollView;
import android.widget.TextView;

public class ExceptionNDK extends Activity {
     TextView mTextView;
     Button mBtn01;
     Button mBtn02;
     Button mBtn03;
     Button mBtn04;
     ScrollView detail_scroll;
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
	    
	    detail_scroll=(ScrollView)findViewById(R.id.detail_scroll);
	}
    
	 private OnClickListener mListener= new OnClickListener(){
         String mString = new String();
		@Override
		public void onClick(View view) {
			switch(view.getId()){
			case R.id.mBtn01:
				mString=showException(13); 
				SendMessage(mString);
				break;
			case R.id.mBtn02:
				mString=showException(130); 
				SendMessage(mString);
				break;
				
			case R.id.mBtn03:
				try{
				    doit();
				}catch (Exception e){
					SendMessage("doit throw exception!");
				}
				break;
				
				
			case R.id.mBtn04:
				SendMessage("-------test()");
				SendMessage(test());
				SendMessage( "-------testArray()");
				String[] s1 = testArray();
				for (int i = 0; i < s1.length; i++) {
					SendMessage("testArray result index :" +i+"=" +s1[i]);
				}

				SendMessage("testObject()");
				SendMessage(testObject().ssid);
				SendMessage(testObject().mac);
				SendMessage(String.valueOf(testObject().level));

				SendMessage("-----getScanResultsA()");
				ScanResult[] s2 = getScanResultsA();
				for (int i = 0; i < s2.length; i++) {
					SendMessage("index"+ i );
					SendMessage(s2[i].ssid);
					SendMessage(s2[i].mac);
					SendMessage(String.valueOf(s2[i].level));
				}

				SendMessage("-------getScanResults()");
				List<ScanResult> list = getScanResults();
				SendMessage(list.get(0).ssid);
				SendMessage(list.get(0).mac);
				SendMessage(String.valueOf(list.get(0).level));
		
				break;	
				
			}
			
		}
		 
	 };
	 
	private void SendMessage(String str){
		mHandler.obtainMessage(SHOWCALLBACKINFO, str).sendToTarget();
	} 
	
	private final static int SHOWCALLBACKINFO =2;
	 @SuppressLint("HandlerLeak")
		Handler mHandler = new Handler() {
			@Override
			public void handleMessage(Message msg) {
				if (msg.what == SHOWCALLBACKINFO) {
					 final String str = (String) msg.obj;
					 mTextView.append(str + "\n");
					 detail_scroll.fullScroll(View.FOCUS_DOWN);
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
