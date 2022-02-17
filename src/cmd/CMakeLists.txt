include_directories(${INCLUDE_DIRECTORIES} ${PROJECT_SOURCE_DIR}/src)

add_executable(parser_demo parser.cc)
target_link_libraries(parser_demo sql_parser_proto sql_parser_server brpc protobuf glog gflags ssl crypto z snappy dl pthread)
