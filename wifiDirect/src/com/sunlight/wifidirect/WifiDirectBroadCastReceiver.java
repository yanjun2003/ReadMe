package com.sunlight.wifidirect;

import java.util.ArrayList;
import java.util.List;


import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.net.NetworkInfo;
import android.net.wifi.p2p.WifiP2pDevice;
import android.net.wifi.p2p.WifiP2pDeviceList;
import android.net.wifi.p2p.WifiP2pManager;
import android.net.wifi.p2p.WifiP2pManager.Channel;
import android.net.wifi.p2p.WifiP2pManager.ConnectionInfoListener;
import android.net.wifi.p2p.WifiP2pManager.PeerListListener;
import android.util.Log;
import android.widget.Toast;


@SuppressWarnings("unused")
public class WifiDirectBroadCastReceiver extends BroadcastReceiver {
    private  final String TAG = "BroadCasterChange";
	private WifiP2pManager manager;
    private Channel channel;
	private  MainActivity activity;

	
	
    public WifiDirectBroadCastReceiver(WifiP2pManager manager, Channel channel,MainActivity activity) {
        super();
        this.manager = manager;
        this.channel = channel;
        this.activity = activity;
    }
    private void StartScanWifiPoint(){
    	  manager.discoverPeers(channel, new WifiP2pManager.ActionListener() {
              @Override
              public void onSuccess() {
               //   Toast.makeText(this, "Discovery Initiated",
                 //         Toast.LENGTH_SHORT).show();
            	  Log.i(TAG,"discover  success.......");
              }

              @Override
              public void onFailure(int reasonCode) {
               //   Toast.makeText(this, "Discovery Failed : " + reasonCode,
                    //      Toast.LENGTH_SHORT).show();
            	  Log.i(TAG,"discover  fail......");
              }
          });
    }
	@Override
	public void onReceive(Context context, Intent intent) {
        String action = intent.getAction();
        if (WifiP2pManager.WIFI_P2P_STATE_CHANGED_ACTION.equals(action)) {
        	Log.i(TAG,"1..WIFI_P2P_STATE_CHANGED_ACTION");
            //判断wifi 点对点功能是否开启
            int state = intent.getIntExtra(WifiP2pManager.EXTRA_WIFI_STATE, -1);
            Log.d(TAG, "P2P state changed  to" + state);
            if (state == WifiP2pManager.WIFI_P2P_STATE_ENABLED) {
                Log.i(TAG, "wifi p2p state enable,wifi p2p enabled");
                activity.showStatus(true);
            } else {
                Log.i(TAG, "wifi p2p state disable,wifi p2p disable");
                activity.showStatus(false);
            }
            
        } else if (WifiP2pManager.WIFI_P2P_PEERS_CHANGED_ACTION.equals(action)) {
        	Log.i(TAG,"2..WIFI_P2P_PEERS_CHANGED_ACTION");
            if (manager != null) {
            	  manager.requestPeers(channel, activity.mP2pListener);
            }
        } else if (WifiP2pManager.WIFI_P2P_CONNECTION_CHANGED_ACTION.equals(action)) {
        	Log.i(TAG,"3..WIFI_P2P_CONNECTION_CHANGED_ACTION");
            if (manager == null) {
                return;
            }
            Log.i(TAG, "WIFI_P2P_CONNECTION_CHANGED_ACTION happened");
            NetworkInfo networkInfo = (NetworkInfo) intent
                    .getParcelableExtra(WifiP2pManager.EXTRA_NETWORK_INFO);
            
            if (networkInfo.isConnected()) {
                Log.d(TAG,
                        "Connected to p2p network. Requesting network details");
                manager.requestConnectionInfo(channel,
                        (ConnectionInfoListener) activity);
            } else {
            	manager.requestPeers(channel, activity.mP2pListener);
            }
        } else if (WifiP2pManager.WIFI_P2P_THIS_DEVICE_CHANGED_ACTION.equals(action)) {
        	Log.i(TAG,"4..WIFI_P2P_THIS_DEVICE_CHANGED_ACTION");
            //开始搜索wifi peer to peer 热点
            StartScanWifiPoint();
            manager.requestPeers(channel, activity.mP2pListener);
        }
    }


}
