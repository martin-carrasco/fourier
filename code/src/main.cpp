#include "utility/image_manager.h"
#include "utility/sfml_wrapper.h"

using namespace std;

int main(void)
{
    //Load image from file
    sf::Image img = ImageManager::load_img("res/image/input/lena.jpg");
    //Convert to RGBA complex matrix
    vector< vector< cn > > mat = ImageManager::convert_complex(img); 
    //Make fourier manipulator object
    ImageTransform trans(mat);
    //Create image filter
    ImageLowFilter* filter = new ImageLowFilter();
    
    //Apply filter to convolution
    trans.apply_transform(filter);

    //Get transformed image back
    sf::Image trans_img = ImageManager::make_image(trans.get_matrix());   

    ImageManager::save_img("res/image/output/tranform.png", trans_img);
    //Create window manager
    WindowManager manager(128, 128, "FT test");  
    manager.load_img(trans_img);

    while(manager.is_open()){
        
        manager.clear();
        manager.draw_sprite();
        manager.display();
    }

   
    //ImageManager::save_img("res/image/output/tranform.png", img);
    //Render img
    
    return 0;
}
