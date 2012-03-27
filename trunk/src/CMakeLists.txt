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
	./Entity/Components/Terrain.h
	./Entity/Components/TerrainNavGraph.h
	./Entity/Components/AnimateRotation.h
	./Entity/Components/Textured.h
	./Entity/Components/PathFinder.h
)
SOURCE_GROUP("Header Files\\Entity\\Components" FILES ${ENTITY_COMPONENT_HDRS})
#---------------------------------------------------------------
set(ENTITY_COMPONENT_SRCS
	./Entity/Components/Health.cpp
	./Entity/Components/Sprite.cpp
	./Entity/Components/Cube.cpp
	./Entity/Components/Terrain.cpp
	./Entity/Components/TerrainNavGraph.cpp
	./Entity/Components/AnimateRotation.cpp
	./Entity/Components/Textured.cpp
	./Entity/Components/PathFinder.cpp
)
SOURCE_GROUP("Source Files\\Entity\\Components" FILES ${ENTITY_COMPONENT_SRCS})
#---------------------------------------------------------------
set(STRUCTURES_GRAPH_HDRS
	./Structures/Graph/Graph.h
	./Structures/Graph/GraphEdge.h
	./Structures/Graph/GraphNode.h
)
SOURCE_GROUP("Header Files\\Structures\\Graph" FILES ${STRUCTURES_GRAPH_HDRS})
#---------------------------------------------------------------
set(STRUCTURES_GRAPH_SRCS
	./Structures/Graph/Graph.cpp
	./Structures/Graph/GraphEdge.cpp
	./Structures/Graph/GraphNode.cpp
)
SOURCE_GROUP("Source Files\\Structures\\Graph" FILES ${STRUCTURES_GRAPH_SRCS})
#---------------------------------------------------------------
set(STRUCTURES_TREE_HDRS
	./Structures/Tree/Tree.h
	./Structures/Tree/TreeEdge.h
	./Structures/Tree/TreeNode.h
)
SOURCE_GROUP("Header Files\\Structures\\Tree" FILES ${STRUCTURES_TREE_HDRS})
#---------------------------------------------------------------
set(STRUCTURES_TREE_SRCS
	./Structures/Tree/Tree.cpp
	./Structures/Tree/TreeEdge.cpp
	./Structures/Tree/TreeNode.cpp
)
SOURCE_GROUP("Source Files\\Structures\\Tree" FILES ${STRUCTURES_TREE_SRCS})
#---------------------------------------------------------------
set(STRUCTURES_HDRS
)
SOURCE_GROUP("Header Files\\Structures" FILES ${STRUCTURES_HDRS})
#---------------------------------------------------------------
set(STRUCTURES_SRCS
)
SOURCE_GROUP("Source Files\\Structures" FILES ${STRUCTURES_SRCS})
#---------------------------------------------------------------
set(ALGORITHMS_SEARCH_HDRS
	./Algorithms/Search/ISearch.h
	./Algorithms/Search/BredthFirst.h
	./Algorithms/Search/DepthFirst.h
	./Algorithms/Search/Dijkstras.h
	./Algorithms/Search/AStar.h
)
SOURCE_GROUP("Header Files\\Algorithms\\Search" FILES ${ALGORITHMS_SEARCH_HDRS})
#---------------------------------------------------------------
set(ALGORITHMS_SEARCH_SRCS
	./Algorithms/Search/BredthFirst.cpp
	./Algorithms/Search/DepthFirst.cpp
	./Algorithms/Search/Dijkstras.cpp
	./Algorithms/Search/AStar.cpp
)
SOURCE_GROUP("Source Files\\Algorithms\\Search" FILES ${ALGORITHMS_SEARCH_SRCS})
#---------------------------------------------------------------
set(ALGORITHMS_HDRS
)
SOURCE_GROUP("Header Files\\Algorithms" FILES ${ALGORITHMS_HDRS})
#---------------------------------------------------------------
set(ALGORITHMS_SRCS
)
SOURCE_GROUP("Source Files\\Algorithms" FILES ${ALGORITHMS_SRCS})
#---------------------------------------------------------------
set(HDRS
	${DependsTotem_HDRS}
	${DependsTotemAddons_HDRS}
	${ENTITY_HDRS} 
	${ENTITY_COMPONENT_HDRS}
	${STRUCTURES_HDRS}
	${STRUCTURES_GRAPH_HDRS}
	${STRUCTURES_TREE_HDRS}
	${ALGORITHMS_HDRS}
	${ALGORITHMS_SEARCH_HDRS}
)
#---------------------------------------------------------------
set(SRCS
	${ENTITY_SRCS}
	${ENTITY_COMPONENT_SRCS}
	${STRUCTURES_SRCS}
	${STRUCTURES_GRAPH_SRCS}
	${STRUCTURES_TREE_SRCS}
	${ALGORITHMS_SRCS}
	${ALGORITHMS_SEARCH_SRCS}
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