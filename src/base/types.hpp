#pragma once
#include <ofMain.hpp>

typedef ofVec2f Vec2;
typedef ofVec3f Vec3;

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned long long u64;
typedef signed long long s64;

typedef union settingsType {
    u64 settings;
    u64* multiSettings;
} settingsType;