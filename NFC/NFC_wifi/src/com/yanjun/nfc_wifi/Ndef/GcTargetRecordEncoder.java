package com.yanjun.nfc_wifi.Ndef;




public class GcTargetRecordEncoder implements RecordEncoder {

	@Override
	public boolean canEncode(Record record) {
		return record instanceof GcTargetRecord;
	}

	@Override
	public NdefRecord encodeRecord(Record record, NdefMessageEncoder messageEncoder) {
		byte[] payload = messageEncoder.encodeSingle(((GcTargetRecord)record).getTargetIdentifier());
		return new NdefRecord(NdefConstants.TNF_WELL_KNOWN, GcTargetRecord.TYPE, record.getId(), payload);
	}
}
