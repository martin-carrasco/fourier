//#include "../include/image_manager.h"
#include "../include/opencv_manager.h"
#include <vector>

using namespace std;

int main(void)
{
    generate_csv();
    vector< vector<cn> > img_matrix = load_img("../output/output.txt");
    img_transform(img_matrix);
    save_img(img_matrix);
    display_csv();
    
    return 0;
}
