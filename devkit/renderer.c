#include "renderer.h"

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "utils.h"

void DrawScaledText(ALLEGRO_FONT* font, ALLEGRO_COLOR color, float x, float y,
                    float xscale, float yscale, int alignment,
                    const char* text) {
  ALLEGRO_TRANSFORM transform;
  al_identity_transform(&transform);  // Start with an identity transform
  al_scale_transform(
      &transform, xscale,
      yscale);  // Apply scaling (e.g., sx=2.0, sy=2.0 for double size)
  al_use_transform(&transform);  // Use the transform for subsequent drawing

  al_draw_text(font, color, x, y, alignment, text);
  // al_draw_text(font, color, x, y, alignment, text);
  al_identity_transform(&transform);
  al_use_transform(&transform);  // Use the transform for subsequent drawing
}

void DrawCenteredScaledText(ALLEGRO_FONT* font, ALLEGRO_COLOR color, float x,
                            float y, float xscale, float yscale, char* text) {
  DrawScaledText(font, color, x, y, xscale, yscale, ALLEGRO_ALIGN_CENTRE, text);
}

void FillRenderer(Renderer* renderer) {
  al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
  al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
  al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

  renderer->display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
  must_init(renderer->display, "display");

  renderer->display_buffer =
      al_create_bitmap(DISPLAY_BUFFER_WIDTH, DISPLAY_BUFFER_HEIGHT);
  must_init(renderer->display_buffer, "display buffer");

  renderer->font = al_create_builtin_font();
  must_init(renderer->font, "font");

  renderer->energy_icon = al_load_bitmap("assets/energy.png");
  must_init(renderer->energy_icon, "energy icon");

}

void RenderBackground(Renderer* renderer) {
  al_clear_to_color(al_map_rgb(0, 0, 0));
}

void RenderDeckCompra(Renderer* renderer, Combate* combate)
{
    Player* p = &combate->player;

    int x = DRAW_DECK_COMPRA_X;
    int y = DRAW_DECK_COMPRA_Y;

    // fundo
    al_draw_filled_rounded_rectangle(
        x, y,
        x + DECK_WIDTH, y + DECK_HEIGHT,
        8, 8, DECK_BG_COLOR
    );

    // borda
    al_draw_rounded_rectangle(
        x, y,
        x + DECK_WIDTH, y + DECK_HEIGHT,
        8, 8, DECK_BORDER_COLOR, 4
    );

    // texto central: QUANTIDADE
    char txt[32];
    sprintf(txt, "%d", p->baralhoCompra.quantity);

    al_draw_text(renderer->font, TEXT_COLOR_BLACK,
                 x + DECK_WIDTH / 2,
                 y + DECK_HEIGHT / 2 - 10,
                 ALLEGRO_ALIGN_CENTER,
                 txt);

    // texto “COMPRA” embaixo
    al_draw_text(renderer->font, TEXT_COLOR_WHITE,
                 x + DECK_WIDTH / 2,
                 y + DECK_HEIGHT + 12,
                 ALLEGRO_ALIGN_CENTER,
                 "Compra");
}

void RenderDeckDescarte(Renderer* renderer, Combate* combate)
{
    Player* p = &combate->player;

    int x = DRAW_DECK_DESCARTE_X;
    int y = DRAW_DECK_DESCARTE_Y;

    // fundo
    al_draw_filled_rounded_rectangle(
        x, y,
        x + DECK_WIDTH, y + DECK_HEIGHT,
        8, 8, DECK_BG_COLOR
    );

    // borda
    al_draw_rounded_rectangle(
        x, y,
        x + DECK_WIDTH, y + DECK_HEIGHT,
        8, 8, DECK_BORDER_COLOR, 4
    );

    // texto central: QUANTIDADE
    char txt[32];
    sprintf(txt, "%d", p->baralhoDescarte.quantity);

    al_draw_text(renderer->font, TEXT_COLOR_BLACK,
                 x + DECK_WIDTH / 2,
                 y + DECK_HEIGHT / 2 - 10,
                 ALLEGRO_ALIGN_CENTER,
                 txt);

    // texto “DESCARTE” embaixo
    al_draw_text(renderer->font, TEXT_COLOR_WHITE,
                 x + DECK_WIDTH / 2,
                 y + DECK_HEIGHT + 12,
                 ALLEGRO_ALIGN_CENTER,
                 "Descarte");
}


void RenderStatusBars(ALLEGRO_FONT* font,
                      float x_begin, float x_end, float y_start,
                      int life, int maxLife,
                      int shield)
{
    float width = x_end - x_begin;

    /* ==============================
       BARRA DE VIDA
       ============================== */

    float lifeRatio = (float)life / (float)maxLife;
    if (lifeRatio < 0) lifeRatio = 0;
    if (lifeRatio > 1) lifeRatio = 1;

    float lifeWidth = width * lifeRatio;
    float lifeHeight = 30;

    // fundo
    al_draw_filled_rectangle(
        x_begin, y_start,
        x_end, y_start + lifeHeight,
        LIFE_BAR_BG
    );

    // preenchimento
    al_draw_filled_rectangle(
        x_begin, y_start,
        x_begin + lifeWidth, y_start + lifeHeight,
        LIFE_BAR_FILL
    );

    // texto "X / Max"
    char txtLife[32];
    sprintf(txtLife, "%d / %d", life, maxLife);

    al_draw_text(font, TEXT_COLOR_BLACK,
                 (x_begin + x_end) / 2,
                 y_start + 11,
                 ALLEGRO_ALIGN_CENTER,
                 txtLife);

    /* ==============================
       BARRA DE ESCUDO
       ============================== */

    if (shield > 0)
    {
        float shieldRatio = (float)shield;
        if (shieldRatio < 0) shieldRatio = 0;
        if (shieldRatio > 1) shieldRatio = 1;

        float shieldWidth = width * shieldRatio;
        float shieldHeight = 25;
        float sy = y_start + lifeHeight + 10; // 10 px de espaçamento

        // fundo
        al_draw_filled_rectangle(
            x_begin, sy,
            x_end, sy + shieldHeight,
            SHIELD_BAR_BG
        );

        // preenchimento
        al_draw_filled_rectangle(
            x_begin, sy,
            x_begin + shieldWidth, sy + shieldHeight,
            SHIELD_BAR_FILL
        );

        // texto
        char txtShield[32];
        sprintf(txtShield, "%d", shield);

        al_draw_text(font, TEXT_COLOR_BLACK,
                     (x_begin + x_end) / 2,
                     sy + 8,
                     ALLEGRO_ALIGN_CENTER,
                     txtShield);
    }
}


void RenderPlayer(const Renderer* renderer, Player* player, int begin_x, int mid_y, int radius){
    float centerX = begin_x;
    float centerY = mid_y;

    al_draw_filled_circle(centerX, centerY, radius, PLAYER_BODY_COLOR);
    al_draw_circle(centerX, centerY, radius, PLAYER_BODY_BORDER, 10);

    float x_begin = centerX - radius;
    float x_end   = centerX + radius;
    float y_start = centerY + radius + 20;

    RenderStatusBars(renderer->font,
                     x_begin, x_end, y_start,
                     player->base.life, player->base.maxLife,
                     player->base.shield);
}

void RenderCard(Renderer* renderer, Carta *carta, int x, int y) {
    ALLEGRO_BITMAP* bmp = al_create_bitmap(CARD_WIDTH, CARD_HEIGHT);
    al_set_target_bitmap(bmp);

    ALLEGRO_COLOR bg;
    ALLEGRO_COLOR border;

    if(carta->type == 'A') {
      bg = CARD_COLOR_ATTACK;
      border = CARD_BORDER_ATTACK;
    } else if (carta->type == 'D') {
      bg =CARD_COLOR_DEFENSE;
      border = CARD_BORDER_DEFENSE;
    } else {
      bg = CARD_COLOR_SPECIAL;  
      border = CARD_BORDER_SPECIAL; 
    }

    // fundo
    al_draw_filled_rounded_rectangle(0, 0, CARD_WIDTH, CARD_HEIGHT,5, 5, bg); //preenchimento
    al_draw_rounded_rectangle(0, 0, CARD_WIDTH, CARD_HEIGHT,5,5, border, 16); // borda

    //texto das cartas
    ALLEGRO_COLOR color = al_map_rgb(0,0,0);
    char texto[32];

    sprintf(texto, "Tipo: %c", carta->type);
    DrawScaledText(renderer->font, color, 10, 10, 2, 2, ALLEGRO_ALIGN_LEFT, texto);

    sprintf(texto, "Custo: %d", carta->custo);
    DrawScaledText(renderer->font, color, 10, 40, 2, 2, ALLEGRO_ALIGN_LEFT, texto);

    sprintf(texto, "Efeito: %d", carta->effect);
    DrawScaledText(renderer->font, color, 10, 70, 2, 2, ALLEGRO_ALIGN_LEFT, texto);

    // volta para o buffer principal
    al_set_target_bitmap(renderer->display_buffer);
    al_draw_bitmap(bmp, x, y, 0);

    al_destroy_bitmap(bmp);
}

void RenderPlayerHand(Renderer* renderer, Combate *combate) {
    Player *p = &combate->player;

    int qtdCartasMao = p->qtdMaoCartas;
    int spacing = 20;

    int total_width = qtdCartasMao * CARD_WIDTH + (qtdCartasMao - 1) * spacing;
    int x_start = (DISPLAY_BUFFER_WIDTH - total_width) / 2;
    int y = DISPLAY_BUFFER_HEIGHT - CARD_HEIGHT;

    for (int i = 0; i < qtdCartasMao; i++) {
        int x = x_start + i * (CARD_WIDTH + spacing);

        int y_offset = (i == p->selectedCarta) ? -20 : 0;

        RenderCard(renderer, &p->mao[i], x, y + y_offset);
    }
}

void RenderEnemies(Renderer* renderer, Combate *combate) {
    int count = combate->qtdInimigos;

    for (int i = 0; i < count; i++) {

        Inimigo *inimigo = &combate->inimigos[i];

        /*if (inimigo->base.life <= 0) continue; */

        int x = DISPLAY_BUFFER_WIDTH - 200 - (count - 1 - i) * ENEMY_SPACING;
        int y = ENEMY_Y;

        // Instancia o corpo e borda do ininimigo por constantes--
        ALLEGRO_COLOR body = ENEMY_COLOR_BODY;
        ALLEGRO_COLOR border = ENEMY_COLOR_BORDER;

        // corpo do inimigo
        al_draw_filled_circle(x, y, ENEMY_RADIUS, body);

        // borda do inimigo
        al_draw_circle(x, y, ENEMY_RADIUS, border, 10);

       //Texto para inimigo fraco ou forte
        const char *label;

        if (inimigo->type == 'f') {
            label = "FRACO";
        } else if (inimigo->type == 'F') {
            label = "FORTE";
        } 

        al_draw_text(
            renderer->font, //fonte usada
            al_map_rgb(0,0,0), //cor texto
            x, //Posição X onde o texto será desenhado
            y - 10, //Posição Y
            ALLEGRO_ALIGN_CENTER, //alinhamento (LEFT, CENTER, RIGHT)
            label //texto a ser impresso
        );

        //Destacando ininimigo selecionado com borda amarela
        if (i == combate->player.selectedEnemy &&
            combate->player.selectedMode == 1) {

            ALLEGRO_COLOR sel = al_map_rgb(255, 255, 0);
            float s = ENEMY_RADIUS + 12;

            // sempre círculo agora
            al_draw_circle(x, y, s, sel, 6);
        }

        // Criar quadrado que representa proxima ação inimigo
        Acao *proxima = &inimigo->cicloJogada[inimigo->indiceAcaoAtual];

        ALLEGRO_COLOR cicloColor =
            (proxima->type == 'A')
            ? CICLO_COLOR_ATTACK
            : CICLO_COLOR_DEFENSE;

        al_draw_filled_rectangle(
            x - 30, y - ENEMY_RADIUS - 60,
            x + 30, y - ENEMY_RADIUS - 10,
            cicloColor
        );

        char intentTxt[16];
        sprintf(intentTxt, "%d", proxima->effect);

        al_draw_text(
            renderer->font,
            al_map_rgb(0,0,0),
            x,
            y - ENEMY_RADIUS - 48,
            ALLEGRO_ALIGN_CENTER,
            intentTxt
        );

        // Inicializa a barra de vida e escudo dos inimigos pela função
        RenderStatusBars(renderer->font,
              x - ENEMY_RADIUS, x + ENEMY_RADIUS,
              y + ENEMY_RADIUS + 20,
              inimigo->base.life, inimigo->base.maxLife, inimigo->base.shield);
    }
}



void RenderEnergy(Renderer* renderer, Combate *combate) {
    Player *player = &combate->player;

    int x = 0;
    int y = DISPLAY_BUFFER_HEIGHT - 1070;
    int xBaseImage = x + 220, xEspaçamento = 0, yBaseImage = y + 20 ;

    // Inserindo imagens de energia de acordo com o que o player tem
    for(int i = 0; i < player->energy; i++) {
      al_draw_scaled_bitmap(
        renderer->energy_icon,
        0, 0,                            
        al_get_bitmap_width(renderer->energy_icon),
        al_get_bitmap_height(renderer->energy_icon),
        xBaseImage + xEspaçamento, yBaseImage,                            
        90, 90,                          
        0
      );
      xEspaçamento += 70;
    }
    
    char txt[25];
    sprintf(txt, "Energia: ");
    
    DrawScaledText(renderer->font, TEXT_COLOR_WHITE,
                   x + 10, y + 10, 3, 3,
                   ALLEGRO_ALIGN_LEFT, txt);
}

void RenderTurno(Renderer *renderer, Combate *combate)
{
    char txt[32];
    sprintf(txt, "Turno: %d", combate->qtdBatalhas);

    al_draw_text(
        renderer->font,
        al_map_rgb(255, 255, 255),             
        DISPLAY_BUFFER_WIDTH / 2, // centro do eixo x
        20, // topo da tela
        ALLEGRO_ALIGN_CENTER,
        txt
    );
}


void Render(Renderer* renderer, Combate *combate) {
  al_set_target_bitmap(renderer->display_buffer);
  RenderBackground(renderer);
  RenderTurno(renderer, combate); //renderiza o número do turno atual
  RenderPlayer(renderer, &combate->player, PLAYER_BEGIN_X, PLAYER_BEGIN_Y, PLAYER_RADIUS); // renderiza o player
  RenderEnergy(renderer, combate); // renderiza energia
  RenderEnemies(renderer, combate); // renderiza inimigos
  RenderPlayerHand(renderer, combate); // renderiza as cartas da mão do player
  RenderDeckDescarte(renderer, combate); // renderiza o icone de descarte
  RenderDeckCompra(renderer, combate); // renderiza o icone de compra

  al_set_target_backbuffer(renderer->display);
  

  al_draw_scaled_bitmap(renderer->display_buffer, 0, 0, DISPLAY_BUFFER_WIDTH,
                        DISPLAY_BUFFER_HEIGHT, 0, 0, DISPLAY_WIDTH,
                        DISPLAY_HEIGHT, 0);

  al_flip_display();
}

void ClearRenderer(Renderer* renderer) {
  al_destroy_display(renderer->display);
  al_destroy_bitmap(renderer->display_buffer);
  al_destroy_font(renderer->font);
}