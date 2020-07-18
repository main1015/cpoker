//
// Created by myth on 2020/7/16.
//

#include <stdio.h>
#include <iostream>
#include<ctime>
#include <armadillo>
#include "lib/assemble.h"

using namespace arma;

int main() {

    clock_t startTime,endTime;

//    imat A(13,4);
//    A.zeros();
//    for(int i=0; i<13; i++){
//        for(int j=0; j<4; j++){
//            A(i, j) = i + j * 13;
//        }
//    }
//    A(0, 0) = 1;
//    A(0, 1) = 1;
//    A(10, 1) = 1;
//    A(10, 3) = 1;
//    A(11, 1) = -1;

//    A.print("A:");
//    cout << "max(A): " << endl << max(A) << endl;
//    (A + 1).print(">1:");
//    cout << "------------------------------------------" << endl;
//    cout << A.col(0) << endl;
//    cout << "------------------------------------------" << endl;
//    cout << A.row(0) << endl;
//    uvec b = find(A >= 1);

//    uvec b = find(A.col(1) >=26);
//
//    b.print(">>");


    Card hands[5] = {
//            Card{3, 0},
//            Card{5, 1},
//            Card{2, 0},
//            Card{5, 3},
//            Card{14, 0},

            Card{11, 2},
            Card{12, 2},
            Card{10, 2},
            Card{7, 3},
            Card{6, 0},

    };
    Card cards[2] = {
//            Card{4, 0},
//            Card{5, 0},

            Card{8, 2},
            Card{13, 2},
    };

    int hl = sizeof(hands) / sizeof(hands[0]);
    int cl = sizeof(cards) / sizeof(cards[0]);

    startTime = clock();
    CR cr = compose_poker(hands, hl, cards, cl);
    endTime = clock();
    double t = endTime - startTime;
    cout << t << " us" << endl;
    cout << "The run time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    cout << "state:" << cr.model << endl;
    cr.cards.print("cards:");
    return 0;
}