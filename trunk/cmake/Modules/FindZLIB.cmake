FIND_PATH(ZLIB_INCLUDE_DIR zlib.h
	../depends/include
)

FIND_LIBRARY(ZLIB_LIBRARY_DEBUG
    NAMES zlib-static-mt-debug
    PATHS ../depends/lib
)
FIND_LIBRARY(ZLIB_LIBRARY_RELEASE
    NAMES zlib-static-mt
    PATHS ../depends/lib
)
