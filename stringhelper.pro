

TEMPLATE = app
CONFIG += console
CONFIG -= qt


#DESTDIR += bin
CONFIG  += x86_64

OBJECTS_DIR = .tmp
MOC_DIR = .tmp
UI_DIR = .tmp
RCC_DIR = .tmp

QMAKE_CXXFLAGS += -gdwarf-3

QMAKE_CXXFLAGS_DEBUG += -O0
QMAKE_CXXFLAGS_DEBUG += -std=c++0x
QMAKE_CXXFLAGS_DEBUG += -Wparentheses
QMAKE_CXXFLAGS_DEBUG += -Wreturn-type
QMAKE_CXXFLAGS_DEBUG += -Wshadow
QMAKE_CXXFLAGS_DEBUG += -Wextra
QMAKE_CXXFLAGS_DEBUG += -Wunused-parameter
QMAKE_CXXFLAGS_DEBUG -= -Wwrite-strings
QMAKE_CXXFLAGS_DEBUG -= -Wunused-variable
QMAKE_CXXFLAGS_DEBUG += -Wno-unused-variable
QMAKE_CXXFLAGS_DEBUG += -Wno-unused-but-set-variable
QMAKE_CXXFLAGS_DEBUG += -Weffc++

QMAKE_CXXFLAGS_RELEASE += -O2
QMAKE_CXXFLAGS_RELEASE += -std=c++0x
QMAKE_CXXFLAGS_RELEASE += -Wparentheses
QMAKE_CXXFLAGS_RELEASE += -Wreturn-type
QMAKE_CXXFLAGS_RELEASE += -Wshadow
QMAKE_CXXFLAGS_RELEASE += -Wextra
QMAKE_CXXFLAGS_RELEASE += -Wunused-parameter
QMAKE_CXXFLAGS_RELEASE -= -Wwrite-strings
QMAKE_CXXFLAGS_RELEASE -= -Wunused-variable
QMAKE_CXXFLAGS_RELEASE += -Wno-unused-variable
QMAKE_CXXFLAGS_RELEASE += -Weffc++

              ^

SOURCES += src/main.cpp \
    src/hstring/stringhelper.cpp \
    src/hstring/gettokens.cpp \
    src/test_hstring.cpp \
    src/test1.cpp

HEADERS +=  \
    src/hstring/stringhelper.h \
    src/hstring/gettokens.h \
    src/test_hstring.h

INCLUDEPATH += $$PWD/src
INCLUDEPATH += $$PWD/src/hstring


message("qmake stringhelper")

OTHER_FILES += \
    lgpl-3.0.txt \
    README.md