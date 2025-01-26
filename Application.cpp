//
// Created by Yilin on 4/17/23.
//

#include "Application.h"
#include <iostream>

// 0.7 / 1.3

void Application::run()
{
    const int width = 899;
    const int height = 526;

    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(width, height, 32), "Simon");// , sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    // font
    sf::Font font;
    font.loadFromFile("SourceHanSansCN-Regular.otf");

    sf::Texture background;
    background.loadFromFile("image005.png");

    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(width, height));
    rect.setTexture(&background);

    sf::Texture mouse1;
    mouse1.loadFromFile("image001.png");

    sf::Texture mouse2;
    mouse2.loadFromFile("image003.jpg");
    
    //AnimatedSprite sp(mouse1, 2, 4);
    //AnimationSprite sp(mouse2, 4, 4);
    //sp.setPosition(200.0f, 200.0f);

    std::vector<AnimationSprite> mouses;
    int score = 0;

    // timer
    sf::Clock clock;
    clock.restart();
    float second = 0.0f;

    char buf[256] = { 0 };

    while (window.isOpen()) {
        // generate mouse
        if (second < 30.0f) {
            second = clock.getElapsedTime().asSeconds();
            if (rand() % 1000 < 10) {
                AnimationSprite mouse = AnimationSprite(mouse1, 2, 4);
                mouse.setScale(0.5f, 0.5f);
                auto rect = mouse.getRect();
                mouse.setPosition(
                    sf::Vector2f(
                        rand() % int(width - rect.width),
                        150 + (rand() % int(height - rect.height - 150))
                    )
                );
                mouses.push_back(mouse);
            }
        }

        //event listener
        sf::Event event;
        while (window.pollEvent(event)) {
            if (sf::Event::Closed == event.type) {
                window.close();
            }

            if (second < 30.0f) {
                for (auto& mouse : mouses) {
                    if (!mouse.isClicked()) {
                        mouse.eventHandler(window, event);

                        if (mouse.isClicked()) {
                            mouse.setup(mouse2, 4, 4);// setup to 4x4 image
                            mouse.setFrame(4);// frame start 4
                        }
                    }
                }
            }
        }

        window.clear();
        window.draw(rect);//background
        
        if (second < 30.0f) {
            for (auto itr = mouses.begin(); itr != mouses.end();) {
                itr->update();

                if (itr->getPlayRounds() >= 1) {// Animation playback completed
                    if (itr->isClicked()) {// is clicked, add score
                        ++score;
                    }
                    itr = mouses.erase(itr);
                }
                else {
                    window.draw(*itr);// draw

                    ++itr;
                }
            }

            // text
            snprintf(buf, sizeof(buf), "score: %d time: %0.2f", score, second);
            sf::Text text(buf, font, 32);
            text.setPosition(300, 20);
            text.setColor(sf::Color::Black);
            window.draw(text);
        }
        else {
            // text
            snprintf(buf, sizeof(buf), "score: %d time: %0.2f", score, second);
            sf::Text text(buf, font, 64);
            text.setPosition(200, 200);
            text.setColor(sf::Color::Black);
            window.draw(text);
        }

        window.display();
    }
}