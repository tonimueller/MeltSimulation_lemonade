add_subdirectory(utility)

add_executable(createMelt createMelt.cpp)
target_link_libraries(createMelt LeMonADE CommandlineParser )

add_executable(simulateMelt simulateMelt.cpp)
target_link_libraries(simulateMelt LeMonADE CommandlineParser )

add_executable(analyzeMelt analyzeMelt.cpp)
target_link_libraries(analyzeMelt LeMonADE CommandlineParser )