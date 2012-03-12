cmake_minimum_required(VERSION 2.8)

#---------------------------------------------------------------
project(AITheoryEngine)
#---------------------------------------------------------------
set(DependsTotem_HDRS
  ../depends/include/Totem/IComponent.h
  ../depends/include/Totem/Component.h
  ../depends/include/Totem/ComponentContainer.h
  ../depends/include/Totem/IProperty.h
  ../depends/include/Totem/Property.h
  ../depends/include/Totem/PropertyContainer.h
  ../depends/include/Totem/IPropertyList.h
  ../depends/include/Totem/PropertyList.h
  ../depends/include/Totem/PropertyListContainer.h
  ../depends/include/Totem/HashedString.h
)
SOURCE_GROUP("Header Files\\Depends\\Totem" FILES ${DependsTotem_HDRS})
#---------------------------------------------------------------
set(DependsTotemAddons_HDRS
  ../depends/include/Totem/Addons/EventSystem.h
  ../depends/include/Totem/Addons/DelegateSystem.h
)
SOURCE_GROUP("Header Files\\Depends\\Totem\\Addons" FILES ${DependsTotemAddons_HDRS})
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
	./Entity/Components/Cube.h
	./Entity/Components/AnimateRotation.h
	./Entity/Components/Textured.h
)
SOURCE_GROUP("Header Files\\Entity\\Components" FILES ${ENTITY_COMPONENT_HDRS})
#---------------------------------------------------------------
set(ENTITY_COMPONENT_SRCS
	./Entity/Components/Health.cpp
	./Entity/Components/Sprite.cpp
	./Entity/Components/Cube.cpp
	./Entity/Components/AnimateRotation.cpp
	./Entity/Components/Textured.cpp
)
SOURCE_GROUP("Source Files\\Entity\\Components" FILES ${ENTITY_COMPONENT_SRCS})
#---------------------------------------------------------------
set(HDRS
	${DependsTotem_HDRS}
	${DependsTotemAddons_HDRS}
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
target_link_libraries(AITheoryEngine
  debug ${IRR_LIB_DEBUG} optimized ${IRR_LIB_RELEASE}
)
#---------------------------------------------------------------