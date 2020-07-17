//
// Created by myth on 2020/7/15.
//

#ifndef FIRST_MODEL_H
#define FIRST_MODEL_H

typedef enum _Model{
    // 皇家同花顺，同花色的A， K， Q，J和10。
    ROYAL_FLUSH = 10,
    // 同花顺，五张同花色的连续牌，如有多副同花顺，以最高一张牌（顶张）比大小。
    STRAIGHT_WITH_FLUSH = 9,
    // 四条，四张相同数的牌，第五张是随意一张牌。如有多人四条，以第五张牌比大小。
    FOUR_OF_A_KIND = 8,
    // 葫芦，三张相同数及两张相同数的牌，如出现多副葫芦，先比三张大小，再比两张大小。
    HOUSE = 7,
    // 同花，五张不连号但相花色相同的牌，如出现多副同花，从最大数一直比到第五张。
    FLUSH = 6,
    // 顺子，由五张连号但花色不相同牌组成，如有多幅顺子，以最高一张牌（顶张）比大小。
    STRAIGHT = 5,
    // 三条，由三张相同数和两张不同数的牌组成，如有多幅三条，先比三张，再比单张。
    THREE_ARTICLE = 4,
    // 两对，两对相同牌和随意一张牌组成，如有多幅两对，先比大小对，再比单张大小。
    TWO_PAIR = 3,
    // 一对，由两张相同牌和另三张随意牌组成，如有多幅一对，先比对大小，再比单张大小。
    ONE_PAIR = 2,
    // 高牌，五张散牌，如有多幅高牌，从最大牌开始比，一直到第五张为止。
    HIGH_CARD = 1,
    //
    UNKNOWN = 0,
}Model;

#endif //FIRST_MODEL_H
