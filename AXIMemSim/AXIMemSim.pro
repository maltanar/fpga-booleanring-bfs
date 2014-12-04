QT       += core sql

TARGET = AXIMemSim
TEMPLATE = app

DEFINES += NO_STORAGE VL_PRINTF=printf VM_TRACE=0 VM_COVERAGE=0

SYSTEMC_ROOT = /home/maltanar/systemc
SYSTEMC_ARCH = linux64
VERILATOR_ROOT = /usr/share/verilator

QMAKE_INCDIR += $$SYSTEMC_ROOT/include $$VERILATOR_ROOT/include $$VERILATOR_ROOT/include/vltstd
QMAKE_LIBDIR += $$SYSTEMC_ROOT/lib-$$SYSTEMC_ARCH

LIBS += -lsystemc -lpthread

SOURCES += main.cpp \
    fixedlatencymem.cpp \
    types.cpp \
    axislave.cpp \
    aximasterwrapper.cpp \
    axitypes.cpp \
    peripheral-src/VDataPuller__Syms.cpp \
    peripheral-src/VDataPuller.cpp \
    peripheral-src/verilated.cpp

HEADERS += \
    types.h \
    fixedlatencymem.h \
    params.h \
    axislave.h \
    axitypes.h \
    aximasterwrapper.h \
    peripheral-src/VDataPuller__Syms.h \
    peripheral-src/VDataPuller.h
