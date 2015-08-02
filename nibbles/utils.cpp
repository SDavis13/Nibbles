#include "utils.hpp"
#include "globals.hpp"

int angleOrientation(const b2Vec2& first, const b2Vec2& center, const b2Vec2& last){
    float value = (center.x - first.x) * (last.y - first.y) - (last.x - first.x) * (center.y - first.y);

    if( value >= 0 && value < 0.01 ){
        return COLINEAR;
    }
    if (value > 0) {
        return COUNTERCLOCKWISE;
    }else{
        return CLOCKWISE;
    }
}