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
  ClustTools.h \
  CstInfo.h \
  FlowInfo.h \
  FlowInterfaces.h \
  GenInfo.h \
  GenTools.h \
  JetInfo.h \
  NodeInterfaces.h \
  ParInfo.h \
  ParInterfaces.h \
  ParTools.h \
  RecoInfo.h \
  RecoTools.h \
  TreeInterfaces.h \
  TrkInfo.h \
  TrkInterfaces.h \
  TrkTools.h \
  TwrInfo.h \
  TwrInterfaces.h \
  TwrTools.h \
  TupleInterfaces.h \
  VtxInterfaces.h \
  VtxTools.h \
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
  ClustTools.cc \
  CstInfo.cc \
  FlowInfo.cc \
  FlowInterfaces.cc \
  GenInfo.cc \
  GenTools.cc \
  JetInfo.cc \
  NodeInterfaces.cc \
  ParInfo.cc \
  ParInterfaces.cc \
  ParTools.cc \
  RecoInfo.cc \
  RecoTools.cc \
  TrkInfo.cc \
  TreeInterfaces.cc \
  TrkTools.cc \
  TrkInterfaces.cc \
  TupleInterfaces.cc \
  TwrInfo.cc \
  TwrInterfaces.cc \
  TwrTools.cc \
  VtxInterfaces.cc \
  VtxTools.cc

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
