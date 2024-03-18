set ns [new Simulator]
set nf [open out.nam w]
$ns namtrace-all $nf
set tf [open out.tr w]
$ns trace-all $tf

$ns color 1 red
$ns color 2 brown

proc finish {} {
global ns nf tf
$ns flush-trace
close $nf
close $tf
exec nam out.nam &
exit(0)
}

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]
set n6 [$ns node]
set n7 [$ns node]
set n8 [$ns node]
set n9 [$ns node]

$ns make-lan "$n0 $n1 $n2 $n3 $n4 $n5 $n6 $n7 $n8 $n9"  0.1Mb 0.1ms LL Queue/DropTail Mac/802_3

set tcp0 [new Agent/TCP]
$ns attach-agent $n3 $tcp0
$tcp0 set fid_ 1
set tcpsink0 [new Agent/TCPSink]
$ns attach-agent $n5 $tcpsink0
$ns connect $tcp0 $tcpsink0

set telnet0 [new Application/Telnet]
$telnet0 set packet-size 500
$telnet0 set interval 0.005
$telnet0 attach-agent $tcp0
$ns at 0.5 "$telnet0 start"
$ns at 2.0 "$telnet0 stop"

set tcp1 [new Agent/TCP]
$ns attach-agent $n3 $tcp1
$tcp1 set fid_ 2
set tcpsink0 [new Agent/TCPSink]
$ns attach-agent $n5 $tcpsink0
$ns connect $tcp1 $tcpsink0

set telnet1 [new Application/Telnet]
$telnet1 set packet-size 500
$telnet1 set interval 0.005
$telnet1 attach-agent $tcp1
$ns at 0.5 "$telnet1 start"
$ns at 2.0 "$telnet1 stop"

$ns at 5.0 "finish"
$ns run

