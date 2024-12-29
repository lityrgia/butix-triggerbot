#pragma once
#include <iostream>

struct vec2 {
	float x;
	float y;
};

struct vec3 {
	float x = 0;
	float y = 0;
	float z = 0;

    vec3 operator-(const vec3& other) const {
        return vec3(x - other.x, y - other.y, z - other.z);
    }

    static float distance(const vec3& a, const vec3& b) {
        return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2) + std::pow(b.z - a.z, 2));
    }
};