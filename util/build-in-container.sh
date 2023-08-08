#!/bin/sh

if test "$#" -ne 2; then
	cat >&2 <<EOF
Usage: $0 <C++ standard version> <docker image>

C++ standard versions are 11, 14, 17, etc.

Our docker images are, for example,
 - banditcpp/build-environments:gcc-13
 - banditcpp/build-environments:clang-16
EOF
	exit 2
fi

# run the image
SRCDIR=/usr/src/snowhouse
docker run \
	-v "$PWD":"$SRCDIR" \
	-e "SRCDIR=$SRCDIR" \
	-e "CC=$CC" \
	-e "CXX=$CXX" \
	"$2" "$SRCDIR"/util/build.sh "$1" "$2"
