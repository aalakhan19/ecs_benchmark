set(_pico_ecs_test_libs "")

if(ENABLE_BENCHMARK_ENTT OR ENABLE_BENCHMARK_ENTITYX OR ENABLE_BENCHMARK_GINSENG OR ENABLE_BENCHMARK_MUSTACHE OR ENABLE_BENCHMARK_GAIA_ECS)
  set(_main_test_sources "")
  if(ENABLE_BENCHMARK_ENTT)
    list(APPEND _main_test_sources
      ${CMAKE_CURRENT_SOURCE_DIR}/entity_factory/entt_test.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/application/entt_test.cpp)
  endif()
  if(ENABLE_BENCHMARK_ENTITYX)
    list(APPEND _main_test_sources
      ${CMAKE_CURRENT_SOURCE_DIR}/entity_factory/entityx_test.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/application/entityx_test.cpp)
  endif()
  if(ENABLE_BENCHMARK_GINSENG)
    list(APPEND _main_test_sources
      ${CMAKE_CURRENT_SOURCE_DIR}/application/ginseng_test.cpp)
  endif()
  if(ENABLE_BENCHMARK_MUSTACHE)
    list(APPEND _main_test_sources
      ${CMAKE_CURRENT_SOURCE_DIR}/application/mustache_test.cpp)
  endif()
  if(ENABLE_BENCHMARK_GAIA_ECS)
    list(APPEND _main_test_sources
      ${CMAKE_CURRENT_SOURCE_DIR}/entity_factory/gaia_ecs_test.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/application/gaia_ecs_test.cpp)
  endif()

  add_executable(ecs-benchmark-tests ${_main_test_sources})
  target_include_directories(ecs-benchmark-tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
  target_include_directories(ecs-benchmark-tests PRIVATE ${PROJECT_SOURCE_DIR}/include)
  target_include_directories(ecs-benchmark-tests PRIVATE ${PROJECT_BINARY_DIR}/include)
  target_include_directories(ecs-benchmark-tests PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/include)
  target_link_libraries(ecs-benchmark-tests PRIVATE project_warnings project_options)
  target_compile_definitions(ecs-benchmark-tests PRIVATE TESTING)
  target_link_libraries(ecs-benchmark-tests PRIVATE ecs-benchmark::base)
  target_link_system_libraries(ecs-benchmark-tests PRIVATE Catch2::Catch2 Catch2::Catch2WithMain)

  if(ENABLE_BENCHMARK_ENTT)
    target_link_libraries(ecs-benchmark-tests PRIVATE ecs-benchmark-example-entt)
  endif()
  if(ENABLE_BENCHMARK_ENTITYX)
    target_link_libraries(ecs-benchmark-tests PRIVATE ecs-benchmark-example-entityx)
  endif()
  if(ENABLE_BENCHMARK_GINSENG)
    target_link_libraries(ecs-benchmark-tests PRIVATE ecs-benchmark-example-ginseng)
  endif()
  if(ENABLE_BENCHMARK_MUSTACHE)
    target_link_libraries(ecs-benchmark-tests PRIVATE ecs-benchmark-example-mustache)
  endif()
  if(ENABLE_BENCHMARK_GAIA_ECS)
    target_link_libraries(ecs-benchmark-tests PRIVATE ecs-benchmark-example-gaia-ecs)
  endif()

  catch_discover_tests(ecs-benchmark-tests)
endif()

if(ENABLE_BENCHMARK_FLECS)
  add_executable(
          ecs-benchmark-tests-flecs
          ${CMAKE_CURRENT_SOURCE_DIR}/application/flecs_test.cpp)
  target_include_directories(ecs-benchmark-tests-flecs PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
  target_include_directories(ecs-benchmark-tests-flecs PRIVATE ${PROJECT_SOURCE_DIR}/include)
  target_include_directories(ecs-benchmark-tests-flecs PRIVATE ${PROJECT_BINARY_DIR}/include)
  target_include_directories(ecs-benchmark-tests-flecs PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/include)
  target_link_libraries(ecs-benchmark-tests-flecs PRIVATE project_warnings project_options)
  target_compile_definitions(ecs-benchmark-tests-flecs PRIVATE TESTING)
  target_link_libraries(ecs-benchmark-tests-flecs PRIVATE ecs-benchmark::base)
  target_link_system_libraries(ecs-benchmark-tests-flecs PRIVATE Catch2::Catch2 Catch2::Catch2WithMain)
  target_link_libraries(ecs-benchmark-tests-flecs PRIVATE ecs-benchmark-example-flecs)
  catch_discover_tests(ecs-benchmark-tests-flecs)
endif()

if(ENABLE_BENCHMARK_PICO_ECS)
  add_executable(
          ecs-benchmark-tests-pico-ecs
          ${CMAKE_CURRENT_SOURCE_DIR}/application/pico_ecs_test.cpp
          ${CMAKE_CURRENT_SOURCE_DIR}/entity_factory/pico_ecs_test.cpp)
  target_include_directories(ecs-benchmark-tests-pico-ecs PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
  target_include_directories(ecs-benchmark-tests-pico-ecs PRIVATE ${PROJECT_SOURCE_DIR}/include)
  target_include_directories(ecs-benchmark-tests-pico-ecs PRIVATE ${PROJECT_BINARY_DIR}/include)
  target_include_directories(ecs-benchmark-tests-pico-ecs PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/include)
  target_link_libraries(ecs-benchmark-tests-pico-ecs PRIVATE project_warnings project_options)
  target_compile_definitions(ecs-benchmark-tests-pico-ecs PRIVATE TESTING)
  target_link_libraries(ecs-benchmark-tests-pico-ecs PRIVATE ecs-benchmark::base)
  target_link_system_libraries(ecs-benchmark-tests-pico-ecs PRIVATE Catch2::Catch2 Catch2::Catch2WithMain)
  target_link_libraries(ecs-benchmark-tests-pico-ecs PRIVATE ecs-benchmark-example-pico-ecs)
  catch_discover_tests(ecs-benchmark-tests-pico-ecs)
endif()
