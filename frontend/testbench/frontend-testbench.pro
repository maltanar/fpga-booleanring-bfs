TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

QT += core

SOURCES += main.cpp \
    verilated.cpp \
    VFrontendController__Syms.cpp \
    VFrontendController.cpp \
    CSCGraph.cpp

SYSTEMC_ROOT = /home/maltanar/systemc
SYSTEMC_ARCH = linux64
VERILATOR_ROOT = /usr/share/verilator

QMAKE_INCDIR += $$SYSTEMC_ROOT/include $$VERILATOR_ROOT/include $$VERILATOR_ROOT/include/vltstd
QMAKE_LIBDIR += $$SYSTEMC_ROOT/lib-$$SYSTEMC_ARCH

DEPENDPATH *= $${INCLUDEPATH}

LIBS += -lsystemc -lpthread

HEADERS += \
    VFrontendController__Syms.h \
    VFrontendController.h \
    InputFIFOAdapter.h \
    OutputFIFOAdapter.h \
    CSCGraph.h

