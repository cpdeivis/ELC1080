#!/bin/bash
for i in $(seq 1 10); do
    time ./serial https://pt.wikipedia.org/wiki/Sistema_operativo Java
    # time ./thread https://pt.wikipedia.org/wiki/Sistema_operativo Java 2
    # time ./thread https://pt.wikipedia.org/wiki/Sistema_operativo Java 4
    # time ./thread https://pt.wikipedia.org/wiki/Sistema_operativo Java 8
done