# xecho

Echo command with support for escaped C characters, escaped XML sequences, and more.

xecho is a simple command line program intended to be a replacement for the echo command when necessary. In particular, on [FreeDOS]() (and various old versions of MS-DOS) it's impossible to use the echo command without a new line being echoed, and a ">" character cannot be echoed either. With xecho, both of these problems are solved.

 * Author: Jason Baker (jason@onejasonforsale.com)
 * Github: https://github.com/codercowboy/xecho
 * Copyright: xecho is copyright [Coder Cowboy, LLC](http://www.codercowboy.com) 2018.

# Usage

A dos executable (which will work on windows) and a MacOS binary (built on High Sierra) are available in the [bin](bin) folder of this project.

 - Dos / Windows Executable: [xecho.exe](bin/xecho.exe)
 - MacOS Binary [xecho](bin/xecho)

# Example usage    

    Usage: xecho [options] [string]

    Options:
    
      -sx	suppress XML character replacement
      -sc	suppress C character replacement
      -sn	suppress non-standard character replacement
      -n	supress printing new line after output (like bash)
    
    Supported C Character Replacements:
    
      \a	Alert (Beep, Bell)
      \b	Backspace
      \f	Form Feed
      \n	New Line (Line Feed);  \r	Carriage Return
      \t	Horizontal Tab
      \v	Vertical Tab
      \\	Backslash
      \'	Single Quotation Mark
      \"	Double Quotation Mark
      \?	Question Mark

    Supported XML Character Replacements:
    
      &amp;		&	Ampersand
      &lt;		<	Less-than
      &gt;		>	Greater-than
      &quot;	"	Double Quotation Mark
      &apos;	'	Single Quotation Mark
    
    Supported Non-Standard Character Replacements:
    
      :a: 		*	Asterisk
      :b: 		\b	Backspace
      :c: 		,	Comma
      :d: 		.	Dot (Period)
      :h: 		#	Hash
      :q: 		?	Question Mark
      :f: 		\f	Form Feed
      :n: 		\n	New Line
      :p: 		|	Pipe (Vertical bar)
      :r: 		\r	Carriage Return
      :s: 		 	Space
      :t: 		\t	Horizontal Tab
      :v: 		\v	Vertical Tab
    
      :fslash: 	/	Forward Slash
      :bslash: 	\	Back Slash
      :oparen: 	(	Open Parentheses
      :cparen: 	)	Close Parentheses
      :obrack: 	[	Open Bracket
      :cbrack: 	]	Close Bracket
      :ocbrack: 	{	Open Curly Bracket
      :ccbrack: 	}	Close Curly Braket
      :lt: 		<	Less-than
      :gt: 		>	Greater-than
    
      :amp: 	&	Ampersand
      :apos: 	'	Single Quotation Mark
      :at: 		@	At
      :bcktck: 	`	Back Tick
      :carret: 	^	Carret
      :col: 	:	Colon
      :dash: 	-	Dash (Hyphen)
      :dollar: 	$	Dollar
      :eq: 		=	Equals
      :exclam: 	!	Exclamation Mark
      :pct: 	%	Percent
      :plus: 	+	Plus
      :quot: 	"	Double Quotation Mark
      :scol: 	;	Semicolon
      :tilde: 	~	Tilde
      :udash: 	_	Underscore

# Additional Resources      

 * [More info on C escape codes](https://en.wikipedia.org/wiki/Escape_sequences_in_C)
 * [More info on XML escape codes](https://en.wikipedia.org/wiki/List_of_XML_and_HTML_character_entity_references)
 * [DOS escape codes] - Example: "^>" translates to ">". NOTE: FreeDOS does not currently support these. 
 * [FreeDOS](http://www.freedos.org/) - Open-source, Free MS-DOS replacement.
 * [DOSBox](https://www.dosbox.com/) - Cross-platform DOS emulator for modern hardware.
 * [Em-DOSBox](https://github.com/dreamlayers/em-dosbox) - DosBox in javascript for running in browser.
 * [v86](https://github.com/copy/v86) - Javascript [x86](https://en.wikipedia.org/wiki/X86) vintage PC emulator, allows running various VMs in browser. [demo with win95, linux FreeDOS](https://copy.sh/v86/)
 * [VirtualBox](https://www.virtualbox.org/) - Cross-platform [x86](https://en.wikipedia.org/wiki/X86) virtual machine host.

# Building

xecho is a simple C program. Building the [xecho.c](xecho.c) program on systems with (GCC)[https://gcc.gnu.org/] is easy:

   gcc xecho.c -o xecho

GCC is easily installed on MacOS by installing [XCode]() and [Xcode's Command Line Tools](). Alternatively, GCC can be obtained using [HomeBrew](). On Windows, GCC can easily be installed with [cygwin]().

Building the dos binary is not as easy. I was able to build it using a Windows 98 Virtual Machine running inside VirtualBox on my Mac using these steps:

1. Installed a Windows 98 VM on VirtualBox ([instructions here](https://github.com/happyacro/happyacro-dos/blob/master/Win982018VM.md)).
2. Installed [Open Watcom 1.9](http://www.openwatcom.org) on the Win98 image.
3. Created an Open Watcom project with a target environment of "Dos - 32-bit" and Image Type "Causeway Executable [.exe]".
4. Built the DOS executable in Watcom, ftped it out of the VM to my Mac, then ran it in DOSBox. 

**If you know how to build a 32-bit (or even better: 16-bit) DOS binary w/ GCC, please tell me how!**

# Contributing

If you'd like to contribute to the project, great! Fork and PR, or download and simply email your changes, whatever works. I'll give you credit for your contributions.

Ideas to improve the project:

 * Unit tests
 * Build scripts to build the project (make files, whatever)
 * Build scripts to build cross-platform binaries on one machine (ie build for DOS on MacOS).
 * Linux-compatible binary
 * Man pages
 * Get the project into package managers such as [Homebrew](), [Ports](), [Apt]() etc.
 * Verify executable works on modern versions of windows such as Windows 10.

# License

All content (documentation, source code, and binaries) is licensed with the [Apache license](http://en.wikipedia.org/wiki/Apache_license), which is a great license because it:

* a) covers liability - my code should work, but I'm not liable if you do something stupid with it
* b) allows you to copy, fork, and use the code, even commercially
* c) is [non-viral](http://en.wikipedia.org/wiki/Viral_license), that is, your derivative code doesn't *have to be* open source to use it

Other great licensing options for your own code: [BSD License](https://en.wikipedia.org/wiki/BSD_licenses), [MIT License](https://en.wikipedia.org/wiki/MIT_License), or [Creative Commons](https://en.wikipedia.org/wiki/Creative_Commons_license).

Here's the license:

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
