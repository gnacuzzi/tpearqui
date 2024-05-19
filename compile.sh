#!/bin/bash
docker start tpearqui
docker exec -it tpearqui make clean -C/root/Toolchain
docker exec -it tpearqui make clean -C/root/
docker exec -it tpearqui make -C/root/Toolchain
docker exec -it tpearqui make -C/root/
docker stop tpearqui