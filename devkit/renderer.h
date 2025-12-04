#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include "combate.h"
typedef struct {
  ALLEGRO_DISPLAY* display;
  ALLEGRO_BITMAP* display_buffer;

  ALLEGRO_FONT* font;
  ALLEGRO_BITMAP* energy_icon;
} Renderer;

void FillRenderer(Renderer* renderer);

void Render(Renderer* renderer, Combate *combate);

void ClearRenderer(Renderer* renderer);

#endif