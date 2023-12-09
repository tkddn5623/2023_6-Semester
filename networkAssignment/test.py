from mininet.net import Mininet
from mininet.topo import Topo
from mininet.node import OVSKernelSwitch
from mininet.cli import CLI
from mininet.node import Host
from mininet.log import setLogLevel, info
from mininet.link import Link, TCLink
import socket
import time


class MyTopology(Topo):
    def build(self):
        s0 = self.addSwitch("s0", cls=OVSKernelSwitch, failMode="standalone")
        for i in range(10):
            h = self.addHost(f"h{i}", cls=Host, defaultRoute=None)
            self.addLink(h, s0, cls=TCLink, bw=10000000, delay="0.1ms", loss=0.001)


def main():
    topo = MyTopology()
    net = Mininet(topo=topo, autoSetMacs=True, build=False, ipBase="10.0.0.0/24")

    # net.build()
    net.start()

    for i in range(10):
        h = net.getNodeByName(f"h{i}")
        h.setIP(intf=f"h{i}-eth0", ip=f"10.0.0.{i + 1}/24")

    src, dst = net.hosts[0], net.hosts[1]
    s_bw, c_bw = net.iperf([src, dst], seconds=1)
    s_bw, c_bw = net.iperf([net.hosts[2], dst], seconds=1)
    info(s_bw)
    # CLI(net)
    net.stop()


if __name__ == "__main__":
    setLogLevel("info")
    main()
