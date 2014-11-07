package com.example.student.thread;

import com.example.student.R;

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

public class ThreadNDK extends Activity {
    private TextView threadInfo;
    private Button startBtn,stopBtn;
    private ScrollView detail_scroll;
    private final static int SHOWCALLBACKINFO=2;
    
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_thread);
		threadInfo =(TextView)findViewById(R.id.mInfo);
		startBtn =(Button)findViewById(R.id.mStart);
		stopBtn =(Button)findViewById(R.id.mStop);
		detail_scroll = (ScrollView)findViewById(R.id.detail_scroll);

	    initThread();
		 
	 
		startBtn.setOnClickListener(btnListener);
	    stopBtn.setOnClickListener(btnListener);
	}

	private  OnClickListener btnListener= new OnClickListener(){

		@Override
		public void onClick(View view) {
		   switch(view.getId()){
			   case R.id.mStart:
				   startThread();
				   break;
			   case R.id.mStop:
				   stopThread();
				   break;   
		   }
		}
		
	} ;
	
	@SuppressLint("HandlerLeak")
	Handler mHandler = new Handler() {
		@Override
		public void handleMessage(Message msg) {
			if (msg.what == SHOWCALLBACKINFO) {
				 final String str = (String) msg.obj;
				 threadInfo.append(str + "\n");
				 detail_scroll.fullScroll(View.FOCUS_DOWN);
				 }
			}
		};
		
		//mHandler.obtainMessage(MSG_DIAL, "IOException").sendToTarget();
		public void callback1() {	
			mHandler.obtainMessage(SHOWCALLBACKINFO, "callback1() executed.").sendToTarget();
		}

		public int callback2(int param0, float param1, String param2) {
			String str=new String("callback2(int, float, String) executed: int "+param0+", float "+param1+", String "+param2);
			mHandler.obtainMessage(SHOWCALLBACKINFO, str).sendToTarget();
			return 0;
		}


		public void callback3(String param0) {
			String str=new String("callback3(String) executed: String "+param0);
			mHandler.obtainMessage(SHOWCALLBACKINFO, str).sendToTarget();
		}


		public float callback4(float param0) {
			String str=new String( "callback4(float) executed: float "+param0);
			mHandler.obtainMessage(SHOWCALLBACKINFO, str).sendToTarget();
			return 0;
		}
		

		
    @Override
		protected void onPause() {
			// TODO Auto-generated method stub
    		stopThread();
			super.onPause();
		}

		@Override
		protected void onDestroy() {
			// TODO Auto-generated method stub
			stopThread();
			super.onDestroy();
		}

	public native void initThread();
	public native void startThread();
	public native void stopThread();
}
