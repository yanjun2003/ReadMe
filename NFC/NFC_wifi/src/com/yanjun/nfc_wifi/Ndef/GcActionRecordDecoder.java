package com.yanjun.nfc_wifi.Ndef;


public class GcActionRecordDecoder extends AbstractRecordDecoder<GcActionRecord> {

	public GcActionRecordDecoder() {
		super(GcActionRecord.TYPE);
	}

	@Override
	public GcActionRecord decodeRecord(NdefRecord ndefRecord, NdefMessageDecoder messageDecoder) {
		byte actionFlag = ndefRecord.getPayload()[0];

		GcActionRecord actionRecord = null;

		if ((actionFlag & GcActionRecord.NUMERIC_CODE) != 0) {
			Action action = Action.getActionByValue(ndefRecord.getPayload()[1]);
			actionRecord = new GcActionRecord(action);
		}
		else {

			Record record = messageDecoder.decodeToRecord(ndefRecord.getPayload(), 1,
					ndefRecord.getPayload().length - 1);
			actionRecord = new GcActionRecord(record);
		}

		setIdOnRecord(ndefRecord, actionRecord);
		return actionRecord;
	}

}
