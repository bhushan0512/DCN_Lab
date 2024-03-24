set ns [new Simulator]
$ns color 1 violet
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

$ns duplex-link $n1 $n5 0.011Mb 10ms DropTail
$ns duplex-link $n2 $n3 1Mb 5ms DropTail
$ns duplex-link $n2 $n4 1Mb 5ms DropTail
$ns duplex-link $n1 $n6 1Mb 5ms DropTail
$ns duplex-link $n3 $n6 1Mb 5ms DropTail

$ns duplex-link-op $n1 $n5 color red
$ns duplex-link-op $n2 $n3 color blue

$ns duplex-link-op $n1 $n5 orient left
$ns duplex-link-op $n2 $n3 orient right

$ns queue-limit $n1 $n5 50
$ns queue-limit $n2 $n3 0.011
$ns queue-limit $n2 $n4 50
$ns queue-limit $n1 $n6 50
$ns queue-limit $n3 $n6 50

$n1 color blue
$n2 color red

$n1 shape circle
$n2 shape box

set tcp1 [new Agent/TCP]
$ns attach-agent $n3 $tcp1
$tcp1 set fid_ 1
set tcpsink0 [new Agent/TCPSink]
$ns  attach-agent $n5 $tcpsink0
$ns connect $tcp1 $tcpsink0

set tcp2 [new Agent/TCP]
$ns attach-agent $n4 $tcp2
set tcpsink1 [new Agent/TCPSink]
$ns attach-agent $n6 $tcpsink1
$ns connect $tcp2 $tcpsink1

set ftp0 [new Application/FTP]
set telnet0 [new Application/Telnet]

$ftp0 set packet-size 200
$ftp0 set Interval 0.005
$ftp0 attach-agent $tcp1
$ns at 0.5 "$ftp0 start"
$ns at 4.5 "$ftp0 stop"

$telnet0 set packet-size 200
$telnet0 set interval 0.005
$telnet0 attach-agent $tcp2
$ns at 0.5 "$telnet0 start"
$ns at 4.5 "$telnet0 stop"

$ns at 5.5 "finish"
$ns run
