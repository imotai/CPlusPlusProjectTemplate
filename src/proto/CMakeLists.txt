include_directories(${INCLUDE_DIRECTORIES} ${PROJECT_SOURCE_DIR}/src)
function(compile_proto proto_name project_dir)

add_custom_command(OUTPUT ${project_dir}/src/proto/${proto_name}.pb.cc
        COMMAND ${CMAKE_PREFIX_PATH}/bin/protoc -I ${PROJECT_SOURCE_DIR}/src/proto
        --cpp_out=${project_dir}/src/proto/
        ${project_dir}/src/proto/${proto_name}.proto
        DEPENDS ${project_dir}/src/proto/${proto_name}.proto
        )
endfunction(compile_proto)

compile_proto(sql_parser ${PROJECT_SOURCE_DIR})

add_library(sql_parser_proto STATIC sql_parser.pb.cc)

