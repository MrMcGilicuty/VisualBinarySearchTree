#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include <chrono>
#include <mutex>
#include <thread>
#include "TreeContainer.h"
#include "Node.h"
using namespace std;

mutex treeMutex;

static void generateTree(shared_ptr<TreeContainer> BinaryTree, int size) {

    // Numbers between 0-100.
    for (int x = 0; x < size; x++) {
        int insert = rand() % size + 1;
        Node newNode(insert);

        // Creates a new node and adds it to the list.

        {
            lock_guard<mutex> lock(treeMutex);
            BinaryTree->add(make_shared<Node>(newNode));
        }

        // Simulated delay so its not instant.
        //this_thread::sleep_for(chrono::milliseconds(50));
    }
    cout << "\nFinished Tree Generation\n";
}

int main()
{
    uint16_t size_tree;
    cout << "Size of tree desired: ";
    cin >> size_tree;

    // Setup.

    sf::Font font;
    font.loadFromFile("Caviar Dreams Bold.ttf");
    const sf::Vector2u window_size{2560, 1440};
    sf::RenderWindow window(sf::VideoMode(window_size.x, window_size.y), "BLN Tree", sf::Style::Fullscreen);
    window.clear(sf::Color(25, 25, 25));
    window.display();
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(true);
    window.setKeyRepeatEnabled(false);

    shared_ptr<TreeContainer> BSTree = make_shared<TreeContainer>();
    int maxDepth = 1 + floor((log2(size_tree)));

    thread treeBrain(generateTree, BSTree, size_tree);
    while (window.isOpen())
    {


        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }

        window.clear(sf::Color::Black);
        // Draw your content here

        // Do everything with reading data here
        {
            lock_guard<mutex> lock(treeMutex);
            for (int y = 0; y < size_tree; y++) {
                // Finds the vector of every node on 'x' depth level
                vector<int> treeList = BSTree->deepSearch(BSTree->head, y);
                for (int x = 1; x <= treeList.size(); x++) {
                    int num = treeList[x - 1];
                    if (num == -1) {
                        continue;
                    }

                    const float paddingWidth  = 50;
                    const float paddingHeight = 30;
                    const float circleRadius = 750.0 / size_tree;
                    sf::CircleShape circle(circleRadius); // radius
                    circle.setOutlineColor(sf::Color::White); // outline color
                    circle.setOutlineThickness(5); // thickness of the outline
                    circle.setFillColor(sf::Color(25, 25, 25));
                    circle.setPosition(x * (window_size.x / (treeList.size() + 1)),
                                       y * ((window_size.y - (paddingHeight / maxDepth)) / maxDepth) + paddingHeight);

                    // Create a text object
                    sf::Text text;
                    text.setFont(font); // Set the font
                    text.setCharacterSize(circleRadius / 1.5);
                    text.setString(to_string(num)); // Set the text string
                    text.setFillColor(sf::Color::White); // Set the text color

                    // Center the text in the circle
                    sf::FloatRect textRect = text.getLocalBounds();
                    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                    text.setPosition(circle.getPosition().x + circle.getRadius(), circle.getPosition().y + circle.getRadius());

                    window.draw(circle);
                    window.draw(text);
                }

            }
        }

        window.display();
        
    }

    // Join the thread before exiting main to ensure proper cleanup
    treeBrain.join();

    return 0;
}