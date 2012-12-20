/******************************************************************************
* nwn1gcp.c
*
* Convert protocol qualified URI to NWN application +connect command line.
*
* nwn1gcp:1.0.0.1:1024           len=(20)
* nwn1gcp:254.254.254.254:65535  len=(29)
*
* MingGW: cc -Wall -o nwn1gcp.exe nwn1gcp.c
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

#include <string.h>
#include <stdio.h>
#include <libgen.h>
#include <malloc.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	int len;
	char* uri;
	char* dir_tmp;
	char* dir;
	const char* command_template = "%s/nwmain.exe";
	char command[2048];

	if (argc != 2) return 1;

	len = strlen(argv[0]);
	if ( (len < 7) || (len > 1024) ) return 2;
	dir_tmp = strdup(argv[0]);
	if (dir_tmp == NULL) return 2;
	dir = dirname(dir_tmp);
	if (dir == NULL) return 2;

	len = strlen(argv[1]);
	if ( (len < 20) || (len > 29) ) return 3;
	uri = argv[1];
	if (strstr(uri,"nwn1gcp:") != uri) return 3;
	uri += 8;
	if ( strspn(uri,"1234567890.:") != strlen(uri) ) return 3;
 
	sprintf(command,command_template,dir);

	if ( chdir(dir) != 0 ) return 4;
	free(dir_tmp);

	execl(command,command,"+connect",uri,(char*)NULL);

	return 5;
}
