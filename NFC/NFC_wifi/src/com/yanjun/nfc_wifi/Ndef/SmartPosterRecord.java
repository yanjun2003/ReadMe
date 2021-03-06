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

public class SmartPosterRecord extends Record {

	public static final byte[] TYPE = { 'S', 'p' };

	private TextRecord title;
	private UriRecord uri;
	private ActionRecord action;

	public TextRecord getTitle() {
		return title;
	}

	public void setTitle(TextRecord title) {
		this.title = title;
	}

	public UriRecord getUri() {
		return uri;
	}

	public void setUri(UriRecord uri) {
		this.uri = uri;
	}

	public ActionRecord getAction() {
		return action;
	}

	public void setAction(ActionRecord action) {
		this.action = action;
	}

	@Override
	public String toString() {
		return "SmartPoster: [" + getTitle() + ", " + getUri() + ", " + getAction() + "]";
	}
}
