listnwnshtml.cpp README
=======================

CGI program to generate a table of NWN 1 & 2 servers using the web service
developed by Skywing as a substitue for legacy nwmasterserver/gamespy support.
This program calls the GetOnlineServerList web service method.

Requirements:
-------------

SSL - Usually installed with the base OS install.

gSOAP - May be obtained through the usual package installs on some systems.
For example on Fedora Core try "yum install gsoap gsoap-devel".  Otherwise,
the gSOAP source can be downloaded from http://sourceforge.net/projects/gsoap2/.
The lister has been successfully build using gSOAP version 2.8.3, there are
currently known problems with some later versions such as 2.8.12.

Building:
---------

Run the gSOAP stub compilers as shown below, then compile with g++.

	wsdl2h -s -o nwnwm.h \
		http://api.mst.valhallalegends.com/NWNMasterServerAPI/NWNMasterServerAPI.svc?wsdl
	soapcpp2 -i nwnwm.h
	g++ listnwns.cpp \
		soapC.cpp soapBasicHttpBinding_USCOREINWNMasterServerAPIProxy.cpp \
		-o listnwns -lgsoap++ -lgsoapck++ -lgsoapssl++ -lssl
	g++ listnwnshtml.cpp \
		soapC.cpp soapBasicHttpBinding_USCOREINWNMasterServerAPIProxy.cpp \
		-o listnwns1html.cgi -lgsoap++ -lgsoapck++ -lgsoapssl++ -lssl

Installation:
-------------

The CGI programs need to be placed in the web server's cgi-bin directory
or otherwise configured to run as CGI programs. The generated HTML looks
for the CSS file "/css/listnwnshtml.css" installed relative to the website
root path. Some paths may need adjustment depending on the web server
configuration.

	cp listnwns1html.cgi $WEB_HOME/cgi-bin
	ln $WEB_HOME/cgi-bin/listnwns1html.cgi $WEB_HOME/cgi-bin/listnwns2html.cgi
	cp listnwnshtml.css $WEB_HOME/css

Usage:
------

The CGI programs are invoked through a web browser with no arguments required.
The version of NWN listed is determined by the name of the CGI script. A formated
list of NWN servers is constructed as an HTML web page.

	http://some.nwnwebserver.net/cgi-bin/listnwns1html.cgi
	http://some.nwnwebserver.net/cgi-bin/listnwns2html.cgi

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

