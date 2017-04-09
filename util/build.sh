#!/bin/sh

test -n "$SRCDIR" || SRCDIR=.
test -n "$CC" || CC=cc
test -n "$CXX" || CXX=c++

cxxstandard="$1"
case "$cxxstandard" in
98|03|11|14)
	;;
*)
	echo "Usage: $0 (98|03|11|14) [image name]" >&2
	exit 1
esac

image="$2"
test -n "$image" || image=default

buildpath="builds/$(basename "$image" | sed 's/^.*://')/$(basename "$CXX")/std$cxxstandard"

echo "Build settings:"
echo " * source directory: $SRCDIR"
echo " * C compiler: $CC"
echo " * C++ compiler: $CXX"
echo " * C++ standard: C++$cxxstandard"
echo " * image: $image"
echo " * build path: $buildpath"

mkdir -p "$SRCDIR/$buildpath"
cd "$SRCDIR/$buildpath"
cmake -D"SNOWHOUSE_CXX_STANDARD=C++$cxxstandard" "$SRCDIR" || exit
cmake --build . || exit
