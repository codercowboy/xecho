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


UPDATES:

2018/10/25
 - Added support for non-standard escape codes
 - Added example usage

2018/10/??
 - Initial version

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

struct ReplacementContext {
   char * input;
   int inputIndex;
   char * output;
   int outputIndex;
};

int replaceCharacters(struct ReplacementContext * ctx, char * searchString, char replacementChar);
void printUsage();

int main(int argc, char *argv[]) {    
	//since we're dealing with C89, vars have to be declared before we do
	// anything in a function, sigh.

	struct ReplacementContext ctx;
	
	int inputLength = 0;
	int argIndex = 1;
	int replaceCCharacters = 1;
	int replaceXMLCharacters = 1;
	int replaceNonStandardCharacters = 1;
	int printNewLine = 1;

	ctx.inputIndex = 0;
	ctx.outputIndex = 0;

	if (argc == 1) {
		printUsage();
		exit(1);
	}

	while (argIndex < (argc - 1)) {
		if (strcmp("-sx", argv[argIndex]) == 0) {
			replaceXMLCharacters = 0;
		} else if (strcmp("-sc", argv[argIndex]) == 0) {
			replaceCCharacters = 0;
		} else if (strcmp("-sn", argv[argIndex]) == 0) {
			replaceNonStandardCharacters = 0;
		} else if (strcmp("-n", argv[argIndex]) == 0) {
			printNewLine = 0;
		}
		argIndex++;
	}

	ctx.input = argv[argIndex];
	inputLength = strlen(ctx.input);
	ctx.output = malloc(inputLength);

	while (ctx.inputIndex < inputLength) {
		if (replaceXMLCharacters == 1) {
			if (replaceCharacters(&ctx, "&quote;", '\"')) { continue;
			} else if (replaceCharacters(&ctx, "&apos;", '\'')) { continue;
			} else if (replaceCharacters(&ctx, "&lt;", '<')) { continue;
			} else if (replaceCharacters(&ctx, "&gt;", '>')) { continue;
			} else if (replaceCharacters(&ctx, "&amp;", '&')) { continue; }
		}
		if (replaceCCharacters == 1) {
			if (replaceCharacters(&ctx, "\\\\", '\\')) { continue;
			} else if (replaceCharacters(&ctx, "\\b", '\b')) { continue;
			} else if (replaceCharacters(&ctx, "\\f", '\f')) { continue;
			} else if (replaceCharacters(&ctx, "\\r", '\r')) { continue;
			} else if (replaceCharacters(&ctx, "\\n", '\n')) { continue;
			} else if (replaceCharacters(&ctx, "\\t", '\t')) { continue;
			} else if (replaceCharacters(&ctx, "\\v", '\v')) { continue;
			} else if (replaceCharacters(&ctx, "\\'", '\'')) { continue;
			} else if (replaceCharacters(&ctx, "\\\"", '\"')) { continue;
			} else if (replaceCharacters(&ctx, "\\?", '?')) { continue; }						
		}

		if (replaceNonStandardCharacters == 1) {
			if (replaceCharacters(&ctx, ":a:", '*')) { continue;
			} else if (replaceCharacters(&ctx, ":b:", '\b')) { continue;
			} else if (replaceCharacters(&ctx, ":c:", ',')) { continue;
			} else if (replaceCharacters(&ctx, ":d:", '.')) { continue;
			} else if (replaceCharacters(&ctx, ":h:", '#')) { continue;
			} else if (replaceCharacters(&ctx, ":q:", '?')) { continue;
			} else if (replaceCharacters(&ctx, ":f:", '\f')) { continue;
			} else if (replaceCharacters(&ctx, ":n:", '\n')) { continue;
			} else if (replaceCharacters(&ctx, ":p:", '|')) { continue;
			} else if (replaceCharacters(&ctx, ":r:", '\r')) { continue;
			} else if (replaceCharacters(&ctx, ":s:", ' ')) { continue;
			} else if (replaceCharacters(&ctx, ":t:", '\t')) { continue;
			} else if (replaceCharacters(&ctx, ":v:", '\v')) { continue;
			} else if (replaceCharacters(&ctx, ":amp:", '&')) { continue;
			} else if (replaceCharacters(&ctx, ":fslash:", '/')) { continue;
			} else if (replaceCharacters(&ctx, ":bslash:", '\\')) { continue;
			} else if (replaceCharacters(&ctx, ":oparen:", '(')) { continue;
			} else if (replaceCharacters(&ctx, ":cparen:", ')')) { continue;
			} else if (replaceCharacters(&ctx, ":obrack:", '[')) { continue;
			} else if (replaceCharacters(&ctx, ":cbrack:", ']')) { continue;
			} else if (replaceCharacters(&ctx, ":ocbrack:", '{')) { continue;
			} else if (replaceCharacters(&ctx, ":ccbrack:", '}')) { continue;
			} else if (replaceCharacters(&ctx, ":lt:", '<')) { continue;
			} else if (replaceCharacters(&ctx, ":gt:", '>')) { continue;
			} else if (replaceCharacters(&ctx, ":dash:", '-')) { continue;
			} else if (replaceCharacters(&ctx, ":udash:", '_')) { continue;
			} else if (replaceCharacters(&ctx, ":quot:", '\"')) { continue;
			} else if (replaceCharacters(&ctx, ":apos:", '\'')) { continue;
			} else if (replaceCharacters(&ctx, ":col:", ':')) { continue;
			} else if (replaceCharacters(&ctx, ":scol:", ';')) { continue;
			} else if (replaceCharacters(&ctx, ":at:", '@')) { continue;
			} else if (replaceCharacters(&ctx, ":bcktck:", '`')) { continue;
			} else if (replaceCharacters(&ctx, ":carret:", '^')) { continue;
			} else if (replaceCharacters(&ctx, ":eq:", '=')) { continue;
			} else if (replaceCharacters(&ctx, ":exclam:", '!')) { continue;
			} else if (replaceCharacters(&ctx, ":pct:", '%')) { continue;
			} else if (replaceCharacters(&ctx, ":plus:", '+')) { continue;
			} else if (replaceCharacters(&ctx, ":tilde:", '~')) { continue;
			} else if (replaceCharacters(&ctx, ":dollar:", '$')) { continue; }
		}

		ctx.output[ctx.outputIndex] = ctx.input[ctx.inputIndex];
		ctx.outputIndex++;
		ctx.inputIndex++;
	}
	ctx.output[ctx.outputIndex] = '\0';

	printf("%s", ctx.output);

	if (printNewLine == 1) {
		printf("\n");
	}

	exit(0);
}

int replaceCharacters(struct ReplacementContext * ctx, char * searchString, char replacementChar) {
	int searchStringLength = strlen(searchString);
	if (strncmp(searchString, ctx->input + ctx->inputIndex, searchStringLength) == 0) {
		ctx->inputIndex += strlen(searchString);
		ctx->output[ctx->outputIndex] = replacementChar;
		ctx->outputIndex += 1;
		return 1;
	}
	return 0;
}

void printUsage() {
	printf("xecho displays strings with escaped characters.\n");
	printf("\n");
	printf("Usage: xecho [options] [string]\n");
	printf("\n");
	printf("Options:\n");
	printf("\n");
	printf("  -sx\tsuppress XML character replacement\n");
    printf("  -sc\tsuppress C character replacement\n");
    printf("  -sn\tsuppress non-standard character replacement\n");
    printf("  -n\tsupress printing new line after output (like bash)\n");
    printf("\n");
    printf("Supported C Character Replacements:\n");
    printf("\n");
    printf("  \\a\tAlert (Beep, Bell)\n");
    printf("  \\b\tBackspace\n");
    printf("  \\f\tForm Feed\n");
    printf("  \\n\tNew Line (Line Feed);");
    printf("  \\r\tCarriage Return\n");
    printf("  \\t\tHorizontal Tab\n");
    printf("  \\v\tVertical Tab\n");
    printf("  \\\\\tBackslash\n");
    printf("  \\'\tSingle Quotation Mark\n");
    printf("  \\\"\tDouble Quotation Mark\n");
    printf("  \\?\tQuestion Mark\n");
    printf("\n");
    printf("  More info on C escape codes: \n");
    printf("    https://en.wikipedia.org/wiki/Escape_sequences_in_C\n");
    printf("\n");
    printf("Supported XML Character Replacements:\n");
    printf("\n");
    printf("  &amp;\t\t&\tAmpersand\n");
    printf("  &lt;\t\t<\tLess-than\n");
    printf("  &gt;\t\t>\tGreater-than\n");
    printf("  &quot;\t\"\tDouble Quotation Mark\n");
    printf("  &apos;\t'\tSingle Quotation Mark\n");
    printf("\n");
	printf("  More info on XML escape codes: \n");
    printf("    https://en.wikipedia.org/wiki/List_of_XML_and_HTML_character_entity_references\n");
    printf("\n");
    printf("Supported Non-Standard Character Replacements:\n");
    printf("\n");
    printf("  :a: \t\t*\tAsterisk\n");
	printf("  :b: \t\t\\b\tBackspace\n");
	printf("  :c: \t\t,\tComma\n");
    printf("  :d: \t\t.\tDot (Period)\n");
    printf("  :h: \t\t#\tHash\n");
    printf("  :q: \t\t?\tQuestion Mark\n");        
    printf("  :f: \t\t\\f\tForm Feed\n");
    printf("  :n: \t\t\\n\tNew Line\n");
    printf("  :p: \t\t|\tPipe (Vertical bar)\n");
    printf("  :r: \t\t\\r\tCarriage Return\n");
    printf("  :s: \t\t \tSpace\n");
    printf("  :t: \t\t\\t\tHorizontal Tab\n");
    printf("  :v: \t\t\\v\tVertical Tab\n");                        
    printf("\n");
    printf("  :fslash: \t/\tForward Slash\n");
    printf("  :bslash: \t\\\tBack Slash\n");
    printf("  :oparen: \t(\tOpen Parentheses\n");
    printf("  :cparen: \t)\tClose Parentheses\n");        
    printf("  :obrack: \t[\tOpen Bracket\n");
    printf("  :cbrack: \t]\tClose Bracket\n");
    printf("  :ocbrack: \t{\tOpen Curly Bracket\n");
    printf("  :ccbrack: \t}\tClose Curly Braket\n");
    printf("  :lt: \t\t<\tLess-than\n");
    printf("  :gt: \t\t>\tGreater-than\n");            
    printf("\n");
	printf("  :amp: \t&\tAmpersand\n");
    printf("  :apos: \t'\tSingle Quotation Mark\n");
    printf("  :at: \t\t@\tAt\n");
	printf("  :bcktck: \t`\tBack Tick\n");
	printf("  :carret: \t^\tCarret\n");             
	printf("  :col: \t:\tColon\n");
	printf("  :dash: \t-\tDash (Hyphen)\n");
	printf("  :dollar: \t$\tDollar\n");
	printf("  :eq: \t\t=\tEquals\n");
	printf("  :exclam: \t!\tExclamation Mark\n");
	printf("  :pct: \t%%\tPercent\n");
    printf("  :plus: \t+\tPlus\n");                                
    printf("  :quot: \t\"\tDouble Quotation Mark\n");    
    printf("  :scol: \t;\tSemicolon\n");
	printf("  :tilde: \t~\tTilde\n");      
    printf("  :udash: \t_\tUnderscore\n");    
    printf("\n");
    printf("Copyright: xecho is copyright Coder Cowboy, LLC 2018.\n");
    printf("Author: Jason Baker (jason@onejasonforsale.com)\n");
    printf("Github: https://github.com/codercowboy/xecho\n");
    printf("\n");
}

