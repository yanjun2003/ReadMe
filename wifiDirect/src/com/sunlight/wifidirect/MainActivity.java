package com.sunlight.wifidirect;

import java.util.ArrayList;
import java.util.List;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.IntentFilter;
import android.net.wifi.WpsInfo;
import android.net.wifi.p2p.WifiP2pConfig;
import android.net.wifi.p2p.WifiP2pDevice;
import android.net.wifi.p2p.WifiP2pDeviceList;
import android.net.wifi.p2p.WifiP2pManager;
import android.net.wifi.p2p.WifiP2pManager.ActionListener;
import android.net.wifi.p2p.WifiP2pManager.Channel;
import android.net.wifi.p2p.WifiP2pManager.PeerListListener;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.View.OnClickListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.TextView;


import com.sunlight.wifidirect.R;

public class MainActivity extends Activity {
 	private static final String TAG ="MainScreen";
 	private LinearLayout connnectLL, sendLL;
    private EditText sendText;
    private Button sendBtn;
 
 	private Button ConnectBtn,DisconnectBtn;
 	private TextView statusTextView;
 
 	private boolean isPointFound =false;
 	boolean p2p_connected;
 
 
    private WifiP2pManager manager;
    private final IntentFilter intentFilter = new IntentFilter();
    private Channel channel;
    private BroadcastReceiver receiver = null;

    private ListView myListView;
	
    private WiFiPeerListAdapter mWiFiPeerListAdapter;
    
    private List<WifiP2pDevice> peers = new ArrayList<WifiP2pDevice>();
    public P2pListener mP2pListener;
    
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		Log.i(TAG,"Main Screen initazation");
		
		
        intentFilter.addAction(WifiP2pManager.WIFI_P2P_STATE_CHANGED_ACTION);
        intentFilter.addAction(WifiP2pManager.WIFI_P2P_PEERS_CHANGED_ACTION);
        intentFilter.addAction(WifiP2pManager.WIFI_P2P_CONNECTION_CHANGED_ACTION);
        intentFilter.addAction(WifiP2pManager.WIFI_P2P_THIS_DEVICE_CHANGED_ACTION);

        manager = (WifiP2pManager) getSystemService(Context.WIFI_P2P_SERVICE);
        channel = manager.initialize(this, getMainLooper(), null);
        
        initViews();
	}

	private void ShowConnectBtn(){
		if(p2p_connected){
			ConnectBtn.setEnabled(false);
			DisconnectBtn.setEnabled(true);
			sendLL.setVisibility(View.VISIBLE);
			statusTextView.setText(MainActivity.this.getResources().getString(R.string.connect_point_success));
		}else{
			ConnectBtn.setEnabled(true);
			DisconnectBtn.setEnabled(false);
			sendLL.setVisibility(View.GONE);
			statusTextView.setText(MainActivity.this.getResources().getString(R.string.connect_point_fail));
		}
	}
	
	private void initViews(){
		connnectLL =(LinearLayout)findViewById(R.id.Buttons);
		HideButtons();
		
		ConnectBtn=(Button)connnectLL.findViewById(R.id.connect);
		DisconnectBtn=(Button)connnectLL.findViewById(R.id.disconnect);
		
		sendLL=(LinearLayout)findViewById(R.id.sendmessage);
		sendLL.setVisibility(View.GONE);
		sendText=(EditText)sendLL.findViewById(R.id.sendinfo);
		sendBtn =(Button)sendLL.findViewById(R.id.sendbtn);
		
		
		
		ConnectBtn.setOnClickListener(MyListener);
		DisconnectBtn.setOnClickListener(MyListener);
		p2p_connected =false;
		DisconnectBtn.setEnabled(false);
		
		statusTextView = (TextView)findViewById(R.id.status);
		
		myListView=(ListView)findViewById(R.id.peer_list);
		mP2pListener = new P2pListener();
		mWiFiPeerListAdapter = new WiFiPeerListAdapter(this, R.layout.row_devices, peers);
		myListView.setAdapter(mWiFiPeerListAdapter);
		
	}
	
	
	public void showStatus(boolean status){
		if(status== true){
			if(isPointFound==true){
				ShowButtons();
			}
			statusTextView.setText(this.getResources().getString(R.string.p2p_switch_on_prompt));
		}else{
			HideButtons();
			statusTextView.setText(this.getResources().getString(R.string.p2p_switch_off_prompt));
		}
	}
	
	@Override
	protected void onResume() {
		super.onResume();
		receiver = new WifiDirectBroadCastReceiver(manager, channel, this);
		registerReceiver(receiver, intentFilter);
	}

	@Override
	protected void onPause() {
		super.onPause();
		unregisterReceiver(receiver);
	}

    private static String connectDeviceName ;
	private   OnClickListener MyListener = new OnClickListener(){

		@Override
		public void onClick(View view) {
			switch(view.getId()){
			case R.id.connect:
				
				WifiP2pConfig config = new WifiP2pConfig();
				WifiP2pDevice device = peers.get(0);	
	            config.deviceAddress = device.deviceAddress;
	            connectDeviceName =device.deviceName;
	            		// new String("6a:df:dd:3f:ff:4c");
	            config.wps.setup = WpsInfo.PBC;
	            statusTextView.setText(MainActivity.this.getResources().getString(R.string.connecting_point)+connectDeviceName);
	            manager.connect(channel, config, new ActionListener(){
					@Override
					public void onSuccess() {
						Log.i(TAG,"connect  peer successful ................");
					}

					@Override
					public void onFailure(int reason) {
						Log.i(TAG,"connect  peer failure ................");
					}});
	           
				break;
			case R.id.disconnect:
				manager.removeGroup(channel, new ActionListener(){

					@Override
					public void onSuccess() {
						p2p_connected=false;
						ShowConnectBtn();
					}

					@Override
					public void onFailure(int reason) {	
					}
					
				});
				break;
			}
		}
		
	};
	
	private void HideButtons(){
		connnectLL.setVisibility(View.GONE);
	}
	
	private void ShowButtons(){
		connnectLL.setVisibility(View.VISIBLE);
		ShowConnectBtn();
	}
	
	private void showFindPoints(){
		isPointFound =true;
		showStatus(true);
	}
	
	private void HideFindPoints(){
		isPointFound =false;
		connnectLL.setVisibility(View.GONE);
		sendLL.setVisibility(View.GONE);
	}
	
    private class WiFiPeerListAdapter extends ArrayAdapter<WifiP2pDevice> {

        private List<WifiP2pDevice> items;

        public WiFiPeerListAdapter(Context context, int textViewResourceId,
                List<WifiP2pDevice> objects) {
            super(context, textViewResourceId, objects);
            items = objects;
        }

        @Override
        public View getView(int position, View convertView, ViewGroup parent) {
            View view = convertView;
            if (view == null) {
                LayoutInflater inflater = (LayoutInflater) getSystemService(
                        Context.LAYOUT_INFLATER_SERVICE);
                view = inflater.inflate(R.layout.row_devices, null);
            }
            WifiP2pDevice device = items.get(position);
            if (device != null) {
                TextView top = (TextView) view.findViewById(R.id.device_name);
                TextView bottom = (TextView) view.findViewById(R.id.device_details);
                if (top != null) {
                    top.setText(device.deviceName);
                }
                if (bottom != null) {
                    bottom.setText(getDeviceStatus(device.status));
                }
            }
            return view;
        }
    }
    
    private  String getDeviceStatus(int deviceStatus) {
        Log.d(TAG, "Peer status :" + deviceStatus);
        switch (deviceStatus) {
            case WifiP2pDevice.AVAILABLE:
              	p2p_connected=false;
            	ShowConnectBtn();
            
                return "Available";
            case WifiP2pDevice.INVITED:
              	p2p_connected=false;
            	ShowConnectBtn();
                return "Invited";
            case WifiP2pDevice.CONNECTED:
            	p2p_connected=true;
				ShowConnectBtn();
                return "Connected";
            case WifiP2pDevice.FAILED:
              	p2p_connected=false;
            	ShowConnectBtn();
                return "Failed";
            case WifiP2pDevice.UNAVAILABLE:
              	p2p_connected=false;
            	ShowConnectBtn();
            	p2p_connected=false;
            	ShowConnectBtn();
                return "Unavailable";
            default:
              	p2p_connected=false;
            	ShowConnectBtn();
                return "Unknown";

        }
    }

   
    
	public  class  P2pListener  implements PeerListListener{
		@Override
		public void onPeersAvailable(WifiP2pDeviceList peerList) {
			 peers.clear();
		     peers.addAll(peerList.getDeviceList());
		     int num= peers.size();
		     Log.i(TAG,"Find "+num+ " wifi peers");
			 mWiFiPeerListAdapter.notifyDataSetChanged();
			 Log.i(TAG,"get the peers infor "+ peerList.toString());
			  if(num >0){
				    statusTextView.setText(MainActivity.this.getResources().getString(R.string.find_point_success));
					p2p_connected=true;
	            	 showFindPoints();
	             }else{
	             	p2p_connected=false;
	             	statusTextView.setText(MainActivity.this.getResources().getString(R.string.find_point_fail));
	             	ShowConnectBtn();
	            	 HideFindPoints();
	             }
		}
		
	}

	
}
