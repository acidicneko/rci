#!/bin/bash

install() {
	make -j $(nproc)
	mv build/rci "$GITMAN_BIN"/rci
}

uninstall() {
	rm "$GITMAN_BIN"/rci
}

update() {
	install
}

if [ "$1" = "install" ] ; then
	install
elif [ "$1" = "uninstall" ] ; then
	uninstall
elif [ "$1" = "update" ] ; then
	update
else
	echo "unknown option"
	exit 1
fi
