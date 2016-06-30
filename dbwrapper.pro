
CONFIG(debug, debug|release) {
	message("dbwrapper_debug")

	TARGET = dbwrapper_debug

	DESTDIR = $$_PRO_FILE_PWD_/../.dist
	OBJECTS_DIR = $$_PRO_FILE_PWD_/../.int/dbwrapper_debug

} else {
	message("dbwrapper_release")

	TARGET = dbwrapper

	DESTDIR = $$_PRO_FILE_PWD_/../.dist
	OBJECTS_DIR = $$_PRO_FILE_PWD_/../.int/dbwrapper_release
}

TEMPLATE = app
CONFIG += console precompile_header c++14
CONFIG -= qt
MAKEFILE = $$_PRO_FILE_PWD_/dbwrapper.makefile

#-------------------------------------------------------------------------------------------------
# warnings
#-------------------------------------------------------------------------------------------------
QMAKE_CXXFLAGS_WARN_ON += \
	-Wno-parentheses \
	-Wno-unused-variable \
	-Wno-unused-parameter \
	-Wno-unused-local-typedefs \
	-Wno-attributes \
	-Wno-unused-but-set-variable \
	-Wno-unused-result \
	-Wno-switch

#-------------------------------------------------------------------------------------------------
# compiler flags
#-------------------------------------------------------------------------------------------------
QMAKE_CXXFLAGS += \
	-m64 \
	-msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 -mavx -mf16c \
	-g \
	-fpic \
	-fdata-sections \
	-ffunction-sections \
	-fno-strict-aliasing \
	-I$$_PRO_FILE_PWD_/../auxiliary \
	-I$$_PRO_FILE_PWD_/../audioconvert \
	-I$$_PRO_FILE_PWD_/../postgres \
	-I$$_PRO_FILE_PWD_/../thirdparty/postgresql/src/include \
	-I$$_PRO_FILE_PWD_/../thirdparty/postgresql_config/linux \
	-I$$_PRO_FILE_PWD_/platform/linux

PRECOMPILED_HEADER = $$_PRO_FILE_PWD_/platform/linux/platform.h

CONFIG(debug, debug|release) {
	DEFINES += _DEBUG DEBUG

} else {
	DEFINES += NDEBUG

	QMAKE_CFLAGS_RELEASE -= -O0 -O1 -O2
	QMAKE_CFLAGS_RELEASE *= -O3

	QMAKE_CXXFLAGS_RELEASE -= -O0 -O1 -O2
	QMAKE_CXXFLAGS_RELEASE *= -O3
}

#-------------------------------------------------------------------------------------------------
# linker flags
#-------------------------------------------------------------------------------------------------
LIBS += \
	-L$$DESTDIR \
	-Wl,--unresolved-symbols=report-all \
	-Wl,--gc-sections \
	-Wl,-rpath,./

LIBS += \
	-l:libboost_system.a \
	-l:libboost_filesystem.a

CONFIG(debug, debug|release) {
	LIBS += \
		-lauxiliary_debug

} else {
	LIBS += \
		-lauxiliary \
		-O3
}

QMAKE_LFLAGS_RELEASE -= -Wl,-O0 -Wl,-O1 -Wl,-O2
QMAKE_LFLAGS_RELEASE *= -Wl,-O3

#-------------------------------------------------------------------------------------------------
# dependencies
#-------------------------------------------------------------------------------------------------
makedist.commands = objcopy -v --strip-debug --strip-unneeded --target elf64-x86-64 $$DESTDIR/$${TARGET} $$DESTDIR/$${TARGET}_dist

first.depends = $(first) makedist
export(first.depends)
export(makedist.commands)

QMAKE_EXTRA_TARGETS += first makedist

#------------------------------------------------------------------------------------------------
# files
#-------------------------------------------------------------------------------------------------
SOURCES += \
	platform/linux/main.cpp \
    source/SpeechStorage/SpeechStorage.cpp \
    source/SpeechStorage/TemplatesForUtterances.cpp \
    source/SpeechStorage/SpeechStorageDialog.cpp

HEADERS += \
	../postgres/postgres.h \
	../postgres/source/ArgumentsDynamicBinder.h \
	../postgres/source/ArgumentsStaticBinder.h \
	../postgres/source/ArgumentsVerifier.h \
	../postgres/source/PostgresClient.h \
	../postgres/source/PostgresConnection.h \
	../postgres/source/PostgresStatement.h \
	../postgres/source/PostgresTemplate.h \
	../postgres/source/PostgresTraits.h \
	platform/linux/platform.h \
    source/SpeechStorage/Miscellaneous.h \
    source/SpeechStorage/SpeechStorage.h \
    source/SpeechStorage/TemplatesForUtterances.h \
    source/SpeechStorage/SpeechStorageDialog.h

