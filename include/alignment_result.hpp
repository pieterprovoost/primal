#ifndef ALIGNMENT_RESULT_HPP
#define ALIGNMENT_RESULT_HPP

#include <string>

struct AlignmentResult {
    std::string aligned_seq1;
    std::string aligned_seq2;
    std::string match_line;
    int score;
    int start_i;
    int start_j;
    int end_i;
    int end_j;
    int exact_matches;
    int iupac_matches;
    int mismatches;
    int gaps;
    double identity;
    double similarity;
    
    std::string to_fasta(int line_width = 80) const;
    std::string to_alignment_format(int line_width = 60) const;
};

#endif
