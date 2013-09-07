#!/opt/local/bin/fish

redo-ifchange params.fish
. params.fish

set -g passed 0
set -g failed 0

function run
  set base (basename $argv[1])
  if eval $argv[1]
    set passed (math $passed '+ 1')
  else
    echoerr $base': FAILED with status '$status 1>&2
    set failed (math $failed '+ 1')
  end 
end

echoerr 'running tests'

for file in fish/*
  if not echo $file | grep -q '~$'
    run $file
  end
end

echoerr $passed' passed, '$failed' failed'