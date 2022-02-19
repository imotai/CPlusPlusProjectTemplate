include_directories(${INCLUDE_DIRECTORIES} ${PROJECT_SOURCE_DIR}/src)

find_package(absl)
list(
        APPEND
        ABSL_LIBS
        absl::algorithm
        absl::base
        absl::cord
        absl::debugging
        absl::flat_hash_map
        absl::flags
        absl::memory
        absl::meta
        absl::numeric
        absl::random_random
        absl::strings
        absl::strings_internal
        absl::synchronization
        absl::time
        absl::status
        absl::bad_variant_access
)

find_package(ICU COMPONENTS i18n io uc data)

if (NOT ICU_FOUND)
    message(STATUS "ICU package Not Found")
    find_library(ICU_I18N icui18n)
    find_library(ICU_IO icuio)
    find_library(ICU_UC icuuc)
    find_library(ICU_DATA icudata)
    set(ICU_LIBRARIES ${ICU_I18N} ${ICU_IO} ${ICU_UC} ${ICU_DATA})
endif ()

add_executable(parser_demo parser.cc)
target_link_libraries(parser_demo sql_parser_server  zetasql ${ABSL_LIBS} re2 ${ICU_LIBRARIES} sql_parser_proto brpc protobuf leveldb glog gflags ssl crypto z snappy dl pthread)
