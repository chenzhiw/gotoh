Gotoh
=====


Short (around 500 lines) C implementation of the Gotoh algorithm, also known as the
[Needleman-Wunsch](http://en.wikipedia.org/wiki/Needleman-Wunsch) algorithm with affine gap penalties.


### Features ###

* C99-compliant, only uses `stdio.h`, `stdlib.h`, `string.h`, and `ctype.h`
* basic command-line interface
* read FASTA files
* read NCBI/EMBOSS scoring matrix files
* exact same results as [EMBOSS Needle](http://www.ebi.ac.uk/Tools/psa/emboss_needle/)
* initial values in the dynamic programming arrays can be loaded from files


Due to the last point, the program can be used for experimenting with different scoring schemes, for example:
* gap opening penalties depending on the residues surrounding the gap
* substitution scores depending on the matched residues *and* their positions in the sequence
* doing something else than biological sequence alignment, such as dynamic time warping


### Usage ###

Compile with this command:
```
gcc -std=c99 gotoh.c main.c -o align
```
Then type `./align` and read the help message.

Basic example showing how to use the code:
```C
gth_Seq sequence1 = gth_read_fasta("first_sequence.fasta");
gth_Seq sequence2 = gth_read_fasta("second_sequence.fasta");
gth_Sub matrix = gth_read_matrix("BLOSUM62");
int gapopen=10, gapextend=1, endopen=0, endextend=0;

gth_Arr array = gth_init(sequence1.len, sequence2.len);
gth_set_sub(array, sequence1.res, sequence2.res, matrix.score);
gth_set_gap(array, gapopen, gapextend, endopen, endextend);
int score = gth_align(array);

printf(">%s\n", sequence1.name);
gth_putseq(stdout, sequence1.res, array.gapX);
printf("\n\n>%s\n", sequence2.name);
gth_putseq(stdout, sequence2.res, array.gapY);
printf("\n");

gth_free(array);
free(sequence1.res);
free(sequence2.res);
```


### Reference ###
Durbin, Eddy, Krogh, Mitchison. [Biological Sequence Analysis](http://books.google.com/books?id=R5P2GlJvigQC),
*Cambridge University Press*, 1998.

