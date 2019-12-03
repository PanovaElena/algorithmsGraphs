set(target realData)

file(GLOB hdrs "include/*.h*" "../include/*.h*")
file(GLOB srcs "src/*.c*")

add_executable(${target} ${srcs} ${hdrs})
target_link_libraries(${target} ${ALL_LIBRARIES})

target_include_directories(${target} PUBLIC ${ALL_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../include)
    
add_definitions(-DDATABASE="${CMAKE_SOURCE_DIR}/database/USA-road-t.txt")