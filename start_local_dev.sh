#! /bin/bash
#
# start_local_dev.sh

sudo docker run -v `pwd`:/tpl --name tpl -dt ghcr.io/imotai/centos7_gcc7_build_env:0.0.5 bash
sudo docker exec -t tpl bash -c "cd /depends && tar -zxvf thirdparty.tar.gz"
echo "use sudo docker exec -it tpl bash to enter dev enviroment"



