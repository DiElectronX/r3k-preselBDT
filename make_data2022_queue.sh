#!/bin/bash
set -euo pipefail

# Configuration
YEAR=2022
START=0
END=58

FILELIST_BASE="filelists/FinalList/${YEAR}files/Data"
OUTDIR="/eos/user/j/jfratice/RK/preselBDT_output/data/${YEAR}/full"

OUTFILE="filelists_to_process_data${YEAR}.txt"

# Safety check
if [ -f "${OUTFILE}" ]; then
  echo "ERROR: ${OUTFILE} already exists. Refusing to overwrite."
  exit 1
fi

echo "Writing ${OUTFILE}"

for i in $(seq ${START} ${END}); do
  FILELIST="${FILELIST_BASE}/${i}.txt"
  OUTNAME="data${YEAR}_${i}_presel.root"
  echo "${FILELIST} ${OUTNAME} ${OUTDIR}" >> "${OUTFILE}"
done

echo "Done."
echo "Preview:"
head -n 5 "${OUTFILE}"
