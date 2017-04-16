#!/usr/bin/env python
# -*- coding: utf -*-
import sys
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import numpy as np


def main():
    if len(sys.argv) != 2:
        print('Usage: {} <log file>'.format(sys.argv[0]))
        sys.exit(1)
    throughputs = {}
    delays = {}
    with open(sys.argv[1]) as f:
        for l in f:
            if 'Window size' in l:
                current_size = int(l.split()[2])
                throughputs.setdefault(current_size, [])
                delays.setdefault(current_size, [])
            if 'throughput' in l:
                throughputs[current_size].append(float(l.split()[2]))
            elif 'signal delay' in l:
                delays[current_size].append(float(l.split()[4]))
    for window_size in throughputs:
        plt.scatter(
            delays[window_size],
            throughputs[window_size],
            marker='x',
            label=window_size)
    plt.gca().invert_xaxis()
    plt.ylabel('Throughput (Mbits/s)')
    plt.xlabel('Delay (ms)')
    plt.title('Fixed window sizes')
    plt.legend()
    plt.savefig('exercise_a.png', bbox_inches='tight')


if __name__ == '__main__':
    main()
