package com.yanjun.nfc_wifi.Ndef;

import java.util.List;


public class GcDataRecordDecoder extends AbstractRecordDecoder<GcDataRecord> {

	public GcDataRecordDecoder() {
		super(GcDataRecord.TYPE);
	}

	@Override
	public GcDataRecord decodeRecord(NdefRecord ndefRecord, NdefMessageDecoder messageDecoder) {
		GcDataRecord dataRecord = new GcDataRecord();

		List<Record> records = messageDecoder.decodeToRecords(ndefRecord.getPayload());
		for (Record record : records) {
			dataRecord.add(record);
		}
		setIdOnRecord(ndefRecord, dataRecord);
		return dataRecord;
	}
}
