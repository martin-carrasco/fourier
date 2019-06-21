#include "../include/opencv_manager.h"


using namespace std;

void generate_csv(){
  Img image = cv::imread(FILENAME, cv::IMREAD_GRAYSCALE);
  fstream file(OUTPUT_FILE, ios::out);
  file << cv::format(image, cv::Formatter::FMT_CSV);
  file.close();
}

void display_csv(){
  // Read CSV
  // Source: https://answers.opencv.org/question/55210/reading-csv-file-in-opencv/
  fstream inputfile(INPUT_FILE, ios::in);
  string current_line;

  // vector allows you to add data without knowing the exact size beforehand
  vector<vector<int>> all_data;

  // Start reading lines as long as there are lines in the file
  while (getline(inputfile, current_line)) {

    // Now inside each line we need to seperate the cols
    vector<int> values;
    stringstream temp(current_line);
    string single_value;
    while (getline(temp, single_value, ',')) {

      // convert the string element to a integer value
      values.push_back(atoi(single_value.c_str()));
    }

    // add the row to the complete data vector
    all_data.push_back(values);
  }
  inputfile.close();

  // Now add all the data into a Mat element
  Img vect = Img::zeros((int) all_data.size(), (int) all_data[0].size(), CV_8UC1);

  // Loop over vectors and add the data
  for (int rows = 0; rows < all_data.size(); rows++) {
    for (int cols = 0; cols < all_data[0].size(); cols++) {
      vect.at<uchar>(rows, cols) = all_data[rows][cols];
    }
  }

  // Show image
  cv::namedWindow("Image", cv::WINDOW_NORMAL);
  cv::imshow("Image", vect);
  cv::waitKey(0);
}
