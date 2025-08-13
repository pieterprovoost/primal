#include "../include/local_aligner.hpp"

LocalAligner::LocalAligner(int exact_match, int iupac_match, int mismatch, int gap)
    : exact_match_score(exact_match), iupac_match_score(iupac_match),
      mismatch_penalty(mismatch), gap_penalty(gap) {
    initialize_iupac_codes();
}

int LocalAligner::get_exact_match_score() const { return exact_match_score; }
int LocalAligner::get_iupac_match_score() const { return iupac_match_score; }
int LocalAligner::get_mismatch_penalty() const { return mismatch_penalty; }
int LocalAligner::get_gap_penalty() const { return gap_penalty; }

void LocalAligner::set_scores(int exact_match, int iupac_match, int mismatch, int gap) {
    exact_match_score = exact_match;
    iupac_match_score = iupac_match;
    mismatch_penalty = mismatch;
    gap_penalty = gap;
}
