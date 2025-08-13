#ifndef LOCAL_ALIGNER_HPP
#define LOCAL_ALIGNER_HPP

#include "alignment_result.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class LocalAligner {
private:
    int exact_match_score;
    int iupac_match_score;
    int mismatch_penalty;
    int gap_penalty;
    
    std::unordered_map<char, std::unordered_set<char> > iupac_codes;
    
    void initialize_iupac_codes();
    int get_score(char char1, char char2);
    char get_match_type(char char1, char char2);
    AlignmentResult traceback(const std::string& seq1, const std::string& seq2, 
                              const std::vector<std::vector<int> >& score_matrix,
                              int start_i, int start_j);

public:
    LocalAligner(int exact_match = 3, int iupac_match = 2, int mismatch = -2, int gap = -3);
    
    AlignmentResult align(const std::string& sequence1, const std::string& sequence2);
    
    int get_exact_match_score() const;
    int get_iupac_match_score() const;
    int get_mismatch_penalty() const;
    int get_gap_penalty() const;
    
    void set_scores(int exact_match, int iupac_match, int mismatch, int gap);
};

#endif
