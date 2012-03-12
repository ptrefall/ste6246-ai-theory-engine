cmake_minimum_required(VERSION 2.8)

#---------------------------------------------------------------
project(AITheoryEngine)
#---------------------------------------------------------------
set(ENTITY_HDRS
	./Entity/Entity.h
	./Entity/EntityManager.h
)
SOURCE_GROUP("Header Files\\Entity" FILES ${ENTITY_HDRS})
#---------------------------------------------------------------
set(ENTITY_SRCS
	./Entity/EntityManager.cpp
)
SOURCE_GROUP("Source Files\\Entity" FILES ${ENTITY_SRCS})
#---------------------------------------------------------------
set(ENTITY_COMPONENT_HDRS
	./Entity/Components/Health.h
	./Entity/Components/Sprite.h
)
SOURCE_GROUP("Header Files\\Entity\\Components" FILES ${ENTITY_COMPONENT_HDRS})
#---------------------------------------------------------------
set(ENTITY_COMPONENT_SRCS
	./Entity/Components/Health.cpp
	./Entity/Components/Sprite.cpp
)
SOURCE_GROUP("Source Files\\Entity\\Components" FILES ${ENTITY_COMPONENT_SRCS})
#---------------------------------------------------------------
set(HDRS
	${ENTITY_HDRS} 
	${ENTITY_COMPONENT_HDRS}
)
#---------------------------------------------------------------
set(SRCS
	${ENTITY_SRCS}
	${ENTITY_COMPONENT_SRCS}
	./main.cpp
)
#---------------------------------------------------------------
find_package(Irrlicht REQUIRED)
#---------------------------------------------------------------
add_executable(AITheoryEngine ${HDRS} ${SRCS})
#---------------------------------------------------------------
set_target_properties(AITheoryEngine PROPERTIES DEBUG_POSTFIX _d)
set_target_properties(AITheoryEngine PROPERTIES LINKER_LANGUAGE CXX)
#---------------------------------------------------------------
target_link_libraries(TradingAgent
  debug ${IRR_LIB_DEBUG} optimized ${IRR_LIB_RELEASE}
)
#---------------------------------------------------------------