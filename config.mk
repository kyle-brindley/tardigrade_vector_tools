# Micromorphic filter, a variationally based filter for DNS
#
# Author: Nathan A. Miller (LANL / CU Boulder)
# Email:  nathanm@lanl.gov
# Date:   July 13, 2018
#
# This is the common configuration file for all of the included makefiles

# Check for icc compiler or default to g++
ICC_EXIST:=$(shell which icc)
ifdef ICC_EXIST
    CXX=icc
    CFLAGS=-std=c++11 -Wall -ansi -pedantic -O3 -I. -fmax-errors=5
else
    CXX=g++
    CFLAGS=-std=gnu++11 -Wall -ansi -pedantic -O3 -I. -fmax-errors=5
endif

# Location of the Eigen library
EIGEN=-I$(abspath $(patsubst %/,%,$(dir $(abspath $(lastword $(MAKEFILE_LIST)))))/../eigen)

# The python command
PYTHON=/apps/anaconda3/bin/python

# Additional includes
ROOTDIR:=$(abspath $(patsubst %/,%,$(dir $(abspath $(lastword $(MAKEFILE_LIST)))))/../)
SOURCE=$(ROOTDIR)/vector_tools/src/cpp
HEADER=$(ROOTDIR)/vector_tools/src/cpp
