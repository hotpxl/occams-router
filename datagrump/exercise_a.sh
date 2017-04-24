#!/bin/bash
set -euo pipefail

for ((WINDOW_SIZE = 2; WINDOW_SIZE <= 512; WINDOW_SIZE *= 2)); do
  cp -f controller-a.cc controller.cc
  cp -f controller-a.hh controller.hh
  sed -i -e "s/WINDOW_SIZE_CHANGE_ME/${WINDOW_SIZE}/g" controller.cc
  make > /dev/null
  echo "Window size: ${WINDOW_SIZE}"
  ./run-contest yy 2>&1
  ./run-contest yy 2>&1
  ./run-contest yy 2>&1
done
