proc foo {a b} {
  puts "1: $a $b"
  return aa
  puts "2: $a $b"
}

foo 1 ""{};
