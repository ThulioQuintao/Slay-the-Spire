#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

int main() {
    al_init();
    al_install_keyboard();
    al_init_primitives_addon();

    ALLEGRO_DISPLAY *display = al_create_display(800, 600);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_EVENT event;
    bool running = true;
    float x = 400, y = 300;

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_keyboard_event_source());

    while (running) {
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            running = false;
        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_UP: y -= 10; break;
                case ALLEGRO_KEY_DOWN: y += 10; break;
                case ALLEGRO_KEY_LEFT: x -= 10; break;
                case ALLEGRO_KEY_RIGHT: x += 10; break;
                case ALLEGRO_KEY_ESCAPE: running = false; break;
            }
        }

        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_filled_circle(x, y, 30, al_map_rgb(255, 0, 0));
        al_flip_display();
    }

    al_destroy_event_queue(queue);
    al_destroy_display(display);
    return 0;
}
