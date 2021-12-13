firmware_path := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

VERSION = latest
BUILDER_VERSION = latest
CONFIG = default

all:
	@ docker run --rm -e "TERM=xterm" -v $(firmware_path):/firmware ghcr.io/vives-projectwerk-2021/pulu-firmware-builder:$(BUILDER_VERSION) $(VERSION) $(CONFIG)
