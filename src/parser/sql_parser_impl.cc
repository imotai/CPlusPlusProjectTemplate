//
//
// sql_parser_impl.cc
// Copyright (C) 2022 4Paradigm Author zombie <zombie@zombie-ub2104>
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

#include "parser/sql_parser_impl.h"
#include "zetasql/parser/parser.h"
#include "absl/status/status.h"
#include "absl/strings/string_view.h"


namespace cpluscplustemplate {

void ParseSQLServerImpl::ParseSQL(RpcController* ctrl,
        const ParserSQLRequest* request,
        ParserSQLResponse* reponse,
        Closure* done) {
    absl::string_view sql(request->sql().c_str(), request->sql().size());
    zetasql::ParseOptions opt;
    std::unique_ptr<zetasql::ParseOutput> output;
    auto status = zetasql::ParseStatement(sql, opt, &output);
    if (status.ok()) {
        response->set_ast(output->statement()->DebugString());
    }else {
        response->set_ast(status.ToString());
    }
    done->Run();
}

}  // cpluscplustemplate



