/******************************************************************
*
* Round for Java
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

package org.cybergarage.round;

public class Error
{
	private int code;
	private String message;
	
	public Error(int code, String message) {
		this.code = code;
		this.message = message;
	}

	public int getCode() {
		return this.code;
	}

	public String getMessage() {
		return this.message;
	}
	
	public boolean equals(Error err) {
		if (err.getCode() != this.code)
			return false;
		String errorMsg = err.getMessage();
		if ((errorMsg == null) && (this.message == null))
			return false;
		return errorMsg.equals(this.message);
	}
}
