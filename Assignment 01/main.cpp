
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// In order to load the resources like cute_image.png, you have to set up
// your target scheme:
//
// - Select "Edit Scheme…" in the "Product" menu;
// - Check the box "use custom working directory";
// - Fill the text field with the folder path containing your resources;
//        (e.g. your project folder)
// - Click OK.
//
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <memory>
struct MyShape
{
    std::shared_ptr<sf::Shape> s;
    std::string name;
    sf::Vector2f speed;
};

int main(int argc, char * argv[])
{
    
    std::vector<MyShape> shapes;
    std::string token,fdir, shapeName;
    float posx, posy, sx, sy, radius, width, height;
    int r, b, g, winx,winy,size,f_r,f_g,f_b;
    sf::Font arial;
    sf::Text text;
    // event handling
    sf::Event event;
    
    
    //Reading File
    std::ifstream fin("/Users/mariaaloysius/Downloads/COMP4300_A1/Assignment 01/Assignment 01/conf.txt");

    while (fin.good())
    {
        fin>>token;
        if (token == "Window")
        {
            fin>>winx>>winy;
        }
        else if (token == "Font")
        {
            fin>>fdir>>size>>f_r>>f_g>>f_b;
            if (!arial.loadFromFile("/Users/mariaaloysius/Downloads/COMP4300_A1/Assignment 01/Assignment 01/fonts/arial.ttf"))
            {
                // if we can't load the font, print an error to the error console and exit
                std::cerr << "Could not load font!\n";
                exit(-1);
            }
            std::cout<<"font done";
        }
        else if (token == "Rectangle")
        {
            fin>>shapeName>>posx>>posy>>sx>>sy>>r>>g>>b>>width>>height;
            MyShape shape;
            shape.s = std::make_shared<sf::RectangleShape>(sf::Vector2f(width,height));
            shape.s->setPosition(posx, posy);
            shape.s->setFillColor(sf::Color(r,g,b));
            shape.name=shapeName;
            shape.speed=sf::Vector2f(sx,sy);
            shapes.push_back(shape);
            std::cout<<"rectangle done";
        }
        else if (token == "Circle")
        {
            fin>>shapeName>>posx>>posy>>sx>>sy>>r>>g>>b>>radius;
            MyShape shape;
            shape.s = std::make_shared<sf::CircleShape>(radius);
            shape.s->setPosition(posx, posy);
            shape.s->setFillColor(sf::Color(r,g,b));
            shape.name=shapeName;
            shape.speed=sf::Vector2f(sx,sy);
            shapes.push_back(shape);
            std::cout<<"circle done";
        }
    }
    
    sf::RenderWindow window(sf::VideoMode(winx, winy), "Assignment 01");
    while (window.isOpen())
    {
        //event handling
        while (window.pollEvent(event))
        {
            // this event triggers when the window is closed
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            
            // this event is triggered when a key is pressed
            if (event.type == sf::Event::KeyPressed)
            {
                // print the key that was pressed to the console
                std::cout << "Key pressed with code = " << event.key.code << "\n";
                
                // example, what happens when x is pressed
                if (event.key.code == sf::Keyboard::X)
                {
                    // reverse the direction of the circle on the screen
                    //circleMoveSpeed *= -1.0f;
                    std::cout<<"reverseCircle";
                }
                
                // what happens when y is pressed
                if (event.key.code == sf::Keyboard::Y)
                {
                    // reverse the direction of the circle on the screen
                    //rectangleMoveSpeed *= -1.0f;
                    std::cout<<"reverseRec";
                }
            }
        }
        
        //Drawing Texts and shapes
        window.clear();
        float shapeposx,shapeposy;
        for (auto & i : shapes)
        {
            //animation
            i.s->setPosition(i.s->getPosition().x-i.speed.x, i.s->getPosition().y-i.speed.y);
            
            //bouncing
            if((i.s->getPosition().x < 0) || (i.s->getLocalBounds().width + i.s->getPosition().x) > winx || (i.s->getPosition().y <0) || (i.s->getLocalBounds().height + i.s->getPosition().y) > winy)
            {
                i.speed *=-1.0f;
            }
            
            //text
            text.setFont(arial);
            text.setFillColor(sf::Color(f_r,f_g,f_b));
            text.setString(i.name);
            
            //text positioning
            shapeposx = i.s->getPosition().x;
            shapeposy = i.s->getPosition().y;
            text.setPosition(shapeposx-i.speed.x,shapeposy-i.speed.y);
            
            //draw
            window.draw(*i.s);
            window.draw(text);
        }
        window.display();
        
    }
    
    
    return 0;
}


