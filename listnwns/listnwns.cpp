//-----------------------------------------------------------------------------
// listnwns.cpp - List active NWN servers
//
// See the README file "listnwns.README.markdown" for further details.
//
// Copyright 2012-2013 eeriegeek - License: http://opensource.org/licenses/MIT
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//-----------------------------------------------------------------------------

#include "WSHttpBinding_USCOREINWNMasterServerAPI.nsmap"
#include "soapWSHttpBinding_USCOREINWNMasterServerAPIProxy.h"

void print_usage(const char* pname)
{
	fprintf(stderr,"usage: %s NWN1|NWN2 <servername|ipaddress:port>\n",pname);
}

void print_header()
{
	fprintf(stderr,"Row  Prod  O                        ServerName       IP_Address:Port"
		"                ModuleName  ACT/MAX  L  P   Bld  X      Last Heartbeat (GMT)\n");
	fprintf(stderr,"---  ----  -  --------------------------------  --------------------"
		"  ------------------------  -------  -  -  ----  -  ------------------------\n");
}

void print_ith_row( ns4__NWGameServer* p, int i )
{
	printf( "%3u  %4.4s  %1u  %32.32s  %20.20s  %24.24s  %3u %3u  %1u  %1u  %4.4u  %1.1u  %s",
		i,
		p->Product, *(p->Online), p->ServerName, p->ServerAddress, p->ModuleName,
		*(p->ActivePlayerCount), *(p->MaximumPlayerCount), *(p->LocalVault), *(p->PrivateServer),
		*(p->BuildNumber), *(p->ExpansionsMask),
		asctime(gmtime((p->LastHeartbeat)))
	);
}

int main(int argc, char* argv[])
{

	if ( (argc < 2) || (argc > 3) ) { print_usage(argv[0]); return 1; }
	if ( ! ( (strcmp("NWN1",argv[1])==0) || (strcmp("NWN2",argv[1])==0) ) ) { print_usage(argv[0]); return 1; }

	WSHttpBinding_USCOREINWNMasterServerAPIProxy s;
	s.soap_endpoint = "http://api.mst.valhallalegends.com/NWNMasterServerAPI/NWNMasterServerAPI.svc/ASMX";

	if ( argc == 2 ) {
		//fprintf(stderr,"Listing Servers for [%s]\n",argv[1]);

		struct _ns1__GetOnlineServerList* gosl          = new _ns1__GetOnlineServerList;
		struct _ns1__GetOnlineServerListResponse* goslr = new _ns1__GetOnlineServerListResponse;
		gosl->Product = (char*)malloc(strlen(argv[1])+1); strcpy(gosl->Product,argv[1]);
		int r = s.GetOnlineServerList(gosl,goslr);

		if ( r == SOAP_OK ) {
			if ( goslr->GetOnlineServerListResult ) {
				print_header();
				int n = goslr->GetOnlineServerListResult->__sizeNWGameServer;
				for ( int i = 0; i < n; i++ ) {
					ns4__NWGameServer* p = goslr->GetOnlineServerListResult->NWGameServer[i];
					print_ith_row(p,i);
				}
			}
		} else {
			s.soap_stream_fault(std::cerr);
		}
		free(gosl->Product);
		delete goslr;
		delete gosl;

	} else { // if ( argc == 3 )

		if ( strspn(argv[2],"1234567890") > 0 ) { // starts with a number 
			//fprintf(stderr,"Searching for Product [%s], Server Address [%s]\n",argv[1],argv[2]);

			struct _ns1__LookupServerByAddress* lsba          = new _ns1__LookupServerByAddress;
			struct _ns1__LookupServerByAddressResponse* lsbar = new _ns1__LookupServerByAddressResponse;
			lsba->Product = (char*)malloc(strlen(argv[1])+1);
			strcpy(lsba->Product,argv[1]);
			lsba->ServerAddress = (char*)malloc(strlen(argv[2])+1);
			strcpy(lsba->ServerAddress,argv[2]);

			if ( s.LookupServerByAddress(lsba,lsbar) == SOAP_OK ) {
				if ( lsbar->LookupServerByAddressResult ) {
					print_header();
					ns4__NWGameServer* p = lsbar->LookupServerByAddressResult;
					print_ith_row(p,0);
				}
			} else {
				s.soap_stream_fault(std::cerr);
			}
			free(lsba->Product);
			free(lsba->ServerAddress);
			delete lsbar;
			delete lsba;

		} else { // starts with not a number
			//fprintf(stderr,"Searching for Product [%s], Server Name [%s]\n",argv[1],argv[2]);

			struct _ns1__LookupServerByName* lsbn          = new _ns1__LookupServerByName;
			struct _ns1__LookupServerByNameResponse* lsbnr = new _ns1__LookupServerByNameResponse;
			lsbn->Product = (char*)malloc(strlen(argv[1])+1);
			strcpy(lsbn->Product,argv[1]);
			lsbn->ServerName = (char*)malloc(strlen(argv[2])+1);
			strcpy(lsbn->ServerName,argv[2]);

			if ( s.LookupServerByName(lsbn,lsbnr) == SOAP_OK ) {
				if ( lsbnr->LookupServerByNameResult ) {
					int n = lsbnr->LookupServerByNameResult->__sizeNWGameServer;
					print_header();
					for ( int i = 0; i < n; i++ ) {
						ns4__NWGameServer* p = lsbnr->LookupServerByNameResult->NWGameServer[i];
						print_ith_row(p,i);
					}
				}
			} else {
				s.soap_stream_fault(std::cerr);
			}
			free(lsbn->Product);
			free(lsbn->ServerName);
			delete lsbnr;
			delete lsbn;

		}

	}

	s.destroy();

	return 0;
} 

