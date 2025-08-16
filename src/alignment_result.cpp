#include "../include/alignment_result.hpp"
#include <string>

std::string AlignmentResult::to_fasta(int line_width) const {
    std::string fasta_output;
    
    fasta_output += ">Query\n";    
    for (size_t i = 0; i < aligned_seq1.length(); i += line_width) {
        fasta_output += aligned_seq1.substr(i, line_width) + "\n";
    }
    
    fasta_output += ">Subject\n";    
    for (size_t i = 0; i < aligned_seq2.length(); i += line_width) {
        fasta_output += aligned_seq2.substr(i, line_width) + "\n";
    }
    
    return fasta_output;
}

std::string AlignmentResult::to_alignment_format(int line_width) const {
    std::string alignment_output;
    
    for (size_t i = 0; i < aligned_seq1.length(); i += line_width) {
        size_t end_pos = std::min(i + line_width, aligned_seq1.length());
        
        int query_pos = start_i;
        int subject_pos = start_j;
        
        for (size_t k = 0; k < i; ++k) {
            if (aligned_seq1[k] != '-') query_pos++;
            if (aligned_seq2[k] != '-') subject_pos++;
        }
        
        int query_end = query_pos;
        int subject_end = subject_pos;
        for (size_t k = i; k < end_pos; ++k) {
            if (aligned_seq1[k] != '-') query_end++;
            if (aligned_seq2[k] != '-') subject_end++;
        }
        
        alignment_output += "Query    ";
        alignment_output += std::to_string(query_pos);
        alignment_output += std::string(8 - std::to_string(query_pos + 1).length(), ' ');
        alignment_output += aligned_seq1.substr(i, end_pos - i);
        alignment_output += " " + std::to_string(query_end - 1) + "\n";
        
        alignment_output += std::string(17, ' ');
        alignment_output += match_line.substr(i, end_pos - i) + "\n";
        
        alignment_output += "Subject  ";
        alignment_output += std::to_string(subject_pos);
        alignment_output += std::string(8 - std::to_string(subject_pos + 1).length(), ' ');
        alignment_output += aligned_seq2.substr(i, end_pos - i);
        alignment_output += " " + std::to_string(subject_end - 1) + "\n";
    }
    
    return alignment_output;
}
