target_sources(Evo
    PRIVATE
        Chromosome.hpp
        Creature.hpp
        Food.hpp
)

target_include_directories(Evo PUBLIC ${CMAKE_CURRENT_LIST_DIR})
