set(GOOGLEBENCH_EXTERNAL_ROOT ${CMAKE_BINARY_DIR}/externals/googlebench)
set(GOOGLEBENCH_EXTERNAL_REPO "https://github.com/google/benchmark.git")

ExternalProject_ADD(
  #--External-project-name------
  googlebench
  #--Core-directories-----------
  PREFIX             ${GOOGLEBENCH_EXTERNAL_ROOT}
  #--Download step--------------
  GIT_REPOSITORY     ${GOOGLEBENCH_EXTERNAL_REPO}
  GIT_SHALLOW 1
  TIMEOUT            10
  LOG_DOWNLOAD       ON
  #--Update step----------
  #UPDATE_COMMAND     ${GIT_EXECUTABLE} pull
  UPDATE_COMMAND ""
  #--Patch step----------
  # PATCH_COMMAND sh -c "cp <SOURCE_DIR>/scripts/CMakeLists.txt <SOURCE_DIR>"
  #--Configure step-------------
  CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DBENCHMARK_ENABLE_TESTING=OFF -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
  LOG_CONFIGURE ON
  #--Build step-----------------
  BUILD_COMMAND ${CMAKE_MAKE_PROGRAM}
  LOG_BUILD ON
  #--Install step---------------
  # INSTALL_COMMAND    ""
  # INSTALL_DIR ${CMAKE_BINARY_DIR}/
  #--Install step---------------
  # INSTALL_COMMAND    ""
)

ExternalProject_Get_Property(googlebench INSTALL_DIR)

set(GOOGLEBENCH_LIBS "${INSTALL_DIR}/lib")
set(GOOGLEBENCH_INCLUDE "${INSTALL_DIR}/include")
link_directories(${GOOGLEBENCH_LIBS})
