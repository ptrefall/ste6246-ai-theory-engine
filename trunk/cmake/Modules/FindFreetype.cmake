
FIND_PATH(ROCKET_DIR include/freetype/freetype.h
      ../depends
    )

FIND_PATH(ROCKET_INCLUDE_PATH freetype/freetype.h
      ../depends/include
    )
	
FIND_LIBRARY(FREETYPE_LIB_RELEASE
	NAMES freetype-static-mt
    PATHS ../depends/lib
    )

FIND_LIBRARY(FREETYPE_LIB_DEBUG
	NAMES freetype-static-mt-debug
    PATHS ../depends/lib
    )
