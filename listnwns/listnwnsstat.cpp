/******************************************************************************
* listnwnsstat.cpp
*
* See the associated listnwnsstat.README.markdown file for details.
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

/* Converts a hex character to its integer value */
char from_hex(char ch) {
  return isdigit(ch) ? ch - '0' : tolower(ch) - 'a' + 10;
}

/* Converts an integer value to its hex character*/
char to_hex(char code) {
  static char hex[] = "0123456789abcdef";
  return hex[code & 15];
}

/* Returns a url-encoded version of str */
/* IMPORTANT: be sure to free() the returned string after use */
char *url_encode(char *str) {
  char *pstr = str, *buf = (char*)malloc(strlen(str) * 3 + 1), *pbuf = buf;
  while (*pstr) {
    if (isalnum(*pstr) || *pstr == '-' || *pstr == '_' || *pstr == '.' || *pstr == '~') 
      *pbuf++ = *pstr;
    else if (*pstr == ' ') 
      *pbuf++ = '+';
    else 
      *pbuf++ = '%', *pbuf++ = to_hex(*pstr >> 4), *pbuf++ = to_hex(*pstr & 15);
    pstr++;
  }
  *pbuf = '\0';
  return buf;
}

/* Returns a url-decoded version of str */
/* IMPORTANT: be sure to free() the returned string after use */
char *url_decode(char *str) {
  char *pstr = str, *buf = (char*)malloc(strlen(str) + 1), *pbuf = buf;
  while (*pstr) {
    if (*pstr == '%') {
      if (pstr[1] && pstr[2]) {
        *pbuf++ = from_hex(pstr[1]) << 4 | from_hex(pstr[2]);
        pstr += 2;
      }
    } else if (*pstr == '+') { 
      *pbuf++ = ' ';
    } else {
      *pbuf++ = *pstr;
    }
    pstr++;
  }
  *pbuf = '\0';
  return buf;
}

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
	//fprintf(stderr,"usage: %s <argv0 must be listnwns1html.cgi or listnwn2html.cgi>\n",pname);
}

void print_http_header()
{
	printf(
		"Content-Type: text/html\n"
		//"Cache-Control: max-age:60\n"
		"\n"
	);
}

void print_error(const char* message)
{
	printf(
		"Content-Type: text/html\n"
		"Cache-Control: no-cache\n"
		"\n"
		"<html>\n"
		"<head>\n"
		"<title>Error</title>\n"
		"</head>\n"
		"<body>\n"
		"<div>%s</div>\n"
		"</body>\n"
		"</html>\n",
		message
	);
}

void print_header()
{
	printf(
		"<html>\n"
		"<head>\n"
		"<title>NWN Server Status</title>\n"
		"<link rel=\"stylesheet\" type=\"text/css\" href=\"/css/listnwnsstat.css\">\n"
		"</head>\n"
		"<body>\n"
		"<div class=\"s_srvtab\">\n"
	);
}
void print_footer()
{
	printf(
		"</div>\n"
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
    string encModuleDescription = html_encode_special(p->ModuleDescription);

#ifdef __foo__
		"<td class=\"s_number\">%u</td>"                                 /* Row Count */
		"<div class=\"s_number\">%u</div>\n"                             /* Online */
		"<td class=\"s_number\">%u</td><td class=\"s_number\">%u</td>"   /* MinimumLevel, MaximumLevel */
		"<td class=\"s_code\">%s</td>"                                   /* PvPLevel */
		"<td class=\"s_number\">%u</td><td class=\"s_number\">%u</td>"   /* LocalVault, PrivateServer */
		"<td class=\"s_number\">%u</td><td class=\"s_number\">%u</td>"   /* PlayerPause, OnePartyOnly */
		"<td class=\"s_number\">%u</td><td class=\"s_number\">%u</td>"   /* ELCEnforced, ILREnforced */
		"<td class=\"s_number\">%u</td><td class=\"s_number\">%u</td>"   /* BuildNumber, ExpansionsMask */
		"<td class=\"s_text\">%s</td>"                                   /* ModuleDescription */
		"<td class=\"s_title\">%s</td>"                                  /* HeartBeat */
		"<td>%s</td>"                                                    /* PWCUrl */
#endif

	printf(
		"<div class=\"s_srvrow\">\n"
		"<div class=\"s_srvnam\">%s</div>\n"                                        /* ServerName */
		"<div class=\"s_modnam\">%s</div>\n"                                        /* ModuleName */
		"<div class=\"s_lnkmodnam\"><a href=\"%s\" target=\"_top\">%s</a></div>\n"  /* ModuleName (w/ URI link) */
		"<div class=\"s_srvadr\">%s</div>\n"                                        /* ServerAddress */
		"<div class=\"s_lnksrvadr\"><a href=\"nwn1gcp:%s\">%s</a></div>\n"          /* ServerAddress (w/ URI link) */
		"<div class=\"sl_gamtyp\">Game Type</div>\n"                                /* Players (Label) */
		"<div class=\"s_gamtyp\">%s</div>\n"                                        /* GameType */
		"<div class=\"sl_player\">Players</div>\n"                                  /* Players (Label) */
		"<div class=\"s_actplr\">%u</div>\n"                                        /* ActivePlayers */
		"<div class=\"sl_actmax\">/</div>\n"                                        /* ActMax Seperator (Label) */
		"<div class=\"s_maxplr\">%u</div>\n"                                        /* MaximumPlayers */
		"</div>\n",
		encServerName.c_str(),
		encModuleName.c_str(),
		p->ModuleUrl, encModuleName.c_str(),
		p->ServerAddress,
		p->ServerAddress, p->ServerAddress,
		game_type_label[*(p->GameType)],
		*(p->ActivePlayerCount),
		*(p->MaximumPlayerCount)
	);

	// Unused Fields: p->Product
		//(i+1),
		//*(p->Online),
		//*(p->MinimumLevel), *(p->MaximumLevel),
		//game_pvp_label[*(p->PVPLevel)],
		//*(p->LocalVault), *(p->PrivateServer),
		//*(p->PlayerPause), *(p->OnePartyOnly),
		//*(p->ELCEnforced), *(p->ILREnforced) ,
		//*(p->BuildNumber), *(p->ExpansionsMask),
		//encModuleDescription.c_str(),
		//tbuf,
		//p->PWCUrl
}

void print_error_with_style(const char* message)
{
	printf("<div class=\"s_errorm\">%s</div>\n",message);
}


int main(int argc, char* argv[])
{
	char* qs = getenv("QUERY_STRING");
	if ( (qs == NULL) || (strnlen(qs,256) > 255) ) { print_error("Invalid QUERY_STRING."); return 1; }
	//printf("QUERY_STRING [%s]\n",qs);

	char* a_ptr;
	char* b_ptr;

	a_ptr = strstr(qs,"ServerName=");
	if ( a_ptr == NULL ) { print_error("Query parameter ServerName is required."); return 1; }
	a_ptr = a_ptr + strlen("ServerName=");
	b_ptr = strstr(a_ptr,"&");
	if ( b_ptr != NULL ) *b_ptr='\0';
	char* server_name = url_decode(a_ptr);
	if ( b_ptr != NULL ) *b_ptr='&';

	a_ptr = strstr(qs,"Product=");
	if ( a_ptr == NULL ) { print_error("Query parameter Product is required."); return 1; }
	a_ptr = a_ptr + strlen("Product=");
	b_ptr = strstr(a_ptr,"&");
	if ( b_ptr != NULL ) *b_ptr='\0';
	char* product = url_decode(a_ptr);
	if ( b_ptr != NULL ) *b_ptr='&';

	//printf("Product [%s], ServerName [%s]\n",product,server_name);

	// Scary... declaring the proxy seems to overrun memory, protect it.
	char guardbuf1[1024];
	BasicHttpBinding_USCOREINWNMasterServerAPIProxy s;
	char guardbuf2[1024];
	s.soap_endpoint  = "http://api.mst.valhallalegends.com/NWNMasterServerAPI/NWNMasterServerAPI.svc/ASMX";

	struct _ns1__LookupServerByName* lsbn          = new _ns1__LookupServerByName;
	struct _ns1__LookupServerByNameResponse* lsbnr = new _ns1__LookupServerByNameResponse;
	//lsbn->Product = (char*)malloc(strlen(product)+1);
	lsbn->Product = product;
	strcpy(lsbn->Product,product);
	//lsbn->ServerName = (char*)malloc(strlen(server_name)+1);
	lsbn->ServerName = server_name;
	strcpy(lsbn->ServerName,server_name);

	print_http_header();
	print_header();
	if ( (s.LookupServerByName(lsbn,lsbnr) == SOAP_OK) && (lsbnr->LookupServerByNameResult != NULL) ) {
		int n = lsbnr->LookupServerByNameResult->__sizeNWGameServer;
		if ( n > 0 ) {
			for ( int i = 0; i < n; i++ ) {
				ns4__NWGameServer* p = lsbnr->LookupServerByNameResult->NWGameServer[i];
				print_ith_row(p,i);
			}
		} else {
			string m = "No information found for server name: ";
			m.append(server_name);
			print_error_with_style(m.c_str());
		}
	} else {
		print_error_with_style("Unable to communicate with master server");
		//s.soap_stream_fault(std::cerr);
	}
	print_footer();

	s.destroy();

	return 0;
} 

