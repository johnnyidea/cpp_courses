#!/bin/bash
ARG=${1:-./exec}

echo "$ARG"
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes  --verbose --log-file=valgrind-out.txt  "$ARG"

