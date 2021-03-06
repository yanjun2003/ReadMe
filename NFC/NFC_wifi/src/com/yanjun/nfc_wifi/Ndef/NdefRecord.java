/**
 * Copyright 2011 Adrian Stabiszewski, as@nfctools.org
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.yanjun.nfc_wifi.Ndef;

public class NdefRecord {

	private short tnf;
	private byte[] type;
	private byte[] id;
	private byte[] payload;

	public NdefRecord(short tnf, byte[] type, byte[] id, byte[] payload) {
		this.tnf = tnf;
		this.type = type;
		this.id = id;
		this.payload = payload;
	}

	public short getTnf() {
		return tnf;
	}

	public byte[] getType() {
		return type;
	}

	public byte[] getId() {
		return id;
	}

	public byte[] getPayload() {
		return payload;
	}

}
