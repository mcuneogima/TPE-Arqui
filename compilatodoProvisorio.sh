docker start TPE-Arqui
docker exec -it TPE-Arqui make clean -C /root/Toolchain
docker exec -it TPE-Arqui make clean -C /root
docker exec -it TPE-Arqui make -C /root/Toolchain
docker exec -it TPE-Arqui make -C /root
docker stop TPE-Arqui
