#!/usr/bin/env python2.7
##
# Copyright (c) OpenLoop, 2016
#
# This material is proprietary of The OpenLoop Alliance and its members.
# All rights reserved.
# The methods and techniques described herein are considered proprietary
# information. Reproduction or distribution, in whole or in part, is forbidden
# except by express written permission of OpenLoop.
#
# Source that is published publicly is for demonstration purposes only and
# shall not be utilized to any extent without express written permission of
# OpenLoop.
#
# Please see http://www.opnlp.co for contact information
##

import socket
import logging
import argparse
import select
from datetime import datetime

MAX_MESSAGE_SIZE = 2048
LOG_PATH = "podctl.log"
LOG_LEVEL = logging.WARN

logging.basicConfig(level=LOG_LEVEL, filename=LOG_PATH)


class Pod:
    def __init__(self, sock):
        self.sock = sock

    def ping(self):
        self.sock.send("ping")
        self.last_ping = datetime.now()

    def handle_data(self, data):
        if "PONG" in data:
            self.last_pond = datetime.now()

    def command(self, cmd):
        self.sock.send(cmd + "\n")

    def transcribe(self, data):
        logging.info("[DATA] {}".format(data))


def isPositiveInt(s):
    try:
        return int(s) > 0
    except ValueError:
        return False


def makeLine(msg):
    """Takes a message and prepends a timestamp to it for logging"""
    lineToWrite = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    return lineToWrite + msg + "\n"


if "__main__" == __name__:
    parser = argparse.ArgumentParser(description="Openloop Command Client")

    parser.add_argument("-v", "--verbose", action="store_true")

    parser.add_argument("--port", type=int, default=7779,
                        help="Pod server port")

    parser.add_argument("-p", "--host", default="127.0.0.1",
                        help="Pod server port")

    args = parser.parse_args()

    if args.verbose:
        logging.basicConfig(level=logging.DEBUG)

    print("Connecting to {}:{}".format(args.host, args.port))

    sock = socket.create_connection((args.host, args.port))

    pod = Pod(sock)

    running = True
    while running:
        (ready, _, _) = select.select([sock], [], [], 1)

        if sock in ready:
            data = sock.recv(MAX_MESSAGE_SIZE)

            print data.rstrip()

            pod.handle_data(data)

            # TODO: Read from STDIN with a timeout
            cmd = raw_input()

            pod.command(cmd)
