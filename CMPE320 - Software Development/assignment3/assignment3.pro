QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    fractioncalculator.cpp

HEADERS += \
    FractionLibrary/Fraction_global.h \
    FractionLibrary/fraction.h \
    fractioncalculator.h

FORMS += \
    fractioncalculator.ui

INCLUDEPATH += -L“$$PWD/FractionLibrary”

LIBS += -L“$$PWD/FractionLibrary/Fraction.dll”

LIBS += "$$PWD/FractionLibrary/libFraction.a"

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    FractionLibrary/Fraction.dll

