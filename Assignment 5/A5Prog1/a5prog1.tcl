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

set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]
set n6 [$ns node]

$ns duplex-link $n1 $n5 1Mb 10ms DropTail
$ns duplex-link $n2 $n3 1Mb 5ms DropTail
$ns duplex-link $n2 $n4 1Mb 5ms DropTail
$ns duplex-link $n1 $n6 1Mb 5ms DropTail
$ns duplex-link $n3 $n6 1Mb 5ms DropTail

$ns queue-limit $n1 $n5 50
$ns queue-limit $n2 $n3 50
$ns queue-limit $n2 $n4 50
$ns queue-limit $n1 $n6 50
$ns queue-limit $n3 $n6 50

Agent/Ping instproc recv {from rtt} {
$self instvar node_
puts "node [$node_ id] has recieved ping answer $from with round trip time $rtt ms"}

set p1 [new Agent/Ping]
$ns attach-agent $n1 $p1

set p2 [new Agent/Ping]
$ns attach-agent $n3 $p2

$ns connect $p1 $p2
$ns at 0.2 "$p1 send"
$ns at 0.6 "$p2 send"
$ns at 0.4 "$p1 send"
$ns at 0.8 "$p2 send"

$ns at 1.0 "finish"
$ns run
