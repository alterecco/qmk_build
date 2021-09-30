export ROOTDIR := $(shell pwd)

# Add qmk wrapper to path
#export PATH := $(ROOTDIR)/bin:$(PATH)

git-submodule:
	+$(MAKE) -C "$(ROOTDIR)/qmk_firmware" git-submodule
