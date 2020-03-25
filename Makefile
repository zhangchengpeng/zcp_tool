#获取当前正在执行的makefile的绝对路径，gnu make会自动将所有读取的makefile路径都会加入到MAKEFILE_LIST变量
#make_file_path := $(abspath $(lastword $(MAKEFILE_LIST)))
#proj_path := $(shell echo $(dir $(make_file_path)) | sed 's/.$$//')
#PROJ_PATH := $(proj_path)
#export PROJ_PATH

DIR_DEP = dep

DIR_MODULES = comm    \
              example \
              src

all: check
	@for dir in $(DIR_MODULES); \
	do \
		make -C $$dir; \
		echo; \
	done

clean:
	@for dir in $(DIR_MODULES); \
	do \
		make -C $$dir clean; \
		echo; \
	done

install: check
	@for dir in $(DIR_DEP); \
	do \
		make -C $$dir install; \
		echo; \
	done

uninstall:
	@for dir in $(DIR_DEP); \
	do \
		make -C $$dir uninstall; \
		echo; \
	done

format:
	@for dir in $(DIR_MODULES); \
	do \
		make -C $$dir format; \
		echo; \
	done

check:
	@mkdir -p obj
	@mkdir -p lib