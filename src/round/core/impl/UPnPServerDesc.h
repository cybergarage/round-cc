/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_UPNPSERVER_DESC_H_
#define _ROUNDCC_UPNPSERVER_DESC_H_

namespace Round {

static const std::string FRACTAL_NODESERVER_DEVICE_DESCRIPTION =
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
"<root xmlns=\"urn:schemas-upnp-org:device-1-0\">\n"
"   <specVersion>\n"
"     <major>1</major>\n"
"     <minor>0</minor>\n"
"   </specVersion>\n"
"   <device>\n"
"     <deviceType>urn:cybergarage-org:device:round:1</deviceType>\n"
"     <friendlyName>Round</friendlyName>\n"
"     <manufacturer>CyberGarage</manufacturer>\n"
"     <manufacturerURL>http://www.cybergarage.org</manufacturerURL>\n"
"     <modelDescription>Round Server</modelDescription>\n"
"     <modelName>Round</modelName>\n"
"     <modelNumber>1.0</modelNumber>\n"
"     <modelURL>http://www.cybergarage.org</modelURL>\n"
"     <serviceList>\n"
"       <service>\n"
"         <serviceType>urn:cybergarage-org:service:round:1</serviceType>\n"
"         <serviceId>urn:cybergarage-org:serviceId:node:1</serviceId>\n"
"         <SCPDURL>/service/node/description.xml</SCPDURL>\n"
"         <controlURL>/service/node/control</controlURL>\n"
"         <eventSubURL>/service/node/eventSub</eventSubURL>\n"
"       </service>\n"
"     </serviceList>\n"
"     <presentationURL>/presentation</presentationURL>\n"
"  </device>\n"
"</root>\n"
"";

static const std::string FRACTAL_NODESERVER_SERVICE_NODE_DESCRIPTION =
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
"<scpd xmlns=\"urn:schemas-upnp-org:service-1-0\">\n"
"   <specVersion>\n"
"     <major>1</major>\n"
"     <minor>0</minor>\n"
"   </specVersion>\n"
"   <actionList>\n"
"     <action>\n"
"       <name>GetStatus</name>\n"
"       <argumentList>\n"
"         <argument>\n"
"           <name>Version</name>\n"
"           <relatedStateVariable>Version</relatedStateVariable>\n"
"           <direction>out</direction>\n"
"         </argument>\n"
"       </argumentList>\n"
"     </action>\n"
"   </actionList>\n"
"   <serviceStateTable>\n"
"     <stateVariable sendEvents=\"no\">\n"
"       <name>Version</name>\n"
"       <dataType>string</dataType>\n"
"     </stateVariable>\n"
"   </serviceStateTable>\n"
"</scpd>\n"
"";

}

#endif
