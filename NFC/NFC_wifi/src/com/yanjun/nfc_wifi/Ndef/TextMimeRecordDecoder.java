package com.yanjun.nfc_wifi.Ndef;



public class TextMimeRecordDecoder extends AbstractRecordDecoder<TextMimeRecord> {

	public TextMimeRecordDecoder() {
		super(new byte[0]);
	}

	@Override
	public boolean canDecode(NdefRecord ndefRecord) {
		return new String(ndefRecord.getType()).startsWith("text/");
	}

	@Override
	public TextMimeRecord decodeRecord(NdefRecord ndefRecord, NdefMessageDecoder messageDecoder) {
		TextMimeRecord textMimeRecord = new TextMimeRecord(new String(ndefRecord.getType()), new String(
				ndefRecord.getPayload()));
		setIdOnRecord(ndefRecord, textMimeRecord);
		return textMimeRecord;
	}
}
