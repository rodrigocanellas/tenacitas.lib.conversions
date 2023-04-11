TEMPLATE = subdirs

SUBDIRS = tst

include (../../../tenacitas.bld/qtcreator/common.pri)

HEADERS=$$BASE_DIR/tenacitas.lib.conversions/alg/cvt.h \
        $$BASE_DIR/tenacitas.lib.conversions/alg/internal/internal.h \
        $$BASE_DIR/tenacitas.lib.conversions/alg/int.h \
        $$BASE_DIR/tenacitas.lib.conversions/typ/base.h \
        $$BASE_DIR/tenacitas.lib.conversions/typ/result.h \
        $$BASE_DIR/tenacitas.lib.conversions/alg/separator.h

DISTFILES += \
    $$BASE_DIR/tenacitas.lib.conversions/README.md
