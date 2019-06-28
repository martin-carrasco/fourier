#ifndef FOURIER_SFML_WRAPPER_H
#define FOURIER_SFML_WRAPPER_H

#include <SFML/Graphics.hpp>
#include "types.h"
#include <string>
#include <vector>

class WindowManager{
    private:
        sf::RenderWindow window;
        sf::Event event;
        sf::Texture texture;
        sf::Sprite sprite;
    public:
        WindowManager(int width, int height, std::string name);
        bool is_open(); 
        bool poll_event();
        sf::Event& get_event();

        void close();
        void display();
        void clear();

        void load_img(sf::Image img);
        
        void draw_sprite();
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
        static sf::Image make_image(std::vector< std::vector< cn > > matrix){
            int width, height;
            
            width = matrix.size();
            height = matrix[0].size();

            sf::Image img;
            img.create(width, height);

            for(int x = 0;x < width;x++){
                for(int y = 0;y < height;y++){
                    cn pixel_color = matrix[x][y];

                    //sf::Color color(real(pixel_color.R),
                                    //real(pixel_color.G),
                                    //real(pixel_color.B),
                                    //real(pixel_color.A));

                    img.setPixel(x, y, color);
                }
            }
            return img;
        }
        static std::vector< std::vector< cn> > convert_complex(sf::Image& img){
            int max_x, max_y;
            max_x = img.getSize().x;
            max_y = img.getSize().y;

            std::vector< std::vector< cn > > matrix(max_x, std::vector< cn >(max_y, 0));

            for(int x = 0;x < max_x;x++){
                for(int y = 0;y < max_y;y++){
                    cn pixel;
                    sf::Color pixel_color = img.getPixel(x, y);

                    pixel.R = pixel_color.r;
                    pixel.G = pixel_color.g;
                    pixel.B = pixel_color.b;
                    pixel.A = pixel_color.a;

                    matrix[x][y] = pixel;
                }
            }
            return matrix;
     }
    
};


#endif
