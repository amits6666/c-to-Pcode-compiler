#include <stdio.h>

void main(){
    int i1;
    int i2;
    float f1;
    float f2;
    double d1;
    double d2;

    i1 = 5;
    /* i1 = 5.000 -> No need to support this line */
    i2 = 10;
    /* i1 = 10.000 -> No need to support this line */
    f1 = 8.82000000;
    f2 = 10.0;
    /* f2 = 10 -> No need to support this line */
    d1 = 5.12;
    d2 = 18.0;

    printf("%d\n", 5);
    /* printf("%d\n", 5.0); -> No need to support this line */

    printf("%f\n", 10.5);
    printf("%f\n", 10.0);
    /* printf("%f\n", 10); -> No need to support this line */

    f1 = ((i2 == 10)?2.5:1.0) + ((d1 == d2)?0.0:-3.2);

    f1 = ((i2 == 10)?2.5:1.0) + ((d1 == d2)?0.0:-2.5);

    printf("%f\n", f1);
    printf("%f\n", f2);

    printf("%d\n", i1++);
    printf("%d\n", ++i2);

    while(i1 < 15){
        i1 += (i2 == 11)?2:1;
        printf("%d\n",i1);
    }

    
    for(i1=0 ; i1 <= i2 ; i1++){
        printf("%d\n",i1);
        printf("%d\n",i2);
    }


    return;
}
