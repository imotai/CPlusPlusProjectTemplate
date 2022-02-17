//
//
// parser.cc
// Copyright (C) 2022 Author zombie <zombie@zombie-ub2104>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//



#include <iostream>
#include "parser/sql_parser_impl.h"
#include "gflags/gflags.h"
#include "proto/sql_parser.pb.h"
#include "glog/logging.h"
#include "brpc/channel.h"

DEFINE_uint32(port, "Set the port of parser server");
DEFINE_string(role, "Set the role of process, server or cmd");
DEFINE_string(sql, "Set sql to parse");

void StartParserServer() {
    cpluscplustemplate::ParseSQLServerImpl service = new cpluscplustemplate::ParseSQLServerImpl();
    brpc::ServerOptions options;
    brpc::Server server;
    if (server.AddService(service, brpc::SERVER_DOESNT_OWN_SERVICE) != 0) {
        exit(1);
    }
    std::string endpoint = "127.0.0.1:" + FLAGS_port;
    if (server.Start(endpoint.c_str(), &options) != 0) {
        exit(1);
    }
    std::cout << "start parse server on port " << FLAGS_port << std::endl;
    server.RunUntilAskedToQuit();
}

int ParseSQL() {
	brpc::Channel channel;
    std::string endpoint = "127.0.0.1:" + FLAGS_port;
    // Initialize the channel, NULL means using default options.
    brpc::ChannelOptions options;
    if (channel.Init(endpoint.c_str(), "", &options) != 0) {
        LOG(ERROR) << "Fail to initialize channel";
        return -1;
    }
    ::cpluscplustemplate::ParseSQLServer_Stub stub(&channel);
    ::cpluscplustemplate::ParseSQLRequest request;
    request.set_sql(FLAGS_sql);
    ::cpluscplustemplate::ParseSQLResponse response;
    brpc::Controller cntl;

    stub.ParseSQL(&cntl, &request, &response, NULL);
    if (!cntl.Failed()) {
        std::cout << response.ast() << std::endl;
    }
    return 0;
}

int main(int argc, char* argv[]) {
    ::google::ParseCommandLineFlags(&argc, &argv, true);
    if (FLAGS_role == "server") {
        StartParserServer();
    }else {
        ParseSQL();
    }
    return 0;
}
