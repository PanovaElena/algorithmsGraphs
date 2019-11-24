set(target spanningTrees)

file(GLOB hdrs "include/*.h*")

add_custom_target(${target} SOURCES ${hdrs})

set(ALL_INCLUDES ${ALL_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)
