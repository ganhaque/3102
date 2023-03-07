#!/bin/fish
for i in (seq 4 16)
  echo "2^$i"
  ./a.out (math "2^$i")
end

