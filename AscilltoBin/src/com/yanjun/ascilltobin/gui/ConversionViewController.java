package com.yanjun.ascilltobin.gui;


import com.yanjun.ascilltobin.AsciiToBin_Main;
import com.yanjun.ascilltobin.R;
import android.graphics.Canvas;
import android.os.AsyncTask;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;

public class ConversionViewController extends View implements OnClickListener, OnItemSelectedListener{

	private AsciiToBin_Main hMain;
	private LayoutInflater mvInflater;
	private View mvConversionView;
	private Button mvConvertB;
	private Button mvToTutorialB;
	private Spinner mvConversionTypeSP;
	private EditText mvAsciiStringET;
	private EditText mvBinStringET;
	private ArrayAdapter<CharSequence> mvSpinnerAdapter;
	
	public ConversionViewController(AsciiToBin_Main main) {
		super(main.getAct());
		hMain = main;
		
		
	}
	
	@SuppressWarnings("static-access")
	public void initGUI(){
		
		mvInflater = (LayoutInflater) hMain.getAct().getSystemService(hMain.getAct().LAYOUT_INFLATER_SERVICE);
		mvConversionView = mvInflater.inflate(R.layout.conversion_layout, hMain.getRootViewFlipper(),false);
		hMain.getRootViewFlipper().addView(mvConversionView);
		
		//hMain.getRootRL().addView(mvConversionView);
		
		mvConvertB = (Button)hMain.getAct().findViewById(R.id.convertB);
		mvToTutorialB = (Button)hMain.getAct().findViewById(R.id.conversion_To_Tutorial_B);
		mvAsciiStringET = (EditText)hMain.getAct().findViewById(R.id.asciiStringET);
		mvBinStringET = (EditText)hMain.getAct().findViewById(R.id.binStringET);
		mvConversionTypeSP = (Spinner)hMain.getAct().findViewById(R.id.conversionTypeSP);
		
		mvConvertB.setOnClickListener(this);
		mvToTutorialB.setOnClickListener(this);
		mvConversionTypeSP.setOnItemSelectedListener(this);
		
	}
	
	public void initSpinnerElements(){
		mvSpinnerAdapter = ArrayAdapter.createFromResource(hMain.getAct(), R.array.conversion_choices_array, android.R.layout.simple_spinner_item);
		mvSpinnerAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
		mvConversionTypeSP.setAdapter(mvSpinnerAdapter);
		mvConversionTypeSP.setSelection(0);
		
		//Now that that the UI is ready, display it
		////hMain.getRootViewFlipper().showNext();
	}
	
	@Override
	protected void onDraw(Canvas c){
		super.onDraw(c);
		
	}

	@Override
	public void onClick(View v) {
		if(v==mvConvertB){
			Log.d("me", "button pressed! Conversion type selected currently is "+mvSpinnerAdapter.getItem(mvConversionTypeSP.getSelectedItemPosition()));
			if(mvConversionTypeSP.getSelectedItemPosition() == 0){
				
				//This is the convert ascii to binary string choice
				//Calls the native method calculateBinFromAsciiStringJNI
				//Not a terribly heavy process, but since it is disparate from
				//the UI we should probably grant it its own thread...
				//Uncomment when UI overlay bug is solved
				new NativeStringConversionTask(0).execute(mvAsciiStringET.getText().toString());
				
				
				//mvBinStringET.setText(hMain.getConverter().calculateBinFromAsciiStringJNI(mvAsciiStringET.getText().toString()));
			}
			else if(mvConversionTypeSP.getSelectedItemPosition() == 1){
				//This is the convert binary to ascii string choice
				
				//First, preferrably prior to engaging JNI, we validate the input
				//binary string must resolve to decimal between 32 and 126 inclusive
				//int decValue = Integer.parseInt(mvBinStringET.getText().toString(),2);
				//UPDATE: actually this'd require us to parse the input string as 8-tuple substrings
				//and validate each of those separately.  Let the native lib handle it since it already
				//does that work.
				
				new NativeStringConversionTask(1).execute(mvBinStringET.getText().toString());
				
				/*
				if(decValue >=32 && decValue <= 126){
				
					new NativeStringConversionTask(1).execute(mvBinStringET.getText().toString());
				}
				else{
					CustomDialog cd = new CustomDialog();
					cd.setDialogMessage("")
				}
				*/
				
				//mvAsciiStringET.setText(hMain.getConverter().calculateAsciiFromBinStringJNI(mvBinStringET.getText().toString()));
			}
		}
		else if(v==mvToTutorialB){
			//hMain.getRootViewFlipper().setDisplayedChild(1);
			hMain.getRootViewFlipper().showNext();
			//hMain.getAct().setContentView(R.layout.tutorial_layout);
		}
		
	}

	@Override
	public void onItemSelected(AdapterView<?> arg0, View arg1, int arg2,
			long arg3) {
		Log.d("me", "itemselectedlistener received a callback! the position selected is "+arg2);
		
	}

	@Override
	public void onNothingSelected(AdapterView<?> arg0) {
		Log.d("me", "itemselectedlistener received a no items slected callaback");
		
	}
	
	//Uncomment once the UI overlay issue is solved
	private class NativeStringConversionTask extends AsyncTask<String,Integer,String>{
		private int taskID = 0;
		
		public NativeStringConversionTask(int id){
			taskID = id;
		}
		
		@Override
		protected void onPreExecute(){
			Log.d("me","in the preExecute of the nativeStringConversion Async task");
		}
		
		
		@Override
		protected String doInBackground(String... s) {
			//NB: if we wanted onProgressUpdate to be called with something we would
			//invoke publishProgress(something) in this function
			
			Log.d("me", "bg task started with taskID "+taskID);
			  if(taskID == 0){
				publishProgress(taskID);
				return hMain.getConverter().calculateBinFromAsciiStringJNI(s[0].toString());
			  }
			  else if (taskID == 1){
				  publishProgress(taskID);
				return hMain.getConverter().calculateAsciiFromBinStringJNI(s[0].toString());
			  }
			  else{
				  publishProgress(taskID);
				  return "This shouldn't appear.  if it does... may the gods below help us all";
			  }
			
		}
		
		
		//Not sure why this seems to be claiming to not be part of asynctask...
		//well anyway, the compiler seems to be making me comment the override annotation 
		//for the nonce
		//UPDATE: the highly dignified and technical reason for the error was that I can't
		//spell progress correctly... f^&k lol
		@Override
		protected void onProgressUpdate(Integer... progress){
			Log.d("me", "progressUpdate called!  And I'm totally gonna nail that redhead chick from the lobby! Why, her tits must've been "+((1<<progress[0])+1)+" times the size of aforementioned_awesomechick's ;)! Wonder if'n she's a natural redhead...");
		}
		
		
		
		@Override
		protected void onPostExecute(String result){
			
			Log.d("me", "calling postExecute...");
			if(taskID == 0){
				mvBinStringET.setText((String)result);
			  }
			  else if (taskID == 1){
				  mvAsciiStringET.setText((String)result);
			  }
			  else{
				  mvBinStringET.setText("This shouldn't appear.  if it does... may the gods below help us all");
				  mvAsciiStringET.setText("This shouldn't appear.  if it does... may the gods below help us all");
			  }
			//mvBinStringET.setText(s);
		}
		
	}
	

}
