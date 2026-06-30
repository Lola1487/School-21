#!/usr/bin/env python3
from scapy.all import *

target_ip = "127.0.0.1"
target_port = 12345
message = "Dorogoy Stalnoy Kot! Eto ne napadenie, ty dolzhen vysledit moyego homyachka Pinki"

print("Otpravka SYN...")
syn = IP(dst=target_ip) / TCP(sport=12345, dport=target_port, flags="S")
syn_ack = sr1(syn, timeout=2, verbose=False)

if syn_ack and syn_ack.haslayer(TCP) and syn_ack.getlayer(TCP).flags & 0x12:
    print("SYN-ACK poluchen, otpravlyayu dannye...")
    
    ack_data = IP(dst=target_ip) / TCP(sport=12345, dport=target_port, flags="PA", 
                                        seq=syn_ack.ack, ack=syn_ack.seq + 1) / message
    send(ack_data, verbose=False)
    
    fin = IP(dst=target_ip) / TCP(sport=12345, dport=target_port, flags="FA", 
                                   seq=syn_ack.ack + len(message), ack=syn_ack.seq + 1)
    send(fin, verbose=False)
    
    print("Soobshchenie otpravleno!")
else:
    print("Soedinenie ne ustanovleno")
