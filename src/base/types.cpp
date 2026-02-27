#include "raster.hpp"

RasRectangle::RasRectangle() {
    x = 0;
    y = 0;
    position.x = 0;
    position.y = 0;
    width = 0;
    height = 0;
}

RasRectangle RasRectangle::operator=(ofRectangle other) {
    this->set(other.x, other.y, other.width, other.height);
    return *this;
}

void RasRectangle::set(float x, float y, float width, float height) {
    x *= mul;
    y *= mul;
    ofRectangle::set(x, y, width, height);
    scale(mul, mul);
}