#include <iostream>
#include "CImg/CImg.h"
#include "pHash/pHash.h"

using namespace std;

int main(int argv, char **argc)
{
    Digest dig1, dig2;

    if(argv != 3) {
        printf ("Pass two images as parameter");
        exit (EXIT_FAILURE);
    }

    try {
        ph_image_digest(argc[1], 1.0, 1.0, dig1, 180);
        ph_image_digest(argc[2], 1.0, 1.0, dig2, 180);

    } catch (CImgException) {
        printf ("One of the passed images can not be found");
        exit (EXIT_FAILURE);
    }

    double pcc;
    ph_crosscorr(dig1, dig2, pcc, 0.90);

    printf("%f", pcc);
}