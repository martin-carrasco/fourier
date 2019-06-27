#include "../../include/utility/sfml_wrapper.h" 

using namespace std;
using namespace sf;

WindowManager::WindowManager(int width, int height, string name) : window(VideoMode(width, height), name){

}
bool WindowManager::is_open(){
    return this->window.isOpen();
} 
bool WindowManager::poll_event(){
    return this->window.pollEvent(event);
}

Event& WindowManager::get_event(){
    return this->event; 
}

void WindowManager::close(){
    this->window.close();
}

void WindowManager::clear(){
    this->window.clear(Color::Black);
}

void WindowManager::display(){
    this->window.display();
}

void WindowManager::draw_pixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue){
    Vector2f pos(x, y);
    RectangleShape pixel;

    pixel.setSize({1.f, 1.f});
    pixel.setFillColor({red, green, blue});
    pixel.setPosition(pos);

    this->window.draw(pixel);    
}

