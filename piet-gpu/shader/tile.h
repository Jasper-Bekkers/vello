// SPDX-License-Identifier: Apache-2.0 OR MIT OR Unlicense

// Code auto-generated by piet-gpu-derive

struct PathRef {
    uint offset;
};

struct TileRef {
    uint offset;
};

struct TileSegRef {
    uint offset;
};

struct TransformSegRef {
    uint offset;
};

struct Path {
    uvec4 bbox;
    TileRef tiles;
};

#define Path_size 12

PathRef Path_index(PathRef ref, uint index) {
    return PathRef(ref.offset + index * Path_size);
}

struct Tile {
    TileSegRef tile;
    int backdrop;
};

#define Tile_size 8

TileRef Tile_index(TileRef ref, uint index) {
    return TileRef(ref.offset + index * Tile_size);
}

struct TileSeg {
    vec2 origin;
    vec2 vector;
    float y_edge;
    TileSegRef next;
};

#define TileSeg_size 24

TileSegRef TileSeg_index(TileSegRef ref, uint index) {
    return TileSegRef(ref.offset + index * TileSeg_size);
}

struct TransformSeg {
    vec4 mat;
    vec2 translate;
};

#define TransformSeg_size 24

TransformSegRef TransformSeg_index(TransformSegRef ref, uint index) {
    return TransformSegRef(ref.offset + index * TransformSeg_size);
}

Path Path_read(Alloc a, PathRef ref) {
    uint ix = ref.offset >> 2;
    uint raw0 = read_mem(a, ix + 0);
    uint raw1 = read_mem(a, ix + 1);
    uint raw2 = read_mem(a, ix + 2);
    Path s;
    s.bbox = uvec4(raw0 & 0xffff, raw0 >> 16, raw1 & 0xffff, raw1 >> 16);
    s.tiles = TileRef(raw2);
    return s;
}

void Path_write(Alloc a, PathRef ref, Path s) {
    uint ix = ref.offset >> 2;
    write_mem(a, ix + 0, s.bbox.x | (s.bbox.y << 16));
    write_mem(a, ix + 1, s.bbox.z | (s.bbox.w << 16));
    write_mem(a, ix + 2, s.tiles.offset);
}

Tile Tile_read(Alloc a, TileRef ref) {
    uint ix = ref.offset >> 2;
    uint raw0 = read_mem(a, ix + 0);
    uint raw1 = read_mem(a, ix + 1);
    Tile s;
    s.tile = TileSegRef(raw0);
    s.backdrop = int(raw1);
    return s;
}

void Tile_write(Alloc a, TileRef ref, Tile s) {
    uint ix = ref.offset >> 2;
    write_mem(a, ix + 0, s.tile.offset);
    write_mem(a, ix + 1, uint(s.backdrop));
}

TileSeg TileSeg_read(Alloc a, TileSegRef ref) {
    uint ix = ref.offset >> 2;
    uint raw0 = read_mem(a, ix + 0);
    uint raw1 = read_mem(a, ix + 1);
    uint raw2 = read_mem(a, ix + 2);
    uint raw3 = read_mem(a, ix + 3);
    uint raw4 = read_mem(a, ix + 4);
    uint raw5 = read_mem(a, ix + 5);
    TileSeg s;
    s.origin = vec2(uintBitsToFloat(raw0), uintBitsToFloat(raw1));
    s.vector = vec2(uintBitsToFloat(raw2), uintBitsToFloat(raw3));
    s.y_edge = uintBitsToFloat(raw4);
    s.next = TileSegRef(raw5);
    return s;
}

void TileSeg_write(Alloc a, TileSegRef ref, TileSeg s) {
    uint ix = ref.offset >> 2;
    write_mem(a, ix + 0, floatBitsToUint(s.origin.x));
    write_mem(a, ix + 1, floatBitsToUint(s.origin.y));
    write_mem(a, ix + 2, floatBitsToUint(s.vector.x));
    write_mem(a, ix + 3, floatBitsToUint(s.vector.y));
    write_mem(a, ix + 4, floatBitsToUint(s.y_edge));
    write_mem(a, ix + 5, s.next.offset);
}

TransformSeg TransformSeg_read(Alloc a, TransformSegRef ref) {
    uint ix = ref.offset >> 2;
    uint raw0 = read_mem(a, ix + 0);
    uint raw1 = read_mem(a, ix + 1);
    uint raw2 = read_mem(a, ix + 2);
    uint raw3 = read_mem(a, ix + 3);
    uint raw4 = read_mem(a, ix + 4);
    uint raw5 = read_mem(a, ix + 5);
    TransformSeg s;
    s.mat = vec4(uintBitsToFloat(raw0), uintBitsToFloat(raw1), uintBitsToFloat(raw2), uintBitsToFloat(raw3));
    s.translate = vec2(uintBitsToFloat(raw4), uintBitsToFloat(raw5));
    return s;
}

void TransformSeg_write(Alloc a, TransformSegRef ref, TransformSeg s) {
    uint ix = ref.offset >> 2;
    write_mem(a, ix + 0, floatBitsToUint(s.mat.x));
    write_mem(a, ix + 1, floatBitsToUint(s.mat.y));
    write_mem(a, ix + 2, floatBitsToUint(s.mat.z));
    write_mem(a, ix + 3, floatBitsToUint(s.mat.w));
    write_mem(a, ix + 4, floatBitsToUint(s.translate.x));
    write_mem(a, ix + 5, floatBitsToUint(s.translate.y));
}
