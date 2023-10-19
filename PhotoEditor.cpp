// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name:				PhotoEditor.cpp
// Last Modification Date:	9/10/2023
// Author1 and ID and Group:	Farida Youssry 20221219 
// Author2 and ID and Group:	Shahd Abdel Nasser 20220480
// Author3 and ID and Group:	Mohamed Osama 20220477
// Teaching Assistant:		xxxxx xxxxx
// Purpose: a program that displays a menu of choices for the user that allow him to load an image and choose the filter to apply 
 
#include <iostream>
#include <fstream>   
#include <cstring>
#include <algorithm>
#include <cmath> 
#include "bmplib.cpp" 
using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];
unsigned char image_RGB [SIZE][SIZE][RGB];
unsigned char image2_RGB [SIZE][SIZE][RGB];

void loadImage () {
    char imageFileName[100];


    cout << "Enter the source image file name: ";
    cin >> imageFileName;



    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

void saveImage () {
    char imageFileName[100];


    cout << "Enter the target image file name: ";
    cin >> imageFileName;


    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}

void loadRGBImage () {
    char imageFileName[100];


    cout << "Enter the source image file name : ";
    cin >> imageFileName;



    strcat (imageFileName, ".bmp");
    readRGBBMP(imageFileName, image_RGB);
}

void saveRGBImage () {
    char imageFileName[100];


    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    
    strcat (imageFileName, ".bmp");
    writeRGBBMP(imageFileName, image_RGB);
}

void black_and_white() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {

            //turn the pixel to white if it's greater than average
            if (image[i][j] > 127)
                image[i][j] = 255;
            else // turn the pixel to black if it's smaller or equal to average
                image[i][j] = 0;
        }
    }
}

void invert_image(){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {

            //turn every black pixel to white
            if (image[i][j]==0){
                image[i][j]+=255;
            }

                //turn every white pixel to black
            else if (image[i][j]==255){
                image[i][j]-=255;
            }
                //turn every gray pixel to opposite level of brightness
            else{
                image[i][j]=255-image[i][j];
            }
        }
    }
}

void merge_images(){

    //get the second image that will be merged with
    char imageFileName2[100];
    cout << "Please enter name of image file to merge with:" ;
    cin >> imageFileName2;

    strcat (imageFileName2, ".bmp");
    readGSBMP(imageFileName2, image2);

    //get the average of the two pixels
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            image[i][j]=(image[i][j]+image2[i][j])/2;
        }
    }
}

void flip_image() {
    char choice; // the way of flipping(v or h)
    cout << "Flip (h)orizontally or (v)ertically ?";
    cin >> choice;
    while (choice != 'v' && choice != 'h') { //making sure to enter a valid choice
        cout << "invalid choice please enter v or h ";
        cin >> choice;
    }

    if (choice == 'v') {
        //swapping the elements in the first half of the row with the corresponding elements in the second half of the row.
        for (int i = 0, x = SIZE - 1; i < SIZE / 2; i++, x--) {
            for (int j = 0; j < SIZE; j++) {
                swap(image[i][j], image[x][j]);

            }
        }

    } else {
        //swapping the elements in the left half of the row with the corresponding elements in the right half of the row.
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0, y = SIZE - 1; j < SIZE / 2; j++, y--) {
                swap(image[i][j], image[i][y]);

            }
        }
    }
}

void rotate_image(){
    int rotate_angle;
    int cnt; // setting a counter to loop over the function once, twice or three times depending on the user's input
    cout<<"Please enter 90 or 180 or 270 ";
    cin>>rotate_angle;
    if (rotate_angle==90){
        cnt=1;}
    else if (rotate_angle==180){cnt=2;}
    else cnt=3;
    for (int c=0; c<cnt; c++){
        // rotating and swapping the rows
        for (int i=0; i<SIZE; i++) {

            for (int j = i + 1; j < SIZE; j++) {
                swap(image[i][j], image[j][i]);
            }
        }

        for (int i=0; i<SIZE; i++){

            for(int j=0; j<SIZE/2; j++){
                swap(image[i][j], image[i][SIZE-j-1]);
            }
        }
    }
}

void detect_image_edge(){
    unsigned char image2[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (image[i][j] > 127)
                image[i][j] = 255;
            else
                image[i][j] = 0;
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            // check both i and j
            if (i < SIZE - 2 && j < SIZE - 2 && (image[i][j] != image[i + 1][j + 1] && image[i + 1][j + 1] == image[i + 2][j + 2]) || (image[i][j] == image[i + 1][j + 1] && image[i + 1][j + 1] != image[i + 2][j + 2]))
                image2[i][j]=image[i+1][j+1];
            else
                image2[i][j]=255;

        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = image2[i][j];
        }
    }
}

void darken_and_lighten_image() {

    cout << "Do you want to (d)arken or (l)ighten?";
    char input;
    cin >> input;

    if (input == 'd' || input == 'D') {

        //decrease the pixel by half to darken the image
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = image[i][j] * 1 / 2;
            }
        }

    }
    else if (input == 'l' || input == 'L')
    {
        //multiply the pixel by 1.5 and if it exceeds 255, turn the pixel to white.
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = min (255, (int) (image [i][j]*1.5));
            }
        }
    }
}

void enlarge_image() {
    unsigned char image2[SIZE][SIZE];
    int n;
    cout << " which quarter do you want to enlarge?";
    cin >>
        n;
    while (n != 1 && n != 2 && n != 3 && n != 4) { //making sure the user will enter a valid quarter
        cout << "please enter 1 or 2 or 3 or 4";
        cin >>
            n;
    }
    if (n == 1) { //looping in the first quarter
        for (
                int i = 0;
                i < 128; i++) {
            for (
                    int j = 0;
                    j < 128; j++) {
                for (
                        int r = 0;
                        r < 2; r++) {//r is the enlarged row
                    for (
                            size_t c = 0;
                            c < 2; c++) {//c is the enlarged column
                        image2[i * 2 + r][j * 2 + c] = image[i][j];


                    }
                }
            }
        }
    } else if (n == 2) {//looping in the secound quarter
        for (
                int i = 0;
                i < 128; i++) {
            for (
                    int j = 128;
                    j < 256; j++) {
                for (
                        size_t r = 0;
                        r < 2; r++) {//r is the enlarged row
                    for (
                            size_t c = 0;
                            c < 2; c++) {//c is the enlarged column
                        image2[i * 2 + r][(j - 128) * 2 + c] = image[i][j];

                    }
                }
            }
        }
    } else if (n == 3) {//looping in the third quarter
        for (
                int i = 128;
                i < 256; i++) {
            for (
                    int j = 0;
                    j < 128; j++) {
                for (
                        size_t r = 0;
                        r < 2; r++) {//r is the enlarged row
                    for (
                            size_t c = 0;
                            c < 2; c++) {//c is the enlarged column
                        image2[(i - 128) * 2 + r][j * 2 + c] = image[i][j];

                    }
                }
            }
        }
    } else {//looping in the fourth quarter
        for (
                int i = 128;
                i < 256; i++) {
            for (
                    int j = 128;
                    j < 256; j++) {
                for (
                        size_t r = 0;
                        r < 2; r++) {//r is the enlarged row
                    for (
                            size_t c = 0;
                            c < 2; c++) {//c is the enlarged column
                        image2[(i - 128) * 2 + r][(j - 128) * 2 + c] = image[i][j];

                    }
                }
            }
        }
    }
    for (int i = 0; i < 256; ++i) {
        for (int j = 0; j < 256; ++j) {
            image[i][j]=image2[i][j];

        }
    }
}

void shrink_image() {
    int x;
    cout << "Shrink to half(2) , third (3), or quarter (4)? ";
    cin >> x;
    if(x==2||x==3||x==4){
        int H = SIZE / x; //New height of the image after shrinking.
        int W = SIZE / x;  //New width of the image after shrinking.
        int temp[H][W]; //new array for the shrunk image.

        //two for loops for the new height and width
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                int sum = 0;
                for (int k = 0; k < x; k++) {
                    for (int l = 0; l < x; l++) {
                        //putting each 4 pixels in 1 pixel example:x=2.
                        sum += image[i * x + k][j * x + l];
                        //sum of every 4 pixels example:x=2.
                    }
                }
                temp[i][j] = sum / (x * x); //average of the pixels.
            }                               //if the input was 1/2 we take the average of 4 pixels and put it into one pixel only
        }
        for(int i=0 ;i<SIZE;i++){ //two for loops to access each index in the original 256 image
            for(int j=0 ;j<SIZE;j++){
                image[i][j]=255; //turning the original image to white so the new image has a white background.
            }}
        // inserting the new shrunk image into the original image.
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                image[i][j] = temp[i][j];}
        }
    }
}

void mirror_image(){
    string s;
    cout << "Please type right or left or top or lower";
    cin>> s;
    if (s=="right"){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                image[i][j]=image[i][256-j];
            }
        }
    }

    else if (s=="left"){
        for (int i = SIZE; i > 0; i--) {
            for (int j = SIZE; j> 0; j--) {
                image[i][j]=image[i][256-j];
            }
        }
    }
    else if (s=="top"){
        for (int j = SIZE; j > 0; j--) {
            for (int i = SIZE; i> 0; i--) {
                image[i][j]=image[256-i][j];
            }
        }
    }
    else {
        for (int j = 0; j < SIZE; j++) {
            for (int i = 0; i< SIZE; i++) {
                image[i][j]=image[256-i][j];
            }
        }
    }
}

void shuffle_image() {

    int arr[4], cnt{1}, row = 0, column = 0, j = 0, k = 0, new_column = 0, new_row = 0;

    // Prompt the user to enter the order of the image quadrants
    cout << "Enter the order of the image you want: ";

    // Read the user-defined order into an array
    for (int i = 0; i < 4; i++) {
        cin >> arr[i];
    }
    unsigned image_output[SIZE][SIZE];

    // Loop through the input order and shuffle the image quadrants
    for (int i = 0; i < 4; i++) {
        if (arr[i] == 1) {
            // Shuffle quadrant 1
            for (row = new_row, j = 0; j < SIZE / 2; row++, j++) {
                for (column = new_column, k = 0; k < SIZE / 2; column++, k++) {
                    image_output[row][column] = image[j][k];
                }
            }
        } else if (arr[i] == 2) {
            // Shuffle quadrant 2
            for (row = new_row, j = 0; j < SIZE / 2; row++, j++) {
                for (column = new_column, k = SIZE / 2; k < SIZE; column++, k++) {
                    image_output[row][column] = image[j][k];
                }
            }
        } else if (arr[i] == 3) {
            // Shuffle quadrant 3
            for (row = new_row, j = SIZE / 2; j < SIZE; row++, j++) {
                for (column = new_column, k = 0; k < SIZE / 2; column++, k++) {
                    image_output[row][column] = image[j][k];
                }
            }
        } else if (arr[i] == 4) {
            // Shuffle quadrant 4
            for (row = new_row, j = SIZE / 2; j < SIZE; row++, j++) {
                for (column = new_column, k = SIZE / 2; k < SIZE; column++, k++) {
                    image_output[row][column] = image[j][k];
                }
            }
        }

        ++cnt;

        // Update the new row and column according to the quadrant count
        if (cnt == 2){
            new_row = 0;
            new_column= SIZE / 2;
        }
        else if (cnt == 3) {
            new_row = SIZE / 2;
            new_column = 0;
        }
        else if (cnt == 4) {
            new_row = SIZE / 2;
            new_column = SIZE / 2;
        }
    }

    // Display the shuffled image back on the output image
    for (int i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            image[i][j] = image_output[i][j];
        }
    }
}

void blur_image() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                //image[i][j]=(image[i-1][j-1]+image[i-1][j]+image[i-1][j+1]+image[i][j-1]+image[i][j+1]+image[i+1][j-1]+image[i+1][j]+image[i+1][j+1])/8;
                image[i][j] = (image[i - 1][j - 2] + image[i - 1][j - 1] + image[i - 1][j] + image[i - 1][j + 1] +
                               image[i - 1][j + 2] + image[i][j - 2] + image[i][j - 1] + image[i][j + 1] +
                               image[i][j + 2] + image[i + 1][j - 2] + image[i + 1][j - 1] + image[i + 1][j] +
                               image[i + 1][j + 1] + image[i + 1][j + 2]) / 14;
            }
        }
    }

void crop_image() {
    int x, y, l, w;
    unsigned char white[SIZE][SIZE];

    cout << "Please enter x y l w";
    cin >> x >> y >> l >> w;

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            white[i][j] = 255;
        }
    }

    for (int i = x; i < x + w; i++) {
        for (int j = y; j < y + l; j++) {
            white[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = white[i][j];
        }
    }
}

void skew_horizontally() {
    double skew_angle;
    cout<<"Please enter degree to skew right: ";
    cin >> skew_angle;
    unsigned char output_image[SIZE][SIZE] = {}; // Initialize the temporary image array
    double skew_distance = tan(skew_angle * M_PI / 180.0) * SIZE; // Calculate the distance to remove
    double shrink = (double)SIZE / (SIZE - skew_distance); // Calculate the shrink ratio
    double step = skew_distance / 256; // Calculate the step size for skewing
    double current_position = 0, skew_adjustment = 0;

    // Iterate through each row of the image
    for (int i = 0; i < SIZE; ++i) {
        current_position = 0;

        // Iterate through each column in the temporary image
        for (int j = static_cast<int>(skew_distance - skew_adjustment); j < SIZE - skew_adjustment; ++j) {
            int avg = 0, pixel_count = 0;

            // Iterate through the original image to calculate the average in the skewed region
            for (int k = max(0, static_cast<int>(ceil(current_position - shrink)));
                 k < min(SIZE, static_cast<int>(ceil(current_position + shrink))); ++k, ++pixel_count) {
                avg += image[i][k];
            }

            // Calculate the average value and assign it to the temporary image
            if (pixel_count > 0) {
                avg /= pixel_count;
            }
            output_image[i][j] = static_cast<unsigned char>(avg);
            current_position += shrink;
        }
        skew_adjustment += step;
    }

    // Copy the temporary image back to the original image
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = output_image[i][j];
        }
    }
}

void skew_vertically() {
    double skew_angle; // Angle of vertical skew in degrees
    cout<<"Please enter degree to skew Up: ";
    cin>> skew_angle;

    unsigned char output_image[SIZE][SIZE] = {}; // Initialize the output image array
    double skew_distance = tan(skew_angle * M_PI / 180.0) * SIZE; // Calculate the vertical skew distance
    double compress_ratio = (double) SIZE / (SIZE - skew_distance); // Calculate the vertical compression ratio
    double step = skew_distance / 256; // Calculate the step size for vertical skew
    double current_position = 0, skew_adjustment = 0;

    // Iterate through each column of the input image
    for (int column = 0; column < SIZE; ++column) {
        current_position = 0;

        // Iterate through each row in the output image
        for (int row = static_cast<int>(skew_distance - skew_adjustment); row < SIZE - skew_adjustment; ++row) {
            int average = 0, pixel_count = 0;

            // Iterate through the input image to calculate the average in the vertically skewed region
            for (int input_row = std::max(0, static_cast<int>(std::ceil(current_position - compress_ratio)));
                 input_row < std::min(SIZE, static_cast<int>(std::ceil(current_position + compress_ratio))); ++input_row, ++pixel_count) {
                average += image[input_row][column];
            }

            // Calculate the average value and assign it to the output image
            if (pixel_count > 0) {
                average /= std::max(1, pixel_count);
            }
            output_image[row][column] = static_cast<unsigned char>(average);
            current_position += compress_ratio;
        }
        skew_adjustment += step;
    }

    // Copy the output image back to the input image
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = output_image[i][j];
        }
    }
}

void RGB_black_and_white(){
    int Total = 0;
    int red = 0, green = 0, blue = 0;

    // Calculate the sum of intensities for each color channel
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            red += image_RGB[i][j][0];
            green += image_RGB[i][j][1];
            blue += image_RGB[i][j][2];
        }
    }

    // Calculate average intensities
    int avg_red = red / (SIZE * SIZE);
    int avg_green = green / (SIZE * SIZE);
    int avg_blue = blue / (SIZE * SIZE);

        // Convert to black and white based on average intensities
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (image_RGB[i][j][0] > avg_red||image_RGB[i][j][1] > avg_green||image_RGB[i][j][2] > avg_blue){
                    image_RGB[i][j][0] = 255;
                    image_RGB[i][j][1] = 255;
                    image_RGB[i][j][2] = 255;
                }
                else
                {
                    image_RGB[i][j][0] = 0;
                    image_RGB[i][j][1] = 0;
                    image_RGB[i][j][2] = 0;
                }
            }
        }
}

void RGB_to_invert_image(){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            for (int k = 0; k < RGB; ++k) {
                //turn every black pixel to white
                if (image_RGB[i][j][k]==0){
                    image_RGB[i][j][k]+=255;
                }

                    //turn every white pixel to black
                else if (image_RGB[i][j][k]==255){
                    image_RGB[i][j][k]-=255;
                }
                    //turn every gray pixel to opposite level of brightness
                else{
                    image_RGB[i][j][k]=255-image_RGB[i][j][k];
                }
            }

        }
    }
}

void RGB_merge_images(){

    //get the second image that will be merged with
    char imageFileName2[100];
    cout << "Please enter name of image file to merge with:" ;
    cin >> imageFileName2;


    strcat (imageFileName2, ".bmp");
    readRGBBMP(imageFileName2, image2_RGB);

    //get the average of the two pixels
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            for (int k = 0; k < RGB; ++k) {
                image_RGB[i][j][k]=(image_RGB[i][j][k]+image2_RGB[i][j][k])/2;
            }
        }
    }
}

void RGB_flip_image() {
    char choice; // the way of flipping(v or h)
    cout << "Flip (h)orizontally or (v)ertically ?";
    cin >> choice;
    while (choice != 'v' && choice != 'h') { //making sure to enter a valid choice
        cout << "invalid choice please enter v or h ";
        cin >> choice;
    }

    if (choice == 'v') {
        //swapping the elements in the first half of the row with the corresponding elements in the second half of the row.
        for (int i = 0, x = SIZE - 1; i < SIZE / 2; i++, x--) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; ++k) {
                    swap(image_RGB[i][j][k], image_RGB[x][j][k]);
                }
            }
        }

    } else {
        //swapping the elements in the left half of the row with the corresponding elements in the right half of the row.
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0, y = SIZE - 1; j < SIZE / 2; j++, y--) {
                for (int k = 0; k < RGB; ++k) {
                    swap(image_RGB[i][j][k], image_RGB[i][y][k]);
                }
            }
        }
    }
}

void RGB_detect_image_edge(){
    RGB_black_and_white();
    unsigned char image2[SIZE][SIZE][RGB];

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                // check both i and j
                if (i < SIZE - 2 && j < SIZE - 2 &&
                    ( image_RGB[i][j][k] != image_RGB[i + 1][j + 1][k] && image_RGB[i + 1][j + 1][k] == image_RGB[i + 2][j + 2][k]) ||
                    ( image_RGB[i][j][k] == image_RGB[i + 1][j + 1][k] && image_RGB[i + 1][j + 1][k] != image_RGB[i + 2][j + 2][k]))
                    image2[i][j][k] = image_RGB[i + 1][j + 1][k];
                else
                    image2[i][j][k] = 255;

            }
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k <RGB; ++k) {
                image_RGB[i][j][k] = image2[i][j][k];
            }
        }
    }

}

void RGB_rotate_image(){
    int rotate_angle;
    int cnt; // setting a counter to loop over the function once, twice or three times depending on the user's input
    cout<<"Please enter 90 or 180 or 270 ";
    cin>>rotate_angle;
    if (rotate_angle==90){
        cnt=1;}
    else if (rotate_angle==180){cnt=2;}
    else cnt=3;
    for (int c=0; c<cnt; c++){
        // rotating and swapping the rows
        for (int i=0; i<SIZE; i++) {
            for (int j = i + 1; j < SIZE; j++) {
                for (int k = 0; k < RGB; ++k) {
                    swap(image_RGB[i][j][k], image_RGB[j][i][k]);
                }
            }
        }

        for (int i=0; i<SIZE; i++){
            for(int j=0; j<SIZE/2; j++){
                for (int k = 0; k < RGB; ++k) {
                    swap(image_RGB[i][j][k], image_RGB[i][SIZE-j-1][k]);
                }
            }
        }
    }
}

void RGB_darken_and_lighten_image() {

    cout << "Do you want to (d)arken or (l)ighten? ";
    char input;
    cin >> input;

    if (input == 'd' || input == 'D') {

        //decrease the pixel by half to darken the image
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; ++k) {
                    image_RGB[i][j][k] = image_RGB[i][j][k] * 1 / 2;
                }
            }
        }
    }
    else if (input == 'l' || input == 'L')
    {
        //multiply the pixel by 1.5 and if it exceeds 255, turn the pixel to white.
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; ++k) {
                    image_RGB[i][j][k] = min (255, (int) (image_RGB [i][j][k] *1.5));
                }
            }
        }
    }
}

void RGB_enlarge_image() {
    unsigned char image2[SIZE][SIZE][RGB];
    int n;
    cout << "Which quarter do you want to enlarge? Enter 1, 2, 3, or 4: ";
    cin >> n;

    while (n != 1 && n != 2 && n != 3 && n != 4) {
        cout << "Please enter 1, 2, 3, or 4: ";
        cin >> n;
    }

    if (n == 1) {
        for (int i = 0; i < 128; i++) {
            for (int j = 0; j < 128; j++) {
                for (int r = 0; r < 2; r++) {
                    for (int c = 0; c < 2; c++) {
                        for (int k = 0; k < RGB; k++) {
                            image2[i * 2 + r][j * 2 + c][k] = image_RGB[i][j][k];
                        }
                    }
                }
            }
        }
    } else if (n == 2) {
        for (int i = 0; i < 128; i++) {
            for (int j = 128; j < 256; j++) {
                for (int r = 0; r < 2; r++) {
                    for (int c = 0; c < 2; c++) {
                        for (int k = 0; k < RGB; k++) {
                            image2[i * 2 + r][(j - 128) * 2 + c][k] = image_RGB[i][j][k];
                        }
                    }
                }
            }
        }
    } else if (n == 3) {
        for (int i = 128; i < 256; i++) {
            for (int j = 0; j < 128; j++) {
                for (int r = 0; r < 2; r++) {
                    for (int c = 0; c < 2; c++) {
                        for (int k = 0; k < RGB; k++) {
                            image2[(i - 128) * 2 + r][j * 2 + c][k] = image_RGB[i][j][k];
                        }
                    }
                }
            }
        }
    } else {
        for (int i = 128; i < 256; i++) {
            for (int j = 128; j < 256; j++) {
                for (int r = 0; r < 2; r++) {
                    for (int c = 0; c < 2; c++) {
                        for (int k = 0; k < RGB; k++) {
                            image2[(i - 128) * 2 + r][(j - 128) * 2 + c][k] = image_RGB[i][j][k];
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; k++) {
                image_RGB[i][j][k] = image2[i][j][k];
            }
        }
    }
}

void RGB_shrink_image() {
    int x;
    cout << "Shrink to half(2) , third (3), or quarter (4)? ";
    cin >> x;

    if (x == 2 || x == 3 || x == 4) { // Corrected the condition
        int H = SIZE / x; // New height of the image after shrinking.
        int W = SIZE / x; // New width of the image after shrinking.
        int L = RGB;      // New length of the image after shrinking.
        int temp_RGB[H][W][L]; // New array for the shrunk image.

        // Two nested loops for the new height and width
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                for (int k = 0; k < L; ++k) {
                    int sum = 0;
                    for (int m = 0; m < x; m++) {
                        for (int l = 0; l < x; l++) {
                            for (int n = 0; n < x; ++n) {
                                // Adding each (x*x*x) pixels to get the sum
                                sum += image_RGB[i * x + m][j * x + l][k];
                            }
                        }
                    }
                    temp_RGB[i][j][k] = sum / (x * x * x); // Average of the pixels.
                }
            }
        }

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image_RGB[i][j][0] = 255; // Turning the original image to white (R channel) so the new image has a white background.
                image_RGB[i][j][1] = 255; // Turning the original image to white (G channel) so the new image has a white background.
                image_RGB[i][j][2] = 255; // Turning the original image to white (B channel) so the new image has a white background.
            }
        }

        // Inserting the new shrunk image into the original image.
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                for (int k = 0; k < L; ++k) {
                    image_RGB[i][j][k] = temp_RGB[i][j][k];
                }
            }
        }
    }
}

void RGB_mirror_image() {
    string s;
    cout << "Please type right or left or top or lower: ";
    cin >> s;

    if (s == "right") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; k++) {
                    image_RGB[i][j][k] = image_RGB[i][SIZE - 1 - j][k];
                }
            }
        }
    } else if (s == "left") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE ; j++) {
                for (int k = 0; k < RGB; k++) {
                    image_RGB[i][SIZE - 1 - j][k] = image_RGB[i][j][k];
                }
            }
        }
    } else if (s == "top") {
        for (int j = 0; j < SIZE; j++) {
            for (int i = 0; i < SIZE; i++) {
                for (int k = 0; k < RGB; k++) {
                    image_RGB[SIZE - 1 - i][j][k] = image_RGB[i][j][k];
                }
            }
        }
    } else if (s == "lower") {
        for (int j = 0; j < SIZE; j++) {
            for (int i = 0; i < SIZE; i++) {
                for (int k = 0; k < RGB; k++) {
                    image_RGB[i][j][k] = image_RGB[SIZE - 1 - i][j][k];
                }
            }
        }
    } else {
        cout << "Invalid input. Please enter right, left, top, or lower." << endl;
    }
}

void RGB_shuffle_image() {
        int arr[4], cnt = 1, row = 0, column = 0, j = 0, k = 0, new_column = 0, new_row = 0;

        // Prompt the user to enter the order of the image quadrants
        cout << "Enter the order of the image you want: ";

        // Read the user-defined order into an array
        for (int i = 0; i < 4; i++) {
            cin >> arr[i];
        }

        unsigned image_output[SIZE][SIZE][3]; // Assuming RGB image

        // Loop through the input order and shuffle the image quadrants
        for (int i = 0; i < 4; i++) {
            if (arr[i] == 1) {
                // Shuffle quadrant 1
                for (row = new_row, j = 0; j < SIZE / 2; row++, j++) {
                    for (column = new_column, k = 0; k < SIZE / 2; column++, k++) {
                        for (int layer = 0; layer < 3; layer++) { // Iterate over RGB channels
                            image_output[row][column][layer] = image_RGB[j][k][layer];
                        }
                    }
                }
            } else if (arr[i] == 2) {
                // Shuffle quadrant 2
                for (row = new_row, j = 0; j < SIZE / 2; row++, j++) {
                    for (column = new_column, k = SIZE / 2; k < SIZE; column++, k++) {
                        for (int layer = 0; layer < 3; layer++) {
                            image_output[row][column][layer] = image_RGB[j][k][layer];
                        }
                    }
                }
            } else if (arr[i] == 3) {
                // Shuffle quadrant 3
                for (row = new_row, j = SIZE / 2; j < SIZE; row++, j++) {
                    for (column = new_column, k = 0; k < SIZE / 2; column++, k++) {
                        for (int layer = 0; layer < 3; layer++) {
                            image_output[row][column][layer] = image_RGB[j][k][layer];
                        }
                    }
                }
            } else if (arr[i] == 4) {
                // Shuffle quadrant 4
                for (row = new_row, j = SIZE / 2; j < SIZE; row++, j++) {
                    for (column = new_column, k = SIZE / 2; k < SIZE; column++, k++) {
                        for (int layer = 0; layer < 3; layer++) {
                            image_output[row][column][layer] = image_RGB[j][k][layer];
                        }
                    }
                }
            }

            ++cnt;

            // Update the new row and column according to the quadrant count
            if (cnt == 2) {
                new_row = 0;
                new_column = SIZE / 2;
            } else if (cnt == 3) {
                new_row = SIZE / 2;
                new_column = 0;
            } else if (cnt == 4) {
                new_row = SIZE / 2;
                new_column = SIZE / 2;
            }
        }

        // Copy the shuffled image back to the original image
        for (int i = 0; i < SIZE; i++) {
            for (j = 0; j < SIZE; j++) {
                for (int layer = 0; layer < 3; layer++) {
                    image_RGB[i][j][layer] = image_output[i][j][layer];
                }
            }
        }
    }

void RGB_blur_image() {
    unsigned temp_image[SIZE][SIZE][RGB]; // Create a temporary image to store the blurred values

    for (int i = 1; i < SIZE - 1; i++) {
        for (int j = 1; j < SIZE - 1; j++) {
            for (int k = 0; k < RGB; k++) {
                int sum = 0;
                for (int x = -1; x <= 1; x++) {
                    for (int y = -1; y <= 1; y++) {
                        sum += image_RGB[i + x][j + y][k];
                    }
                }
                // Update the temporary image with the averaged value
                temp_image[i][j][k] = sum / 9;
            }
        }
    }

    // Copy the blurred image back to the original
    for (int i = 1; i < SIZE - 1; i++) {
        for (int j = 1; j < SIZE - 1; j++) {
            for (int k = 0; k < RGB; k++) {
                image_RGB[i][j][k] = temp_image[i][j][k];
            }
        }
    }
}

void RGB_crop_image() {
    int x, y, z, l, w, h;
    unsigned char white[SIZE][SIZE][RGB];

    cout << "Please enter x y l w h";
    cin >> x >> y >> z >> l >> w >> h;

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j){
            for (int k = 0; k < RGB; ++k) {
                white[i][j][k] = 255;
            }
        }
    }

    for (int i = x; i < x + w; i++) {
        for (int j = y; j < y + l; j++){
            for (int k = 0; k < z + h; ++k) {
                white[i][j][k] = image_RGB[i][j][k];
            }
        }
    }

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j){
            for (int k = 0; k < RGB ; ++k) {
                image_RGB[i][j][k] = white[i][j][k];
        }
    }
}
}

void RGB_skew_horizontally() {
    double skew_angle;
    cout << "Please enter degree to skew right: ";
    cin >> skew_angle;
    unsigned char output_image[SIZE][SIZE][RGB] = {}; // Initialize the temporary image array
    double skew_distance = tan(skew_angle * M_PI / 180.0) * SIZE; // Calculate the distance to remove
    double shrink = (double) SIZE / (SIZE - skew_distance); // Calculate the shrink ratio
    double step = skew_distance / 256; // Calculate the step size for skewing
    double current_position = 0, skew_adjustment = 0;

// Iterate through each row of the image
    for (int i = 0; i < SIZE; ++i) {
        current_position = 0;

        // Iterate through each column in the temporary image
        for (int j = static_cast<int>(skew_distance - skew_adjustment); j < SIZE - skew_adjustment; ++j) {
            int avg_r = 0, avg_g = 0, avg_b = 0, pixel_count = 0;

            // Iterate through the original image to calculate the average in the skewed region for each channel
            for (int k = max(0, static_cast<int>(ceil(current_position - shrink)));
                 k < min(SIZE, static_cast<int>(ceil(current_position + shrink))); ++k, ++pixel_count) {
                avg_r += image_RGB[i][k][0]; // Add the red value
                avg_g += image_RGB[i][k][1]; // Add the green value
                avg_b += image_RGB[i][k][2]; // Add the blue value
            }

            // Calculate the average value and assign it to the temporary image for each channel
            if (pixel_count > 0) {
                avg_r /= pixel_count;
                avg_g /= pixel_count;
                avg_b /= pixel_count;
            }
            output_image[i][j][0] = static_cast<unsigned char>(avg_r);
            output_image[i][j][1] = static_cast<unsigned char>(avg_g);
            output_image[i][j][2] = static_cast<unsigned char>(avg_b);
            current_position += shrink;
        }
        skew_adjustment += step;
    }

// Copy the temporary image back to the original image
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image_RGB[i][j][0] = output_image[i][j][0];
            image_RGB[i][j][1] = output_image[i][j][1];
            image_RGB[i][j][2] = output_image[i][j][2];
        }
    }
}

void RGB_skew_vertically() {
    double skew_angle;
    cout << "Please enter degree to skew up: ";
    cin >> skew_angle;
    unsigned char output_image[SIZE][SIZE][RGB] = {}; // Initialize the temporary image array
    double skew_distance = tan(skew_angle * M_PI / 180.0) * SIZE; // Calculate the distance to remove
    double shrink = (double) SIZE / (SIZE - skew_distance); // Calculate the shrink ratio
    double step = skew_distance / 256; // Calculate the step size for skewing
    double current_position = 0, skew_adjustment = 0;

// Iterate through each column of the image
    for (int i = 0; i < SIZE; ++i) {
        current_position = 0;

        // Iterate through each row in the temporary image
       for (int j = static_cast<int>(skew_distance - skew_adjustment); j < SIZE - skew_adjustment; ++j) {
            int avg_r = 0, avg_g = 0, avg_b = 0, pixel_count = 0;

            // Iterate through the original image to calculate the average in the skewed region for each channel
            for (int k = max(0, static_cast<int>(ceil(current_position - shrink)));
            k < min(SIZE, static_cast<int>(ceil(current_position + shrink))); ++k, ++pixel_count) {
                avg_r += image_RGB[k][i][0]; // Add the red value
                avg_g += image_RGB[k][i][1]; // Add the green value
                avg_b += image_RGB[k][i][2]; // Add the blue value
               }

            // Calculate the average value and assign it to the temporary image for each channel
            if (pixel_count > 0) {
                avg_r /= pixel_count;
                avg_g /= pixel_count;
                avg_b /= pixel_count;
                }
            output_image[j][i][0] = static_cast<unsigned char>(avg_r);
            output_image[j][i][1] = static_cast<unsigned char>(avg_g);
            output_image[j][i][2] = static_cast<unsigned char>(avg_b);
            current_position += shrink;
            }
        skew_adjustment += step;
        }

// Copy the temporary image back to the original image
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image_RGB[i][j][0] = output_image[i][j][0];
            image_RGB[i][j][1] = output_image[i][j][1];
            image_RGB[i][j][2] = output_image[i][j][2];
            }
        }
}

int main() {
    //checking if the file is RGB or GS
    string s;
    cout<<"Is the color mode of the image RGB or GS?";
    cin>> s;

    if(s=="RGB" || s=="rgb"){
        cout << "Ahlan ya user ya habibi \n";
        loadRGBImage();
        cout << "Please select a filter to apply or 0 to exit:\n"
                "\n"
                "1-\tBlack & White Filter\n"
                "2-\tInvert Filter\n"
                "3-\tMerge Filter \n"
                "4-\tFlip Image\n"
                "5-\tRotate Image\n"
                "6-\tDarken and Lighten Image\n"
                "7-\tDetect Image Edges\n"
                "8-\tEnlarge Image\n"
                "9-\tShrink Image\n"
                "10-\tMirror Image\n"
                "11-\tShuffle Image\n"
                "12-\tBlur Image\n"
                "13-\tCrop Image\n"
                "14-\tSkew Horizontally\n"
                "15-\tSkew Vertically\n";

        int input;
        cin >> input;
        if (input == 1) {
            RGB_black_and_white();
        } else if (input == 2) {
            RGB_to_invert_image();
        } else if (input == 3) {
            RGB_merge_images();
        } else if (input == 4) {
            RGB_flip_image();
        } else if (input == 5) {
            RGB_rotate_image();
        } else if (input == 6) {
            RGB_darken_and_lighten_image();
        } else if (input == 7) {
            RGB_detect_image_edge();
        } else if (input == 8) {
            RGB_enlarge_image();
        } else if (input == 9) {
            RGB_shrink_image();
        } else if (input == 10) {
            RGB_mirror_image();
        } else if (input == 11) {
            RGB_shuffle_image();
        } else if (input == 12) {
            RGB_blur_image();
        } else if (input == 13) {
            RGB_crop_image();
        } else if (input == 14) {
            RGB_skew_horizontally();
        } else if (input == 15) {
            RGB_skew_vertically();
        } else {
            return 0;
        }
        saveRGBImage();
    }

    else if (s== "GS" || s=="gs")
        {
            cout << "Ahlan ya user ya habibi \n";
            loadImage();
            cout << "Please select a filter to apply or 0 to exit:\n"
                    "\n"
                    "1-\tBlack & White Filter\n"
                    "2-\tInvert Filter\n"
                    "3-\tMerge Filter \n"
                    "4-\tFlip Image\n"
                    "5-\tRotate Image\n"
                    "6-\tDarken and Lighten Image\n"
                    "7-\tDetect Image Edges\n"
                    "8-\tEnlarge Image\n"
                    "9-\tShrink Image\n"
                    "10-\tMirror Image\n"
                    "11-\tShuffle Image\n"
                    "12-\tBlur Image\n"
                    "13-\tCrop Image\n"
                    "14-\tSkew Horizontally\n"
                    "15-\tSkew Vertically\n";

            int input;
            cin >> input;

            if (input == 1) {
                black_and_white();
            } else if (input == 2) {
                invert_image();
            } else if (input == 3) {
                merge_images();
            } else if (input == 4) {
                flip_image();
            } else if (input == 5) {
                rotate_image();
            } else if (input == 6) {
                darken_and_lighten_image();
            } else if (input == 7) {
                detect_image_edge();
            } else if (input == 8) {
                enlarge_image();
            } else if (input == 9) {
                shrink_image();
            } else if (input == 10) {
                mirror_image();
            } else if (input == 11) {
                shuffle_image();
            } else if (input == 12) {
                blur_image();
            } else if (input == 13) {
                crop_image();
            } else if (input == 14) {
                skew_horizontally();
            } else if (input == 15) {
                skew_vertically();
            } else {
                return 0;
            }
            saveImage();
        }

    return 0;
}
