#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import regex

for root, dirs, files in os.walk(
        "/Users/zhoush/Documents/Notes/books/system/APUE"):
    for filename in files:
        x = regex.findall("(fig|ex)([0-9]+)\\.([0-9]+)\\.c$", filename)
        if x:
            y = list(x[0])
            y[0] = y[0]
            y[1] = y[1].zfill(2)
            y[2] = y[2].zfill(2)
            src = os.path.join(root, filename)
            dst = os.path.join(root, y[1] + y[0] + y[2] + ".c")
            print(src + " =>" + dst)
            os.rename(src, dst)
