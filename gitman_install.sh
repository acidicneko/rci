#!/bin/bash

DEFAULT_ROOT_LOCATION="$HOME"/.local/share/gitman

install() {
	make -j $(nproc)
	mv build/rci "$DEFAULT_ROOT_LOCATION"/bin/rci
}

uninstall() {
	rm "$DEFAULT_ROOT_LOCATION"/bin/rci
	rm -rf "$DEFAULT_ROOT_LOCATION"/packages/rci
}
