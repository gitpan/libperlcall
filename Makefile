# Copyright (C) 2000 by John Tobey,
# jtobey@john-edwin-tobey.org.  All rights reserved.
# 
#   This program is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation; either version 2 of the License, or
#   (at your option) any later version.
# 
#   This program is distributed in the hope that it will be useful, but
#   WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#   General Public License for more details.
# 
#   You should have received a copy of the GNU General Public License
#   along with this program; see the file COPYING.  If not, write to the
#   Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston,
#   MA 02111-1307  USA

CXX = g++
CC = g++
OPTIMIZE =
PERL = perl
# Perl before 5.5.670(?) added -Dbool=char to ccopts.
# This conflicts with overloaded function declarations.  -Ubool fixes it.
PERL_CFLAGS = $(shell $(PERL) -MExtUtils::Embed -e ccopts) -Wno-unused
PERL_LDFLAGS = $(shell $(PERL) -MExtUtils::Embed -e ldopts)
BASE_CFLAGS = -Wall -g -fPIC $(OPTIMIZE) -I.
CFLAGS = $(BASE_CFLAGS) $(PERL_CFLAGS) $(LCFLAGS)
BASE_CXXFLAGS = $(BASE_CFLAGS)
CXXFLAGS = $(BASE_CXXFLAGS) $(PERL_CFLAGS) -Ubool $(LCXXFLAGS)
PREFIX = /usr/local

LIBOBJS = interpreter.o scalar.o scalarref.o arrayref.o hashref.o coderef.o \
	containers.o
LIBHEADERS = perlcall.hh containers.hh overloads.hh date.hh

.PHONY: all install clean realclean distclean

all: libperlcall.so libperlint.so doc

doc: libperlcall.3

%.3: %.pod
	pod2man --section=3 $< > $@

%.html: %.pod
	pod2html --infile=$< --outfile=$@

test_dynamic: test.o libperlcall.so libperlint.so
	$(CXX) test.o -L. -lperlcall -lperlint -Wl,-rpath,. -o $@

test: test.o $(LIBOBJS) perlxsi.o
	$(CXX) $^ $(PERL_LDFLAGS) -o $@
	-./test


test.o: test.cc
	$(CXX) $(BASE_CXXFLAGS) -c $< -o $@

%.so: %.so.1
	rm -f $@
	ln -s $@.1 $@

libperlint.so.1:
	$(CC) -shared -u perl_alloc -u boot_DynaLoader $(PERL_LDFLAGS) \
		-Wl,-soname,$@ -o $@

perlxsi.c:
	$(PERL) -MExtUtils::Embed -e xsinit

libperlcall.so.1: $(LIBOBJS) perlxsi.o
	$(CXX) -shared $^ -Wl,-soname,$@ -o $@

install: $(LIBHEADERS) libperlcall.so.1 libperlint.so.1
	test -d $(PREFIX)/include/jtobey || mkdir -p $(PREFIX)/include/jtobey
	cp -p $(LIBHEADERS) $(PREFIX)/include/jtobey
	test -d $(PREFIX)/lib || mkdir -p $(PREFIX)/lib
	cp -p libperlcall.so.1 $(PREFIX)/lib
	rm -f $(PREFIX)/lib/libperlcall.so
	ln -s libperlcall.so.1 $(PREFIX)/lib/libperlcall.so
	cp -p libperlint.so.1 $(PREFIX)/lib
	rm -f $(PREFIX)/lib/libperlint.so
	ln -s libperlint.so.1 $(PREFIX)/lib/libperlint.so

clean:
	rm -f *.o perlxsi.c

realclean: clean
	rm -f test test_dynamic

distclean: realclean
	rm -f libperlcall.so libperlcall.so.1 libperlint.so libperlint.so.1

$(LIBOBJS): perlcall.hh
interpreter.o scalar.o scalarref.o arrayref.o hashref.o coderef.o: \
	perlcall_int.hh
containers.o: containers.hh
test.o: perlcall.hh date.hh containers.hh
