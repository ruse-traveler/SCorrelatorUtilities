AUTOMAKE_OPTIONS = foreign

lib_LTLIBRARIES = \
    libscorrelatorutilities.la

AM_LDFLAGS = \
  -L$(libdir) \
  -L$(OFFLINE_MAIN)/lib

AM_CPPFLAGS = \
  -I$(includedir) \
  -I$(OFFLINE_MAIN)/include \
  -I$(ROOTSYS)/include

pkginclude_HEADERS = \
  CalTools.h \
  ClustInfo.h \
  Constants.h \
  CstInfo.h \
  EvtTools.h \
  FlowTools.h \
  GenTools.h \
  Interfaces.h \
  JetTools.h \
  TrkTools.h \
  VtxTools.h \
  SCorrelatorUtilities.h

if ! MAKEROOT6
  ROOT5_DICTS = \
    SCorrelatorUtilities_Dict.cc
endif

libscorrelatorutilities_la_SOURCES = \
  $(ROOT5_DICTS) \
  CalTools.cc \
  ClustInfo.cc \
  CstInfo.cc \
  EvtTools.cc \
  FlowTools.cc \
  GenTools.cc \
  Interfaces.cc \
  JetTools.cc \
  TrkTools.cc \
  VtxTools.cc \
  SCorrelatorUtilities.cc

libscorrelatorutilities_la_LDFLAGS = \
  -L$(libdir) \
  -L$(OFFLINE_MAIN)/lib \
  -lcalo_io \
  -lfun4all \
  -lg4detectors_io \
  -lphg4hit \
  -lg4dst \
  -lg4eval \
  `fastjet-config --libs`


################################################
# linking tests

noinst_PROGRAMS = \
  testexternals

testexternals_SOURCES = testexternals.C
testexternals_LDADD = libscorrelatorutilities.la

testexternals.C:
	echo "//*** this is a generated file. Do not commit, do not edit" > $@
	echo "int main()" >> $@
	echo "{" >> $@
	echo "  return 0;" >> $@
	echo "}" >> $@

# Rule for generating table CINT dictionaries.
%_Dict.cc: %.h %LinkDef.h
	rootcint -f $@ @CINTDEFS@ -c $(DEFAULT_INCLUDES) $(AM_CPPFLAGS) $^

clean-local:
	rm -f *Dict* $(BUILT_SOURCES) *.pcm
