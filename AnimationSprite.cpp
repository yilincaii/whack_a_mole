#include "AnimationSprite.h"

AnimationSprite::AnimationSprite()
{

}

AnimationSprite::AnimationSprite(sf::Texture &texture, int rows, int cols)
{
    setup(texture, rows, cols);
}

void AnimationSprite::setup(sf::Texture &texture, int rows, int cols)
{
    this->width = texture.getSize().x;
    this->height = texture.getSize().y;
    this->rows = rows;
    this->cols = cols;
    this->frame = 0;
    this->playRounds = 0;

    setTexture(texture);
    setupIntRect(texture.getSize(), rows, cols);
}

void AnimationSprite::setupIntRect(sf::Vector2u imgSize, int rows, int cols)
{
    intRect.width = std::round(width / static_cast<float>(cols));
    intRect.height = std::round(height / static_cast<float>(rows));
    intRect.left = 0;
    intRect.top = 0;
    setTextureRect(intRect);
}

// get bounding rect
sf::FloatRect AnimationSprite::getRect()const
{
    sf::Vector2f size = sf::Vector2f(intRect.width, intRect.height);
    sf::Vector2f scale = this->getScale();
    size.x *= scale.x;
    size.y *= scale.y;
    return sf::FloatRect(this->getPosition(), size);
}

int AnimationSprite::getTime() const
{
    return time;
}

void AnimationSprite::setTime(int time)
{
    this->time = time;
}

int AnimationSprite::getFrame()const
{
    return frame;
}

void AnimationSprite::setFrame(int frame)
{
    this->frame = frame;

    int x = frame % this->cols;
    int y = frame / this->cols;

    intRect.left = x * intRect.width;
    intRect.top = y * intRect.height;
    setTextureRect(intRect);
}

void AnimationSprite::resetPlayRounds()
{
    this->playRounds = 0;
}

int AnimationSprite::getPlayRounds()const
{
    return playRounds;
}

void AnimationSprite::eventHandler(sf::RenderWindow &window, sf::Event event)
{
    // check mouse click
    if (!clicked) {
        sf::FloatRect rect = this->getRect();
        switch (event.type) {
        case sf::Event::MouseButtonPressed:
            if (rect.contains(event.mouseButton.x, event.mouseButton.y)) {
                clicked = true;
            }
            break;
        }
    }
}

bool AnimationSprite::isClicked()const
{
    return clicked;
}

void AnimationSprite::animate()
{
    if (clock.getElapsedTime().asMilliseconds() > time) {
        int i = frame + 1;
        if (i >= this->rows * this->cols) {
            ++playRounds;

            i = 0;
        }
        this->setFrame(i);
        clock.restart();
    }
}

void AnimationSprite::update()
{
    animate();
}

void AnimationSprite::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::Sprite s = (*this);
    target.draw(s);

    sf::RectangleShape shape;
    sf::FloatRect rect = this->getRect();
    shape.setFillColor(sf::Color::Transparent);
    if (clicked) {
        shape.setOutlineColor(sf::Color::Red);
    }
    else {
        shape.setOutlineColor(sf::Color::Blue);
    }
    shape.setOutlineThickness(2.0f);
    shape.setPosition(rect.left, rect.top);
    shape.setSize(sf::Vector2f(rect.width, rect.height));
    target.draw(shape);
}
