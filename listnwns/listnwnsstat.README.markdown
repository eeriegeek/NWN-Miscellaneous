listnwnsstat.cpp README
=======================

CGI program to generate an NWN server status. The status message is in the form
of an HTML fragment targeted for embedding in an IFRAME. The query string is
parsed for Product (NWN1/2) and ServerName. The CGI calls Skywing's substitute
master server via the LookupServerByName web service method.

Requirements:
-------------

SSL - Usually installed with the base OS install.

gSOAP - May be obtained through the usual package installs on some systems.
For example on Fedora Core try "yum install gsoap gsoap-devel".  Otherwise,
the gSOAP source can be downloaded from http://sourceforge.net/projects/gsoap2/.
The lister has been successfully build using gSOAP version 2.8.3, there is
currently an unresolved problem with some later versions such as 2.8.12.

Building:
---------

Run the gSOAP stub compilers as shown below, then compile with g++.

	wsdl2h -s -o nwnwm.h \
		http://api.mst.valhallalegends.com/NWNMasterServerAPI/NWNMasterServerAPI.svc?wsdl

	soapcpp2 -i nwnwm.h

	g++ listnwnsstat.cpp \
		soapC.cpp soapBasicHttpBinding_USCOREINWNMasterServerAPIProxy.cpp \
		-o listnwnsstat.cgi -lgsoap++ -lgsoapck++ -lgsoapssl++ -lssl

Installation:
-------------

The CGI programs need to be placed in the web server's cgi-bin directory
or otherwise configured to run as CGI programs. The generated HTML looks
for its CSS file "/css/" relative to the website root path. Some paths may
need adjustment depending on the web server configuration.

	cp listnwnsstat.cgi $WEB_HOME/cgi-bin
	cp listnwnsstat.css $WEB_HOME/html/css

Usage:
------

This CGI program is intended to be invoke through an IFRAME. A server status
as HTML with styled DIV tags is returned with basic fields such as server name
and IP and the number of active players.

	<IFRAME
	name="iframe"
	src="http://some.somenwnserver.net/listnwnsstat.cgi?Product=NWN1&ServerName=My+Dungeon)"
	width=256 height=128 marginwidth=0 marginheight=0 hspace=0 vspace=0
	frameborder=1 scrolling=auto>
	</IFRAME>

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

