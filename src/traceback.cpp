#include "../include/local_aligner.hpp"
#include <vector>

AlignmentResult LocalAligner::traceback(const std::string& seq1, const std::string& seq2, 
                                        const std::vector<std::vector<int> >& score_matrix,
                                        int start_i, int start_j) {
    std::string aligned_seq1, aligned_seq2, match_line;
    
    int i = start_i;
    int j = start_j;
    int actual_start_i = i;
    int actual_start_j = j;
    
    while (i > 0 && j > 0 && score_matrix[i][j] > 0) {
        actual_start_i = i;
        actual_start_j = j;
        
        int diagonal_score = score_matrix[i-1][j-1] + get_score(seq1[i-1], seq2[j-1]);
        int up_score = score_matrix[i-1][j] + gap_penalty;
        int left_score = score_matrix[i][j-1] + gap_penalty;
        
        if (score_matrix[i][j] == diagonal_score) {
            aligned_seq1 = seq1[i-1] + aligned_seq1;
            aligned_seq2 = seq2[j-1] + aligned_seq2;
            match_line = get_match_type(seq1[i-1], seq2[j-1]) + match_line;
            i--; j--;
        } else if (score_matrix[i][j] == up_score) {
            aligned_seq1 = seq1[i-1] + aligned_seq1;
            aligned_seq2 = '-' + aligned_seq2;
            match_line = '.' + match_line;
            i--;
        } else if (score_matrix[i][j] == left_score) {
            aligned_seq1 = '-' + aligned_seq1;
            aligned_seq2 = seq2[j-1] + aligned_seq2;
            match_line = '.' + match_line;
            j--;
        } else {
            break;
        }
    }
    
    int exact_matches = 0, iupac_matches = 0, mismatches = 0, gaps = 0;
    for (size_t k = 0; k < aligned_seq1.length(); ++k) {
        char c1 = aligned_seq1[k];
        char c2 = aligned_seq2[k];
        
        if (c1 == '-' || c2 == '-') {
            gaps++;
        } else if (c1 == c2) {
            exact_matches++;
        } else {
            char match_type = get_match_type(c1, c2);
            if (match_type == ':') {
                iupac_matches++;
            } else {
                mismatches++;
            }
        }
    }
    
    double identity = (double)exact_matches / aligned_seq1.length() * 100.0;
    double similarity = (double)(exact_matches + iupac_matches) / aligned_seq1.length() * 100.0;
    
    AlignmentResult result;
    result.aligned_seq1 = aligned_seq1;
    result.aligned_seq2 = aligned_seq2;
    result.match_line = match_line;
    result.score = score_matrix[start_i][start_j];
    result.start_i = actual_start_i - 1;
    result.start_j = actual_start_j - 1;
    result.end_i = start_i - 1;
    result.end_j = start_j - 1;
    result.exact_matches = exact_matches;
    result.iupac_matches = iupac_matches;
    result.mismatches = mismatches;
    result.gaps = gaps;
    result.identity = identity;
    result.similarity = similarity;
    return result;
}
