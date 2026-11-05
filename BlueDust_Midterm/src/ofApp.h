#pragma once
#include "ofMain.h"

struct Cell {
    glm::vec2 pos;     // esquina superior izquierda de su hueco
    ofColor col;       // color del pixel de la foto
    float tStart;      // segundo en que se "rompe"
    float fallDur;     // segundos que tarda en salir de pantalla
    float drift;       // deriva horizontal (px/s)
    bool falls;        // true = cae, false = se desvanece
    int glitterId;     // textura de purpurina de su hueco
};

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    void buildGlitter();

    ofImage photo;
    std::vector<Cell> cells;
    std::vector<ofImage> glitter;

    int   cellSize = 12;
    float timeNow = 0;
    float fps = 30;

    // --- calendario ---
    float introTime = 10;    // foto quieta
    float lastStart = 155;   // último inicio posible (160 - fallDur máx)
    float kCurve = 2.0f;  // 1 = ritmo constante, >1 = acelera
    float fallProb = 0.6f;  // probabilidad de caer (resto: desvanece)
};