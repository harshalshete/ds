#define TESTBIT(N, bit) (N & (0x1 << bit))

*/
A binary gap within a positive integer N is any maximal sequence of consecutive zeros that is surrounded by ones at both ends in the binary representation of N.

For example, number 9 has binary representation 1001 and contains a binary gap of length 2. The number 529 has binary representation 1000010001 and contains two binary gaps: one of length 4 and one of length 3. The number 20 has binary representation 10100 and contains one binary gap of length 1. The number 15 has binary representation 1111 and has no binary gaps. The number 32 has binary representation 100000 and has no binary gaps.

Write a function:

int solution(int N);

that, given a positive integer N, returns the length of its longest binary gap. The function should return 0 if N doesn't contain a binary gap.

For example, given N = 1041 the function should return 5, because N has binary representation 10000010001 and so its longest binary gap is of length 5. Given N = 32 the function should return 0, because N has binary representation '100000' and thus no binary gaps.

Write an efficient algorithm for the following assumptions:
N is an integer within the range [1..2,147,483,647].
*/

int binary_gap(int N) {
    // write your code in C99 (gcc 6.2.0)
    int i = 0, bin_gap = 0;
    int first = -1;
    int second = -1;
    int no_of_bits = sizeof(N) * 8;

    // printf("N %d is of %d bits\n", N, no_of_bits);

    for (i=0; i < no_of_bits; i++) {

        if (TESTBIT(N, i) && (first == -1)) {
            // printf("first 1 is at %d\n", i);
            first = i;
        } else if (TESTBIT(N, i) && (second == -1)) {            

            second = i;

            // If we found consecutive 1's then update first with newly found bit number.
            if (second == (first + 1)) {
                first = second;
                second = -1;
                continue;
            }

            // printf("second 1 is at %d\n", i);

            // do not break here, instead refresh everything and continue till last bit
            if (bin_gap == -1) {
                bin_gap = (second - (first + 1));
                // printf("bin_gap = %d\n", bin_gap);
                first = i;
                second = -1;
            } else {
                int new_gap = (second - (first + 1));
                if (new_gap > bin_gap) {
                    bin_gap = new_gap;
                    // printf("bin_gap = %d\n", bin_gap);
                }
                first = i;
                second = -1;
            }
        }
    }   

    return bin_gap;
}
