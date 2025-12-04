#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#define GAME_KEY_SEEN 1
#define GAME_KEY_DOWN 2

#define DISPLAY_BUFFER_WIDTH 1920.0
#define DISPLAY_BUFFER_HEIGHT 1080.0

#define DISPLAY_SCALE 1.0
#define DISPLAY_WIDTH DISPLAY_SCALE* DISPLAY_BUFFER_WIDTH
#define DISPLAY_HEIGHT DISPLAY_SCALE* DISPLAY_BUFFER_HEIGHT

#define DRAW_DECK_DESCARTE_X 30
#define DRAW_DECK_DESCARTE_Y 820

#define DRAW_DECK_COMPRA_X 30
#define DRAW_DECK_COMPRA_Y 940

#define DECK_WIDTH 80
#define DECK_HEIGHT 80

//Numeração da vez de cada entidade
#define TURN_PLAYER   0
#define TURN_ENEMIES  1

#define PLAYER_BEGIN_X 500
#define PLAYER_BEGIN_Y 400
#define PLAYER_RADIUS 100

#define ENEMY_SPACING 300
#define ENEMY_RADIUS 105
#define ENEMY_Y 400

#define HEALTH_BAR_HEIGHT 20
#define HEALTH_BAR_BACKGROUND_EXTRA 1

#define HEALTH_BAR_RX 0
#define HEALTH_BAR_RY 0

#define HAND_BEGIN_X 325
#define HAND_BEGIN_Y 780

#define CARD_WIDTH 280
#define CARD_HEIGHT 420

// ======== CORES DE CARTAS ========

// ATAQUE → vermelho claro
#define CARD_COLOR_ATTACK        al_map_rgb(255, 120, 120)
#define CARD_BORDER_ATTACK       al_map_rgb(170, 30, 30)

// DEFESA → azul claro
#define CARD_COLOR_DEFENSE       al_map_rgb(130, 180, 255)
#define CARD_BORDER_DEFENSE      al_map_rgb(20, 60, 140)

// ESPECIAL → amarelo claro
#define CARD_COLOR_SPECIAL       al_map_rgb(255, 240, 120)
#define CARD_BORDER_SPECIAL      al_map_rgb(200, 170, 40)



// ======== CORES DO TEXTO ========
#define TEXT_COLOR_BLACK         al_map_rgb(20, 20, 20)
#define TEXT_COLOR_WHITE         al_map_rgb(255, 255, 255)



// ======== CORES DO JOGADOR ========

// Vida do jogador
#define PLAYER_LIFE_BAR_BG       al_map_rgb(230, 230, 230)
#define PLAYER_LIFE_BAR_FILL     al_map_rgb(80, 200, 80)

// Escudo do jogador
#define PLAYER_SHIELD_BAR_BG     al_map_rgb(200, 200, 200)
#define PLAYER_SHIELD_BAR_FILL   al_map_rgb(150, 220, 255)

// Corpo (círculo do jogador)
#define PLAYER_BODY_COLOR        al_map_rgb(255, 220, 120)
#define PLAYER_BODY_BORDER       al_map_rgb(180, 140, 40)




// ======== CORES DOS INIMIGOS ========

// Corpo e borda
#define ENEMY_COLOR_BODY         al_map_rgb(230, 90, 90)
#define ENEMY_COLOR_BORDER       al_map_rgb(160, 20, 20)

// Ciclo de ação dos inimigos
#define CICLO_COLOR_ATTACK      al_map_rgb(255, 70, 70)
#define CICLO_COLOR_DEFENSE     al_map_rgb(70, 160, 255)


// ======== CORES DE FUNDO E UI ========

// Fundo da tela
#define BACKGROUND_COLOR         al_map_rgb(0, 0, 0)

// Deck (retângulo no canto)
#define DECK_BG_COLOR            al_map_rgb(255, 255, 255)
#define DECK_BORDER_COLOR        al_map_rgb(200, 200, 200)

// Área por trás das cartas
#define CARD_AREA_BG             al_map_rgb(240, 240, 240)

// Barra de vida
#define LIFE_BAR_FILL      al_map_rgb(60, 255, 60)
#define LIFE_BAR_BG        al_map_rgb(120, 120, 120)
// Barra de escudo
#define SHIELD_BAR_BG      al_map_rgb(120, 120, 120)
#define SHIELD_BAR_FILL    al_map_rgb(130, 180, 255)



typedef enum {
  MOVE_LEFT = 0,
  MOVE_RIGHT = 1,
} CursorMovementDirection;

#endif