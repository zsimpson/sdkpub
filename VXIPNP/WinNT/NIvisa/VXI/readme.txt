This readme contains information about the mfnameid.tbl and model.tbl files.

YOU SHOULD NEVER MANUALLY EDIT ANY OF THESE FILES!

The National Instruments VXI and VISA drivers use these files. The
files contain VXI manufacturer names and model codes. The NI-VXI and NI-VISA
drivers read this information and present human-readable device information
to the user.

Any VXI vendor who wants to add content to these tables should send the
following information to National Instruments technical support
(support@ni.com):
1) Business contact information (name, email, phone number)
2) Company information (manufacturer name, VXI manufacturer ID)
3) Device information (VXI model codes and model names)

Users who want to add content to these tables must use the appropriate VXI
editor utility. The utility is Measurement & Automation Explorer (MAX)
on Win32, VXIedit on Linux or Solaris, and vxitedit on other platforms.

IF YOU MANUALLY EDIT THESE FILES, THE NATIONAL INSTRUMENTS DRIVERS WILL NOT
NECESSARILY USE THE INFORMATION YOU ADD OR MODIFY.
