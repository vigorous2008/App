###########################################################################
## Makefile generated for MATLAB file/project 'extmessage'. 
## 
## Makefile     : extmessage_rtw.mk
## Generated on : Thu Oct 26 12:54:10 2017
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
MATLAB_ARCH_BIN           = C:\PROGRA~1\MATLAB\R2017a\binglnxa64
MASTER_ANCHOR_DIR         = 
START_DIR                 = D:\matlab_m\1
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

PRODUCT = $(RELATIVE_PATH_TO_ANCHOR)extmessage.a
PRODUCT_TYPE = "static-library"
BUILD_TYPE = "Static Library"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = -ccflags$(START_DIR)codegenlibextmessage -ccflags$(START_DIR) -ccflags$(MATLAB_ROOT)externinclude -ccflags$(MATLAB_ROOT)simulinkinclude -ccflags$(MATLAB_ROOT)rtwcsrc -ccflags$(MATLAB_ROOT)rtwcsrcext_modecommon -ccflags$(MATLAB_ROOT)rtwcert

INCLUDES = 

###########################################################################
## DEFINES
###########################################################################

DEFINES_STANDARD = MODEL=extmessage HAVESTDIO USE_RTMODEL

DEFINES = 

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)codegenlibextmessageextmessage_initialize.c $(START_DIR)codegenlibextmessageextmessage_terminate.c $(START_DIR)codegenlibextmessageextmessage.c $(START_DIR)codegenlibextmessageabs.c $(START_DIR)codegenlibextmessagefft.c $(START_DIR)codegenlibextmessagefilter.c $(START_DIR)codegenlibextmessageifft.c $(START_DIR)codegenlibextmessagelx_smooth.c $(START_DIR)codegenlibextmessagediff.c $(START_DIR)codegenlibextmessageany.c $(START_DIR)codegenlibextmessagefilterpointer2.c $(START_DIR)codegenlibextmessagemean.c $(START_DIR)codegenlibextmessagesign.c $(START_DIR)codegenlibextmessagenullAssignment.c $(START_DIR)codegenlibextmessagesort1.c $(START_DIR)codegenlibextmessagesortIdx.c $(START_DIR)codegenlibextmessagemod.c $(START_DIR)codegenlibextmessageextmessage_emxutil.c $(START_DIR)codegenlibextmessageextmessage_emxAPI.c $(START_DIR)codegenlibextmessagert_nonfinite.c $(START_DIR)codegenlibextmessagertGetNaN.c $(START_DIR)codegenlibextmessagertGetInf.c

ALL_SRCS = 

###########################################################################
## OBJECTS
###########################################################################

OBJS = extmessage_initialize.o extmessage_terminate.o extmessage.o abs.o fft.o filter.o ifft.o lx_smooth.o diff.o any.o filterpointer2.o mean.o sign.o nullAssignment.o sort1.o sortIdx.o mod.o extmessage_emxutil.o extmessage_emxAPI.o rt_nonfinite.o rtGetNaN.o rtGetInf.o

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


%.o : $(START_DIR)codegenlibextmessage%.c
	   "$@" $(subst ,/,"$<")


%.o : $(START_DIR)codegenlibextmessage%.cpp
	  -o "$@" $(subst ,/,"$<")


%.o : $(MATLAB_ROOT)rtwcsrc%.c
	   "$@" $(subst ,/,"$<")


%.o : $(MATLAB_ROOT)rtwcsrc%.cpp
	  -o "$@" $(subst ,/,"$<")


extmessage_initialize.o : $(START_DIR)codegenlibextmessageextmessage_initialize.c
	   "$@" $(subst ,/,"$<")


extmessage_terminate.o : $(START_DIR)codegenlibextmessageextmessage_terminate.c
	   "$@" $(subst ,/,"$<")


extmessage.o : $(START_DIR)codegenlibextmessageextmessage.c
	   "$@" $(subst ,/,"$<")


abs.o : $(START_DIR)codegenlibextmessageabs.c
	   "$@" $(subst ,/,"$<")


fft.o : $(START_DIR)codegenlibextmessagefft.c
	   "$@" $(subst ,/,"$<")


filter.o : $(START_DIR)codegenlibextmessagefilter.c
	   "$@" $(subst ,/,"$<")


ifft.o : $(START_DIR)codegenlibextmessageifft.c
	   "$@" $(subst ,/,"$<")


lx_smooth.o : $(START_DIR)codegenlibextmessagelx_smooth.c
	   "$@" $(subst ,/,"$<")


diff.o : $(START_DIR)codegenlibextmessagediff.c
	   "$@" $(subst ,/,"$<")


any.o : $(START_DIR)codegenlibextmessageany.c
	   "$@" $(subst ,/,"$<")


filterpointer2.o : $(START_DIR)codegenlibextmessagefilterpointer2.c
	   "$@" $(subst ,/,"$<")


mean.o : $(START_DIR)codegenlibextmessagemean.c
	   "$@" $(subst ,/,"$<")


sign.o : $(START_DIR)codegenlibextmessagesign.c
	   "$@" $(subst ,/,"$<")


nullAssignment.o : $(START_DIR)codegenlibextmessagenullAssignment.c
	   "$@" $(subst ,/,"$<")


sort1.o : $(START_DIR)codegenlibextmessagesort1.c
	   "$@" $(subst ,/,"$<")


sortIdx.o : $(START_DIR)codegenlibextmessagesortIdx.c
	   "$@" $(subst ,/,"$<")


mod.o : $(START_DIR)codegenlibextmessagemod.c
	   "$@" $(subst ,/,"$<")


extmessage_emxutil.o : $(START_DIR)codegenlibextmessageextmessage_emxutil.c
	   "$@" $(subst ,/,"$<")


extmessage_emxAPI.o : $(START_DIR)codegenlibextmessageextmessage_emxAPI.c
	   "$@" $(subst ,/,"$<")


rt_nonfinite.o : $(START_DIR)codegenlibextmessagert_nonfinite.c
	   "$@" $(subst ,/,"$<")


rtGetNaN.o : $(START_DIR)codegenlibextmessagertGetNaN.c
	   "$@" $(subst ,/,"$<")


rtGetInf.o : $(START_DIR)codegenlibextmessagertGetInf.c
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


