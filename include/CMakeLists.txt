target_sources(Evo
    PRIVATE
        RenderWindow.hpp
)

target_include_directories(Evo PUBLIC ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(model)
add_subdirectory(service)
add_subdirectory(utils)
