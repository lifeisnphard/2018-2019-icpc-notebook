#!/bin/bash
# Script to generate LaTeX sections for ICPC notebook
# Usage: ./caderno.sh > notebook_content.tex

echo "% ICPC/IOI Competitive Programming Notebook"
echo ""

# Function to process directory
process_directory() {
    local dir=$1
    local title=$2
    
    echo "\\section{${title}}"
    echo ""
    
    # Process all .cpp and .py files in directory and subdirectories
    find "$dir" -type f \( -name "*.cpp" -o -name "*.py" \) | sort | while read -r file; do
        filename=$(basename "$file")
        relpath="${file#./}"
        
        # Determine language
        if [[ $file == *.py ]]; then
            lang="python"
        else
            lang="cpp"
        fi
        
        echo "\\subsection{${filename}}"
        echo "\\inputminted[linenos,tabsize=4,breaklines,fontsize=\\small]{${lang}}{${relpath}}"
        echo ""
    done
}

# Process each category
process_directory "templates" "Templates"
process_directory "data-structures" "Data Structures"
process_directory "graph-algorithms" "Graph Algorithms"
process_directory "string-algorithms" "String Algorithms"
process_directory "number-theory" "Number Theory"
process_directory "dynamic-programming" "Dynamic Programming"
process_directory "geometry" "Geometry"
process_directory "problems" "Problem Solutions"

echo "% End of notebook"
