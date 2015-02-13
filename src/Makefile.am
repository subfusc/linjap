## Process this file with automake to produce Makefile.in

## Created by Anjuta

uidir = $(datadir)/linjap/ui
ui_DATA = linjap.ui

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	$(LINJAP_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = linjap

linjap_SOURCES = \
	main.cpp\
	Mode.cpp \
	Mode.hpp \
	Mode_eng_jap.cpp \
	Mode_eng_jap.hpp \
	NeWindow.cpp \
	NeWindow.hpp \
	PopWindow.cpp \
	PopWindow.hpp \
	Queue.cpp \
	Queue.hpp \
	Word.cpp \
	Word.hpp \
	MainWindow.cpp \
	MainWindow.hpp \
	LList.cpp \
	LList.hpp \
	LListNode.cpp \
	LListNode.hpp \
	LLNNode.cpp \
	LLNNode.hpp \
	Av.hpp \
	Data.cpp \
	Data.hpp \
	Engine.cpp \
	Engine.hpp \
	FileReader.cpp \
	FileReader.hpp \
	HelpWindow.cpp \
	HelpWindow.hpp

linjap_LDFLAGS = 

linjap_LDADD = $(LINJAP_LIBS)

EXTRA_DIST = $(ui_DATA)

# Remove ui directory on uninstall
uninstall-local:
	-rm -r $(uidir)
	-rm -r $(datadir)/linjap
