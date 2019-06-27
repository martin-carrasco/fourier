#ifndef FOURIER_SFML_WRAPPER_H
#define FOURIERI_SFML_WRAPPER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class WindowManager{
    private:
        sf::RenderWindow window;
        sf::Event event;
    public:
        WindowManager(int width, int height, std::string name);
        bool is_open(); 
        bool poll_event();
        sf::Event& get_event();

        void close();
        void display();
        void clear();


        void draw_pixel(int x, int y, sf::Uint8 red, sf::Uint8 green, sf::Uint8 blue);
        //const sf::Uint8* get_pixel_buffer();
};

class ImageManager{
    public:
        static sf::Image load_img(const std::string& name){
            sf::Image img;
            img.loadFromFile(name);
            return img;
        }   
        static void save_img(const std::string& name, sf::Image& img){
            img.saveToFile(name);
        }
    
};


#endif
