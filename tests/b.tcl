set a 5
puts [expr {< 1 3}]

for {set i 0} {<= $i 5} {incr i} {
  for {set j 7} {< $j 10} {set j [expr {+ $j 1}]} {
    puts "$i $j"
  }
}

if {< 2 1} {
  puts 11
} else {
  puts 22
}

proc foo {a b c} {
  puts "$a $b $c"
}

foo 1 2 3

proc foo {a b c} {
  puts "$a $b $c"
}

foo 4 5 6
