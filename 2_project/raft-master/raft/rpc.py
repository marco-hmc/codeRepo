#!/usr/bin/env python
# coding: utf-8
'''
@File    :   rpc.py
@Time    :   2022/03/19 14:46:35
@Author  :   https://github.com/hangsz
@Version :   0.1.0
@Contact :   zhenhang.sun@gmail.com
'''

import json
import socket

class Rpc(object):
    def __init__(self, addr=None, timeout=None):
        """

        Args:
            addr (tuple[str, int], optional):  ip and port. Defaults to None.
            timeout (int, optional): . Defaults to None.
        """

        self.ss = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        if addr:
            self.bind(tuple(addr))
        if timeout:
            self.ss.settimeout(timeout)

    def bind(self, addr):
        """bind addr

        Args:
            addr (tuple[str, int]): ip and port
        """
        self.addr = tuple(addr)
        self.ss.bind(addr)

    def settimeout(self, timeout):
        """set timeout

        Args:
            timeout (int): 
        """
        self.ss.settimeout(timeout)

    def send(self, data, addr=None):
        """send data

        Args:
            data (dict): 
            ddr (tuple[str, int], optional): dst ip and port. Defaults to None.
        """
        if addr:
            data = json.dumps(data).encode("utf-8")
            self.ss.sendto(data, tuple(addr))

    def recv(self, addr=None, timeout=None):
        """receive data

        Args:
            addr (tuple[str, int], optional): ip and port. Defaults to None.
            timeout (int, optional): . Defaults to None.

        Returns:
            tuple[dict, tuple[str, int]]: data and (ip, port)
        """
        if addr:
            self.bind(addr)
        if not self.addr:
            raise ("please bind to an addr")

        if timeout:
            self.settimeout(timeout)

        data, addr = self.ss.recvfrom(65535)
        return json.loads(data), addr

    def close(self):
        self.ss.close()
