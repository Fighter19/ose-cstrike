# Counter-Strike: Source as a game module: weapon scripts the engine can read (the game's
# own are encrypted) and team loadouts. Linked into every app as an object library so its
# static registration is kept.
file(GLOB OSE_CSTRIKE_SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_library(ose_game_cstrike OBJECT ${OSE_CSTRIKE_SOURCES})
target_link_libraries(ose_game_cstrike PUBLIC ose_engine)
target_compile_definitions(ose_game_cstrike PRIVATE OSE_CSTRIKE_CONTENT="${CMAKE_CURRENT_SOURCE_DIR}/content")
ose_warnings(ose_game_cstrike)
set_property(GLOBAL APPEND PROPERTY OSE_GAME_MODULES ose_game_cstrike)

if(OSE_BUILD_TESTS)
    find_package(doctest CONFIG REQUIRED)
    file(GLOB OSE_CSTRIKE_TEST_SOURCES CONFIGURE_DEPENDS tests/*.cpp)
    add_executable(ose_cstrike_tests ${CMAKE_SOURCE_DIR}/tests/unit/main.cpp ${OSE_CSTRIKE_TEST_SOURCES})
    target_link_libraries(ose_cstrike_tests PRIVATE ose_engine doctest::doctest)
    target_compile_definitions(ose_cstrike_tests PRIVATE OSE_CSTRIKE_CONTENT="${CMAKE_CURRENT_SOURCE_DIR}/content")
    ose_warnings(ose_cstrike_tests)
    add_test(NAME unit_cstrike COMMAND ose_cstrike_tests)
    set_tests_properties(unit_cstrike PROPERTIES LABELS "unit")
    # With the game installed: the scripts' models and sounds exist. Skipped without OSE_CSS_DIR
    # (the directory containing cstrike/).
    add_test(NAME assets_cstrike COMMAND ${CMAKE_COMMAND} -E env sh -c
        "if [ -z \"$OSE_CSS_DIR\" ]; then echo 'OSE_CSS_DIR not set, skipping'; exit 77; fi; \
         $<TARGET_FILE:ose_cstrike_tests> --test-case='*game content*'")
    set_tests_properties(assets_cstrike PROPERTIES LABELS "assets" SKIP_RETURN_CODE 77)
endif()
