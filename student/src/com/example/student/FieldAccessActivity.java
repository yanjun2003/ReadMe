package com.example.student;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ScrollView;
import android.widget.TextView;

public class FieldAccessActivity extends Activity {
    private TextView mTextView;
    private ScrollView detail_scroll;
    private Button myBtn;
    private String mStr;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_fieldaccess);
		mTextView =(TextView)findViewById(R.id.mTextView);
		detail_scroll=(ScrollView)findViewById(R.id.detail_scroll);
		
		
		myBtn=(Button)findViewById(R.id.begin);
		
		mStr=new String("abc");
		myBtn.setOnClickListener(new OnClickListener(){

			@Override
			public void onClick(View arg0) {
				// TODO Auto-generated method stub
				SendMessage("Before access the mStr = "+mStr);
				access();
				SendMessage("after access");
			    SendMessage("  mStr = \"" + mStr + "\"");
			}
			
		});
	
	}
		
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
			
			
	private native void access();
	
}
