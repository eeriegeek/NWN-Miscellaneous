README
======

The program nwn1gcp.exe is a simple helper filter to allow NWN to
be launched from a URI (from a bookmark or html page). It's single
purpose is to convert protocol qualified URIs of the form:

	 nwn1gcp:<connect_string>

to a correct command line capable of launching the NWN application
with the +connect command line option. URIs for protocol nwn1gcp
are expected in one of the forms as the single command argument:

	nwn1gcp:127.0.0.1:5121
	nwn1gcp:nwn.example.com:5121

These examples will be transformed to a command line and executed as:

	C:\Games\NWN1\nwmain.exe +connect 127.0.0.1:5121
	C:\Games\NWN1\nwmain.exe +connect nwn.example.com:5121

In general, any valid IP address or DNS name should work. The port
specification is optional if the server is running on the default
port of 5121.

Files:
------

	nwn1gcp.txt   - This README file
	nwn1gcp.c     - C source for URI launcher
	nwn1gcp.rc    - Launcher resource file
	nwn1gcp.ico   - Launcher icon
	nwn1gcp.reg   - Launcher registry entries
	nwn1gcp.exe   - Compiled URI launcher

Building:
---------
If you wish to build the .exe from source, this is an example using MingGW:

	set path=C:\Software\MinGW\bin;%path%
	windres nwn1gcp.rc -O coff -o nwn1gcp.res
	cc -Wall -Wextra -O2 -o nwn1gcp.exe nwn1gcp.c nwn1gcp.res

Installation:
-------------

1) Unpack nwn1gcp_vNNN.zip in the NWN main directory (where nwmain.exe resides.)
2) Edit the nwn1gcp.reg file changing the path on the last line to reflect the
full path to the nwn1gcp.exe file in the NWN main directory.
3) Load (merge) the nwn1gcp.reg file (right click - merge) into the registry.
4) Test a URL in your browser such as: nwn1gcp:127.0.0.1:5121, NWN should launch

Uninstalling:
-------------

1) Change to the NWN main directory, and delete all nwn1gcp.* files.
2) Run regedit and expand HKEY_CLASSES_ROOT tree, select nwn1gcp and delete it.

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

