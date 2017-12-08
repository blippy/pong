pong : pong.cc
	g++ $< -o $@ -lsfml-graphics -lsfml-window -lsfml-system
