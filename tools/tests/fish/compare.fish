# ----------------------------------------------------------------------
# compare.fish: test compare
# ----------------------------------------------------------------------

../build/compare fish/compare-in-{1,2}.txt > fish/compare.out 2>&1
diff fish/compare.out fish/compare.ref 1>&2
