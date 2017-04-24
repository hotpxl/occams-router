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
            if 'Low' in l:
                low_watermark = int(l.split()[1])
                high_watermark = int(l.split()[3])
                throughputs.setdefault((low_watermark, high_watermark), [])
                delays.setdefault((low_watermark, high_watermark), [])
            if 'throughput' in l:
                throughputs[(low_watermark,
                             high_watermark)].append(float(l.split()[2]))
            elif 'signal delay' in l:
                delays[(low_watermark,
                        high_watermark)].append(float(l.split()[4]))
    for marks in throughputs:
        plt.scatter(
            delays[marks],
            throughputs[marks],
            marker='x',
            label='[{}, {}]'.format(marks[0], marks[1]))
    plt.gca().invert_xaxis()
    plt.ylabel('Throughput (Mbits/s)')
    plt.xlabel('Delay (ms)')
    plt.xscale('log')
    plt.title('Fixed window sizes')
    plt.legend()
    plt.savefig('exercise_c.png', bbox_inches='tight')


if __name__ == '__main__':
    main()
