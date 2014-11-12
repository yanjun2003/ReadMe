package com.example.student;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;
import android.app.Activity;
import android.content.Intent;

public class MainActivity extends Activity {
    private static final String TAG = "StudentActivity";
	TextView mTextView;
	private Student mStudent=null;
	
	private int ival;
	private float fval;
	private String str;
	
	private Button exceptionBtn,threadBtn,OpenGLBtn,OpenSLBtn;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
			super.onCreate(savedInstanceState);
			setContentView(R.layout.activity_main);
			mTextView =(TextView)findViewById(R.id.mTextView);
			mTextView.setText(stringFromJNIDynamic() + "\r\n");
			    
			exceptionBtn=(Button)findViewById(R.id.excptionBtn);
			exceptionBtn.setOnClickListener(MyListener);
			threadBtn=(Button)findViewById(R.id.threadBtn);
			threadBtn.setOnClickListener(MyListener);
			OpenGLBtn=(Button)findViewById(R.id.GLBtn);
			OpenGLBtn.setOnClickListener(MyListener);
			
			OpenSLBtn=(Button)findViewById(R.id.SLBtn);
			OpenSLBtn.setOnClickListener(MyListener);
			
		    Log.d(TAG, "onCreate");
	        ival = intFromJni();
	        Log.d(TAG, "ival="+ival);
	        intToJni((int)123); 
	        fval = floatFromJni();
	        Log.d(TAG, "fval="+fval);
	        floatToJni((float)456.78);
	        str = stringFromJni(); 
	        Log.d(TAG, "str="+str);
	        stringToJni("Hello From Java");
	        
	        
	        mStudent = new Student();
	        for (int i=0; i<3; i++) {
	            getStudentInfoByIndex(mStudent, i);
	            Log.d(TAG, "Student["+i+"] -- "+mStudent);
	            mStudent.sayHello();
	        }
	}

	private OnClickListener MyListener= new OnClickListener(){
        Intent intent = new Intent();
		@Override
		public void onClick(View view) {
			// TODO Auto-generated method stub
			switch(view.getId()){
			case R.id.threadBtn:
				intent.setAction("com.example.student.thread");
				startActivity(intent);
				break;
				
			case R.id.excptionBtn:
				intent.setAction("com.example.student.exception");
				startActivity(intent);
				break;
				
			case R.id.GLBtn:
				intent.setAction("com.example.student.gl_test");
				startActivity(intent);
				break;
				
			case R.id.SLBtn:
				intent.setAction("com.example.student.SL_test_audio");
				startActivity(intent);
				break;
			}
		}
		
	};
	
	static {
		System.loadLibrary("NDKdemo-jni");
	}
	
	public native String stringFromJNIStatic();
	public native String stringFromJNIDynamic();
	private native int intFromJni();
	private native void intToJni(int val);
	private native float floatFromJni();
	private native void floatToJni(float val);
	private native String stringFromJni();
	private native void stringToJni(String val);
	private native int getStudentInfoByIndex(Student student, int index);	
	
	@Override
	public void onBackPressed() {
		finish();
	}
}
