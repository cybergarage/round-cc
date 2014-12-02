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

import java.net.InetAddress;

public class Node
{
	private InetAddress host;
	
	public Node(InetAddress host) {
		this.host = host;
	}
	
	public InetAddress getHost() {
		return host;
	}

	public boolean postMessage() {
		return false;
	}
}
