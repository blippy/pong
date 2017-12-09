#include <cmath>
#include <unistd.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
//#include <SFML/RectangleShape.hpp>

void sleep_secs(float s)
{
	usleep(s * 1000000);
}
int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    // Load a sprite to display
    
    sf::Texture texture;
    if (!texture.loadFromFile("tux1.png"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);


    sf::RectangleShape bat;
    bat.setSize(sf::Vector2f(10, 100));
    bat.setFillColor(sf::Color::White);
    const float batx = 720;
    float baty = 300-50;
    bat.setPosition(batx, baty);

    /*
    st::Texture bat_texture;
    if(!texture.create(200, 200)) {
	    assert(false);
    }
    */


    // Create a graphical text to display
    
    sf::Font font;
    if (!font.loadFromFile("courier.ttf"))
        return EXIT_FAILURE;
    sf::Text text("Hello SFML", font, 50);


    
    sf::Music music;
    if (!music.openFromFile("spin.wav"))
        return EXIT_FAILURE;
    //music.play();
    

    float scale = 0.1;
    //float dx = scale * (rand() % 20 - 10);
    float dx = scale * -7;
    float dy = scale * (rand() % 20 - 10);

    const float x0 = 650;
    float x=x0, y =300;
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Clear screen
        window.clear();
        // Draw the sprite
	sprite.setPosition(x, y);
        window.draw(sprite);

	//if(window.pollEvent(ev)) {
	const float bat_dy = 1.2;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		baty -= bat_dy;
		if(baty<0) baty = 0;
	} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		baty += bat_dy;      
		if(baty+100 > 600 ) baty = 600-100;
	} 


	bat.setPosition(batx, baty);
	window.draw(bat);

	// Draw the string
	window.draw(text);
	// Update the window
	window.display();

	
	if(x +25 > batx) {
		// out of bounds	
		x = x0;
		dx = - fabs(dx);
		sprite.setPosition(x, y);
		window.draw(sprite);
		window.display();
		sleep_secs(3);
	} else 	if(sprite.getGlobalBounds().intersects(bat.getGlobalBounds()))  {
		dx = -fabs(dx); // ensure it always go to the left
		dx = dx * 1.05; // make it go faster
		x = batx -50;
		music.play(); 
	} else {
		x += dx;
	}

	if(x<0) { x = 0 ; dx = - dx; music.play(); }
	if(x +50 > 800) { x = 800 -50 ; dx = - dx; music.play();}

	y += dy;
	if(y<0) { y = 0 ; dy = - dy; music.play(); }
	if(y +59 > 600) { y = 600 -59 ; dy = - dy; music.play();}
	//sleep_secs(0.01);

    }
    return EXIT_SUCCESS;
}

