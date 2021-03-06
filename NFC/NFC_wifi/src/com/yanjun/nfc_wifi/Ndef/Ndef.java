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



/**
 * Simple entry class for getting the different encoders and decoders. If used in a dependency injection container the
 * encoders/decoders can be injected directly via @Inject. This class won't be needed then.
 * 
 */
public class Ndef {

	private static NdefRecordEncoder ndefRecordEncoder = new NdefRecordEncoder();
	private static NdefRecordDecoder ndefRecordDecoder = new NdefRecordDecoder();
	private static NdefMessageEncoder ndefMessageEncoder = new NdefMessageEncoder(ndefRecordEncoder);
	private static NdefMessageDecoder ndefMessageDecoder = new NdefMessageDecoder(ndefRecordDecoder);

	static {
		ndefRecordDecoder.addRecordDecoder(new SmartPosterDecoder());
		ndefRecordDecoder.addRecordDecoder(new TextRecordDecoder());
		ndefRecordDecoder.addRecordDecoder(new UriRecordDecoder());
		ndefRecordDecoder.addRecordDecoder(new ActionRecordDecoder());
		ndefRecordDecoder.addRecordDecoder(new GenericControlRecordDecoder());
		ndefRecordDecoder.addRecordDecoder(new GcTargetRecordDecoder());
		ndefRecordDecoder.addRecordDecoder(new GcActionRecordDecoder());
		ndefRecordDecoder.addRecordDecoder(new GcDataRecordDecoder());
		ndefRecordDecoder.addRecordDecoder(new TextMimeRecordDecoder());

		ndefRecordEncoder.addRecordEncoder(new SmartPosterRecordEncoder());
		ndefRecordEncoder.addRecordEncoder(new TextRecordEncoder());
		ndefRecordEncoder.addRecordEncoder(new UriRecordEncoder());
		ndefRecordEncoder.addRecordEncoder(new ActionRecordEncoder());
		ndefRecordEncoder.addRecordEncoder(new GenericControlRecordEncoder());
		ndefRecordEncoder.addRecordEncoder(new GcTargetRecordEncoder());
		ndefRecordEncoder.addRecordEncoder(new GcActionRecordEncoder());
		ndefRecordEncoder.addRecordEncoder(new GcDataRecordEncoder());
		ndefRecordEncoder.addRecordEncoder(new TextMimeRecordEncoder());
	}

	public static NdefRecordDecoder getNdefRecordDecoder() {
		return ndefRecordDecoder;
	}

	public static NdefRecordEncoder getNdefRecordEncoder() {
		return ndefRecordEncoder;
	}

	public static NdefMessageDecoder getNdefMessageDecoder() {
		return ndefMessageDecoder;
	}

	public static NdefMessageEncoder getNdefMessageEncoder() {
		return ndefMessageEncoder;
	}
}
