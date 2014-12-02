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

import junit.framework.Test;
import junit.framework.TestCase;
import junit.framework.TestSuite;

import org.cybergarage.round.Error;

/**
 * Unit test for simple App.
 */
public class MessageTest 
    extends TestCase
{
    /**
     * Create the test case
     *
     * @param testName name of the test case
     */
    public MessageTest( String testName )
    {
        super( testName );
    }

    /**
     * @return the suite of tests being tested
     */
    public static Test suite()
    {
        return new TestSuite( MessageTest.class );
    }

    protected void setUp() throws Exception {
    }
    
    public void testMessageMethods() throws Exception {
    	Message msg = new Message();
    
    	assertTrue(msg.getVersion() != null);

    	String TEST_METHOD = "hello";
    	assertEquals(msg.getMethod(), null);
    	assertTrue(msg.setMethod(TEST_METHOD));
    	assertEquals(msg.getMethod(), TEST_METHOD);

    	String TEST_PARAMS = "{\"value\":1}";
    	assertEquals(msg.getParams(), null);
    	assertTrue(msg.setParams(TEST_PARAMS));
    	assertEquals(msg.getParams(), TEST_PARAMS);

    	String TEST_ID = "12345";
    	assertEquals(msg.getId(), null);
    	assertTrue(msg.setId(TEST_ID));
    	assertEquals(msg.getId(), TEST_ID);

    	String TEST_RESULT = "{\"value\":1}";
    	assertEquals(msg.getResult(), null);
    	assertTrue(msg.setResult(TEST_RESULT));
    	assertEquals(msg.getParams(), TEST_RESULT);
    	  
    	Error TEST_ERROR = new Error(12345, "12345");
    	assertEquals(msg.getError(), null);
    	assertTrue(msg.setError(TEST_ERROR));
    	assertTrue(TEST_ERROR.equals(msg.getError()));
    	  
    	// Check again not to orverride.
    	  
    	assertEquals(msg.getMethod(), TEST_METHOD);
    	assertEquals(msg.getParams(), TEST_PARAMS);
    	assertEquals(msg.getId(), TEST_ID);
    	assertEquals(msg.getParams(), TEST_RESULT);
    	assertTrue(TEST_ERROR.equals(msg.getError()));
    }
}
