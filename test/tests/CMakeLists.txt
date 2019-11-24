set(target tests)

file(GLOB hdrs "include/*.h*")
file(GLOB srcs "src/*.c*")

add_executable(${target} ${srcs} ${hdrs})
target_link_libraries(${target} gtest ${ALL_LIBRARIES})

target_include_directories(${target} PUBLIC ${ALL_INCLUDES}
 ${CMAKE_SOURCE_DIR}/test/gtest ${CMAKE_CURRENT_SOURCE_DIR}/include)
