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
        exit 0
}


set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
$ns duplex-link $n0 $n1 1Mb 10ms DropTail
$ns duplex-link $n1 $n2 1Mb 5ms DropTail
$ns queue-limit $n0 $n1 50
$ns queue-limit $n1 $n2 50

set udp1 [new Agent/UDP]
$ns attach-agent $n0 $udp1
set null [new Agent/Null]
$ns attach-agent $n2 $null

$ns connect $udp1 $null
set cbr1 [new Application/Traffic/CBR]
$cbr1 set packet-size 500
$cbr1 set interval 0.005
$cbr1 attach-agent $udp1

$ns at 0.5 "$cbr1 start"
$ns at 5.0 "$cbr1 stop"
$ns at 5.5 "finish"
$ns run

