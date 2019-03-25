C2IP = python3 /opt/fil_testing/bin/c2IPsrc.py
C2HLS = python3 /opt/fil_testing/bin/c2hls.py
DAT2FIL= python3 /opt/fil_testing/bin/create_filTest.py
BITGEN = python3 /opt/fil_testing/bin/create_pl.py


TOP=blowfish

INC_DIRS = ./src
INC_DIRS += /opt/utf/rc-unity/include/

OUTPUT=output
OUTPUTDOCKER=outputDocker
TEMPLATE=m1s1
OVERLAY=zed$(TEMPLATE)
TOOLCHAIN_VERSION=2017.4
DOCKER_IMG=jcaba/zed_$(TEMPLATE):version$(TOOLCHAIN_VERSION)
WORKDIR=/workspace


.PHONY: hls fil_tests bitgen


all: hdl fil


hdl: runner
	$(C2IP) -l vhdl -t $(TOP) -tb sim -I $(INC_DIRS) -o $(OUTPUT) ./src --csim --cosim


runner:
	@cd sim; make; cd -

hls:
	@mkdir $(OUTPUT)
	$(C2HLS) -t $(TOP) -tb sim -I $(INC_DIRS) -o $(OUTPUT) ./src --csim --cosim

fil:
	$(RM) -rf $(OUTPUTDOCKER)
	mkdir -p $(OUTPUTDOCKER)
	docker run -i -v /opt/Xilinx:/opt/Xilinx -v $(CURDIR):$(WORKDIR)/host -v $(CURDIR)/$(OUTPUTDOCKER):/$(OUTPUTDOCKER) -e XILINXD_LICENSE_FILE='1900@172.20.48.102:1901@172.20.48.102:1702@172.20.48.102' -e UT='ut_blowfish.cc' $(DOCKER_IMG)


clean:
	$(RM) -rf tmp_* *~ $(OUTPUT) $(OUTPUTDOCKER)
