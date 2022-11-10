#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "BinaryTree.h"

void createShapes(BinaryTree& t, std::vector<sf::CircleShape>& circles, std::vector<sf::Text>& strings, sf::Font& font, sf::VertexArray& vertex, int width)
{
    circles.clear();
    strings.clear();
    vertex.clear();

    std::function<void(Node*, int, int)> l = [&](Node* n, int lvl, int i) {
        auto posX = width * i / pow(2, lvl + 1);
        auto posY = 50 + lvl * 95;

        if (n != t.root)
            vertex.append(sf::Vertex(sf::Vector2f(posX, posY)));

        sf::Text text(n->value, font, 21);
        text.setFillColor(sf::Color(0, 0, 0));
        auto textBox = text.getLocalBounds();
        text.setOrigin(textBox.width / 2 + 4, textBox.height / 2 + 7);
        text.setPosition(posX, posY);

        sf::CircleShape circle(20);
        circle.setFillColor(sf::Color(255, 255, 255));
        auto circleBox = circle.getLocalBounds();
        circle.setOrigin(circleBox.width / 2, circleBox.height / 2);
        circle.setPosition(posX, posY);

        circles.push_back(circle);
        strings.push_back(text);

        if (n->nodes[0])
        {
            vertex.append(sf::Vertex(sf::Vector2f(posX, posY)));
            l(n->nodes[0], lvl + 1, i * 2 - 1);
        }
        if (n->nodes[1])
        {
            vertex.append(sf::Vertex(sf::Vector2f(posX, posY)));
            l(n->nodes[1], lvl + 1, i * 2 + 1);
        }
    };

    l(t.root, 0, 1);
}

int main()
{
    int wWidth = 1310;
    int wHeight = 610;

    //Creating a Window
    sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "Binary Trees from algebraic expressions");
    window.setFramerateLimit(60);

    //Creating a Tree
    //BinaryTree t("((12+5)*7-6*11+3)*8");
    BinaryTree t("(12 + 5) * 7 - 6 * (11 + 3) * 8");
    t.Print();

    //Creating circles, lines and strings
    std::vector<sf::CircleShape> circles;
    std::vector<sf::Text> strings;
    sf::Font font;
    font.loadFromFile("Xolonium-Regular.ttf");
    sf::VertexArray vertex(sf::Lines);

    createShapes(t, circles, strings, font, vertex, wWidth);

    //Main loop
    while (window.isOpen())
    {
        //Event handling
        sf::Event event;
        while (window.pollEvent(event))
        {
            //When closing the window
            if (event.type == sf::Event::Closed)
                window.close();

            //When a key is pressed
            if (event.type == sf::Event::KeyPressed)
            {
                //std::cout << "Key pressed: " << event.key.code << '\n';
                
                //If the key pressed is escape
                if (event.key.code == sf::Keyboard::Escape)
                {
                    std::string s;
                    std::cout << "Enter a new expression:\n";
                    std::cin >> s;
                    t.Update(s);
                    createShapes(t, circles, strings, font, vertex, wWidth);
                    std::cout << '\n';
                    t.Print();
                }
            }
        }

        //Drawing on the screen
        window.clear();                 //clears the screen (color)
        
        window.draw(vertex);

        for (auto circle : circles)
        {
            //Draws the objects created
            window.draw(circle);
        }
        for (auto string : strings)
        {
            //Draws the objects created
            window.draw(string);
        }

        //Displays the screen
        window.display();
    }
  
    return 0;
}
