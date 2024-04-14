set ns [new Simulator]
set nf [open out.nam w]
$ns namtrace-all $nf
set tf [open out.tr w]
$ns trace-all $tf

$ns color 1 red
$ns color 2 blue

proc finish {} {
global ns nf tf
$ns flush-trace
close $nf
close $tf
exec nam out.nam &
exit(0)
}

set numnodes 7

for { set i 0 } {$i<$numnodes} {incr i} {
set n($i) [$ns node]
}

for { set i 1 } {$i<7} {incr i} {
$ns duplex-link $n(0) $n($i) 1Mb 10ms DropTail }

$ns duplex-link-op $n(0) $n(1) orient left-up
$ns duplex-link-op $n(0) $n(2) orient right-up

$ns duplex-link-op $n(0) $n(3) orient left
$ns duplex-link-op $n(0) $n(4) orient left-down

$ns duplex-link-op $n(0) $n(5) orient right
$ns duplex-link-op $n(0) $n(6) orient right-down

set udp0 [new Agent/UDP]
$ns attach-agent $n(0) $udp0
$udp0 set fid_ 1
set null1 [new Agent/Null]
$ns attach-agent $n(2) $null1
$ns connect $udp0 $null1

set cbr0 [new Application/Traffic/CBR]
$cbr0 set packet-size 500
$cbr0 set interval 0.005
$cbr0 attach-agent $udp0
$ns at 0.3 "$cbr0 start"
$ns at 1.5 "$cbr0 stop"

set tcp0 [new Agent/TCP]
$ns attach-agent $n(3) $tcp0
$tcp0 set fid_ 2
set tcpsink0 [new Agent/TCPSink]
$ns attach-agent $n(5) $tcpsink0
$ns connect $tcp0 $tcpsink0

set ftp0 [new Application/FTP]
$ftp0 set packet-size 500
$ftp0 set interval 0.01
$ftp0 attach-agent $tcp0
$ns at 0.5 "$ftp0 start"
$ns at 2.0 "$ftp0 stop"

$ns at 2.5 "finish"
$ns run
