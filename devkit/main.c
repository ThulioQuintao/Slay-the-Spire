#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "constants.h"
#include "renderer.h"
#include "utils.h"
#include "inimigo.h"
#include "jogador.h"
#include "combate.h"

int main() {
  srand(time(NULL));

  must_init(al_init(), "allegro");
  must_init(al_init_image_addon(), "allegro");
  must_init(al_init_primitives_addon(), "primitives");
  must_init(al_install_keyboard(), "keyboard");

  ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
  must_init(timer, "timer");

  ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
  must_init(queue, "queue");

  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_timer_event_source(timer));
  unsigned char keyboard_keys[ALLEGRO_KEY_MAX];
  ClearKeyboardKeys(keyboard_keys);
  ALLEGRO_EVENT event;

  Renderer renderer;
  FillRenderer(&renderer);
  al_register_event_source(queue,
                           al_get_display_event_source(renderer.display));
  
  //Iniciar Combate
  Combate combate;
  startGame(&combate);
  al_start_timer(timer);

  while (1) {
    al_wait_for_event(queue, &event);
    int done = 0, print_combat = 0, redraw = 0.;

    switch (event.type) {
      
      case ALLEGRO_EVENT_TIMER:
        redraw = 1;

        //Controle da tecla Q (sai do jogo)
        if (keyboard_keys[ALLEGRO_KEY_Q]) {
          done = 1;
          break;
        }
        
        //Controle da seta esquerda (seleção)
        if (keyboard_keys[ALLEGRO_KEY_LEFT] & GAME_KEY_SEEN) {
          ProcessSetaEsquerda(&combate);
        }

        // Controle da seta direita (seleção)
        if (keyboard_keys[ALLEGRO_KEY_RIGHT] & GAME_KEY_SEEN) {
          ProcessSetaDireita(&combate);
        }
        
        //Controle da tecla Enter (Confirma ação/seleção)
        if (keyboard_keys[ALLEGRO_KEY_ENTER] & GAME_KEY_SEEN) {
          ProcessEnter(&combate);
        }

        //Controle da tecla Space (zera vida dos inimigos)
        if (keyboard_keys[ALLEGRO_KEY_SPACE] & GAME_KEY_SEEN) {
          killAllEnemies(&combate);
        }

        //Controle da tecla x (Player fica com 1 de vida)
        if (keyboard_keys[ALLEGRO_KEY_X] & GAME_KEY_SEEN) {
            combate.player.base.life = 1;
        }

        // Controle da tecla Esc (Pula para o turno do ininmigo)
        if (keyboard_keys[ALLEGRO_KEY_ESCAPE] & GAME_KEY_SEEN) {
            ProcessEsc(&combate);
        }

        for (int i = 0; i < ALLEGRO_KEY_MAX; i++) {
          keyboard_keys[i] &= ~GAME_KEY_SEEN;
        }
        break;
      
      case ALLEGRO_EVENT_KEY_DOWN:
        keyboard_keys[event.keyboard.keycode] = GAME_KEY_SEEN | GAME_KEY_DOWN;
        break;
      case ALLEGRO_EVENT_KEY_UP:
        keyboard_keys[event.keyboard.keycode] &= ~GAME_KEY_DOWN;
        break;
      case ALLEGRO_EVENT_DISPLAY_CLOSE:
        done = true;
        break;
      
    }

    // Se a vida do player chegar a 0
    if (combate.player.base.life <= 0) {
        printf("\n=== GAME OVER ===\n");
        printf("Você morreu!\n");
        break;     
    }

    // Se a quantidade de batalhar chegar a 10
    if(combate.qtdBatalhas == 10) {
      printf("Você escalou a torre!");
      break;
    }

    if (done) {
      break;
    }    
    
    if (redraw) {
      Render(&renderer, &combate);
      redraw = 0;
    }
  }
  al_destroy_timer(timer);
  al_destroy_event_queue(queue);
  ClearRenderer(&renderer);
  return 0;
}