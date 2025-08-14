# primal

Local sequence alignment with IUPAC code support.

## Installation

```bash
make && make install
```

## Usage

``` bash
./primal --demo                                               
=== Local sequence alignment ===
Parameters:
  Exact match score: 3
  IUPAC match score: 2
  Mismatch penalty: -2
  Gap penalty: -3

Performing alignment...

=== Results ===
Score: 251
Identity: 90.625%
Similarity: 93.75%
Exact matches: 87
IUPAC matches: 3
Mismatches: 2
Gaps: 4

=== Alignment ===
Query    1       CTGAAGGRATTGCCCCACAACG-A--ACCTTGTTCGTAGTGTCAGTAATTATTACTTCAT 57
                 |||||||:||||||||||||||.|..||||||||||||||||||||||||||||||||||
Subject  468     CTGAAGGAATTGCCCCACAACGAACTACCTTGTTCGTAGTGTCAGTAATTATTACTTCAT 527
Query    58      TAATACTGGTTGTGGCCAWGCCTGTGMTAGCTGCCG 93
                 |**|||||||||||||||:|||||||:||.||||||
Subject  528     TTTTACTGGTTGTGGCCATGCCTGTGCTA-CTGCCG 562
```