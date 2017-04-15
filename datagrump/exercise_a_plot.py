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
    throughputs = []
    delays = []
    with open(sys.argv[1]) as f:
        for l in f:
            if 'throughput' in l:
                throughputs.append(float(l.split()[2]))
            elif 'signal delay' in l:
                delays.append(float(l.split()[4]))
    plt.scatter(throughputs, delays)
    plt.gca().invert_xaxis()
    plt.ylabel('Throughput (Mbits/s)')
    plt.xlabel('Delay (ms)')
    plt.title('Fixed window sizes')
    plt.savefig('exercise_a.png', bbox_inches='tight')


if __name__ == '__main__':
    main()
