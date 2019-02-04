#include <genesis.h>

#include "player.h"
#include "common.h"
#include "sector.h"
#include "palette.h"
#include "span_buf.h"
#include "draw.h"

#include "map.h"





void print_pos() {
  char buf[32];
  sprintf(buf, "x: ");
  fix32ToStr(ply.where.x, buf+3, 3);
  VDP_drawTextBG(PLAN_A, buf, 0, 12);
  sprintf(buf, "y: ");
  fix32ToStr(ply.where.y, buf+3, 3);
  VDP_drawTextBG(PLAN_A, buf, 0, 13);
  sprintf(buf, "z: ");
  fix32ToStr(ply.where.z, buf+3, 3);
  VDP_drawTextBG(PLAN_A, buf, 0, 14);
  sprintf(buf, "ang: ");
  fix16ToStr(ply.angle, buf+5, 1);
  VDP_drawTextBG(PLAN_A, buf, 0, 15);
  sprintf(buf, "sect: %u", ply.cur_sector->sectnum);
  VDP_drawTextBG(PLAN_A, buf, 0, 16);
}

void clear_pos() {
  for(int i = 12; i <= 16; i++){
    VDP_clearTextLineBG(PLAN_A, i);
  }
}

void print_fps() {
  char buf[32];
  fix32ToStr(getFPS_f(), buf, 1);
  VDP_drawTextBG(PLAN_A, buf, 0, 4);
}

void clear_fps() {
  VDP_clearTextLineBG(PLAN_A, 4);
}

int main() {

  
  BMP_init(0, PLAN_B, 3, 0);
  
  BMP_setBufferCopy(0);

  loadPalette(3);

  int show_fps = 0;
  int show_pos = 0;
  

  fix16 angle_speed = FIX16(16);
  fix32 move_speed = FIX32(1);

  ply.anglecos = fix16ToFix32(cosFix16(fix16ToInt(ply.angle)));
  ply.anglesin = fix16ToFix32(sinFix16(fix16ToInt(ply.angle)));
  u16 last_joy = 0;
  
  ply.cur_sector = find_player_sector(&root_node);
  ply.where.z = ply.cur_sector->floor_height + eye_height;

  int menu = 1;
  while(menu) {
    VDP_drawTextBG(PLAN_A, "BSP Renderer v0.11", 10, 8);
    VDP_drawTextBG(PLAN_A, "use d-pad to move ", 0, 12);
    VDP_drawTextBG(PLAN_A, "x/a - adjusts camera y-position", 0, 13);
    VDP_drawTextBG(PLAN_A, "y + up/dn - adjusts sector ceiling height", 0, 14);
    VDP_drawTextBG(PLAN_A, "b + up/dn - adjusts sector floor height", 0, 15);
    VDP_drawTextBG(PLAN_A, "z/c - toggles fps display / debug info", 0, 16);
    VDP_drawTextBG(PLAN_A, "mode - toggles wireframe mode", 0, 17);
    VDP_drawTextBG(PLAN_A, "--- press start ---", 10, 19);
    u16 joy = JOY_readJoypad(0);
    if(joy & BUTTON_START) {
      menu = 0;
    }
  }
  for(int i = 8; i <= 26; i++) {
    VDP_clearTextLineBG(PLAN_A, i);
  }

  while(1)
    {     
      u16 joy = JOY_readJoypad(0);
      if(joy & BUTTON_Z && !(last_joy & BUTTON_Z)) {
	      show_fps = show_fps ? 0 : 1;
        if(!show_fps) { clear_fps(); }
      }
      if(joy & BUTTON_C && !(last_joy & BUTTON_C)) {
        show_pos = show_pos ? 0 : 1;
        if(!show_pos) { clear_pos(); }
      }
		
      if(joy & BUTTON_MODE && !(last_joy & BUTTON_MODE)) {
        fill = !fill;
      }

      last_joy = joy;
      if((joy & BUTTON_Y || joy & BUTTON_B) && (joy & BUTTON_UP || joy & BUTTON_DOWN)) {
        //sector* sect = find_player_sector(&root_node);
        sector* sect = ply.cur_sector;
        fix32 inc = (joy & BUTTON_DOWN) ? fix32Neg(FIX32(0.5)) : FIX32(0.5);
        if(joy & BUTTON_Y) {
          sect->ceil_height += inc;
        }
        if(joy & BUTTON_B) {
          sect->floor_height += inc;
        }
        ply.where.z = ply.cur_sector->floor_height + eye_height;
      } else {

        if(joy & BUTTON_UP || joy & BUTTON_DOWN) {
          fix32 oldx = ply.where.x;
          fix32 oldy = ply.where.y;
          fix32 curx = oldx;
          fix32 cury = oldy;

          fix32 speed = (joy & BUTTON_UP) ? move_speed : fix32Neg(move_speed);
          int moved = 0;

          fix32 newx = curx + fix32Mul(speed, ply.anglecos);
          int got_x_collision = 0;


          for(int i = 0; i < ply.cur_sector->num_walls; i++) {
            wall* w = ply.cur_sector->walls[i];
            fix32 oldside = PointSide32(curx, cury, w->v1.x, w->v1.y, w->v2.x, w->v2.y);
            fix32 newside = PointSide32(newx, cury, w->v1.x, w->v1.y, w->v2.x, w->v2.y);
            int signold = (oldside < 0 ? -1 : oldside == 0 ? 0 : 1);
            int signnew = (newside < 0 ? -1 : oldside == 0 ? 0 : 1);
            if(signold != signnew && w->back_sector == NULL) {
              got_x_collision = 1;
              break;
            }
          }

          if(!got_x_collision) {
              moved = 1;
              curx = newx;
          }

          fix32 newy = cury + fix32Mul(speed, ply.anglesin);
          int got_y_collision = 0;

          for(int i = 0; i < ply.cur_sector->num_walls; i++) {
            wall* w = ply.cur_sector->walls[i];
            fix32 oldside = PointSide32(curx, cury, w->v1.x, w->v1.y, w->v2.x, w->v2.y);
            fix32 newside = PointSide32(curx, newy, w->v1.x, w->v1.y, w->v2.x, w->v2.y);
            int signold = (oldside < 0 ? -1 : oldside == 0 ? 0 : 1);
            int signnew = (newside < 0 ? -1 : oldside == 0 ? 0 : 1);
            if(signold != signnew && w->back_sector == NULL) {
                got_y_collision = 1;
                break;
            }
          }
          if(!got_y_collision) {
            moved = 1;
            cury = newy;
          }

          ply.where.x = curx;
          ply.where.y = cury;

          if(moved) {
            // if we've moved, check for new sector
            ply.cur_sector = find_player_sector(&root_node);
            ply.where.z = ply.cur_sector->floor_height + eye_height;
          }
        }
        
      }

      if(joy & BUTTON_LEFT) {
	      ply.angle -= angle_speed;
	      ply.angle = ply.angle & FIX16(1023);
        ply.anglecos = fix16ToFix32(cosFix16(fix16ToInt(ply.angle)));
        ply.anglesin = fix16ToFix32(sinFix16(fix16ToInt(ply.angle)));
      } else if(joy & BUTTON_RIGHT) {
	      ply.angle += angle_speed;
	      ply.angle = ply.angle & FIX16(1023);
        ply.anglecos = fix16ToFix32(cosFix16(fix16ToInt(ply.angle)));
        ply.anglesin = fix16ToFix32(sinFix16(fix16ToInt(ply.angle)));
      }

      if(joy & BUTTON_X) {
        ply.where.z += FIX32(0.5);
      } else if (joy & BUTTON_A) {
        ply.where.z -= FIX32(0.5);
      }



      reset_span_buffer();
      clear_clipping_buffers();

      BMP_waitWhileFlipRequestPending();
      BMP_clear();

      draw_bsp_node(&root_node);

		
      BMP_flip(1);

      VDP_waitVSync();
      if(show_fps) {
        print_fps();
      }
      if(show_pos) {
        print_pos();
      }
      
		
    }
  return (0);
}
