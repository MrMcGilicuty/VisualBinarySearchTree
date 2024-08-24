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
    for (int x = 0; x <= size; x++) {
        int insert = rand() % 10 + 1;
        Node newNode(insert);

        // Creates a new node and adds it to the list.

        {
            lock_guard<mutex> lock(treeMutex);
            BinaryTree->add(make_shared<Node>(newNode));
        }

        // Simulated delay so its not instant.
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    cout << "\nFinished Tree Generation\n";
}

int main()
{
    uint16_t size_tree;
    cout << "Size of tree desired: ";
    cin >> size_tree;

    // Setup.

    const sf::Vector2u window_size{2160, 1240};
    sf::RenderWindow window(sf::VideoMode(window_size.x, window_size.y), "BLN Tree", sf::Style::Default);
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
            for (int x = 0; x < size_tree; x++) {
                // Finds the vector of every node on 'x' depth level
                vector<int> treeList = BSTree->deepSearch(BSTree->head, x);

            }
        }

        window.display();
        
    }

    // Join the thread before exiting main to ensure proper cleanup
    treeBrain.join();

    return 0;
}