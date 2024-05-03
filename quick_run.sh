#!/bin/sh

rm -fr builddir/
meson setup builddir
meson compile -C builddir

./builddir/donglify $@
