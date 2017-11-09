set(GOOGLEBENCH_EXTERNAL_ROOT ${CMAKE_BINARY_DIR}/externals/googlebench)
set(GOOGLEBENCH_EXTERNAL_REPO "https://github.com/google/benchmark.git")

ExternalProject_ADD(
  #--External-project-name------
  googlebench
  #--Depend-on-antrl-tool-----------
  # DEPENDS antlrtool
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
  CONFIGURE_COMMAND  ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Release -DBENCHMARK_ENABLE_TESTING=OFF -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR> <SOURCE_DIR>
  LOG_CONFIGURE ON
  #--Build step-----------------
  BUILD_COMMAND $(MAKE)
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