#include <iostream>
#include <string>

#include "include/local_aligner.hpp"

int main(int argc, char* argv[]) {

    if (argc == 2 && (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help")) {
        std::cout << "Usage:\n";
        std::cout << "  " << argv[0] << " [OPTIONS]\n\n";
        std::cout << "Options:\n";
        std::cout << "  --query <seq>        Query sequence\n";
        std::cout << "  --subject <seq>      Subject sequence\n";
        std::cout << "  --demo               Use demo sequences (ACGTRYSWKMAACAA vs AAACGTACGTACGTAAACGTACTSAGAAAAAACGTACGTAAA)\n";
        std::cout << "  --output <format>    Output format: standard, fasta, or alignment (default: standard)\n";
        std::cout << "  --exact-match <n>    Score for exact matches (default: 3)\n";
        std::cout << "  --iupac-match <n>    Score for IUPAC compatible matches (default: 2)\n";
        std::cout << "  --mismatch <n>       Penalty for mismatches (default: -2)\n";
        std::cout << "  --gap <n>            Penalty for gaps (default: -3)\n";
        std::cout << "  -h, --help           Show this help message\n\n";
        std::cout << "Examples:\n";
        std::cout << "  " << argv[0] << " --demo                                          # Demo with default sequences\n";
        std::cout << "  " << argv[0] << " --query ACGT --subject ACGT                     # Basic alignment\n";
        std::cout << "  " << argv[0] << " --query ACGTR --subject ACGTY --exact-match 5   # Custom scoring\n";
        std::cout << "  " << argv[0] << " --query ACGT --subject ACGT --gap -5            # Different gap penalty\n";
        std::cout << "  " << argv[0] << " --query ACGT --subject ACGT --output fasta     # FASTA format output\n";
        std::cout << "  " << argv[0] << " --help                                          # Show this help\n\n";
        return 0;
    }
        
    int exact_match = 3;
    int iupac_match = 2;
    int mismatch = -2;
    int gap = -3;
    std::string query, subject;
    std::string output_format = "standard";
    
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        
        if (arg == "--demo") {
            query = "CTGAAGGRATTGCCCCACAACGAACCTTGTTCGTAGTGTCAGTAATTATTACTTCATTAATACTGGTTGTGGCCAWGCCTGTGMTAGCTGCCG";
            subject = "AAGCTTATATTTTGTACTAGGTTTATGATCGGGATTGGTAGGTTTAGTTTATAGAACAATAATGCGAACAGAGCTAATACACCCAGGGGCTTTTTATGGTGAGTCTGTGTATAATGTGTTAGTCACATCTCATGGGCTACTTATAATTTTCTTCATAGTAATACCTTTAATAATTGGTTTTTTTGGTAATTGGGCCGTTCCTCTCTTACTTGCAGCTCCGGACATAGTGTTCGCACGGTTAAATAACCTTAGGTTTTGATTACTACCTGCAGCCACAGTTTTACTCCTTATATCTAACGAAGTTGAAGAAGGGGTGGGGACTGGGTGGACATTATACCCCCCTCTCTCTGCTTGACTTGGGCATCCAGCCCCTGCTTTAGAATTTATGATTTTAGGGCTACACATCGCAGGAATGTCATCTATTTTTGCTAGTATTAATTTTGTAACAACAGGTGCCAATATGCGGCCTGAAGGAATTGCCCCACAACGAACTACCTTGTTCGTAGTGTCAGTAATTATTACTTCATTTTTACTGGTTGTGGCCATGCCTGTGCTACTGCCGGGTTAACAATGCTTTTAACCGACCGTAATTTTAATACTTCGTTTTTCGACCCTGTAGGGGGGGGAGACCCTGTCTTATTCATTCATCTTTTC";
        } else if (arg == "--query" && i + 1 < argc) {
            query = argv[++i];
        } else if (arg == "--subject" && i + 1 < argc) {
            subject = argv[++i];
        } else if (arg == "--output" && i + 1 < argc) {
            output_format = argv[++i];
        } else if (arg == "--exact-match" && i + 1 < argc) {
            try {
                exact_match = std::stoi(argv[++i]);
            } catch (const std::exception& e) {
                std::cerr << "Error: Invalid exact-match value: " << argv[i] << "\n";
                return 1;
            }
        } else if (arg == "--iupac-match" && i + 1 < argc) {
            try {
                iupac_match = std::stoi(argv[++i]);
            } catch (const std::exception& e) {
                std::cerr << "Error: Invalid iupac-match value: " << argv[i] << "\n";
                return 1;
            }
        } else if (arg == "--mismatch" && i + 1 < argc) {
            try {
                mismatch = std::stoi(argv[++i]);
            } catch (const std::exception& e) {
                std::cerr << "Error: Invalid mismatch value: " << argv[i] << "\n";
                return 1;
            }
        } else if (arg == "--gap" && i + 1 < argc) {
            try {
                gap = std::stoi(argv[++i]);
            } catch (const std::exception& e) {
                std::cerr << "Error: Invalid gap value: " << argv[i] << "\n";
                return 1;
            }
        }
    }
    
    if (query.empty() || subject.empty()) {
        std::cerr << "Error: Both --query and --subject sequences must be provided, or use --demo\n";
        std::cerr << "Use --help for usage information\n";
        return 1;
    }
    
    LocalAligner aligner(exact_match, iupac_match, mismatch, gap);
        
    // Output based on format
    if (output_format == "fasta") {
        AlignmentResult result = aligner.align(query, subject);
        std::cout << result.to_fasta();
    } else if (output_format == "alignment") {
        AlignmentResult result = aligner.align(query, subject);
        std::cout << result.to_alignment_format();
    } else {
        std::cout << "=== Local sequence alignment ===\n";
        std::cout << "Parameters:\n";
        std::cout << "  Exact match score: " << exact_match << "\n";
        std::cout << "  IUPAC match score: " << iupac_match << "\n";
        std::cout << "  Mismatch penalty: " << mismatch << "\n";
        std::cout << "  Gap penalty: " << gap << "\n\n";
        
        std::cout << "Query sequence: " << query << "\n";
        std::cout << "Subject sequence: " << subject << "\n\n";
        
        std::cout << "Performing alignment...\n";

        AlignmentResult result = aligner.align(query, subject);
    
        std::cout << "\n=== Results ===\n";
        std::cout << "Score: " << result.score << "\n";
        std::cout << "Identity: " << result.identity << "%\n";
        std::cout << "Similarity: " << result.similarity << "%\n";
        std::cout << "Exact matches: " << result.exact_matches << "\n";
        std::cout << "IUPAC matches: " << result.iupac_matches << "\n";
        std::cout << "Mismatches: " << result.mismatches << "\n";
        std::cout << "Gaps: " << result.gaps << "\n";
        
        std::cout << "\n=== Alignment ===\n";
        std::cout << result.to_alignment_format();
    }
    
    return 0;
}
