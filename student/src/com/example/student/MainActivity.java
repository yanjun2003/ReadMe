package com.example.student;

import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;
import android.app.Activity;

public class MainActivity extends Activity {
    private static final String TAG = "StudentActivity";
	TextView mTextView;
	private Student mStudent=null;
	
	private int ival;
	private float fval;
	private String str;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
			super.onCreate(savedInstanceState);
			setContentView(R.layout.activity_main);
			mTextView =(TextView)findViewById(R.id.mTextView);
			mTextView.setText(stringFromJNIDynamic() + "\r\n");
			    
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

	
	static {
		System.loadLibrary("Student-jni");
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
