pong : pong.cc
	g++ $< -o $@ -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system
