#include "../include/local_aligner.hpp"
#include <vector>
#include <algorithm>

AlignmentResult LocalAligner::align(const std::string& sequence1, const std::string& sequence2) {
    if (sequence1.empty() || sequence2.empty()) {
        AlignmentResult empty_result;
        empty_result.aligned_seq1 = "";
        empty_result.aligned_seq2 = "";
        empty_result.match_line = "";
        empty_result.score = 0;
        empty_result.start_i = 0;
        empty_result.start_j = 0;
        empty_result.end_i = 0;
        empty_result.end_j = 0;
        empty_result.exact_matches = 0;
        empty_result.iupac_matches = 0;
        empty_result.mismatches = 0;
        empty_result.gaps = 0;
        empty_result.identity = 0.0;
        empty_result.similarity = 0.0;
        return empty_result;
    }
    
    size_t m = sequence1.length();
    size_t n = sequence2.length();
    
    std::vector<std::vector<int> > score_matrix(m + 1, std::vector<int>(n + 1, 0));
    
    int max_score = 0;
    int max_i = 0;
    int max_j = 0;
    
    for (size_t i = 1; i <= m; ++i) {
        for (size_t j = 1; j <= n; ++j) {
            int match = score_matrix[i-1][j-1] + get_score(sequence1[i-1], sequence2[j-1]);
            int delete_gap = score_matrix[i-1][j] + gap_penalty;
            int insert_gap = score_matrix[i][j-1] + gap_penalty;
            
            score_matrix[i][j] = std::max(0, std::max(match, std::max(delete_gap, insert_gap)));
            
            if (score_matrix[i][j] > max_score) {
                max_score = score_matrix[i][j];
                max_i = static_cast<int>(i);
                max_j = static_cast<int>(j);
            }
        }
    }
    
    return traceback(sequence1, sequence2, score_matrix, max_i, max_j);
}
