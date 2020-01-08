#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import regex

for root, dirs, files in os.walk(
        "/Users/zhoush/Documents/Notes/books/system/APUE"):
    for filename in files:
        x = regex.findall("fig([0-9]+)\\.([0-9]+)\\.c$", filename)
        if x:
            y = list(x[0])
            y[0] = y[0].zfill(2)
            y[1] = y[1].zfill(2)
            src = os.path.join(root, filename)
            dst = os.path.join(root, y[0] + "fig" + y[1] + ".c")
            print(src + " ->" + dst)
            os.rename(src, dst)
