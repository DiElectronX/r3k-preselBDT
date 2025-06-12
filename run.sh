#!/bin/bash

# Directory containing the .txt files
input_dir="/eos/user/j/jodedra/AnalysisWork_2024/BDTScoreadder_FINAL/CMSSW_14_0_1/src/BDTscoreAdder/filelists/FinalList/eoslist_MC_20_11_24"

# Loop over all .txt files in the directory
for full_file_path in "$input_dir"/*.txt; do
    # Extract the file name without the directory path
    filename=$(basename "$full_file_path" .txt)

    # Export the file name as a variable
    export FILE_NAME="$filename"
    
    # Run the C++ command (replace 'your_cpp_command' with the actual command)
    # For example, if your C++ command is an executable called 'process_file'
    ./addbdtscoreMC.exe ${full_file_path} ${FILE_NAME} PartialRecoOutput/
    
    # Wait for the C++ command to finish before proceeding to the next file name
    echo "Finished processing $FILE_NAME"
done

# Print a message indicating the script has finished
echo "Processing complete. All .txt files have been processed."