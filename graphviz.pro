QT += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    libs/qcustomplot/qcustomplot.cpp \
    main.cpp \
    src/mainwindow.cpp \
    src/utils.cpp

HEADERS += \
    include/mainwindow.h \
    include/utils.h \
    libs/exprtk/exprtk.hpp \
    libs/json/json.hpp \
    libs/qcustomplot/qcustomplot.h

FORMS += \
    ui/mainwindow.ui

INCLUDEPATH += \
    libs/json.hpp

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore \
    README.md

RESOURCES += \
    resource.qrc
