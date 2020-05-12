#!/usr/bin/python3

import sys

# 00
# print('Number of arguments:', len(sys.argv))
# print('Arguments are:', str(sys.argv))

# 0
print(sys.argv[0])

# 1
print(sys.argv[1])

# 12
print(sys.argv[1])
print(sys.argv[2])


# list 1
for arg in sys.argv:
    print('Argument:', arg)

# list 2
for i, arg in enumerate(sys.argv):
    print(f'Argument at position {i}:', arg)

