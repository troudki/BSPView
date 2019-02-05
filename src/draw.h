#ifndef DRAW_H
#define DRAW_H

#include <genesis.h>
#include "common.h"

extern u16 ytop[W];
extern u16 ybottom[W];

extern u8 fill;

void clear_clipping_buffers();

void vline(s16 x, s16 y1, s16 y2, u8 col, u8 fill);

void vline_native(u8* buf, s16 cnt, u8 col);


void draw_span(s16 orig_x1, s16 orig_x2, 
               s16 y1a, s16 ny1a, s16 y1b, s16 ny1b, s16 y2a, s16 ny2a, s16 y2b, s16 ny2b, 
               s16 draw_x1, s16 draw_x2, 
               u8 ceil_col, u8 upper_col, u8 wall_col, u8 lower_col, u8 floor_col, u8 update_vertical_clipping);

#endif