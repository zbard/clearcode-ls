
ClearCode - LS Implementation


NAME (To avoid confusion - the name of the generated executable is set to run)
run - list directory contents
SYNOPSIS
run [-SrRdlaisc] [file...]

------------------------------------------------------------------------------

DESCRIPTION
For each operand that names a file of a type other than directory or symbolic link to a directory, ls shall write the name of the file as well as any requested, associated information. For each operand that names a file of type directory, ls shall write the names of files contained within the directory as well as any requested, associated information.

If no operands are specified, ls shall write the contents of the current directory. If more than one operand is specified, ls shall write non-directory operands first.

The ls utility should detect infinite loops; ALAS the executable presented does not do so. Thus for safety
sake - when run in recursive mode it will not follow directories '.','..' and links.

------------------------------------------------------------------------------

OPTIONS

The following options are  supported:

-R 
Recursively list subdirectories encountered. 

-d 
Do not treat directories differently than other types of files. The use of -d with -R produces unspecified results. 

-i 
For each file, write the file's file serial number

-l 
Write out in long format .

-a 
Write out all directory entries, including those whose names begin with a period ( '.' ). Entries beginning with a period shall not be written out unless explicitly referenced, the -a option is supplied.

-r 
Reverse the order of the sort to get reverse collating sequence . 

-s 
Indicate the total number of file system blocks consumed by each file displayed. The block size is implementation-defined.  

-S
Sort output alphabetically.

-c
Turn off color output - Useful when you are redirecting the output to a file and you have a dislike
for junk characters in your output.

------------------------------------------------------------------------------

INPUT

When given inputs in the form of file or directory names the utility shall always give the output 
in them. Since most shells expand wildcards - any such entry will work on the utility.

FORCED WILDCARDS
In case the shell does'nt expand the entries - the utility is capable of matching any entry of the 
form -
		DirPath/DirPath/..../[Wild Card Sequence]

Example of valid inputs :
"/dev/a*"
"/bin/vim/vb?"

Example of invalid input :
"/dev?/vb?/v*"

------------------------------------------------------------------------------
Execution 
	- ClearCode/scripts/run

Compilation
[Plain]
	- Clearcode/scripts/vanilla_run
[All logs]
	- Clearcode/scripts/mem_run
[Memory leak checker]
	- Clearcode/scripts/log_run


------------------------------------------------------------------------------
Missing Features
	- Commenting
	- Make File
------------------------------------------------------------------------------
Bugs
	- When break ^C in piped output - color does'nt go away.
	
------------------------------------------------------------------------------
See Also
	- Doxygen report
	- Profiler report
	- Logger, Mem checker, Unit test framework desc.





