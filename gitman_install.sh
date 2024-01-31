#!/bin/bash

DEFAULT_ROOT_LOCATION="$HOME"/.local/share/gitman

install() {
	make -j $(nproc)
	mv build/rci "$DEFAULT_ROOT_LOCATION"/bin/rci
}

uninstall() {
	rm "$DEFAULT_ROOT_LOCATION"/bin/rci
}


cd /tmp/rci
if [ "$1" = "install" ] ; then
	install
elif [ "$1" = "uninstall" ] ; then
	uninstall
else
	echo "unknown option"
	exit 1
fi
