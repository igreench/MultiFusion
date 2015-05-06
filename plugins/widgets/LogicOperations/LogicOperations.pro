# #####################################################################
# AlignAndDistribute MultiFusion build script. Mangush Vadim, 2015
# #####################################################################
TEMPLATE = lib
TARGET = LogicOperations
CONFIG += plugin
DEPENDPATH += . \
        ./../../../pluginTool
INCLUDEPATH += . \
        ./../../../pluginTool
LIBS += -L./../../../pluginTool
QT += xml \
        xmlpatterns
DESTDIR = ./../../../bin/plugins/LogicOperations
SOURCES += LogicOperations.cpp
HEADERS += LogicOperations.h \
	Plugin.h \
	InterfacePlugin.h \
        SignalHolder.h
TRANSLATIONS = LogicOperations_ru.ts
RESOURCES += LogicOperations.qrc
FORMS += LogicOperations.ui
