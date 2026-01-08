# r3k-preselBDT (BDTScore Adder + Flattener)

This repo converts nested event data into candidate data using root skeleton code. `Events.cc` and `EventsMC.cc` are the workhorse code files. They take in CMGtools output and convert it into a flat ntuple. In addition to flattening, the modules add a branch with the Run 3 RK preselection BDT score, without cutting on it.

## Setting Up

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
cd r3k-preselBDT
```

4. Compile Executables
```
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${CMSSW_BASE}/src/FastForest/build/
g++ -fPIC -std=c++11 src/EventsBase.C src/Events.cc -o addbdtscoredata.exe -lfastforest -I ../FastForest/include/ -L ../FastForest/build/ `root-config --glibs --cflags`
g++ -fPIC -std=c++11 src/EventsBaseMC.C src/EventsMC.cc -o addbdtscoreMC.exe -lfastforest -I ../FastForest/include/ -L ../FastForest/build/ `root-config --glibs --cflags`
```

---

## Running Executables

### Running for Data
```
./addbdtscoredata.exe <file path list (.txt)> <output file name> <output file directory>
```
- Current file lists for data (1/8/2026) are located in `filelists/FinalList/Data/`

### Running for MC
```
./addbdtscoreMC.exe <file path list (.txt)> <output file name> <output file directory>
```
- Current file lists for MC (1/8/2026) are located in `filelists/FinalList/eoslist_MC_20_11_24/`

### Examples

```
mkdir test_outputs
./addbdtscoredata.exe filelists/test_inputs/test_data.txt test_data_output test_outputs/
./addbdtscoreMC.exe filelists/test_inputs/test_mc.txt test_mc_output test_outputs/
```

**⚠️ Note:** XGBOOST MODELS SHOULD BE TRAINED USING OBJECTIVE = objective='binary:logitraw' AND SAVED USING booster.dump_model("model.txt")
