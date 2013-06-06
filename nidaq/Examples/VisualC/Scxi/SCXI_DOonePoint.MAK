# ----------------------------------------------------------------------
# Visual C++ MakeFile for NI-DAQ Example SCXI_DOonePoint.C
# ----------------------------------------------------------------------
#
# Instructions on how to create the executable:
#
#     First make sure that your environmental variables
#     'INCLUDE' and 'LIB' are set correctly, and then invoke
#     the following command from the DOS prompt:
#
#           nmake SCXI_DOonePoint.MAK
#
#     You may also load this .MAK file from Visual C++.
#     Visual C++ will then treat it as an 'external makefile'.
#

#
# Win32 build commands (must use VC++ 2.0 [32-bit] or later)
#

#
# Setup paths for NI-DAQ includes and libraries
#
NIDAQ_INCLUDE=..\..\..\Include
NIDAQ_LIB=..\..\..\Lib
#
# Setup flags for compiling and linking
#
CL_FLAGS=/c /DWIN32 /I$(NIDAQ_INCLUDE)
LINK_FLAGS=/MACHINE:I386

#
# TARGET: Console application
#
TARGET=SCXI_DOonePoint
all: $(TARGET).EXE

$(TARGET).OBJ: $(TARGET).C
    cl $(CL_FLAGS) $(TARGET).C


$(TARGET).EXE: $(TARGET).OBJ
    link $(LINK_FLAGS) /OUT:$(TARGET).EXE $(TARGET).OBJ \
                $(NIDAQ_LIB)\nidex32.lib $(NIDAQ_LIB)\nidaq32.lib


#
# End of MakeFile: SCXI_DOonePoint.MAK
# ----------------------------------------------------------------------
