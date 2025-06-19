QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    BaseHashTableWidget.cpp \
    SceneHashTableWidget.cpp \
    TableElementWidget.cpp \
    main.cpp

HEADERS += \
    ../laba-HashTable-Tychinsky/laba-HashTable-Tychinsky/HashTable.h \
    BaseHashTableWidget.h \
    SceneHashTableWidget.h \
    TableElementWidget.h

FORMS += \
    BaseHashTableWidget.ui \
    TableElementWidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ReadMe.md
