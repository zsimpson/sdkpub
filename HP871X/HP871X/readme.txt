README.TXT
HP 871x Network Analyzer Universal Instrument Driver (UID)
Driver Revision A.01.00  
October 23, 1998

Contents:

1    Introduction

2    VTL/VISA Specific Information
2.1    Instrument Addresses
2.2    Using Callbacks

3    Using the HP 871x Driver in Application Development Environments
3.1    Microsoft Visual C++ and Borland C++
3.2    Microsoft Visual Basic
3.3    HP VEE
3.4    National Instruments LabWindows/CVI

4.0  Known Defects

5.0  Online Information

6.0  VXIPNP Directory Location

7.0  Revision History

8.0  Files Installed

- ---------------------------------------------------------------------------

1.   Introduction

This driver is completely or partially compatible with entire HP 871x family  
of analyzers which include the HP 8711A/B/C, 8712B/C/E, 8713B/C and 8714B/C/E.
The help file included with the HP 871x driver contains instrument and 
programming information.  PLEASE READ AT LEAST THE INTRODUCTION PAGE!
This readme file contains additional information for the user/installer.

The HP 871x Windows 95 (or 98) and Windows NT drivers are actually a single 
32-bit driver.  All references which follow assume Windows 95.  For Windows 
NT, change win95 references to winnt. 

This HP 871x driver conforms to all portions of the VXIplug&play driver
standard which are applicable to conventional GP-IB and other non-VXI
instruments (that is, rack and stack instruments).  The formal VXIplug&play
standard only covers VXI Instruments, and two elements of the standard do not
apply to the HP 871x since it is not a VXI instrument. First, there is no soft
front panel, as the HP 871x can be controlled from it's hardware front panel.
Second, there is no knowledge base file, which is primarily a physical
description of a VXI board.

Aside from these exceptions, you'll find the same features in this driver as
in HP's other VXIplug&play drivers.


1.  Conformance with the VXIplug&play standard.  The only exceptions are that
    it does not have a soft front panel or a knowledge base file.

2.  It is built on top of, and uses the services provided by VISA.  VISA
    supports GP-IB and VXI protocols.  The driver can be used with any
    GP-IB card for which the manufacturer has provided a VISA DLL.

3.  It includes a "Function Panel" (.fp) file which allows it to be used
    with visual programming environments such as HP-VEE, LabWindows, and
    LabVIEW.

4.  It includes a comprehensive on-line help file which complements the
    instrument  manual.  The help file presents application programming
    examples, a cross-reference between instrument commands and driver
    functions, and detailed  documentation of each function, with examples.

5.  Source is included so that the driver can be modified if desired.  The
    source conforms to VXI Plug & Play standards.  Modifications should only
    be done by people who are familiar with the VXIplug&play standard.

6.  It includes a Visual Basic include file (.bas) which contains the function
    calls in Visual Basic syntax, so that driver functions can be called from
    Visual Basic.  If you use Visual Basic with this driver, you should be
    familiar with C/C++ function declarations.  In particular, care must be
    taken when working with C/C++ pointers.
 
- ---------------------------------------------------------------------------

2.   VISA Specific Information

The following topics refer to instances when the driver is used with
different versions of VISA.

2.1    Instrument Addresses

When using HP VXIplug&play instrument drivers, instrument addresses must
be all uppercase letters. Implementation of the addressing scheme is
vendor specific and some vendors support mixed cases. However, for
maximum portability, the instrument address should use uppercase
characters only.

For example:  use "GPIB0::16" instead of "gpib0::16"

2.2   Using Callbacks

Callbacks are not supported with this driver.


- --------------------------------------------------------------------------

3.   Using the HP 871x Driver in Application Development Environments

This section offers suggestions on using the hp871x_32.dll within
various application development environments.

3.1    Microsoft Visual C++ 4.0 (or higher) and Borland C++ 4.5 (or higher)

Refer to your Microsoft Visual C++ or Borland C++ manuals for information
on linking and calling .DLLs.

A.) The driver uses Pascal calling conventions.

B.) Rebuilding the driver DLL should be done in a different directory 
    than the one the driver was installed in order to differentiate the changes.

3.2   Microsoft Visual Basic 5.0 (or higher)

Refer to the Microsoft Visual BASIC manual for information on calling DLLs.
The BASIC include file is hp871x.bas, which is contained in the directory
~vxipnp\win95\include. The ~ refers to the directory in the VXIPNP variable.  
By default this is set to C:\.  You may also need to include the visa.bas
file that comes with your VISA DLL. 

3.3   HP VEE Version 3.2 (or higher)

Your copy of HP VEE for WINDOWS contains a document titled "Using
VXIplug&play Drivers with HP VEE for Windows."  This document contains
the detailed information you need for HP VEE applications.

3.4   National Instruments LabWindows CVI/(R) 4.0.1 (or higher)

The HP 871x driver is supplied as both a source code file and as a dynamic
link library file (dll).  There are several advantages to using the dll
form of the driver.  These include: 

1. Transportability across different computer platforms

2. A higher level of support from Hewlett-Packard for the compiled driver

3. Faster load time for your project

Labwindows/CVI (R) by default will attempt to load the source version
of the instrument driver.  To load the dll you must include the file
hp871x.fp in your project.  This file can be found in the vxipnp\win95\hp871x
directory.  Do not include hp871x.c in your project.  You must also provide 
an include path for hp871x.h.  This is done by adding the directory 
~vxipnp\win95\include to the include paths (CVI Project Option menu) if you 
have not already done so.  The ~ refers to the directory in the VXIPNP 
variable.  By default this is set to C:\.


- ---------------------------------------------------------------------------

4.0  Known Defects

There are no known defects associated with this driver at this time, 
however, it has been noted that LabView seems to slightly scramble the 
location of controls within the function panel, so it may be beneficial
to modify the vi function panels that are generated to make them more 
readable.  This problem is not seen with LabWindows/CVI or HP VEE. 

- ---------------------------------------------------------------------------

5.0  Online Information


Updates to this driver and other HP VXIplug&play drivers can be obtained 
via anonymous ftp from fcext3.external.hp.com in the directory
~dist/mxd/vxipnp/win95/supported.  It can also be obtained on the web at
ftp://fcext3.external.hp.com/dist/mxd/vxipnp/pnpdrver.lis.  Also try: 
http://www.tmo.hp.com/tmo/pia/component_test/PIASupp/English/comptest_drivers.html  
The HP 871x driver is located in a self-extracting archive file called 
871x.exe. If you do not have ftp or web access, the driver can be obtained 
or by calling HP On-line Support at (970) 679-3030.

- ---------------------------------------------------------------------------

6.0  Location of VXIPNP Directory

When installing the version of VISA for use with your particular interface, 
the installer program may allow you to specify a directory location other 
than the root directory on your hard disk for placement of the VXIPNP 
directory.  The hp871x driver will work properly with all programming 
platforms only if the VXIPNP directory is located on the root of your 
hard disk (e.g.  C:\VXIPNP, where C is the drive letter).  If you encounter 
problems because your VXIPNP directory is not in the root, you should do 
the following:  Go to the Control Panel from the Windows Start menu and 
use "Add/Remove Programs" to uninstall first the hp871x driver, then VISA; 
then reinstall VISA, specifying the root directory for placement of VXIPNP 
directory, and reinstall the hp871x driver. 

- ---------------------------------------------------------------------------

7.0  Revision History

A.01.00 - As Issued

- ---------------------------------------------------------------------------

8.0  Files Installed

The Install program will place the following files on the hard drive.

871x_cpp.h    - Header file for use with C++
Hp871X.cpp    - Source code for use with C++
Hp871x.def    - Definition file for use with C++ when building the .dll file
Hp871x.fp     - Function Panel file for use with HP VEE and LabView/LabWindows
Hp871x.h      - Header file for use with HP VEE and LabView/LabWindows
Hp871x.bas    - Module file for use with Visual BASIC
Hp871x.hlp    - Help file for use with all platforms (Optional)
Hp871x.rtf    - Help file in printable format (Optional)
Hp871x_32.dll - Dynamic Link Library file for use with all platforms
Hp871x.lib    - Library file for use with C++
Hp871x_32.lib - Library file (same as above) for use with C++
Readme.txt    - This file that contains general information
4ParmDsp.vee  - Example HP VEE demo program that uses this driver 
4ParmDsp.txt  - Read-me file for the HP VEE demo program

If a particular platform is not going to be used, the corresponding 
platform-specific files may be deleted. 

The demo program is not needed by any platform, but is provided as an 
example of using HP VEE with this driver.  This program demonstrates the 
display of all four S-parameters on the computer's monitor and requires 
an HP 8712ES or 8714ES.  

The help file (.hlp) is not absolutely needed, but is very strongly 
recommended.  The printable help file (.rtf) is not needed unless a 
hard-copy of the help file is desired.  This file can be opened by 
any word processing program and then printed.  This will produce a 
document about 300 pages in length. 

- ---------------------------------------------------------------------------

LabWindows/CVI & LabView are registered trademarks of National Instruments.

