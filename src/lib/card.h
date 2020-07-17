//
// Created by myth on 2020/7/17.
//

#ifndef POKER_CARD_H
#define POKER_CARD_H

typedef struct _card{
    unsigned int number: 4; // 0~15
    unsigned int color:2; // 0~3
} Card;



#endif //POKER_CARD_H
