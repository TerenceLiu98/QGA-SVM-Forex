GA C++ Shared Library

1. Prerequisites for Deployment 

Verify that version 9.4 (R2018a) of the MATLAB Runtime is installed.   
If not, you can run the MATLAB Runtime installer.
To find its location, enter
  
    >>mcrinstaller
      
at the MATLAB prompt.
NOTE: You will need administrator rights to run the MATLAB Runtime installer. 

Alternatively, download and install the Macintosh version of the MATLAB Runtime for R2018a 
from the following link on the MathWorks website:

    http://www.mathworks.com/products/compiler/mcr/index.html
   
For more information about the MATLAB Runtime and the MATLAB Runtime installer, see 
Package and Distribute in the MATLAB Compiler SDK documentation  
in the MathWorks Documentation Center.

2. Files to Deploy and Package

Starting with R2018a, MATLAB Compiler SDK generates two types of C++ shared library 
 interfaces:
- legacy, using the mwArray interface
- generic, using the MATLAB Data API introduced in R2017b
MathWorks recommends the MATLAB Data API, which uses modern C++ features for efficient 
 execution and programming.
Files for the legacy interface can be found in the directory where this readme file is 
 located.
Files for the generic interface can be found in the v2/generic_interface subdirectory.

Files to Package for the Legacy Interface
=========================================
-GA.dylib
-GA.h
-MCRInstaller.zip 
    Note: if end users are unable to download the MATLAB Runtime using the
    instructions in the previous section, include it when building your 
    component by clicking the "Runtime included in package" link in the
    Deployment Tool.
-This readme file

Files to Package for the Generic Interface
(in the v2/generic_interface subdirectory)
==========================================
-GA.ctf (component technology file) 
-readme.txt

3. Definitions

For information on deployment terminology, go to
http://www.mathworks.com/help and select MATLAB Compiler >
Getting Started > About Application Deployment >
Deployment Product Terms in the MathWorks Documentation
Center.

4. Appendix 

A. Mac systems:
In the following directions, replace MR/v94 by the directory on the target machine where 
   MATLAB is installed, or MR by the directory where the MATLAB Runtime is installed.

If the environment variable DYLD_LIBRARY_PATH is undefined, set it to the following 
   string:

MR/v94/runtime/maci64:MR/v94/sys/os/maci64:MR/v94/bin/maci64:MR/v94/extern/bin/maci64

If it is defined, set it to the following:

${DYLD_LIBRARY_PATH}:MR/v94/runtime/maci64:MR/v94/sys/os/maci64:MR/v94/bin/maci64:MR/v94/extern/bin/maci64

    For more detailed information about setting the MATLAB Runtime paths, see Package and 
   Distribute in the MATLAB Compiler SDK documentation in the MathWorks Documentation 
   Center.


     
        NOTE: To make these changes persistent after logout on Linux 
              or Mac machines, modify the .cshrc file to include this  
              setenv command.
        NOTE: The environment variable syntax utilizes forward 
              slashes (/), delimited by colons (:).  



