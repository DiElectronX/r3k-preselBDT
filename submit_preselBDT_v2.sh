#!/bin/bash
set -euo pipefail

MODE=""
QUEUEFILE=""
FILELIST=""
OUTNAME=""
OUTDIR=""

usage() {
  cat <<EOF
Usage:
  # Submit ONE job:
  $0 --mode data|mc --filelist <path/to/list.txt> --outname <name.root> --outdir <eos/dir>

  # Submit MANY jobs from a queue file (your existing 3-column format):
  # Each line: <filelist> <outname> <outdir>
  $0 --mode data|mc --queue <filelists_to_process.txt>

Notes:
  - For batch mode, this script will prepend the MODE as the first column for Condor.
  - Output logs go to logs/ under the initialdir in the submit file.
EOF
}

# Parse args
while [[ $# -gt 0 ]]; do
  case "$1" in
    --mode) MODE="$2"; shift 2;;
    --queue) QUEUEFILE="$2"; shift 2;;
    --filelist) FILELIST="$2"; shift 2;;
    --outname) OUTNAME="$2"; shift 2;;
    --outdir) OUTDIR="$2"; shift 2;;
    -h|--help) usage; exit 0;;
    *) echo "Unknown argument: $1"; usage; exit 1;;
  esac
done

if [[ -z "${MODE}" ]]; then
  echo "ERROR: --mode is required"
  usage
  exit 1
fi

if [[ "${MODE}" != "data" && "${MODE}" != "mc" ]]; then
  echo "ERROR: --mode must be 'data' or 'mc'"
  exit 1
fi

# Ensure logs dir exists (in submit initialdir it should exist; this helps if you run locally too)
mkdir -p logs

TMPQ=""
cleanup() {
  [[ -n "${TMPQ}" && -f "${TMPQ}" ]] && rm -f "${TMPQ}"
}
trap cleanup EXIT

if [[ -n "${QUEUEFILE}" ]]; then
  if [[ ! -f "${QUEUEFILE}" ]]; then
    echo "ERROR: Queue file not found: ${QUEUEFILE}"
    exit 1
  fi

  # Convert 3 columns -> 4 columns by prepending MODE
  TMPQ="$(mktemp)"
  awk -v m="${MODE}" 'NF>=3 {print m, $1, $2, $3}' "${QUEUEFILE}" > "${TMPQ}"

  echo "Submitting batch with mode='${MODE}' from queue file: ${QUEUEFILE}"
  echo "First few expanded lines (mode filelist outname outdir):"
  head -n 5 "${TMPQ}" || true

  condor_submit submit_preselBDT_v2.sub -append "queuefile=${TMPQ}"

else
  # Single job mode requires these fields
  if [[ -z "${FILELIST}" || -z "${OUTNAME}" || -z "${OUTDIR}" ]]; then
    echo "ERROR: For single-job submission you must provide --filelist --outname --outdir"
    usage
    exit 1
  fi

  if [[ ! -f "${FILELIST}" ]]; then
    echo "ERROR: filelist not found: ${FILELIST}"
    exit 1
  fi

  # Build a 1-line queue file for Condor
  TMPQ="$(mktemp)"
  printf "%s %s %s %s\n" "${MODE}" "${FILELIST}" "${OUTNAME}" "${OUTDIR}" > "${TMPQ}"

  echo "Submitting single job:"
  cat "${TMPQ}"

  condor_submit submit_preselBDT_v2.sub -append "queuefile=${TMPQ}"
fi
