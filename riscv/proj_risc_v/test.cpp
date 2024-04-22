#include <iostream>
#include <fstream>

using namespace std;

#define width 320
#define height 240
#define bytes_per_pixel 3
#define marker_color 0

string path = "./uwalacz1.bmp";
char* rde;
unsigned char* rd;
int startingPosition;

//instead of pixels use unsigned int int as a pixel
//(already implemented)
unsigned int getPixelFromData(int x, int y){
    int offset = (x + (height - 1 - y) * width) * bytes_per_pixel + startingPosition;

    unsigned int pixel = rd[offset + 2];
    pixel <<= 8;
    pixel |= rd[offset + 1];
    pixel <<= 8;
    pixel |= rd[offset];

    return pixel;
}

int lineHeight(int sx, int sy){
    unsigned int current_pixel;
    int hgt = 0;

    while(true){
        if(sy >= height) break;
        current_pixel = getPixelFromData(sx, sy);
        if(current_pixel != marker_color) break;
        hgt++;
        sy++;
    }

    return hgt;
}

bool isLineNotMarker(int sx, int sy, int ey){
    //outside of the picter is never of a marker type
    if(sx < 0) return true;
    if(sy < 0) return true;

    unsigned int current_pixel;

    while(true){
        if(sy > ey) break;
        current_pixel = getPixelFromData(sx, sy);
        if(current_pixel == marker_color) return false;
        sy++;
    }

    return true;
}

bool checkMarker(int sx, int sy){
    int current_pixel = getPixelFromData(sx, sy);

    if(current_pixel != marker_color) return false;

    int current_x = sx;
    int current_height = lineHeight(sx, sy);
    int last_height = current_height;
    int best_height = current_height;
    bool hasStep = false;
    int step_x = -1;

    bool condition = isLineNotMarker(sx, sy-1, sy-1);
    condition &= isLineNotMarker(sx-1, sy, sy + current_height - 1);

    if(!condition) return false;

    while(true){
        current_x++;
        if(current_x >= width) break;
        current_height = lineHeight(current_x, sy);
        if(current_height == 0) break;
        condition &= isLineNotMarker(current_x, sy-1, sy-1);
        if(!condition) return false;
        if(current_height == last_height) continue;
        if(hasStep) return false;
        hasStep = true;
        last_height = current_height;
        step_x = current_x;
    }

    condition &= hasStep;
    condition &= isLineNotMarker(step_x, sy + last_height, sy + best_height - 1);
    condition &= isLineNotMarker(current_x, sy, sy + last_height - 1);
    int wdt = current_x - sx;
    condition &= (wdt == best_height / 2);

    if(condition) return true;
    return false;
}

int main(){
    ifstream fin(path);
    int siz = 54 + width * height * 3;
    rde = new char[siz];
    rd = new unsigned char[siz];
    fin.get(rde, siz);
    fin.close();

    for(int i = 0; i<siz; i++){
        rd[i] = (unsigned char)rde[i];
    }

   if(rd[0] != 'B' or rd[1] != 'M'){
       cout<<"wrong file format!";
       return 0;
   }

    startingPosition = rd[10];

    cout<<"pixel: "<<getPixelFromData(1,2)<<endl;

    cout<<startingPosition<<endl;

    for(int i = 0; i<width; i++){
        for(int j = 0; j<height; j++){
            if(checkMarker(i, j)){
                cout<<"marker found: "<<i<<"x"<<j<<endl;
            }
        }
    }

    return 0;
}