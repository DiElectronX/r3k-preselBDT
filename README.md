# r3k-preselBDT (BDTScore Adder + Flattener)

This repo converts nested event data into candidate data using root skeleton code. `Events.cc` and `EventsMC.cc` are the workhorse code files. They take in CMGtools output and convert it into a flat ntuple. In addition to flattening, the modules add a branch with the Run 3 RK preselection BDT score, without cutting on it.

## Seting Up

1. Install CMSSW
```
cmsrel CMSSW_13_1_0
cd CMSSW_13_1_0/src
cmsenv
```

2. Install FastForest XGBoost evaluator and build via CMake
```
git clone git@github.com:guitargeek/FastForest.git
cd FastForest
git checkout e9697cd
mkdir build
cd build
cmake3 ..
make
cp -P src/libfastforest.so* .
```

3. Clone r3k-preselBDT

```
cd ${CMSSW_BASE}/src
git clone git@github.com:DiElectronX/r3k-preselBDT.git
```

4. Compile and Run
```
cd r3k-preselBDT
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${CMSSW_BASE}/src/FastForest/build/
g++ -fPIC -std=c++11 src/EventsBase.C src/Events.cc -o addbdtscoredata.exe -lfastforest -I ../FastForest/include/ -L ../FastForest/build/ `root-config --glibs --cflags`
./addbdtscoredata.exe filelists/inputfiles.txt outputfilename outputfiledir

g++ -fPIC -std=c++11 src/EventsBaseMC.C src/EventsMC.cc -o addbdtscoreMC.exe -lfastforest -I ../FastForest/include/ -L ../FastForest/build/ `root-config --glibs --cflags`
./addbdtscoreMC.exe filelists/inputfiles.txt outputfilename outputfiledir

```

**⚠️ Note:** XGBOOST MODELS SHOULD BE TRAINED USING OBJECTIVE = objective='binary:logitraw' AND SAVED USING booster.dump_model("model.txt")
