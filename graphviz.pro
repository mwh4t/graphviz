QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    libs/qcustomplot/qcustomplot.cpp \
    main.cpp \
    src/authorizationwindow.cpp \
    src/mainwindow.cpp \
    src/utils.cpp

HEADERS += \
    include/authorizationwindow.h \
    include/mainwindow.h \
    include/utils.h \
    libs/exprtk/exprtk.hpp \
    libs/json/json.hpp \
    libs/qcustomplot/qcustomplot.h

FORMS += \
    ui/authorizationwindow.ui \
    ui/mainwindow.ui

INCLUDEPATH += \
    libs/json.hpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore \
    README.md
