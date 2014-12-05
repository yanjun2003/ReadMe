package com.yanjun.nfc_wifi.Ndef;



public class GcDataRecordEncoder implements RecordEncoder {

	@Override
	public boolean canEncode(Record record) {
		return record instanceof GcDataRecord;
	}

	@Override
	public NdefRecord encodeRecord(Record record, NdefMessageEncoder messageEncoder) {
		GcDataRecord dataRecord = (GcDataRecord)record;
		byte[] payload = messageEncoder.encode(dataRecord.getRecords());
		return new NdefRecord(NdefConstants.TNF_WELL_KNOWN, GcDataRecord.TYPE, record.getId(), payload);
	}
}
