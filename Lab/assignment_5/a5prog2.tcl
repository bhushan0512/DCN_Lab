set ns [new Simulator]
set nf [open out.nam w]
$ns namtrace-all $nf
set tf [open out.tr w]
$ns trace-all $tf

proc finish {} {
global ns nf tf
$ns flush-trace
close $nf
close $tf
exec nam out.nam &
exit(0)
}

set numnodes 5

for { set i 0 } {$i<$numnodes} {incr i} {
set nodes($i) [$ns node]
}

for { set i 0 } {$i<$numnodes} {incr i} {
set j [expr {($i+1)%$numnodes}]
$ns duplex-link $nodes($i) $nodes($j) 1Mb 10ms DropTail }

Agent/Ping instproc recv {from rtt} {
$self instvar node_
puts "node [$node_ id] has received ping answer $from with round trip time of $rtt ms"}

set p1 [new Agent/Ping]
$ns attach-agent $nodes(0) $p1

set p2 [new Agent/Ping]
$ns attach-agent $nodes(2) $p2

$ns connect $p1 $p2

$ns at 0.2 "$p1 send"
$ns at 0.6 "$p2 send"
$ns at 0.4 "$p1 send"
$ns at 0.8 "$p2 send"

$ns at 1.0 "finish"
$ns run
