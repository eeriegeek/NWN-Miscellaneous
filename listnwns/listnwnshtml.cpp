/******************************************************************************
* listnwnshtml.cpp
*
* See the associated "listnwnshtml.README.*" file for more information.
*
* Copyright 2012 eerigeek - Licensed under http://opensource.org/licenses/MIT
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
******************************************************************************/

#include <string>
using std::string;

#include "soapBasicHttpBinding_USCOREINWNMasterServerAPIProxy.h"
#include "soapBasicHttpBinding_USCOREINWNMasterServerAPIService.h"
#include "BasicHttpBinding_USCOREINWNMasterServerAPI.nsmap"

bool g_is_nwn1 = true;

#define array_length(array)(sizeof(array)/sizeof(array)[0])
struct html_encode_map_struct { string match; string replace; } html_encode_map[] = { {"&","&amp;"}, {"<","&lt;"}, {">","&gt;"} };
string html_encode_special(string const& s)
{
	string rs = s;
	for ( size_t i = 0; i < array_length(html_encode_map); i++ ) {
		const string& match = html_encode_map[i].match;
		const string& repl = html_encode_map[i].replace;
		string::size_type start = rs.find_first_of(match);
		while (start != string::npos) {
	 		rs.replace(start, match.size(), repl);
	 		start = rs.find_first_of(match, start + repl.size());
		}
	}
	return rs;
}

const char* game_type_label[] = {
	"Action", "Story", "Story lite",
	"Role Play", "Team", "Melee",
	"Arena", "Social", "Alternative",
	"PW Action", "PW Story", "Solo",
	"Tech Support"
};

const char* game_pvp_label[] = {
	"None", "Party", "Full"
};

void print_usage(const char* pname)
{
	fprintf(stderr,"usage: %s <argv0 must be listnwns1html.cgi or listnwn2html.cgi>\n",pname);
}

void print_http_header()
{
	printf(
		"Content-Type: text/html\n"
		//"Cache-Control: max-age:60\n"
		"\n"
	);
}

void print_header()
{
	if (g_is_nwn1) {
		printf(
			"<html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
			"<head>\n"
			"<title>NWN1 Server List</title>\n"
			"<link rel=\"stylesheet\" type=\"text/css\" href=\"listnwnshtml.css\" />\n"
			//"<link rel=\"stylesheet\" type=\"text/css\" href=\"/css/listnwnshtml.css\" />\n"
			"</head>\n"
			"<body>\n"
			"<table>\n"
			"<tr>"
			"<th>Row</th>"
			"<th>Server Name</th>"
			"<th>Site URL</th>"
			"<th>Server Address</th>"
			"<th>Game Type</th>"
			"<th>Module Name</th>"
			"<th>Player Count</th><th>Player Limit</th><th>Min Level</th><th>Max Level</th><th>PvP Level</th>"
			"<th>Local Vault</th><th>Private Server</th>"
			"<th>ELC</th><th>ILR</th>"
			"<th>Build</th><th>Exp</th>"
			"<th>Server Description</th>"
			"<th>Module Description</th>"
			"</tr>\n"
		);
	} else {
		printf(
			"<html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
			"<head>\n"
			"<title>NWN2 Server List</title>\n"
			"<link rel=\"stylesheet\" type=\"text/css\" href=\"listnwnshtml.css\" />\n"
			//"<link rel=\"stylesheet\" type=\"text/css\" href=\"/css/listnwnshtml.css\" />\n"
			"</head>\n"
			"<body>\n"
			"<table>\n"
			"<tr>"
			"<th>Row</th>"
			"<th>Server Name</th>"
			"<th>Site URL</th>"
			"<th>Server Address</th>"
			"<th>Game Type</th>"
			"<th>Module Name</th>"
			"<th>Player Count</th><th>Player Limit</th>"
			"<th>Min Level</th><th>Max Level</th><th>PvP Level</th>"
			"<th>Local Vault</th><th>Private Server</th>"
			"<th>ELC</th><th>ILR</th>"
			"<th>Build</th><th>Exp</th>"
			"<th>Server Description</th>"
			"<th>Module Description</th>"
			"<th>PWC URL</th>"
			"</tr>\n"
		);
	}
}

void print_footer()
{
	printf(
		"</table>\n"
		"</body>\n"
		"</html>\n"
	);
}

void print_ith_row( ns4__NWGameServer* p, int i )
{
	char tbuf[32];
	strftime(tbuf,32,"%Y-%m-%d %H:%M:%S",gmtime(p->LastHeartbeat));

    string encServerName        = html_encode_special(p->ServerName);
    string encModuleName        = html_encode_special(p->ModuleName);
    string encServerDescription = html_encode_special(p->ServerDescription);
    string encModuleDescription = html_encode_special(p->ModuleDescription);

	if (g_is_nwn1) {

		char url[256]; url[0] = '\0';
		char* url_b = strstr(p->ServerDescription,"http://");
		if (url_b) {
			size_t url_l = strspn(url_b,"1234567890.:-/_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
			if ( (url_l > 0) && (url_l < 256) ) {
				memcpy(url,url_b,url_l);
				url[url_l] = '\0';
			}
		}
		if (strlen(url) < 1) {
			char* url_b = strstr(p->ModuleDescription,"http://");
			if (url_b) {
				size_t url_l = strspn(url_b,"1234567890.:-/_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
				if ( (url_l > 0) && (url_l < 256) ) {
					memcpy(url,url_b,url_l);
					url[url_l] = '\0';
				}
			}
		}

		printf(
			"<tr>"
			"<td class=\"s_number\">%u</td>"                                 /* Row Count */
			"<td class=\"s_title\">%s</td>"                                  /* ServerName */
			"<td class=\"s_title\"><a href=\"%s\">%s</a></td>"               /* ModuleUrl */
			"<td class=\"s_title\"><a href=\"nwn1gcp:%s\">%s</a></td>"       /* ServerAddress (w/ URL) */
			"<td class=\"s_code\">%s</td>"                                   /* GameType */
			"<td class=\"s_title\">%s</td>"                                  /* ModuleName */
			"<td class=\"s_number\">%u</td><td class=\"s_number\">%u</td>"   /* ActivePlayers, MaximumPlayers */
			"<td class=\"s_number\">%u</td><td class=\"s_number\">%u</td>"   /* MinimumLevel, MaximumLevel */
			"<td class=\"s_code\">%s</td>"                                   /* PvPLevel */
			"<td class=\"s_number\">%u</td><td class=\"s_number\">%u</td>"   /* LocalVault, PrivateServer */
			"<td class=\"s_number\">%u</td><td class=\"s_number\">%u</td>"   /* ELCEnforced, ILREnforced */
			"<td class=\"s_number\">%u</td><td class=\"s_number\">%u</td>"   /* BuildNumber, ExpansionsMask */
			"<td class=\"s_text\">%s</td>"                                   /* ServerDescription */
			"<td class=\"s_text\">%s</td>"                                   /* ModuleDescription */
			"</tr>\n",
			(i+1),
			encServerName.c_str(),
			url,((strlen(url)>0)?("URL"):("")),
			p->ServerAddress, p->ServerAddress,
			game_type_label[*(p->GameType)],
			encModuleName.c_str(),
			*(p->ActivePlayerCount), *(p->MaximumPlayerCount),
			*(p->MinimumLevel), *(p->MaximumLevel),
			game_pvp_label[*(p->PVPLevel)],
			*(p->LocalVault), *(p->PrivateServer),
			*(p->ELCEnforced), *(p->ILREnforced) ,
			*(p->BuildNumber), *(p->ExpansionsMask),
			encServerDescription.c_str(),
			encModuleDescription.c_str()
		);
		// Unused Fields:
		// 	 p->Product
		//*(p->Online),
		//"<td class=\"s_number\">%u</td>"                                 /* Online */
		//"<td class=\"s_title\"><a href=\"%s\">%s</a></td>"               /* ModuleUrl */
		//"<td>%s</td>"                                                    /* PWCUrl */
		//p->ModuleUrl, p->ModuleUrl,
		//p->PWCUrl
		//"<td class=\"s_title\">%s</td>"                                  /* HeartBeat */
		//tbuf
		//"<td class=\"s_number\">%u</td><td class=\"s_number\">%u</td>"   /* PlayerPause, OnePartyOnly */
		//*(p->PlayerPause), *(p->OnePartyOnly),
	} else {
		printf(
			"<tr>"
			"<td class=\"s_number\">%u</td>"                                 /* Row Count */
			"<td class=\"s_title\">%s</td>"                                  /* ServerName (w/ ModuleUrl ) */
			"<td class=\"s_title\"><a href=\"%s\">%s</a></td>"               /* ModuleUrl */
			"<td class=\"s_title\"><a href=\"nwn2gcp:%s\">%s</a></td>"       /* ServerAddress (w/ URL) */
			"<td class=\"s_code\">%s</td>"                                   /* GameType */
			"<td class=\"s_title\">%s</td>"                                  /* ModuleName */
			"<td class=\"s_number\">%u</td><td class=\"s_number\">%u</td>"   /* ActivePlayers, MaximumPlayers */
			"<td class=\"s_number\">%u</td><td class=\"s_number\">%u</td>"   /* MinimumLevel, MaximumLevel */
			"<td class=\"s_code\">%s</td>"                                   /* PvPLevel */
			"<td class=\"s_number\">%u</td><td class=\"s_number\">%u</td>"   /* LocalVault, PrivateServer */
			"<td class=\"s_number\">%u</td><td class=\"s_number\">%u</td>"   /* ELCEnforced, ILREnforced */
			"<td class=\"s_number\">%u</td><td class=\"s_number\">%u</td>"   /* BuildNumber, ExpansionsMask */
			"<td class=\"s_text\">%s</td>"                                   /* ServerDescription */
			"<td class=\"s_text\">%s</td>"                                   /* ModuleDescription */
			"<td class=\"s_title\"><a href=\"%s\">%s</a></td>"               /* PWCUrl */
			"</tr>\n",
			(i+1),
			encServerName.c_str(),
			p->ModuleUrl,((strlen(p->ModuleUrl)>0)?("URL"):("")),
			p->ServerAddress, p->ServerAddress,
			game_type_label[*(p->GameType)],
			encModuleName.c_str(),
			*(p->ActivePlayerCount), *(p->MaximumPlayerCount),
			*(p->MinimumLevel), *(p->MaximumLevel),
			game_pvp_label[*(p->PVPLevel)],
			*(p->LocalVault), *(p->PrivateServer),
			*(p->ELCEnforced), *(p->ILREnforced) ,
			*(p->BuildNumber), *(p->ExpansionsMask),
			encServerDescription.c_str(),
			encModuleDescription.c_str(),
			p->PWCUrl,((strlen(p->PWCUrl)>0)?("PWC"):(""))
		);
	}
}

int main(int argc, char* argv[])
{
	char product[32];
	strcpy(product,"NWN1");
	if ( strstr(argv[0],"listnwns2html.cgi")!=NULL ) { strcpy(product,"NWN2"); g_is_nwn1 = false; }

	char guardbuf1[1024];
	BasicHttpBinding_USCOREINWNMasterServerAPIProxy s;
	char guardbuf2[1024];
	s.soap_endpoint  = "http://api.mst.valhallalegends.com/NWNMasterServerAPI/NWNMasterServerAPI.svc/ASMX";

	struct _ns1__GetOnlineServerList* gosl          = new _ns1__GetOnlineServerList;
	struct _ns1__GetOnlineServerListResponse* goslr = new _ns1__GetOnlineServerListResponse;
	gosl->Product = const_cast<char*>(product);
	int r = s.GetOnlineServerList(gosl,goslr);

	if ( r == SOAP_OK ) {
		if ( goslr->GetOnlineServerListResult ) {
			print_http_header();
			print_header();
			int n = goslr->GetOnlineServerListResult->__sizeNWGameServer;
			for ( int i = 0; i < n; i++ ) {
				ns4__NWGameServer* p = goslr->GetOnlineServerListResult->NWGameServer[i];
				print_ith_row(p,i);
			}
			print_footer();
		}
	} else {
		s.soap_stream_fault(std::cerr);
	}

	s.destroy();

	return 0;
} 

