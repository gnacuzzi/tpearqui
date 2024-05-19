#!/bin/bash
docker start arquitpe
docker exec -it arquitpe make clean -C/root/Toolchain
docjer exec -it arquitpe make clean -C/root/
docker exec -it arquitpe make -C/root/Toolchain
docker exec -it arquitpe make -C/root/
docker stop arquitpe