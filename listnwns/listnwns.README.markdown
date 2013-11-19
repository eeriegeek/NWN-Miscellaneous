listnwns.cpp README
===================

A simple command line tool for listing currently running  NWN 1 & 2 servers
using the web SOAP service developed by Skywing as a replacement for legacy
gamespy support. This tool calls the GetOnlineServerList, LookupServerByName,
and LookupServerByAddress web service methods from the SOAP service, and
constructs a list of running servers.


Requirements:
-------------

* gSOAP
	The gSOAP toolkit is required to build this tool. The latest version
	used to build and test is gSOAP-2.8.16. The packages may be obtained
	through the OS package tool or built from source. The gSOAP website
	is: http://www.cs.fsu.edu/~engelen/soap.html for source code.


Building:
---------

A basic Makefile is provided. Check the variables set at the top of the file,
especially SOAP_INCS and SOAP_LIBS so the gSOAP installation can be located.
Also make sure the gSOAP bin directory is in your system path before building.

	make listnwns


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

Copyright 2012-2013 eeriegeek - License: http://opensource.org/licenses/MIT

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

