include_directories(${INCLUDE_DIRECTORIES} ${PROJECT_SOURCE_DIR}/src)
add_library(sql_parser_server STATIC sql_parser_impl.cc)
