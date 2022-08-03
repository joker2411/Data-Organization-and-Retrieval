#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Mon Sep 20 15:25:39 2021

@author: dr
"""

# Import collections module:
import collections

# Initialize deque:
dq = collections.deque([4, 5, 6])

# Append to the right:
dq.append(7)
print("Append 7 to the right: ", list(dq))

# Append to the left:
dq.appendleft(3)
print("Append 3 to the left: ", list(dq))

# Append multiple values to right:
dq.extend([8, 9, 10])
print("Append 8, 9 and 10 to the right: ", list(dq))

# Append multiple values to left:
dq.extendleft([1, 2])
print("Append 2 and 1 to the left: ", list(dq))

# Pop element from the right end:
dq.pop()
print("Remove element from the right: ", list(dq))

# Pop element from the left end:
dq.popleft()
print("Remove element from the left: ", list(dq))

# Remove -1:
dq.remove(1)
print("Remove -1: ", list(dq))

# Count the number of times 5 occurs:
i = dq.count(5)
print("Count the number of times 5 occurs: ", i)

# Rotate the deque three times to the right:
dq.rotate(3)
print("Rotate the deque 3 times to the right: ", list(dq))

# Reverse the whole deque:
dq.reverse()
print("Reverse the deque: ", list(dq))