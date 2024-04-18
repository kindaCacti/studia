#include <iostream>
#include <fstream>

using namespace std;

#define width 320
#define height 240

//path buffer for file in asm
string path = "./example_markers.bmp";
//only one buffer in asm
char* rde;
unsigned char* rd;
//can be saved in register
int startingPosition;

//instead of pixels use unsigned int int as a pixel
unsigned int getPixelFromData(int x, int y){
    int offset = (x + (height - 1 - y) * width) * 3 + startingPosition;

    unsigned int pixel = rd[offset + 2];
    pixel <<= 8;
    pixel |= rd[offset + 1];
    pixel <<= 8;
    pixel |= rd[offset];
    //cout<<pixel<<" : "<<(int)rd[offset + 2]<<", "<<(int)rd[offset + 1]<<", "<<(int)rd[offset + 2]<<endl;
    return pixel;
}

bool checkMarker(int sx, int sy){
    unsigned int markerColor = 0;

    if(getPixelFromData(sx, sy) != markerColor) return false;

    int hgt = 0;
    int lhgt = 0;
    int bhgt = 0;
    int n = height;
    int cx = sx;

    bool hasStepDown = false;
    if(sx-1 >= 0 and getPixelFromData(sx-1, sy) == markerColor) return false;
    if(sy+1 < height and getPixelFromData(sx, sy-1) == markerColor) return false;

    unsigned int currentPixel;

    while(true){
        hgt = 0;
        if(cx == width) break; //don't go outside the image

        currentPixel = getPixelFromData(cx, sy);

        if(currentPixel != markerColor) break; //are we still on the marker?

        for(int i = sy; i<n; i++){
            currentPixel = getPixelFromData(cx, i);
            if(currentPixel != markerColor) break;
            hgt++;
        }

        if(lhgt != 0 and hgt != lhgt){
            if(hasStepDown) return false;
            if(hgt > lhgt) return false;
            hasStepDown = true;
            bhgt = lhgt;
        }

        lhgt = hgt;
        cx++;
    }
    
    int wdt = cx - sx;
    bool out = (((wdt == bhgt/2)|(wdt == (bhgt+1)/2))&hasStepDown);

    return out;
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

    getPixelFromData(1, 1);

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