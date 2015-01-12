#!/bin/sh
#
# Script to run read_OK.C on a root file using xrdclient, xrdCL and davix, with 
# percentage parameter starting from 5% up to 100%. 
# Parses result from output, grab the walltime per run and write it to data file
# to be used by ROOT for graph plotting.
#
dir="results/"
davixUK="davixUK"
davixCERN="davixCERN"
xrdCLUK="xrdCLUK"
xrdCLCERN="xrdCLCERN"
xrdClientUK="xrdClientUK"
xrdClientCERN="xrdClientCERN"
davixUK_r="davixUK_r"
davixCERN_r="davixCERN_r"
xrdCLUK_r="xrdCLUK_r"
xrdCLCERN_r="xrdCLCERN_r"
xrdClientUK_r="xrdClientUK_r"
xrdClientCERN_r="xrdClientCERN_r"

davixGrid="davixGrid"

xrdClientUK_r_no_prefetch="xrdClientUK_r_no_prefetch"
xrdCLUK_r_no_prefetch="xrdCLUK_r_no_prefetch"
davixUK_r_no_prefetch="davixUK_r_no_prefetch"

xrdClientUK_no_prefetch="xrdClientUK_no_prefetch"
xrdCLUK_no_prefetch="xrdCLUK_no_prefetch"
davixUK_no_prefetch="davixUK_no_prefetch"

davixCERN_no_prefetch="davixCERN_no_prefetch"


current_time=$(date "+%Y.%m.%d-%H.%M")
davixUK=$dir$davixUK.$current_time
davixCERN=$dir$davixCERN.$current_time
xrdCLUK=$dir$xrdCLUK.$current_time
xrdCLCERN=$dir$xrdCLCERN.$current_time
xrdClientUK=$dir$xrdClientUK.$current_time
xrdClientCERN=$dir$xrdClientCERN.$current_time
davixUK_r=$dir$davixUK_r.$current_time
davixCERN_r=$dir$davixCERN_r.$current_time
xrdCLUK_r=$dir$xrdCLUK_r.$current_time
xrdCLCERN_r=$dir$xrdCLCERN_r.$current_time
xrdClientUK_r=$dir$xrdClientUK_r.$current_time
xrdClientCERN_r=$dir$xrdClientCERN_r.$current_time

davixGrid=$dir$davixGrid.$current_time

xrdClientUK_r_no_prefetch=$dir$xrdClientUK_r_no_prefetch.$current_time
xrdCLUK_r_no_prefetch=$dir$xrdCLUK_r_no_prefetch.$current_time
davixUK_r_no_prefetch=$dir$davixUK_r_no_prefetch.$current_time

davixUK_no_prefetch=$dir$davixUK_no_prefetch.$current_time
xrdClientUK_no_prefetch=$dir$xrdClientUK_no_prefetch.$current_time
xrdCLUK_no_prefetch=$dir$xrdCLUK_no_prefetch.$current_time

davixCERN_no_prefetch=$dir$davixCERN_no_prefetch.$current_time

. ~/Development/root5/bin/thisroot.sh
LD_LIBRARY_PATH=/home/eric/Development/root5/lib64

for i in {5..100..5}
  do
#        echo "PERCENTAGE=$i">>$davixUK
        echo "PERCENTAGE=$i">>$davixCERN
#        echo "PERCENTAGE=$i">>$xrdCLUK
#        echo "PERCENTAGE=$i">>$xrdCLCERN
#        echo "PERCENTAGE=$i">>$xrdClientUK
#        echo "PERCENTAGE=$i">>$xrdClientCERN
#        echo "PERCENTAGE=$i">>$davixUK_r
#        echo "PERCENTAGE=$i">>$davixCERN_r
#        echo "PERCENTAGE=$i">>$xrdCLUK_r
#        echo "PERCENTAGE=$i">>$xrdCLCERN_r
#        echo "PERCENTAGE=$i">>$xrdClientUK_r
#        echo "PERCENTAGE=$i">>$xrdClientCERN_r
#        echo "PERCENTAGE=$i">>$davixGrid
#        echo "PERCENTAGE=$i">>$xrdClientUK_r_no_prefetch
#        echo "PERCENTAGE=$i">>$xrdCLUK_r_no_prefetch
#        echo "PERCENTAGE=$i">>$davixUK_r_no_prefetch
#        echo "PERCENTAGE=$i">>$xrdClientUK_no_prefetch
#        echo "PERCENTAGE=$i">>$xrdCLUK_no_prefetch
#        echo "PERCENTAGE=$i">>$davixUK_no_prefetch
        echo "PERCENTAGE=$i">>$davixCERN_no_prefetch

    for j in {1..10}
      do
                 
#        root -l -b -q 'read_OK.C+("root://gridpp09.ecdf.ed.ac.uk//dpm/ecdf.ed.ac.uk/home/atlas/group.test.hc.NTUP_SMWZ.root","physics",'$i',30,"0.17","/tmp/x509up_u500","",-1,0,1,1)' | grep -o 'WALLTIME=[^\n]*' | cut -f2- -d'=' >> $xrdClientUK
#        root -l -b -q 'read_OK.C+("root://gridpp09.ecdf.ed.ac.uk//dpm/ecdf.ed.ac.uk/home/atlas/group.test.hc.NTUP_SMWZ.root","physics",'$i',30,"0.17","/tmp/x509up_u500","",-1,0,0,1)' | grep -o 'WALLTIME=[^\n]*' | cut -f2- -d'=' >> $xrdCLUK
#        root -l -b -q 'read_OK.C+("https://gridpp09.ecdf.ed.ac.uk/dpm/ecdf.ed.ac.uk/home/atlas/h1big.root","h42",'$i',30,"","/tmp/x509up_u500","",-1,0,0,1)' | grep -o 'WALLTIME=[^\n]*' | cut -f2- -d'=' >> $davixUK
#        root -l -b -q 'read_OK.C+("root://lxfsra04a04.cern.ch//dpm/cern.ch/home/dteam/cake/group.test.hc.NTUP_SMWZ.root","physics",'$i',30,"0.17","/tmp/x509up_u500","",-1,0,1)' | grep -o 'WALLTIME=[^\n]*' | cut -f2- -d'=' >> $xrdClientCERN
#        root -l -b -q 'read_OK.C+("root://lxfsra04a04.cern.ch//dpm/cern.ch/home/dteam/cake/group.test.hc.NTUP_SMWZ.root","physics",'$i',30,"0.17","/tmp/x509up_u500","",-1,0,0)' | grep -o 'WALLTIME=[^\n]*' | cut -f2- -d'=' >> $xrdCLCERN
        root -l -b -q 'read_OK.C+("https://lxfsra04a04.cern.ch/dpm/cern.ch/home/dteam/cake/h1big.root","h42",'$i',30,"","/tmp/x509up_u500","",-1,0,0,1)' | grep -o 'WALLTIME=[^\n]*' | cut -f2- -d'=' >> $davixCERN
#        root -l -b -q 'read_OK.C+("root://gridpp09.ecdf.ed.ac.uk//dpm/ecdf.ed.ac.uk/home/atlas/group.test.hc.NTUP_SMWZ.root","physics",'$i',30,"0.17","/tmp/x509up_u500","",-1,1,1,1)' | grep -o 'WALLTIME=[^\n]*' | cut -f2- -d'=' >> $xrdClientUK_r
#        root -l -b -q 'read_OK.C+("root://gridpp09.ecdf.ed.ac.uk//dpm/ecdf.ed.ac.uk/home/atlas/group.test.hc.NTUP_SMWZ.root","physics",'$i',30,"0.17","/tmp/x509up_u500","",-1,1,0,1)' | grep -o 'WALLTIME=[^\n]*' | cut -f2- -d'=' >> $xrdCLUK_r
#        root -l -b -q 'read_OK.C+("https://gridpp09.ecdf.ed.ac.uk/dpm/ecdf.ed.ac.uk/home/atlas/group.test.hc.NTUP_SMWZ.root","physics",'$i',30,"0.17","/tmp/x509up_u500","",-1,1,0,1)' | grep -o 'WALLTIME=[^\n]*' | cut -f2- -d'=' >> $davixUK_r
#        root -l -b -q 'read_OK.C+("root://lxfsra04a04.cern.ch//dpm/cern.ch/home/dteam/cake/group.test.hc.NTUP_SMWZ.root","physics",'$i',30,"0.17","/tmp/x509up_u500","",-1,1,1,0)' | grep -o 'WALLTIME=[^\n]*' | cut -f2- -d'=' >> $xrdClientCERN_r
#        root -l -b -q 'read_OK.C+("root://lxfsra04a04.cern.ch//dpm/cern.ch/home/dteam/cake/group.test.hc.NTUP_SMWZ.root","physics",'$i',30,"0.17","/tmp/x509up_u500","",-1,1,0,0)' | grep -o 'WALLTIME=[^\n]*' | cut -f2- -d'=' >> $xrdCLCERN_r
#        root -l -b -q 'read_OK.C+("https://lxfsra04a04.cern.ch/dpm/cern.ch/home/dteam/cake/group.test.hc.NTUP_SMWZ.root","physics",'$i',30,"0.17","/tmp/x509up_u500","",-1,1,0,0)' | grep -o 'WALLTIME=[^\n]*' | cut -f2- -d'=' >> $davixCERN_r

#        root -l -b -q 'read_OK.C+("http://grid-deployment.web.cern.ch/grid-deployment/dms/lcgutil/group.test.hc.NTUP_SMWZ.root","physics",'$i',30,"0.17","/tmp/x509up_u500","",-1,0,0)' | grep -o 'WALLTIME=[^\n]*' | cut -f2- -d'=' >> $davixGrid

#        root -l -b -q 'read_OK.C+("root://gridpp09.ecdf.ed.ac.uk//dpm/ecdf.ed.ac.uk/home/atlas/group.test.hc.NTUP_SMWZ.root","physics",'$i',30,"0.17","/tmp/x509up_u500","",-1,1,1,0)' | grep -o 'WALLTIME=[^\n]*' | cut -f2- -d'=' >> $xrdClientUK_r_no_prefetch
#        root -l -b -q 'read_OK.C+("root://gridpp09.ecdf.ed.ac.uk//dpm/ecdf.ed.ac.uk/home/atlas/group.test.hc.NTUP_SMWZ.root","physics",'$i',30,"0.17","/tmp/x509up_u500","",-1,1,0,0)' | grep -o 'WALLTIME=[^\n]*' | cut -f2- -d'=' >> $xrdCLUK_r_no_prefetch
#        root -l -b -q 'read_OK.C+("https://gridpp09.ecdf.ed.ac.uk/dpm/ecdf.ed.ac.uk/home/atlas/group.test.hc.NTUP_SMWZ.root","physics",'$i',30,"0.17","/tmp/x509up_u500","",-1,1,0,0)' | grep -o 'WALLTIME=[^\n]*' | cut -f2- -d'=' >> $davixUK_r_no_prefetch

#        root -l -b -q 'read_OK.C+("https://gridpp09.ecdf.ed.ac.uk/dpm/ecdf.ed.ac.uk/home/atlas/h1big.root","h42",'$i',30,"","/tmp/x509up_u500","",-1,0,0,0)' | grep -o 'WALLTIME=[^\n]*' | cut -f2- -d'=' >> $davixUK_no_prefetch
        
        root -l -b -q 'read_OK.C+("https://lxfsra04a04.cern.ch/dpm/cern.ch/home/dteam/cake/h1big.root","h42",'$i',30,"","/tmp/x509up_u500","",-1,0,0,0)' | grep -o 'WALLTIME=[^\n]*' | cut -f2- -d'=' >> $davixCERN_no_prefetch

      

  done
done


