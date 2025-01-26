#ifndef AnimationSpriteH
#define AnimationSpriteH

#include <SFML/Graphics.hpp>

#include <iostream>
#include <cmath>

class AnimationSprite : public sf::Sprite
{
private:
    int width, height;
    int rows, cols;
    
    int time = 250;
    int frame;
    int playRounds = 0;
    
    sf::Clock clock;
    sf::IntRect intRect;

    bool clicked = false;

public:
    AnimationSprite();
    AnimationSprite(sf::Texture &texture, int rows, int cols);

    void setup(sf::Texture &texture, int rows, int cols);

    // get bounding rect
    sf::FloatRect getRect()const;

    int getTime() const;
    void setTime(int time);

    int getFrame()const;
    void setFrame(int frame);

    void resetPlayRounds();
    int getPlayRounds()const;

    void eventHandler(sf::RenderWindow &window, sf::Event event);
    bool isClicked()const;

    void animate();
    void update();

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    void setupIntRect(sf::Vector2u imgSize, int rows, int cols);
};

#endif // AnimationSpriteH
