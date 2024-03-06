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
  ClustInfo.h \
  ClustInterfaces.h \
  CstInfo.h \
  FlowInfo.h \
  FlowInterfaces.h \
  GenInfo.h \
  JetInfo.h \
  NodeInterfaces.h \
  ParInfo.h \
  RecoInfo.h \
  RecoTools.h \
  TreeInterfaces.h \
  TrkInfo.h \
  TrkInterfaces.h \
  TrkTools.h \
  TupleInterfaces.h \
  VtxInterfaces.h \
  Constants.h \
  Interfaces.h \
  Tools.h \
  Types.h

if ! MAKEROOT6
  ROOT5_DICTS = \
    SCorrelatorUtilities_Dict.cc
endif

libscorrelatorutilities_la_SOURCES = \
  $(ROOT5_DICTS) \
  ClustInfo.cc \
  ClustInterfaces.cc \
  CstInfo.cc \
  FlowInfo.cc \
  FlowInterfaces.cc \
  JetInfo.cc \
  NodeInterfaces.cc \
  ParInfo.cc \
  RecoInfo.cc \
  RecoTools.cc \
  TrkInfo.cc \
  TreeInterfaces.cc \
  TrkTools.cc \
  TrkInterfaces.cc \
  TupleInterfaces.cc \
  VtxInterfaces.cc

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
