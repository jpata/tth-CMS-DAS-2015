#!/bin/bash
NCORES=20
find . -name "job*.sh" | /data/home/jpata/parallel-20141122/bin/parallel -j$NCORES --results results
