#!/bin/bash
set -euo pipefail

MODE="$1"              # data|mc
FILELIST="$2"
LOCAL_FILELIST="$(basename "$FILELIST")"
OUTNAME="$3"
EOSOUTDIR="$4"

echo "=== Job start ==="
echo "Host: $(hostname)"
echo "Workdir: $(pwd)"
echo "MODE    : ${MODE}"
echo "FILELIST: ${FILELIST}"
echo "OUTNAME : ${OUTNAME}"
echo "EOSOUTDIR: ${EOSOUTDIR}"

# Make sure filelist is present locally (it should be via transfer_input_files)
if [ ! -f "${LOCAL_FILELIST}" ]; then
  echo "ERROR: Local filelist '${LOCAL_FILELIST}' not found in sandbox."
  echo "Sandbox contents:"
  ls -la
  exit 10
fi

# Environment
source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=el9_amd64_gcc13

mkdir -p out

# Libraries
echo "Listing shipped_libs:"
ls -la shipped_libs || true

export LD_LIBRARY_PATH="$PWD/shipped_libs:${LD_LIBRARY_PATH:-}"

TBB_DIR="/cvmfs/muoncollider.cern.ch/release/2.9/linux-almalinux9-x86_64/gcc-11.4.1/intel-tbb-2021.12.0-dlxb3l52ovxil74n3rbg6hv43ifzmlmg/lib64"
export LD_LIBRARY_PATH="$PWD/shipped_libs:${TBB_DIR}:${LD_LIBRARY_PATH:-}"

echo "LD_LIBRARY_PATH=$LD_LIBRARY_PATH"

# Choose executable
EXE=""
case "${MODE}" in
  data)
    EXE="./addbdtscoredata.exe"
    ;;
  mc)
    EXE="./addbdtscoreMC.exe"
    ;;
  *)
    echo "ERROR: MODE must be 'data' or 'mc' (got '${MODE}')"
    exit 11
    ;;
esac

if [ ! -f "${EXE}" ]; then
  echo "ERROR: Expected executable '${EXE}' not found in sandbox."
  ls -la
  exit 12
fi

chmod +x "${EXE}"

echo "ldd check:"
ldd "${EXE}" | egrep "fastforest|not found" || true

# Sanity checks (keep if you want)
ls -l jsons/2022/merged2022.json jsons/2023new/merged.json
head -c 80 jsons/2022/merged2022.json; echo
head -c 80 jsons/2023new/merged.json; echo

echo "Checking model file:"
ls -l models/preselbdt15_10_23.txt
head -n 3 models/preselbdt15_10_23.txt

# Run
echo "Running: ${EXE} ${LOCAL_FILELIST} ${OUTNAME} out"
"${EXE}" "${LOCAL_FILELIST}" "${OUTNAME}" "out"

echo "After running, out/ contains:"
ls -lah out || true

# Detect output ROOT
OUTFILE="$(ls -1 out/${OUTNAME}*.root 2>/dev/null | head -n 1 || true)"
if [ -z "${OUTFILE}" ]; then
  OUTFILE="$(ls -1t out/*.root 2>/dev/null | head -n 1 || true)"
fi
if [ -z "${OUTFILE}" ]; then
  echo "ERROR: No ROOT output produced in out/"
  exit 2
fi

echo "Detected output file: ${OUTFILE}"

# Copy to EOS
EOSDEST="root://eosuser.cern.ch/${EOSOUTDIR}"
echo "Copying ${OUTFILE} -> ${EOSDEST}/${OUTNAME}"
xrdcp -f "${OUTFILE}" "${EOSDEST}/${OUTNAME}"
rm -f "${OUTFILE}"

echo "=== Job done ==="
