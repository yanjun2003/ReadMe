package com.yanjun.nfc_wifi.Ndef;



public class TextMimeRecordEncoder implements RecordEncoder {

	@Override
	public boolean canEncode(Record record) {
		return record instanceof TextMimeRecord;
	}

	@Override
	public NdefRecord encodeRecord(Record record, NdefMessageEncoder messageEncoder) {
		TextMimeRecord textMimeRecord = (TextMimeRecord)record;
		return new NdefRecord(NdefConstants.TNF_MIME_MEDIA, textMimeRecord.getContentType().getBytes(), record.getId(),
				textMimeRecord.getContent().getBytes());
	}
}
