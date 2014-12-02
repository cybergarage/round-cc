/******************************************************************
*
* Round for Java
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

package org.cybergarage.round.node;

import org.json.*;
import org.cybergarage.round.Error;

public class Message extends JSONObject
{
	public static final String VERSION = "2.0";
	public static final String JSONRPC = "jsonrpc";
	public static final String METHOD = "method";
	public static final String ID = "id";
	public static final String PARAMS = "params";
	public static final String RESULT = "result";
	public static final String ERROR = "error";
	public static final String CODE = "code";
	public static final String MESSAGE = "message";	
	
	public Message() {
		set(JSONRPC, JSONRPC);
	}

	public String getVersion() {
		return getStr(VERSION);
	}
	
	public boolean setMethod(String value) {
		return set(METHOD, value);
	}

	public String getMethod() {
		return getStr(METHOD);
	}
	
	public boolean setId(String value) {
		return set(ID, value);
	}

	public String getId() {
		return getStr(ID);
	}
	
	public boolean setParams(String value) {
		return set(PARAMS, value);
	}

	public String getParams() {
		return getStr(PARAMS);
	}
	
	public boolean setResult(String value) {
		return set(RESULT, value);
	}

	public String getResult() {
		return getStr(RESULT);
	}
	
	public boolean setError(Error err) {
		JSONObject error = new JSONObject();
		try {
			error.put(CODE, err.getCode());
			error.put(MESSAGE, err.getMessage());
			put(ERROR, error);
		}
		catch (JSONException e) {
			return false;
		}
		
		return true;
	}
	
	public Error getError() {
		int errorCode = 0;
		String errorMsg = "";
		try {
			JSONObject error = getJSONObject(ERROR);
			if (error == null)
				return null;
			errorCode = error.getInt(CODE);
			errorMsg = error.getString(MESSAGE);
		}
		catch (JSONException e) {
			return null;
		}
		
		return new Error(errorCode, errorMsg);
	}
	
	private boolean set(String key, String value) {
		try {
			put(key, value);
		}
		catch (JSONException e) {
			return false;
		}
		return true;
	}

	private String getStr(String key) {
		try {
			return getString(key);
		}
		catch (JSONException e) {
			return null;
		}
	}
}
