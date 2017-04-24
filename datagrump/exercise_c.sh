#!/bin/bash
set -euo pipefail

for ((LOW_WATERMARK = 50; LOW_WATERMARK <= 90; LOW_WATERMARK += 10)); do
for ((HIGH_WATERMARK = 100; HIGH_WATERMARK <= 400; HIGH_WATERMARK += 50)); do
  cp -f controller-c.cc controller.cc
  cp -f controller-c.hh controller.hh
  sed -i -e "s/LOW_WATERMARK/${LOW_WATERMARK}/g" controller.hh
  sed -i -e "s/HIGH_WATERMARK/${HIGH_WATERMARK}/g" controller.hh
  make > /dev/null
  echo "Low ${LOW_WATERMARK} high ${HIGH_WATERMARK}"
  ./run.sh 2>&1
  ./run.sh 2>&1
  ./run.sh 2>&1
done
done
