#include "utility/sfml_wrapper.h" 

using namespace std;

WindowManager::WindowManager(int width, int height, string name) : window(sf::VideoMode(width, height), name){

}
bool WindowManager::is_open(){
    return this->window.isOpen();
} 
bool WindowManager::poll_event(){
    return this->window.pollEvent(event);
}

sf::Event& WindowManager::get_event(){
    return this->event; 
}

void WindowManager::close(){
    this->window.close();
}

void WindowManager::clear(){
    this->window.clear(sf::Color::Black);
}

void WindowManager::display(){
    this->window.display();
}

void WindowManager::draw_pixel(int x, int y, sf::Uint8 red, sf::Uint8 green, sf::Uint8 blue){
    sf::Vector2f pos(x, y);
    sf::RectangleShape pixel;

    pixel.setSize({1.f, 1.f});
    pixel.setFillColor({red, green, blue});
    pixel.setPosition(pos);

    this->window.draw(pixel);    
}

void WindowManager::load_img(sf::Image img){
   texture.loadFromImage(img); 
   sprite.setTexture(texture);
}        
void WindowManager::draw_sprite(){
    this->window.draw(sprite);
}
