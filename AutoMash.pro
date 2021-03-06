QT += qml quick

QMAKE_CXXFLAGS += -pthread
QMAKE_CXXFLAGS += -D__GCC_HAVE_SYNC_COMPARE_AND_SWAP_1
QMAKE_CXXFLAGS += -D__GCC_HAVE_SYNC_COMPARE_AND_SWAP_2
QMAKE_CXXFLAGS += -D__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4
QMAKE_CXXFLAGS += -D__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8

CONFIG += c++11

SOURCES += main.cpp \
    mashschedule.cpp \
    grainbill.cpp \
    hops.cpp \
    pump.cpp \
    i2c.cpp \
    automash.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    mashschedule.h \
    grainbill.h \
    hops.h \
    helpers.h \
    pump.h \
    i2c.h \
    automash.h

macx: LIBS += -L/opt/local/lib/ -lboost_date_time-mt

INCLUDEPATH += /opt/local/include
DEPENDPATH += /opt/local/include
