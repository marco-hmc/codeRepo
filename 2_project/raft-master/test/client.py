#!/usr/bin/env python
# coding: utf-8
'''
@File    :   client.py
@Time    :   2022/03/19 15:35:31
@Author  :   https://github.com/hangsz
@Version :   0.1.0
@Contact :   zhenhang.sun@gmail.com
'''

import logging
import os
import random
import sys
import time
import traceback

from raft.config import config
from raft.rpc import Rpc

logger = logging.getLogger(__name__)


def main() :
    env = os.environ.get("env")
    conf = config[env] if env else config["DEV"]

    rpc_endpoint = Rpc((conf.ip, conf.cport))

    data = {"type": "get_group"}

    rpc_endpoint.send(data, (conf.ip, conf.mport))
    try:
        data, _ = rpc_endpoint.recv()
        group_meta = data['meta']

        print(group_meta)
    except Exception:
        traceback.print_exc()
        sys.exit(1)

    while True:
        try:
            res, _ = rpc_endpoint.recv(timeout=2)
            print("receive: commit success", res)
        except KeyboardInterrupt:
            rpc_endpoint.close()
            return 0
        except Exception:
            traceback.print_exc()

        addr = random.choice(group_meta["nodes"])
        data = {"type": "client_append_entries", "timestamp": int(time.time())}
        print("send: ", data)

        rpc_endpoint.send(data, addr)

        time.sleep(10)


if __name__ == "__main__":
    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s %(levelname)s %(name)s %(funcName)s [line:%(lineno)d]\n%(message)s",
    )
    sys.exit(main())
