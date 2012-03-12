
FIND_PATH(IRR_DIR include/Irrlicht/irrlicht.h
      ../depends
    )
	
FIND_PATH(IRR_INCLUDE_PATH Irrlicht/irrlicht.h
      ../depends/include
    )

FIND_LIBRARY(IRR_LIB_DEBUG
  NAMES Irrlicht-static-mt-debug
  PATHS ../depends/lib
    )
	
FIND_LIBRARY(IRR_LIB_RELEASE
  NAMES Irrlicht-static-mt
  PATHS ../depends/lib
    )