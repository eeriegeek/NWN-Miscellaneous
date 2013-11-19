listnwnsstat.cpp README
=======================

This is a CGI program to display NWN server status on an HTML page. The status
message is in the form of an HTML fragment targeted for embedding in an IFRAME.
The query string is parsed for Product (NWN1/2) and ServerName. The CGI script
calls Skywing's substitute master server LookupServerByName SOAP method.

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

    make listnwnsstat


Installation:
-------------

The CGI programs need to be placed in the web server's cgi-bin directory
or otherwise configured to run as CGI programs. The generated HTML looks
for its CSS file "/css/listnwnsstat.css" relative to the website root path.
Some paths may need adjustment depending on the web server configuration.

	cp listnwnsstat.cgi $WEB_HOME/cgi-bin
	cp listnwnsstat.css $WEB_HOME/html/css


Usage:
------

This CGI program is intended to be invoked through an IFRAME. A server status
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

