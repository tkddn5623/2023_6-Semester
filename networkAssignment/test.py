from mininet.net import Mininet
from mininet.topo import Topo
from mininet.node import OVSKernelSwitch
from mininet.cli import CLI
from mininet.node import Host
from mininet.log import setLogLevel, info
from mininet.link import Link, TCLink
import socket
import time

param_num_of_host = 30


class MyTopology(Topo):
    def build(self):
        s0 = self.addSwitch("s0", cls=OVSKernelSwitch, failMode="standalone")
        for i in range(param_num_of_host):
            h = self.addHost(f"h{i}", cls=Host, defaultRoute=None)
            self.addLink(h, s0, cls=TCLink, bw=1000, delay="100ms", loss=0.03)


def main():
    topo = MyTopology()
    net = Mininet(topo=topo, autoSetMacs=True, build=False, ipBase="10.0.0.0/24")

    # net.build()
    net.start()

    for i in range(param_num_of_host):
        h = net.getNodeByName(f"h{i}")
        h.setIP(intf=f"h{i}-eth0", ip=f"10.0.0.{i + 1}/24")
        h.cmd("iperf -s &")

    print("------------------ Network testing start ------------------")

    h1 = net.getNodeByName("h0")
    for i in range(1, param_num_of_host):
        h2 = net.getNodeByName(f"h{i}")
        print(f"iperf -c {h2.IP()} -t 60 &")
        h1.cmd(f"iperf -c {h2.IP()} -t 60 &")
        # net.iperf([h1, h2], seconds=0.1)

    print("------------------ Iperf start ------------------")
    src, dst = net.hosts[0], net.hosts[1]
    s_bw, c_bw = net.iperf([src, dst], seconds=1)
    print("------------------ Iperf closed ------------------")

    print("------------------ RTT measure start ------------------")
    h3 = net.getNodeByName("h2")
    print(h.cmd(f"ping -c 5 {h3.IP()}"))
    print("------------------ RTT measure close ------------------")

    net.stop()
    print("------------------ Network testing closed ------------------")


if __name__ == "__main__":
    setLogLevel("info")
    main()
