set_property(GLOBAL PROPERTY USE_FOLDERS On)

# ============================================================================ #
# Link up files for the library

set(HEADERS
  # core files
  assert.h
  adiar.h
  data.h
  file.h
  file_stream.h
  file_writer.h
  homomorphism.h
  priority_queue.h
  reduce.h
  tuple.h
  union.h
  util.h

  # bdd files
  bdd/apply.h
  bdd/assignment.h
  bdd/bdd.h
  bdd/build.h
  bdd/count.h
  bdd/evaluate.h
  bdd/if_then_else.h
  bdd/negate.h
  bdd/quantify.h
  bdd/restrict.h

  # debug files
  dot.h
)

set(SOURCES
  # core files
  adiar.cpp
  data.cpp
  file.cpp
  file_stream.cpp
  file_writer.cpp
  homomorphism.cpp
  priority_queue.cpp
  reduce.cpp

  # bdd files
  bdd/apply.cpp
  bdd/assignment.cpp
  bdd/bdd.cpp
  bdd/build.cpp
  bdd/count.cpp
  bdd/evaluate.cpp
  bdd/if_then_else.cpp
  bdd/negate.cpp
  bdd/quantify.cpp
  bdd/restrict.cpp

  # debug files
  dot.cpp
)

if (ADIAR_SHARED)
  add_library(adiar SHARED ${HEADERS} ${SOURCES})
else()
  add_library(adiar STATIC ${HEADERS} ${SOURCES})
endif()

include(GenerateExportHeader)
generate_export_header(adiar)

# ============================================================================ #
# Link dependencies
target_link_libraries(adiar tpie)

# ============================================================================ #
# Setup as library

target_include_directories(adiar PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/..
                                       ${CMAKE_CURRENT_SOURCE_DIR}/..)

set_target_properties(adiar PROPERTIES
  # Language settings
  LINKER_LANGUAGE CXX
  C_STANDARD 17
  C_STANDARD_REQUIRED ON
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
  CXX_VISIBILITY_PRESET hidden

  # Linkage?
  FOLDER adiar

  # Other
  VERSION ${PROJECT_VERSION}
  POSITION_INDEPENDENT_CODE ON
)

install(TARGETS adiar
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
