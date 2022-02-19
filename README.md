# CPlusPlusProjectTemplate

## How to Build

Note `docker` is required

```
git clone https://github.com/imotai/CPlusPlusProjectTemplate.git
# init build enviroment
sh start_local_dev.sh

# build parser
sh build.sh

# clean build env
sh clean_env.sh
```

## Run Demo

```
bash enter_container.sh

cd /tpl/build 
# start parse rpc server
src/cmd/parser_demo >/dev/null 2>&1 &

# send a request to rpc server and get the sql ast
src/cmd/parser_demo --sql="select * from t1" --role=cmd
Script [0-16]
  StatementList [0-16]
    QueryStatement [0-16]
      Query [0-16]
        Select [0-16]
          SelectList [7-8]
            SelectColumn [7-8]
              Star(*) [7-8]
          FromClause [9-16]
            TablePathExpression [14-16]
              PathExpression [14-16]
                Identifier(t1) [14-16]
```

## Features

* [x] add a sql remote parser demo
* [x] support docker image as dependency management system
* [ ] support github action build
* [ ] add gtest report steps to github action
* [ ] add c++ codestyle check steps to github action
* [ ] add c++ coverage report steps to giihub action


## More about build enviroment

* https://github.com/imotai/devbox
* dependency lists https://github.com/imotai/devbox/blob/main/build_env/library.csv
