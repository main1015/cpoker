//
// Created by myth on 2020/7/17.
//

#ifndef POKER_ASSEMBLE_H
#define POKER_ASSEMBLE_H
#include <armadillo>
#include "model.h"
#include "card.h"
using namespace arma;

typedef struct _cr{
    Model model;
    imat cards;
} CR;


typedef struct _lc{
//    int start;
    int length;
    uvec indexs;
} LC;

typedef struct _sr{
    Model model;
    uvec indexs;
} SR;


CR has_max_four(imat pokers, imat numbers, imat colors);
CR has_max_three(imat pokers, imat numbers, imat colors);
CR has_max_two(imat pokers, imat numbers, imat colors);
CR has_max_one(imat pokers, imat numbers, imat colors);

void has_straight_with_flush(CR* cr, imat pokers, imat numbers, imat colors);
SR is_straight(imat numbers);
LC longest_consecutive(uvec numbers);


CR compose_poker(Card* hands, int hl, Card* cards, int cl);

bool check_number(int number);
bool check_color(int color);

#endif //POKER_ASSEMBLE_H
