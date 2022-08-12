if(BUILD_PROJECT_TESTS)
  include(FetchContent)
  # ------------------------------------------------------------------------------
  # Unit testing library for the C++ programming language, based on the xUnit
  # architecture.
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.12.1)

  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
  set(BUILD_GTEST ON CACHE BOOL "" FORCE)

  FetchContent_MakeAvailable(googletest)
endif()