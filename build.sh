#! /bin/bash
#
# build.sh

sudo docker exec -t tpl bash -c "cd /tpl && mkdir -p build && cd build && cmake .. && make -j4"



