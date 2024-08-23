#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <chrono>
#include <mutex>
#include <thread>
#include "TreeContainer.h"
#include "Node.h"
using namespace std;

mutex treeMutex;

static void generateTree(shared_ptr<TreeContainer> BinaryTree, int size) {

    // Numbers between 0-100.
    for (int x = 0; x <= size; x++) {
        int insert = rand() % 10 + 1;
        Node newNode(insert);

        // Creates a new node and adds it to the list.


        BinaryTree->add(make_shared<Node>(newNode));

        // Simulated delay so its not instant.
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main()
{
    uint16_t size_tree;
    cout << "Size of tree desired: ";
    cin >> size_tree;

    const sf::Vector2u window_size{2160, 1240};
    sf::RenderWindow window(sf::VideoMode(window_size.x, window_size.y), "BLN Tree", sf::Style::Default);
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(true);
    window.setKeyRepeatEnabled(false);

    // Setup.
    shared_ptr<TreeContainer> BLNTree = make_shared<TreeContainer>();

    thread treeBrain(generateTree, BLNTree, size_tree);
    cout << "\nFinished Tree Generation\n";
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
        window.display();
    }

    // Join the thread before exiting main to ensure proper cleanup
    treeBrain.join();

    return 0;
}