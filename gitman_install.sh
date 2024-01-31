#!/bin/bash

install() {
	make -j $(nproc)
	mv build/rci "$GITMAN_BIN"/rci
}

uninstall() {
	rm "$GITMAN_BIN"/rci
}


if [ "$1" = "install" ] ; then
	install
elif [ "$1" = "uninstall" ] ; then
	uninstall
else
	echo "unknown option"
	exit 1
fi
