PROJ=lpc-egg
ENGINE=../lpc-egg

help:
	@echo "＝＝＝＝＝＝＝＝＝提示＝＝＝＝＝＝＝＝"
	@echo "---------------- $(PROJ) makefile ---------------------"
	@echo "make build              -- 编译代码"
	@echo "make ut                 -- 单元测试"
	@echo "make clean              -- 删除bin"

build:
	$(ENGINE) -b -l .

ut:
	mkdir -p .temp
	sh unittest/dump_unittest.sh .temp/my_ut.cfg -l ./
	$(ENGINE) -runittest/main -O.temp/my_ut.cfg -l ./

all: build

clean:
	@if [ -d ./bin/ ]; then rm -rf ./bin/; mkdir bin; fi;

