
proc incr {x} {
  upvar $x y
  set y [expr {+ $y 1}]
}

proc decr {x} {
  upvar $x y
  set y [expr {- $y 1}]
}

proc for {start test next body} {
  uplevel $start
  uplevel "while {$test} {
    $body
	$next
  }"
}
