package com.example.student.exception;

public class ScanResult {
	String ssid;
	String mac;
	int level;

	public ScanResult() {
	}

	public ScanResult(String ssid, String mac, int level) {
		this.ssid = ssid;
		this.mac = mac;
		this.level = level;
	}
}