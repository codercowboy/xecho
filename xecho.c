/*

This program was written for a book by Jason Baker called HAPPY:/ACRO.

There is a delightful retro 1996 style website that was made in 2017 to 
promote the book: http://www.happyacro.com.

The purpose of this program is to provide a slightly more advanced 'echo'
command to FreeDOS. FreeDOS' built-in echo command doesn't support escaped
characters, and in particular, there's no way to echo a greater than (>) 
character. With XML and C escape code replacement, echoing multiple new lines
and pipe characters on FreeDOS should be easier.

Documentation for this program is available here: 

https://github.com/codercowboy/xecho

Copyright (c) 2018, Coder Cowboy, LLC. All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
* 1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.
  
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
[INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
[INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  
The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied.

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void main(int argc, char *argv[]) {    
	//since we're dealing with C89, vars have to be declared before we do
	// anything in a function, sigh.
	char * value;
	char current;
	int index = 0;
	int targetIndex = 0;
	char * result;
	int valueLength = 0;
	int argIndex = 1;
	int replaceCCharacters = 1;
	int replaceXMLCharacters = 1;
	int printNewLine = 1;

	if (argc == 1) {
		printf("xecho echos strings with escaped C or XML characters.\n");
		printf("Usage: xecho [options] [string]\n");
		printf("\n");
		printf("Options:");
		printf("\n");
		printf("  -x\tsuppress XML character replacement\n");
        printf("  -c\tsuppress C character replacement\n");
        printf("  -n\tsupress printing new line after output\n");
        printf("\n");
        printf("Supported C Character Replacements:\n");
        printf("\n");
        printf("  \\a\tAlert (Beep, Bell)\n");
        printf("  \\b\tBackspace\n");
        printf("  \\f\tFormfeed\n");
        printf("  \\n\tNewline (Line Feed); see notes below\n");
        printf("  \\r\tCarriage Return\n");
        printf("  \t\tHorizontal Tab\n");
        printf("  \\v\tVertical Tab\n");
        printf("  \\\\\tBackslash\n");
        printf("  \\'\tSingle quotation mark\n");
        printf("  \\\"\tDouble quotation mark\n");
        printf("  \\?\tQuestion mark\n");
        printf("  More info on C escape codes: \n");
        printf("  \thttps://en.wikipedia.org/wiki/Escape_sequences_in_C\n");
        printf("\n");
        printf("Supported XML Character Replacements:\n");
        printf("\n");
        printf("  &amp;\t&  Ampersand\n");
        printf("  &lt;\t<  Less-than\n");
        printf("  &gt;\t>  Greater-than\n");
        printf("  &quot;\t\"  Double quotation mark\n");
        printf("  &apos;\t'  Single quotation mark\n");
        printf("\n");
        printf("  More info on XML escape codes: \n");
        printf("  \thttps://en.wikipedia.org/wiki/List_of_XML_and_HTML_character_entity_references\n");
        printf("\n");
        printf("Copyright: xecho is copyright Coder Cowboy, LLC 2018.\n");
        printf("Author: Jason Baker (jason@onejasonforsale.com)\n");
        printf("Github: https://github.com/codercowboy/xecho\n");
		exit(1);
	}

	while (argIndex < (argc - 1)) {
		if (strcmp("-x", argv[argIndex]) == 0) {
			replaceXMLCharacters = 0;
		} else if (strcmp("-c", argv[argIndex]) == 0) {
			replaceCCharacters = 0;
		} else if (strcmp("-n", argv[argIndex]) == 0) {
			printNewLine = 0;
		}
		argIndex++;
	}

	value = argv[argIndex];
	valueLength = strlen(value);

	result = malloc(valueLength);

	for (index = 0; index < valueLength; index++) {
		current = value[index];
		if (replaceXMLCharacters == 1) {
			if (strncmp(value + index, "&quot;", 6) == 0) {
				current = '\"';
				index += 5;
			} else if (strncmp(value + index, "&apos;", 6) == 0) {
				current = '\'';
				index += 5;
			} else if (strncmp(value + index, "&lt;", 4) == 0) {
				current = '<';
				index += 3;
			} else if (strncmp(value + index, "&gt;", 4) == 0) {
				current = '>';
				index += 3;
			} else if (strncmp(value + index, "&amp;", 5) == 0) {
				current = '&';
				index += 4;
			} 
		}
		if (replaceCCharacters == 1) {
			if (strncmp(value + index, "\\\\", 2) == 0) {
				current = '\\';
				index ++;
			} else if (strncmp(value + index, "\\b", 2) == 0) {
				current = '\b';
				index ++;
			} else if (strncmp(value + index, "\\f", 2) == 0) {
				current = '\f';
				index ++;
			} else if (strncmp(value + index, "\\r", 2) == 0) {
				current = '\r';
				index ++;
			} else if (strncmp(value + index, "\\n", 2) == 0) {
				current = '\n';
				index ++;
			} else if (strncmp(value + index, "\\t", 2) == 0) {
				current = '\t';
				index ++;
			} else if (strncmp(value + index, "\\v", 2) == 0) {
				current = '\v';
				index ++;
			} else if (strncmp(value + index, "\\'", 2) == 0) {
				current = '\'';
				index ++;
			} else if (strncmp(value + index, "\\\"", 2) == 0) {
				current = '\"';
				index ++;
			} 
		}
		result[targetIndex] = current;
		targetIndex++;
	}
	result[targetIndex] = '\0';

	printf("%s", result);

	if (printNewLine == 1) {
		printf("\n");
	}
}

