#!/usr/bin/env python3

VERSION = "0.1"

def help():
    print(commands.keys())

def version():
    print(VERSION)

commands = {
    "help" : help,
    "version": version,
    "exit" : exit
}

def main():
    while (True):
        s = input('> ')
        cmd = commands.get(s)
        if (cmd is None):
            print(f"Command '{s}' not found.")
        else:
            cmd()

main()