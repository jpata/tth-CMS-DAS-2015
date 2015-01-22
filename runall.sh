#!/bin/bash
NCORES=20
find . -name "job*.sh" | /data/shared/gnu-parallel/bin/parallel -j$NCORES --results results
