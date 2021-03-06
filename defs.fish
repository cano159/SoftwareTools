# ----------------------------------------------------------------------
# defs.fish: definitions common to all subdirectories
# ----------------------------------------------------------------------

# Users of this file should set LEVEL first
if not set -q LEVEL
  set -gx LEVEL .
end

redo-ifchange $LEVEL/defs.fish

set -gx CC clang
set -gx CCFLAGS -std=c99

function redo-ifchange-d -d 'Redo if dependencies changed'
  for arg in $argv
    tr '\n' ' ' < $arg | read deps
    set deps (echo $deps | sed -e 's/^.*: *//' -e 's/\\\\//g')
    echo $deps
  end | xargs redo-ifchange
end

function echoerr -d 'Echo args to stderr'
  echo $argv 1>&2
end

function evald -d 'Eval with echo to stderr if DEBUG set'
  if set -q DEBUG
    echoerr $argv
  end
  eval $argv
end 

function debug -d 'Turn build debugging on'
  set -gx DEBUG 1
end

function nodebug -d 'Turn build debugging off'
  set -e DEBUG
end

function doall -d 'Do command on all files matching regex'
  if not test (count $argv) = 2
    echo 'usage: doall command regex' 1>&2
    return 1
  end
  set cmd $argv[1]
  set regex $argv[2] 
  set line 'find . -name '\'$regex\'' -print0 | xargs -0 '$cmd
  eval $line
end

function rm-tmp -d 'Remove temporary files'
  doall rm '*~'
  doall rm '*redo*tmp'
end

function rm-redo -d 'Remove redo database files'
  doall 'rm -R' .redo
end

function make-exec -d 'Build an executable file'
  set base (basename $argv[1])
  set cfile src/$base.c
  set dfile depend/$base.d
  set ofile build/$base
  set lib $LEVEL/lib
  set include -Iinclude -I$lib/include

  redo-ifchange $cfile $lib/build/libst.a
  evald $CC -MD -MF $dfile $CCFLAGS $include -L$lib/build -lst $cfile -o $argv[3]
  redo-ifchange-d $dfile
end
