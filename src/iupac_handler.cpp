#include "../include/local_aligner.hpp"
#include <unordered_set>

void LocalAligner::initialize_iupac_codes() {
    iupac_codes = {
        {'A', {'A'}},
        {'T', {'T'}},
        {'G', {'G'}},
        {'C', {'C'}},
        {'U', {'T'}},
        {'R', {'A', 'G'}},
        {'Y', {'C', 'T'}},
        {'S', {'G', 'C'}},
        {'W', {'A', 'T'}},
        {'K', {'G', 'T'}},
        {'M', {'A', 'C'}},
        {'B', {'C', 'G', 'T'}},
        {'D', {'A', 'G', 'T'}},
        {'H', {'A', 'C', 'T'}},
        {'V', {'A', 'C', 'G'}},
        {'N', {'A', 'C', 'G', 'T'}}
    };
}

int LocalAligner::get_score(char char1, char char2) {
    if (char1 == char2) {
        return exact_match_score;
    }
    
    auto it1 = iupac_codes.find(char1);
    auto it2 = iupac_codes.find(char2);
    
    if (it1 == iupac_codes.end() || it2 == iupac_codes.end()) {
        return mismatch_penalty;
    }
    
    const auto& bases1 = it1->second;
    const auto& bases2 = it2->second;
    
    for (char base1 : bases1) {
        if (bases2.count(base1) > 0) {
            return iupac_match_score;
        }
    }
    
    return mismatch_penalty;
}

char LocalAligner::get_match_type(char char1, char char2) {
    if (char1 == char2) {
        return '|';
    }
    
    auto it1 = iupac_codes.find(char1);
    auto it2 = iupac_codes.find(char2);
    
    if (it1 != iupac_codes.end() && it2 != iupac_codes.end()) {
        const auto& bases1 = it1->second;
        const auto& bases2 = it2->second;
        
        for (char base1 : bases1) {
            if (bases2.count(base1) > 0) {
                return ':';
            }
        }
    }
    
    return '*';
}
