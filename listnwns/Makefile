#
# Makefile
#

CC=g++ 
CXXFLAGS=-Wall -O2
SOAP_INCS='-I/usr/local/share/gsoap/import'
SOAP_LIBS='-L/usr/local/lib'
SOAP_STUBS=soapC.cpp soapWSHttpBinding_USCOREINWNMasterServerAPIProxy.cpp
NWNMS_SOAP_URL='http://api.mst.valhallalegends.com/NWNMasterServerAPI/NWNMasterServerAPI.svc?wsdl'

.PHONY: all
all: listnwns listnwnsstat listnwnshtml

.PHONY: listnwnshtml
listnwnshtml: listnwns2html.cgi

.PHONY: listnwnsstat
listnwnsstat: listnwnsstat.cgi

listnwns2html.cgi: listnwns1html.cgi
	cp -p listnwns1html.cgi listnwns2html.cgi

listnwns1html.cgi: listnwnshtml.cpp $(SOAP_STUBS)
	$(CC) $(CXXFLAGS) listnwnshtml.cpp $(SOAP_INCS) $(SOAP_STUBS) -o listnwns1html.cgi $(SOAP_LIBS) -lgsoap++

listnwnsstat.cgi: listnwnsstat.cpp $(SOAP_STUBS)
	$(CC) $(CXXFLAGS) listnwnsstat.cpp $(SOAP_INCS) $(SOAP_STUBS) -o listnwnsstat.cgi $(SOAP_LIBS) -lgsoap++

listnwns: listnwns.cpp $(SOAP_STUBS)
	$(CC) $(CXXFLAGS) listnwns.cpp $(SOAP_INCS) $(SOAP_STUBS) -o listnwns $(SOAP_LIBS) -lgsoap++

stubs: $(SOAP_STUBS)

soapC.cpp: nwnms.h
	soapcpp2 -1 -i -C -x $(SOAP_INCS) nwnms.h

soapWSHttpBinding_USCOREINWNMasterServerAPIProxy.cpp: nwnms.h
	soapcpp2 -1 -i -C -x $(SOAP_INCS) nwnms.h

nwnms.h:
	wsdl2h -s -o nwnms.h $(NWNMS_SOAP_URL)

.PHONY: distclean
distclean: clean binclean

.PHONY: clean
clean:
	rm -f nwnms.h
	rm -f soapH.h
	rm -f soapC.cpp
	rm -f soapWSHttpBinding_USCOREINWNMasterServerAPIProxy.h	
	rm -f soapWSHttpBinding_USCOREINWNMasterServerAPIProxy.cpp	
	rm -f soapStub.h
	rm -f WSHttpBinding_USCOREINWNMasterServerAPI.nsmap

.PHONY: binclean
binclean:
	rm -f listnwns
	rm -f listnwnsstat.cgi
	rm -f listnwns1html.cgi
	rm -f listnwns2html.cgi

