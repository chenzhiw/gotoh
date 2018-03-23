#include <stdio.h>
#include "gotoh.h"
void align(void)
{
    char seqa[] = "GAATGGAGCCACCTGCGATTCCGTGACCGGAAGCTGCGAGTG";
    char seqb[] = "ATCTGCAGCTGCCAGAATGGAGCCACCTGCGATTCCGTGACC";
    size_t lena = strlen(seqa);
    size_t lenb = strlen(seqb);
    gth_Sub matrix = gth_read_matrix("EDNAMAT");
    int gapopen=10, gapextend=1, endopen=0, endextend=0;

    gth_Arr array = gth_init(lena, lenb);
    gth_set_sub(array, seqa, seqb, matrix.score);
    gth_set_gap(array, gapopen, gapextend, endopen, endextend);
    int score = gth_align(array);

    for (int k=0 ; k<3 ; k++) {
        printf("# scores in array %c:\n", 'X'+k);
        for (size_t i=0 ; i<=array.lenX ; i++) {
            for (size_t j=0 ; j<=0 ; j++) {
                printf("% 15d ", array.data[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }


    printf("Score: %d\n", score);
    gth_putseq(stdout, seqa, array.gapX);
    printf("\n");
    gth_putseq(stdout, seqb, array.gapY);
    printf("\n");

    gth_free(array);
    //free(sequenceX.res);
    //free(sequenceY.res);
}

int main(void)
{
    align();
    return 0;
}
