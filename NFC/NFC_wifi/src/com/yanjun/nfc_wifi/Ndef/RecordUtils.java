package com.yanjun.nfc_wifi.Ndef;



public class RecordUtils {

	public static boolean equalsTarget(GenericControlRecord gcRecord, String targetNameOrUri) {
		if (gcRecord.getTarget().getTargetIdentifier() instanceof TextRecord) {
			return targetNameOrUri.equals(((TextRecord)gcRecord.getTarget().getTargetIdentifier()).getText());
		}
		else if (gcRecord.getTarget().getTargetIdentifier() instanceof UriRecord) {
			return targetNameOrUri.equals(((UriRecord)gcRecord.getTarget().getTargetIdentifier()).getUri());
		}
		else
			return false;
	}

	public static boolean equalsAction(GenericControlRecord gcRecord, String actionName) {
		GcActionRecord actionRecord = gcRecord.getAction();

		if (actionRecord.hasActionRecord() && actionRecord.getActionRecord() instanceof TextRecord) {
			return actionName.equals(((TextRecord)actionRecord.getActionRecord()).getText());
		}
		else
			return false;
	}

	public static boolean equalsAction(GenericControlRecord gcRecord, Action action) {
		GcActionRecord actionRecord = gcRecord.getAction();
		return (actionRecord.hasAction() && actionRecord.getAction().equals(action));
	}

	public static boolean hasRecordByKey(GcDataRecord dataRecord, String key) {
		for (Record record : dataRecord.getRecords()) {
			if (key.equals(record.getKey()))
				return true;
		}
		return false;
	}

	@SuppressWarnings("unchecked")
	public static <T extends Record> T getRecordByKey(GcDataRecord dataRecord, String key) {
		for (Record record : dataRecord.getRecords()) {
			if (key.equals(record.getKey()))
				return (T)record;
		}
		throw new IllegalArgumentException("record with the given key not found");
	}
}
