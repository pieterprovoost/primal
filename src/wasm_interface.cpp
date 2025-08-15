#include "../include/wasm_interface.hpp"
#include <emscripten/bind.h>

WasmAligner::JsAlignmentResult WasmAligner::align_sequences(const std::string& query, const std::string& subject) {
    AlignmentResult result = aligner.align(query, subject);
    
    return JsAlignmentResult{
        result.aligned_seq1,
        result.aligned_seq2,
        result.match_line,
        result.score,
        result.identity,
        result.similarity,
        result.start_i,
        result.end_i,
        result.start_j,
        result.end_j
    };
}

EMSCRIPTEN_BINDINGS(primal_module) {
    emscripten::class_<WasmAligner::JsAlignmentResult>("AlignmentResult")
        .property("query", &WasmAligner::JsAlignmentResult::query)
        .property("subject", &WasmAligner::JsAlignmentResult::subject)
        .property("match_line", &WasmAligner::JsAlignmentResult::match_line)
        .property("score", &WasmAligner::JsAlignmentResult::score)
        .property("identity", &WasmAligner::JsAlignmentResult::identity)
        .property("similarity", &WasmAligner::JsAlignmentResult::similarity)
        .property("queryStart", &WasmAligner::JsAlignmentResult::query_start)
        .property("queryEnd", &WasmAligner::JsAlignmentResult::query_end)
        .property("subjectStart", &WasmAligner::JsAlignmentResult::subject_start)
        .property("subjectEnd", &WasmAligner::JsAlignmentResult::subject_end);
    
    emscripten::class_<WasmAligner>("Aligner")
        .constructor<int, int, int, int>()
        .constructor<>()
        .function("align", &WasmAligner::align_sequences);
}
