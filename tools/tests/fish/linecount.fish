set out (echo 'line1
line2
line3' | eval ../$BUILD/linecount)
test $out = 3