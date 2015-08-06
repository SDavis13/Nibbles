#ifndef UTILS_HPP
#define UTILS_HPP

#include <Box2D/Common/b2Math.h>

int angleOrientation(const b2Vec2& first, const b2Vec2& center, const b2Vec2& last);

float fmax(float f1, float f2);

#endif