#ifndef WASM_INTERFACE_HPP
#define WASM_INTERFACE_HPP

#include "local_aligner.hpp"

class WasmAligner {
private:
    LocalAligner aligner;
    
public:
    WasmAligner(int exact_match = 3, int iupac_match = 2, int mismatch = -2, int gap = -3)
        : aligner(exact_match, iupac_match, mismatch, gap) {}
    
    struct JsAlignmentResult {
        std::string query;
        std::string subject;
        std::string match_line;
        int score;
        double identity;
        double similarity;
        int query_start;
        int query_end;
        int subject_start;
        int subject_end;
    };
    
    JsAlignmentResult align_sequences(const std::string& query, const std::string& subject);
};

#endif
