#!/usr/bin/env python3
import sys
import os

def createAllArgs():
    allArgs = []
    for i in range(1, len(sys.argv)):
        allArgs.append(sys.argv[i])
    for line in sys.stdin.readlines():
        allArgs.append(line.rstrip("\n"))
    return allArgs

# alternativa pentru procesarea de mai sus
# def createAllArgs2():
#     inputlines = sys.stdin.readlines()
#     inputlines = map(lambda line: line.rstrip("\n"), inputlines)
#     return sys.argv[1:] + list(inputlines)

os.execvp(sys.argv[1], createAllArgs())