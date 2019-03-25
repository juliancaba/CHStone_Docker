UNITY_ROOT=/opt/utf/rc-unity
RUNNER=$(UNITY_ROOT)/auto/generate_test_runner.rb


UNIT_TEST=ut_blowfish.cc
RUNNER_TEST=$(UNIT_TEST:.cc=_Runner.cc)


all: links $(RUNNER_TEST)

links:
	ln -sf $(UNITY_ROOT)/src/*.cc .

$(RUNNER_TEST): $(UNIT_TEST)
	ruby $(RUNNER) $^ $@


clean:
	$(RM) -rfv *.o *~
	$(RM) -rfv $(RUNNER_TEST)
	$(RM) rc-unity++.cc unity++.cc


.PHONY: clean
