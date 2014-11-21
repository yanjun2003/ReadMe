package com.yanjun.ascilltobin.gui;

import android.annotation.SuppressLint;
import android.app.AlertDialog;
import android.app.Dialog;
import android.app.DialogFragment;
import android.content.DialogInterface;
import android.os.Bundle;

@SuppressLint("NewApi")
public class CustomDialog extends DialogFragment{
	private String dialogMessage = "Good gravy, can you see me?!  We're doomed!";
	
	public void setDialogMessage(String s){
		dialogMessage = s;
	}
	public String getDialogMessage(){
		return dialogMessage;
	}
	
	 @Override
	    public Dialog onCreateDialog(Bundle savedInstanceState) {
	        // Use the Builder class for convenient dialog construction
	        AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
	        builder.setMessage("That b")
	               .setPositiveButton(android.R.string.ok, new DialogInterface.OnClickListener() {
	                   public void onClick(DialogInterface dialog, int id) {
	                       // FIRE ZE MISSILES!
	                   }
	               })
	               .setNegativeButton("Also ok", new DialogInterface.OnClickListener() {
	                   public void onClick(DialogInterface dialog, int id) {
	                       // User cancelled the dialog
	                   }
	               });
	        // Create the AlertDialog object and return it
	        return builder.create();
	    }
}
