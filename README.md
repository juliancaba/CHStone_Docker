# CHStone_Docker

## Install

- Docker
- Xilinx toolchain version 2017.4 into /opt/Xilinx/2017.4 folder
- Tools located in https://github.com/juliancaba/FIL_tools you must run make -f install as privileged mode


## Run tests in a ZedBoard (using a kernel of CHStone benchmark)

1. Go to a kernel (cd dfadd)
2. make (Perhaps you have to modify the Makefile to denote the license file site)
3. Copy boot.bin to an SD with a Linaro distribution (You can download it from /http://arco.esi.uclm.es/~julian.caba/Xilinx/)
4. Configure the zedboard to start from SD Card
5. Switch-on the zedboard
6. Open a minicom or tera term 
7. Copy the file testFIL to the Linaro Distribution via scp outputDocker/fil_tests/testFIL testing@<ip>: (pass: test)
8. run /home/testing/testFIL in the Linaro distribution

That's all!!
