package com.yanjun.nfc_wifi.Ndef;


public class GcTargetRecordDecoder extends AbstractRecordDecoder<GcTargetRecord> {

	public GcTargetRecordDecoder() {
		super(GcTargetRecord.TYPE);
	}

	@Override
	public GcTargetRecord decodeRecord(NdefRecord ndefRecord, NdefMessageDecoder messageDecoder) {
		Record record = messageDecoder.decodeToRecord(ndefRecord.getPayload());
		GcTargetRecord targetRecord = new GcTargetRecord(record);
		setIdOnRecord(ndefRecord, targetRecord);
		return targetRecord;
	}

}
