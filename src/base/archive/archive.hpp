#pragma once
#include "game.hpp"
#include "ofMain.hpp"

#define little32(symbol) __builtin_bswap32(symbol)
#define little16(symbol) __builtin_bswap16(symbol)

// Structs (thanks wiibrew)

struct U8_archive_header {
    u32 tag; // must be 0x55AA382D "U.8-"
    u32 rootnode_offset; // offset to root_node, always 0x20.
    u32 header_size; // size of header from root_node to end of string table.
    u32 data_offset; // offset to data -- this is rootnode_offset + header_size, aligned to 0x40.
    u8 zeroes[16];
};

struct U8_node {
    u16 type; //this is really a u8
    u16 name_offset; //really a "u24"
    u32 data_offset;
    u32 size;
};

/// @brief Raw U8 archive data and its' size, in a struct.
/// Don't use this if you're trying to load a texture.
struct U8Data {
    void* data;
    u32 size;
};

// Functionals
vector<u8> ReadLZMAArchive(string path);
U8Data getResourceFromU8(vector<u8> &u8Arc, string resource);

// Implement bottom one later
ofImage loadImageFromU8(vector<u8> &arc, string resource);