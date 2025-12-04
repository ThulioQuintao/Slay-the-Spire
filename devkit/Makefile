clean:
	rm *.out

game:
	gcc \
		main.c cartas.c combate.c inimigo_setup.c jogador_setup.c renderer.c utils.c entidade.c\
		-o game.out \
		-lm -g \
		`pkg-config allegro-5 allegro_main-5 \
		allegro_font-5 allegro_image-5 allegro_primitives-5 \
		--libs --cflags`


game-win:
	gcc main.c -o game.out \
		utils.c \
		renderer.c \
		-lm -g\
		$(shell pkg-config allegro-5 allegro_main-5 \
		allegro_font-5 \
		allegro_image-5 allegro_primitives-5 \
		 --libs --cflags)