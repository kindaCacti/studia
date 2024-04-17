#include <bits/stdc++.h>

using namespace std;

struct Pixel{
    int red, green, blue;

    Pixel(int r, int g, int b): red(r), green(g), blue(b){
    }

    string stringify(){
        return "{"+to_string(red)+","+to_string(green)+","+to_string(blue)+"}";
    }

    bool operator==(Pixel& left){
        if(left.red == red and left.green == green and left.blue == blue){
            return true;
        }
        return false;
    }

    bool operator!=(Pixel& left){
        return !((*this) == left);
    }
};

vector<unsigned char> readData;
vector<vector<Pixel>> pixels;
int width = 320;

bool checkMarker(int sx, int sy){
    Pixel markerColor(0,0,0);
    if(pixels[sy][sx] != markerColor) return false;

    int hgt = 0;
    int lhgt = 0;
    int bhgt = 0;
    int n = pixels.size();
    int cx = sx;

    bool hasStepDown = false;
    if(sx-1 >= 0 and pixels[sy][cx-1] == markerColor) return false;
    if(sy-1 >= 0 and pixels[sy-1][cx] == markerColor) return false;

    while(true){
        hgt = 0;
        if(cx == width) break; //don't go outside the image
        if(pixels[sy][cx] != markerColor) break; //are we still on the marker?

        for(int i = sy; i<pixels.size(); i++){
            if(pixels[i][cx] != markerColor) break;
            hgt++;
        }

        if(lhgt != 0 and hgt != lhgt){
            if(hasStepDown) return false;
            hasStepDown = true;
            bhgt = lhgt;
        }

        lhgt = hgt;
        cx++;
    }
    
    int wdt = cx - sx;
    bool out = (((wdt == bhgt/2)|(wdt == (bhgt+1)/2))&hasStepDown);
    if(out){
        cout<<sx<<"x"<<sy<<":haha "<<wdt<<" : "<<bhgt<<endl;
    }
    return out;
}

int main(){
    ifstream fin("example_markers.bmp");
    unsigned char a;
    int ns = -1;
    while(fin>>a){
        readData.push_back(a);
    }
    fin.close();
    int startingPosition = readData[10] - 2;

    cout<<startingPosition<<endl;

    //width 320px, height 240 px,
    int moved = 0;
    for(int i = startingPosition; i<readData.size();){
        pixels.push_back({});
        for(int j = i, k = 0; k<width; j+=3, k++){
            pixels.back().push_back(Pixel(readData[j+2], readData[j+1], readData[j]));
            moved += 3;
            i = j+3;
        }
        if(moved % 4){
            i += (4-(moved%4));
        }
    }

    reverse(pixels.begin(), pixels.end());


    cout<<pixels.back()[0].stringify()<<endl;

    cout<<pixels.size()<<"x"<<pixels[0].size()<<endl;

    for(int i = 0; i<pixels.size(); i++){
        for(int j = 0; j<pixels[i].size(); j++){
            bool chk = checkMarker(j, i);
            Pixel markerColor(0,0,0);
            if(chk){
                cout<<"marker found: "<<j<<"x"<<i<<endl;
            }
        }
    }

    return 0;
}