###########################################################################
## Makefile generated for MATLAB file/project 'extmessage2'. 
## 
## Makefile     : extmessage2_rtw.mk
## Generated on : Tue Nov 07 14:51:06 2017
## MATLAB Coder version: 3.3 (R2017a)
## 
## Build Info:
## 
## Final product: $(RELATIVE_PATH_TO_ANCHOR)extmessage2.a
## Product type : static-library
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile
# COMPUTER                Computer type. See the MATLAB "computer" command.

PRODUCT_NAME              = extmessage2
MAKEFILE                  = extmessage2_rtw.mk
COMPUTER                  = PCWIN64
MATLAB_ROOT               = C:\PROGRA~1\MATLAB\R2017a
MATLAB_BIN                = C:\PROGRA~1\MATLAB\R2017a\bin
MATLAB_ARCH_BIN           = C:\PROGRA~1\MATLAB\R2017a\binglnxa64
MASTER_ANCHOR_DIR         = 
START_DIR                 = D:\matlab_m\3
ARCH                      = win64
RELATIVE_PATH_TO_ANCHOR   = .
C_STANDARD_OPTS           = 
CPP_STANDARD_OPTS         = 

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          QuestaSim_Linux\Incisive v1.0 | gmake (64-bit Linux)
# Supported Version(s):    1.0
# ToolchainInfo Version:   R2017a
# Specification Revision:  1.0
# 
TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = 

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# C Compiler: C Compiler
CC = gcc

# Linker: Linker
LD = gcc

# C++ Compiler: GNU C++ Compiler
CPP = g++

# C++ Linker: GNU C++ Linker
CPP_LD = g++

# Archiver: GNU Archiver
AR = ar

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_BIN)
MEX = "mex"

# Download: Download
DOWNLOAD =

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: GMAKE Utility
MAKE = echo "### Successfully generated all binary outputs."


#-------------------------
# Directives/Utilities
#-------------------------

CDEBUG              =
C_OUTPUT_FLAG       =
LDDEBUG             =
OUTPUT_FLAG         =
CPPDEBUG            = -g
CPP_OUTPUT_FLAG     = -o
CPPLDDEBUG          = -g
OUTPUT_FLAG         = -o
ARDEBUG             =
STATICLIB_OUTPUT_FLAG =
MEX_DEBUG           = -g
RM                  =
ECHO                =
MV                  =
RUN                 =

#----------------------------------------
# "Faster Builds" Build Configuration
#----------------------------------------

ARFLAGS              =
CFLAGS               =
CPPFLAGS             =
CPP_LDFLAGS          =
CPP_SHAREDLIB_LDFLAGS  =
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
LDFLAGS              =
MEX_CPPFLAGS         =
MEX_CPPLDFLAGS       =
MEX_CFLAGS           =
MEX_LDFLAGS          =
MAKE_FLAGS           =  $(MAKEFILE)
SHAREDLIB_LDFLAGS    =

#--------------------
# File extensions
#--------------------

H_EXT               = .h
OBJ_EXT             = .o
C_EXT               = .c
EXE_EXT             =
SHAREDLIB_EXT       = .so
HPP_EXT             = .hpp
OBJ_EXT             = .o
CPP_EXT             = .cpp
EXE_EXT             =
SHAREDLIB_EXT       = .so
STATICLIB_EXT       = .a
MEX_EXT             = .mexa64
MAKE_EXT            = .do


###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = $(RELATIVE_PATH_TO_ANCHOR)extmessage2.a
PRODUCT_TYPE = "static-library"
BUILD_TYPE = "Static Library"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = -ccflags$(START_DIR)codegenlibextmessage2 -ccflags$(START_DIR) -ccflags$(MATLAB_ROOT)externinclude -ccflags$(MATLAB_ROOT)simulinkinclude -ccflags$(MATLAB_ROOT)rtwcsrc -ccflags$(MATLAB_ROOT)rtwcsrcext_modecommon -ccflags$(MATLAB_ROOT)rtwcert

INCLUDES = 

###########################################################################
## DEFINES
###########################################################################

DEFINES_STANDARD = MODEL=extmessage2 HAVESTDIO USE_RTMODEL

DEFINES = 

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)codegenlibextmessage2extmessage2_initialize.c $(START_DIR)codegenlibextmessage2extmessage2_terminate.c $(START_DIR)codegenlibextmessage2extmessage2.c $(START_DIR)codegenlibextmessage2highp.c $(START_DIR)codegenlibextmessage2fft.c $(START_DIR)codegenlibextmessage2sin.c $(START_DIR)codegenlibextmessage2xcorr.c $(START_DIR)codegenlibextmessage2ifft.c $(START_DIR)codegenlibextmessage2diff.c $(START_DIR)codegenlibextmessage2extmessage2_emxutil.c $(START_DIR)codegenlibextmessage2extmessage2_emxAPI.c $(START_DIR)codegenlibextmessage2rt_nonfinite.c $(START_DIR)codegenlibextmessage2rtGetNaN.c $(START_DIR)codegenlibextmessage2rtGetInf.c

ALL_SRCS = 

###########################################################################
## OBJECTS
###########################################################################

OBJS = extmessage2_initialize.o extmessage2_terminate.o extmessage2.o highp.o fft.o sin.o xcorr.o ifft.o diff.o extmessage2_emxutil.o extmessage2_emxAPI.o rt_nonfinite.o rtGetNaN.o rtGetInf.o

ALL_OBJS = 

###########################################################################
## PREBUILT OBJECT FILES
###########################################################################

PREBUILT_OBJS = 

###########################################################################
## LIBRARIES
###########################################################################

LIBS = 

###########################################################################
## SYSTEM LIBRARIES
###########################################################################

SYSTEM_LIBS = 

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CFLAGS += 

#-----------------
# C++ Compiler
#-----------------

CPPFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CPPFLAGS += 

###########################################################################
## INLINED COMMANDS
###########################################################################

###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build clean info prebuild download execute


all : build
	 "### Successfully generated all binary outputs."


build : prebuild 


prebuild : 


download : build


execute : download


###########################################################################
## FINAL TARGET
###########################################################################

#---------------------------------
# Create a static library         
#---------------------------------

 :  
	 "### Creating static library "" ..."
	    $(subst ,/,$(subst ,/,))
	 "### Created: "


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

%.o : %.c
	   "$@" $(subst ,/,"$<")


%.o : %.cpp
	  -o "$@" $(subst ,/,"$<")


%.o : $(START_DIR)%.c
	   "$@" $(subst ,/,"$<")


%.o : $(START_DIR)%.cpp
	  -o "$@" $(subst ,/,"$<")


%.o : $(START_DIR)codegenlibextmessage2%.c
	   "$@" $(subst ,/,"$<")


%.o : $(START_DIR)codegenlibextmessage2%.cpp
	  -o "$@" $(subst ,/,"$<")


%.o : $(MATLAB_ROOT)rtwcsrc%.c
	   "$@" $(subst ,/,"$<")


%.o : $(MATLAB_ROOT)rtwcsrc%.cpp
	  -o "$@" $(subst ,/,"$<")


extmessage2_initialize.o : $(START_DIR)codegenlibextmessage2extmessage2_initialize.c
	   "$@" $(subst ,/,"$<")


extmessage2_terminate.o : $(START_DIR)codegenlibextmessage2extmessage2_terminate.c
	   "$@" $(subst ,/,"$<")


extmessage2.o : $(START_DIR)codegenlibextmessage2extmessage2.c
	   "$@" $(subst ,/,"$<")


highp.o : $(START_DIR)codegenlibextmessage2highp.c
	   "$@" $(subst ,/,"$<")


fft.o : $(START_DIR)codegenlibextmessage2fft.c
	   "$@" $(subst ,/,"$<")


sin.o : $(START_DIR)codegenlibextmessage2sin.c
	   "$@" $(subst ,/,"$<")


xcorr.o : $(START_DIR)codegenlibextmessage2xcorr.c
	   "$@" $(subst ,/,"$<")


ifft.o : $(START_DIR)codegenlibextmessage2ifft.c
	   "$@" $(subst ,/,"$<")


diff.o : $(START_DIR)codegenlibextmessage2diff.c
	   "$@" $(subst ,/,"$<")


extmessage2_emxutil.o : $(START_DIR)codegenlibextmessage2extmessage2_emxutil.c
	   "$@" $(subst ,/,"$<")


extmessage2_emxAPI.o : $(START_DIR)codegenlibextmessage2extmessage2_emxAPI.c
	   "$@" $(subst ,/,"$<")


rt_nonfinite.o : $(START_DIR)codegenlibextmessage2rt_nonfinite.c
	   "$@" $(subst ,/,"$<")


rtGetNaN.o : $(START_DIR)codegenlibextmessage2rtGetNaN.c
	   "$@" $(subst ,/,"$<")


rtGetInf.o : $(START_DIR)codegenlibextmessage2rtGetInf.c
	   "$@" $(subst ,/,"$<")


###########################################################################
## DEPENDENCIES
###########################################################################

 :  rtw_proj.tmw


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	 "### PRODUCT = "
	 "### PRODUCT_TYPE = "
	 "### BUILD_TYPE = "
	 "### INCLUDES = "
	 "### DEFINES = "
	 "### ALL_SRCS = "
	 "### ALL_OBJS = "
	 "### LIBS = "
	 "### MODELREF_LIBS = "
	 "### SYSTEM_LIBS = "
	 "### TOOLCHAIN_LIBS = "
	 "### CFLAGS = "
	 "### LDFLAGS = "
	 "### SHAREDLIB_LDFLAGS = "
	 "### CPPFLAGS = "
	 "### CPP_LDFLAGS = "
	 "### CPP_SHAREDLIB_LDFLAGS = "
	 "### ARFLAGS = "
	 "### MEX_CFLAGS = "
	 "### MEX_CPPFLAGS = "
	 "### MEX_LDFLAGS = "
	 "### MEX_CPPLDFLAGS = "
	 "### DOWNLOAD_FLAGS = "
	 "### EXECUTE_FLAGS = "
	 "### MAKE_FLAGS = "


clean : 
	 "### Deleting all derived files..."
	 $(subst /,\,)
	 $(subst /,\,)
	 "### Deleted all derived files."


