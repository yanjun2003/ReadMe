package com.yanjun.nfc_wifi.Ndef;

import java.util.ArrayList;
import java.util.List;



public class GenericControlRecordEncoder implements RecordEncoder {

	@Override
	public boolean canEncode(Record record) {
		return record instanceof GenericControlRecord;
	}

	@Override
	public NdefRecord encodeRecord(Record record, NdefMessageEncoder messageEncoder) {

		GenericControlRecord myRecord = (GenericControlRecord)record;

		List<Record> records = new ArrayList<Record>();

		records.add(myRecord.getTarget());

		if (myRecord.getAction() != null)
			records.add(myRecord.getAction());
		if (myRecord.getData() != null)
			records.add(myRecord.getData());

		byte[] subPayload = messageEncoder.encode(records);

		byte[] payload = new byte[subPayload.length + 1];
		payload[0] = myRecord.getConfigurationByte();
		System.arraycopy(subPayload, 0, payload, 1, subPayload.length);

		return new NdefRecord(NdefConstants.TNF_WELL_KNOWN, GenericControlRecord.TYPE, record.getId(), payload);
	}

}
