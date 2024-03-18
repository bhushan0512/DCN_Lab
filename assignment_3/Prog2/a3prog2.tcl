set ns [new Simulator]
$ns color 1 brown
$ns color 2 green
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
exit (0)
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
set n10 [$ns node]
set n11 [$ns node]

$ns make-lan "$n0 $n1 $n2 $n3 $n4 $n5 $n6 $n7 $n8 $n9 $n10 $n11"  0.22Mb 10ms LL Queue/DropTail Mac/802_3

$n0 color red
$n1 color red
$n2 color red
$n3 color red
$n4 color blue
$n5 color blue
$n6 color blue
$n7 color blue
$n8 color blue
$n9 color purple
$n10 color purple
$n11 color purple

set udp1 [new Agent/UDP]
$ns attach-agent $n0 $udp1
set null1 [new Agent/Null]
$ns attach-agent $n3 $null1
$ns connect $udp1 $null1

set tcp1 [new Agent/TCP]
$ns attach-agent $n4 $tcp1
$tcp1 set fid_ 1
set tcpsink0 [new Agent/TCPSink]
$ns attach-agent $n8 $tcpsink0
$ns connect $tcp1 $tcpsink0

set tcp2 [new Agent/TCP]
$ns attach-agent $n9 $tcp2
$tcp2 set fid_ 2
set tcpsink1 [new Agent/TCPSink]
$ns attach-agent $n11 $tcpsink1
$ns connect $tcp2 $tcpsink1

set cbr1 [new Application/Traffic/CBR]
$cbr1 set packet-size 200
$cbr1 set interval 0.005
$cbr1 attach-agent $udp1
$ns at 0.5 "$cbr1 start"
$ns at 4.0 "$cbr1 stop"

set ftp0 [new Application/FTP]
$ftp0 set packet-size 200
$ftp0 set interval 0.005
$ftp0 attach-agent $tcp1
$ns at 0.5 "$ftp0 start"
$ns at 4.0 "$ftp0 stop"

set telnet0 [new Application/Telnet]
$telnet0 set packet-size 200
$telnet0 set interval 0.005
$telnet0 attach-agent $tcp2
$ns at 0.5 "$telnet0 start"
$ns at 4.5 "$telnet0 stop"

$ns at 5.0  "finish"
$ns run 

