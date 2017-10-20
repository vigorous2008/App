###########################################################################
## Makefile generated for MATLAB file/project 'extmessage'. 
## 
## Makefile     : extmessage_rtw.mk
## Generated on : Fri Oct 20 14:07:24 2017
## MATLAB Coder version: 3.3 (R2017a)
## 
## Build Info:
## 
## Final product: $(RELATIVE_PATH_TO_ANCHOR)extmessage.a
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

PRODUCT_NAME              = extmessage
MAKEFILE                  = extmessage_rtw.mk
COMPUTER                  = PCWIN64
MATLAB_ROOT               = C:\PROGRA~1\MATLAB\R2017a
MATLAB_BIN                = C:\PROGRA~1\MATLAB\R2017a\bin
MATLAB_ARCH_BIN           = C:\PROGRA~1\MATLAB\R2017a\binwin64
MASTER_ANCHOR_DIR         = 
START_DIR                 = D:\matlab_m\1
ARCH                      = win64
RELATIVE_PATH_TO_ANCHOR   = .
C_STANDARD_OPTS           = 
CPP_STANDARD_OPTS         = 

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          QuestaSim_Win64 v1.0 | nmake (64-bit Windows)
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

# Builder: NMAKE Utility
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
MEX_EXT             = .mexw64
MAKE_EXT            = .do


###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = $(RELATIVE_PATH_TO_ANCHOR)extmessage.a
PRODUCT_TYPE = "static-library"
BUILD_TYPE = "Static Library"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = $(START_DIR)codegenlibextmessage;$(START_DIR);$(MATLAB_ROOT)externinclude;$(MATLAB_ROOT)simulinkinclude;$(MATLAB_ROOT)rtwcsrc;$(MATLAB_ROOT)rtwcsrcext_modecommon;$(MATLAB_ROOT)rtwcert

INCLUDES = 

###########################################################################
## DEFINES
###########################################################################

DEFINES_STANDARD = MODEL=extmessage HAVESTDIO USE_RTMODEL

DEFINES = 

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)codegenlibextmessageextmessage_initialize.c $(START_DIR)codegenlibextmessageextmessage_terminate.c $(START_DIR)codegenlibextmessageextmessage.c $(START_DIR)codegenlibextmessagefft.c $(START_DIR)codegenlibextmessagefilter.c $(START_DIR)codegenlibextmessageifft.c $(START_DIR)codegenlibextmessagelx_smooth.c $(START_DIR)codegenlibextmessagediff.c $(START_DIR)codegenlibextmessageany.c $(START_DIR)codegenlibextmessagenullAssignment.c $(START_DIR)codegenlibextmessageextmessage_emxutil.c $(START_DIR)codegenlibextmessageextmessage_emxAPI.c $(START_DIR)codegenlibextmessagert_nonfinite.c $(START_DIR)codegenlibextmessagertGetNaN.c $(START_DIR)codegenlibextmessagertGetInf.c

ALL_SRCS = 

###########################################################################
## OBJECTS
###########################################################################

OBJS = extmessage_initialize.o extmessage_terminate.o extmessage.o fft.o filter.o ifft.o lx_smooth.o diff.o any.o nullAssignment.o extmessage_emxutil.o extmessage_emxAPI.o rt_nonfinite.o rtGetNaN.o rtGetInf.o

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

CFLAGS_BASIC = $(DEFINES) 

CFLAGS =  

#-----------------
# C++ Compiler
#-----------------

CPPFLAGS_BASIC = $(DEFINES) 

CPPFLAGS =  

###########################################################################
## INLINED COMMANDS
###########################################################################

###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build clean info prebuild download execute set_environment_variables


all : build
	@cmd /C " ### Successfully generated all binary outputs."


build : set_environment_variables prebuild 


prebuild : 


download : build


execute : download


set_environment_variables : 
	@set INCLUDE=$(INCLUDES);$(INCLUDE)
	@set LIB=$(LIB)


###########################################################################
## FINAL TARGET
###########################################################################

#---------------------------------
# Create a static library         
#---------------------------------

 :  
	@cmd /C " ### Creating static library "" ..."
	    $(subst ,\,$(subst ,\,))
	@cmd /C " ### Created: "


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

.c.o :
	   "$@" $(subst ,\,"$<")


.cpp.o :
	  -o "$@" $(subst ,\,"$<")


.c.o :
	   "$@" $(subst ,\,"$<")


.cpp.o :
	  -o "$@" $(subst ,\,"$<")


.c.o :
	   "$@" $(subst ,\,"$<")


.cpp.o :
	  -o "$@" $(subst ,\,"$<")


.c.o :
	   "$@" $(subst ,\,"$<")


.cpp.o :
	  -o "$@" $(subst ,\,"$<")


.c.o :
	   "$@" $(subst ,\,"$<")


.c.o :
	   "$@" $(subst ,\,"$<")


.c.o :
	   "$@" $(subst ,\,"$<")


.c.o :
	   "$@" $(subst ,\,"$<")


.c.o :
	   "$@" $(subst ,\,"$<")


.c.o :
	   "$@" $(subst ,\,"$<")


.c.o :
	   "$@" $(subst ,\,"$<")


.c.o :
	   "$@" $(subst ,\,"$<")


.c.o :
	   "$@" $(subst ,\,"$<")


.c.o :
	   "$@" $(subst ,\,"$<")


.c.o :
	   "$@" $(subst ,\,"$<")


.c.o :
	   "$@" $(subst ,\,"$<")


.c.o :
	   "$@" $(subst ,\,"$<")


.c.o :
	   "$@" $(subst ,\,"$<")


.c.o :
	   "$@" $(subst ,\,"$<")


###########################################################################
## DEPENDENCIES
###########################################################################

 :  rtw_proj.tmw


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	@cmd /C " ### PRODUCT = "
	@cmd /C " ### PRODUCT_TYPE = "
	@cmd /C " ### BUILD_TYPE = "
	@cmd /C " ### INCLUDES = "
	@cmd /C " ### DEFINES = "
	@cmd /C " ### ALL_SRCS = "
	@cmd /C " ### ALL_OBJS = "
	@cmd /C " ### LIBS = "
	@cmd /C " ### MODELREF_LIBS = "
	@cmd /C " ### SYSTEM_LIBS = "
	@cmd /C " ### TOOLCHAIN_LIBS = "
	@cmd /C " ### CFLAGS = "
	@cmd /C " ### LDFLAGS = "
	@cmd /C " ### SHAREDLIB_LDFLAGS = "
	@cmd /C " ### CPPFLAGS = "
	@cmd /C " ### CPP_LDFLAGS = "
	@cmd /C " ### CPP_SHAREDLIB_LDFLAGS = "
	@cmd /C " ### ARFLAGS = "
	@cmd /C " ### MEX_CFLAGS = "
	@cmd /C " ### MEX_CPPFLAGS = "
	@cmd /C " ### MEX_LDFLAGS = "
	@cmd /C " ### MEX_CPPLDFLAGS = "
	@cmd /C " ### DOWNLOAD_FLAGS = "
	@cmd /C " ### EXECUTE_FLAGS = "
	@cmd /C " ### MAKE_FLAGS = "


clean : 
	 "### Deleting all derived files..."
	@if exist   
	 
	 "### Deleted all derived files."


