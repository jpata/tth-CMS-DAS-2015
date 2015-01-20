#this configuration supports splitting the run into multiple small jobs
#it is configured via the environment variable TTH_JOBINDEX, run as
# $TTH_JOBINDEX=3 Analyzer Analyzer_par_cfg.py
#the job index must be within [0...Njobs], where Njobs is determined
#based on the required job size (per_job) and total number of events (Ntot)
#The total number of events is read on the fly

#import analyzer configuration base
from CMSDAS.TTH.Analyzer_cfg import *

import ROOT
import os, sys

#total number of events in input files
#this will be read from ROOT TTrees
Ntot = 0

#events per job, configure manually
#suitable job length ~10 minutes
per_job = 1000000

#loop over pre-configured input samples
for s in process.fwliteInput.samples:

    #get the input filename
    fn = process.fwliteInput.pathToFile.value() + process.fwliteInput.ordering.value() + s.name.value() + ".root"
    #get the TTree with events
    tf = ROOT.TFile(fn)
    tt = tf.Get("tree")

    #get the number of events in the TTree
    N = tt.GetEntries()
    Ntot += N

#calculate the total number of jobs to run
#this division rounds down (e.g. 5/2 = 2)
total_jobs = Ntot / per_job

#in case there are leftover events, create an additional job
if Ntot % per_job != 0:
    total_jobs += 1

def set_job_index(job_index):
    """
    Configures the imported process to run across the events corresponding to the job index

    Arguments:
        job_index - 0-based counter/index of the job to configure
    """
    if not (job_index >= 0 and job_index < total_jobs):
        raise Exception("Incorrect job index: {0:d}/{1:d}".format(job_index, total_jobs))

    #first event to analyze (inclusive)
    #0-based indexing
    first_event = job_index * per_job

    #last event to analyze (inclusive)
    #subtract one from Ntot because events start from 0
    last_event = min((job_index+1) * per_job - 1, Ntot - 1)

    process.fwliteInput.firstEvent = cms.uint64(first_event)
    process.fwliteInput.lastEvent = cms.uint64(last_event)

    #also set the output file name
    process.fwliteInput.outFileName = cms.string("output_%d.root" % job_index)
    return first_event, last_event

#run as standalone, such as $python Analyzer_par_cfg.py --create
if __name__ == "__main__" and hasattr(sys, "argv") and  "--create" in sys.argv:
    #loop over 0...total_jobs
    for nj in range(total_jobs):
        #set the event range corresponding to the job
        first_event, last_event = set_job_index(nj)

        #create a bash file to run locally or submit via a batch system
        ofname = "job_%d.sh" % nj
        ofi = open(ofname, "w")
        ofi.write("#!/bin/bash\n")
        ofi.write('set -e\n')
        ofi.write('echo "Processing %d to %d"\n' % (first_event, last_event))
        ofi.write('TTH_JOBINDEX=%d AnalyzerCSV python/Analyzer_par_cfg.py\n' % nj)
        ofi.write('echo "Job done with exit code $?"\n')
        ofi.close()
        os.system("chmod +x %s" % ofname)

else: #this used as configuration, e.g. $Analyzer Analyzer_par_cfg.py
    #0 .. njobs-1, index of jobs, read from an environment variable
    job_index = int(os.environ["TTH_JOBINDEX"])
    set_job_index(job_index)
    print process.dumpPython()
