# BDTScore Adder
## Overview of code
This repo converts nested event data into candidate data using root skeleton code.

Events.cc and EventsMC.cc are the workhorse code files. They take in CMGtools output and convert it into a flat ntuple.

Currently the preselection BDT stored in models/ is not cutting but only being evaluated and saved.





Install CMSSW
```
cmsrel CMSSW_13_1_0
cd CMSSW_13_1_0/src
cmsenv
```
install fastforest xgboost evaluator
```
git clone git@github.com:guitargeek/FastForest.git
```
build it
```
cd FastForest
git checkout e9697cd
mkdir build
cd build
cmake3 ..
make
cp -P src/libfastforest.so* .
```
add bdtscoreadder repo

```
cd ${CMSSW_BASE}/src
git clone git@github.com:jay-odedra/BDTscoreAdder.git
```
compile code
```
cd BDTscoreAdder
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${CMSSW_BASE}/src/FastForest/build/
g++ -fPIC -std=c++11 src/EventsBase.C src/Events.cc -o addbdtscoredata.exe -lfastforest -I ../FastForest/include/ -L ../FastForest/build/ `root-config --glibs --cflags`
./addbdtscoredata.exe filelists/inputfiles.txt outputfilename outputfiledir

g++ -fPIC -std=c++11 src/EventsBaseMC.C src/EventsMC.cc -o addbdtscoreMC.exe -lfastforest -I ../FastForest/include/ -L ../FastForest/build/ `root-config --glibs --cflags`
./addbdtscoreMC.exe filelists/inputfiles.txt outputfilename outputfiledir

```
XGBOOST MODELS SHOULD BE TRAINED USING OBJECTIVE = objective='binary:logitraw' AND SAVED USING booster.dump_model("model.txt")
