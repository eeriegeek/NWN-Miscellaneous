listnwns.cpp README
===================

Simple command line tool to list NWN 1 & 2 servers using the web service
developed by Skywing as a replacement for legacy gamespy support. This tool
calls the GetOnlineServerList, LookupServerByName, and LookupServerByAddress
web service methods.


Requirements:
-------------

* ssl - usually installed with a base OS install
* gsoap - may be optained under Fedora Core with "yum install gsoap gsoap-devel"


Building:
---------

Must run the gSOAP stub compilers as shown below and compile with g++.

	wsdl2h -s -o nwnwm.h \
		http://api.mst.valhallalegends.com/NWNMasterServerAPI/NWNMasterServerAPI.svc?wsdl
	soapcpp2 -i nwnwm.h
	g++ listnwns.cpp \
		soapC.cpp soapBasicHttpBinding_USCOREINWNMasterServerAPIProxy.cpp \
		-o listnwns -lgsoap++ -lgsoapck++ -lgsoapssl++ -lssl


Usage:
------

List all known servers for the given version/product (i.e. NWN1 or NWN2.)

	listnwns NWN1|NWN2

List known servers with the given NWN version and NWN server name (not DNS!)

	listnwns NWN1|NWN2 <servername>

List the unique server with the given NWN version and IP address:port.

	listnwns NWN1|NWN2 <ipaddress:port>


License:
--------

Copyright 2012 eerigeek - Licensed under http://opensource.org/licenses/MIT

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

