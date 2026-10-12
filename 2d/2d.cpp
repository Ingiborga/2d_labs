// 2d.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS

#define STB_IMAGE_IMPLEMENTATION
#include "D:/proj/2d/2d/2d/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "D:/proj/2d/2d/2d/stb_image_write.h"
#include <iostream>
#include <fstream> 
#include <string> 
#include <vector>

using namespace std;

void save_picture(string path, string name, int x, int y, int n, const void* data) {
    int ans=stbi_write_png((path+name).c_str(), x,  y,  n, data,x*n);
    return;
}

void b_w(unsigned char* cur_in,unsigned char* cur_to, int x, int y, int n) {
    int cur_bit = 0;
    while (cur_bit < x * y) {
        unsigned char* r = cur_in;
        unsigned char* g = cur_in + 1;
        unsigned char* b = cur_in + 2;
        unsigned char* r_1 = cur_to;
        unsigned char* g_1 = cur_to + 1;
        unsigned char* b_1 = cur_to + 2;
        unsigned char gray = static_cast<unsigned char>(0.299 * (*r) + 0.587 * (*g) + 0.114 * (*b));
        *r_1 = gray;
        *g_1 = gray;
        *b_1 = gray;
        cur_in += n;
        cur_to += n;
        cur_bit++;
    }
    cout << "deleted colors\n";
}
void sepia(unsigned char* cur_in, unsigned char* cur_to, int x, int y, int n) {
    int cur_bit = 0;
    while (cur_bit < x * y) {
        unsigned char* r = cur_in;
        unsigned char* g = cur_in + 1;
        unsigned char* b = cur_in + 2;
        unsigned char* r_1 = cur_to;
        unsigned char* g_1 = cur_to + 1;
        unsigned char* b_1 = cur_to + 2;
        unsigned char new_r = (0.300 * (*r) + 0.769 * (*g) + 0.189 * (*b)>=255)? 255 : static_cast<unsigned char>(0.300 * (*r) + 0.769 * (*g) + 0.189 * (*b));
        unsigned char new_g = (0.349 * (*r) + 0.686 * (*g) + 0.186 * 0>=255)? 255: static_cast<unsigned char>(0.349 * (*r) + 0.686 *(* g) + 0.186 * 0);
        unsigned char new_b = (0.272 * (*r) + 0.534 * (*g) + 0.131 * (*b)>=255)? 255 : static_cast<unsigned char>(0.272 * (*r) + 0.534 * (*g) + 0.131 * (*b));
        *r_1 = (new_r>=255) ? 255 : new_r;
        *g_1 = (new_g >= 255) ? 255 : new_g;
        *b_1 = (new_b >= 255) ? 255 : new_b;
        cur_in += n;
        cur_to += n;
        cur_bit++;
    }
    cout << "made it sepia\n";
}
void gauss(unsigned char* cur_in, unsigned char* cur_to, int x, int y, int n) {

}

int main(int argc, char* argv[])
{
    string filename;
    string path = "D:/proj/2d/2d/";
    cout << "type file name\n";
    cin >> filename;
    int x,y,n;

    unsigned char* data = stbi_load((path+filename).c_str(), &x, &y, &n, 0);
    if (data == NULL) {
        cout << "Cannot load image: " << stbi_failure_reason() << endl;
        return -1;
    }
    size_t size = (size_t)x * y * n;
    std::vector<unsigned char> out_data(data, data + size);
    const void* data_u = out_data.data();

    //чб
    b_w(data, out_data.data(), x, y, n);

    save_picture(path, "b_w.png", x, y, n, data_u);
    //сепия
    sepia(data, out_data.data(), x, y, n);
    save_picture(path, "sepia.png", x, y, n, data_u);
    //Размытие по Гаусс
    //gauss(data, out_data.data(), x, y, n);
    return -1;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
