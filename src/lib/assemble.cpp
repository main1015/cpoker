//
// Created by myth on 2020/7/17.
//

#include "assemble.h"

CR has_max_four(imat pokers, imat numbers, imat colors){
    CR cr;
    return cr;
}
CR has_max_three(imat pokers, imat numbers, imat colors){
    /*
     * 最大含有3个相同
     * */
    CR cr;
    cr.model = UNKNOWN;
    cr.cards.zeros(13, 4);
    uvec b = find(numbers.col(0) == 3 );
    if(!b.is_empty()){
        // 3, .....
        int index = b[0];
        cr.cards.row(index) = pokers.row(index);
        // 大于2个相同的牌
        uvec nb = find(numbers.col(0) >= 2);
        int size = nb.size();
        if (size > 1){
            // 3,3,1; 3,2,2; 3,2,1,1
            // 葫芦
            cr.model = HOUSE;
            int i = size - 1;
            for(; i >= 0; i--){
                int ix = nb[i];
                if(ix == index){
                    continue;
                }else{
//                    imat row = pokers.row(i);
                    int j = 0, n = 0;
                    for(;j < 4; j++){
                        if(n<2){

                            if(pokers(ix, j)){
                                cr.cards(ix, j) = pokers(ix, j);
                                n++;
                            }
                        }else{
                            break;
                        }
                    }
                    break;
                }
            }
        }else{
            // 3,1,1,1,1
            has_straight_with_flush(&cr, pokers, numbers, colors);
            // 出现大于5张同色的牌
            if(cr.model == UNKNOWN){
                // 三条
                cr.model = THREE_ARTICLE;
                uvec ob = find(numbers.col(0) == 1 );
                int os = ob.size();
                for(int i=os-1, j=0; i>=0, j<2; i--,j++){
                    int ix = ob[i];
                    uvec r = find(pokers.row(ix) == 1);
                    cr.cards(ix, r[0]) = 1;
                }
            }
        }
    }

    return cr;
}
CR has_max_two(imat pokers, imat numbers, imat colors){
    CR cr;
    return cr;
}
CR has_max_one(imat pokers, imat numbers, imat colors){
    CR cr;
    return cr;
}


void has_straight_with_flush(CR* cr, imat pokers, imat numbers, imat colors){
    // 出现大于5张同色的牌
    uvec b = find(colors.row(0) >= 5 );
    int size = b.size();
    if(size){
        // 同花
        cr->model = FLUSH;
        cr->cards.fill(0);
        int i = b[0];
        // 取出某种色的数组
        imat _color = pokers.col(i);
        SR sr = is_straight(_color);
        if(sr.model == STRAIGHT){
            // 同花顺
            cr->model = STRAIGHT_WITH_FLUSH;
            size = sr.indexs.size();
            for(int j=0; j<size;j++){
                int ix = sr.indexs[j];
                cr->cards(ix, i) = 1;
            }
            if(sr.indexs[0] == 10-2){
                // 皇家同花顺
                cr->model = ROYAL_FLUSH;
            }

        }else{
            // 同花
            size = sr.indexs.size();
            for(int j=0; j<size;j++){
                int ix = sr.indexs[j];
                cr->cards(ix, i) = 1;
            }

        }
    }else{
        SR sr = is_straight(numbers);
        if(sr.model == STRAIGHT){
            // 顺子
            cr->model = STRAIGHT;
            cr->cards.fill(0);

            size = sr.indexs.size();
            for(int j=0; j<size;j++){
                int ix = sr.indexs[j];
                uvec r = find(pokers.row(ix) == 1);
                cr->cards(ix, r[0]) = 1;
            }
        }

    }
}

SR is_straight(imat numbers){
    // 判断是否为顺子
    uvec b = find(numbers.col(0) >= 1 );
    SR sr;
    int size = b.size();
    int l = size > 5? 5: size;
    uvec idx(l);
    for(int i=size-1, j=4; i>=0, j>=0; i--, j--){
        idx(j) = b[i];
    }
    sr.model = UNKNOWN;
    sr.indexs = idx;
    if(size >= 5){
        LC lc = longest_consecutive(b);
        if(lc.length >=5){
            sr.model = STRAIGHT;
            sr.indexs = lc.indexs;
        }
    }
    return sr;
}

LC longest_consecutive(uvec numbers){
    // 查找最大连续数, 必须是升序排列的数组
    LC lc;

    int size = numbers.size();
    int sizes[size], indexs[size];

    int i = 1, j = 0, index = 0;
    sizes[j] = 1;
    indexs[j] = 0;
    j++;
    for(; i<size; i++){
        if(numbers[i-1] + 1 == numbers[i]){
            sizes[j-1] += 1;
        }else{

            indexs[j] = i;
            sizes[j] = 1;
            j++;
        }
    }
    int nums = 0, mx = 0;
    for(int k=0; k < j; k++){
        if(size-nums < mx){
            break;
        }else{
            int s = sizes[k];
            nums += s;
            if(mx < s){
                mx = s;
                index = k;
            }
        }
    }
    uvec idx;
    // 连续数的个数等于4并且最小为2（0）时，要判断是否有A
    if(mx == 4 && index==0 && numbers[size-1] == 12){
        idx.set_size(mx+1);
        lc.length = mx+1;
        idx(mx) = numbers[size-1];
    }else{
        idx.set_size(mx);
        lc.length = mx;
    }
    for(int n=0; n < mx; n++){
        idx(n) = numbers[index +n];
    }


//    lc.start = index;
    lc.indexs = idx;
    return lc;

}

CR compose_poker(Card *hands, int hl, Card *cards, int cl){


//    int l = hl + cl;
    imat pokers, numbers, colors;
    pokers.zeros(13,4);
    numbers.zeros(13,1);
    colors.zeros(1,4);
    int i=0, j=0;
    for(; i < cl; i++){
        Card c = cards[i];
        int _n = c.number - 2;
        int _c = c.color;

        if(check_number(c.number) && check_color(_c)){
            pokers(_n, _c) = 1;
            numbers(_n, 0) += 1;
            colors(0, _c) += 1;
        }

    }

    for(; j < hl; j++){
        Card h = hands[j];
        int _n = h.number - 2;
        int _c = h.color;
        if(check_number(h.number) && check_color(_c)){
            pokers(_n, _c) = 1;
            numbers(_n, 0) += 1;
            colors(0, _c) += 1;
        }
    }
    int nx = numbers.max();
    CR cr;
    switch (nx){
        case 4:
            cr = has_max_four(pokers, numbers, colors);
            break;
        case 3:
            cr = has_max_three(pokers, numbers, colors);
            break;
        case 2:
            cr = has_max_two(pokers, numbers, colors);
            break;
        case 1:
            cr = has_max_one(pokers, numbers, colors);
            break;
        default:
            // todo 需要抛出异常
            break;
    }

    return cr;
}


bool check_number(int number){
    if(2 <= number && number <= 14){
        return true;
    }else{
        return false;
    }
}

bool check_color(int color){
    if(0 <= color && color <= 3){
        return true;
    }else{
        return false;
    }
}