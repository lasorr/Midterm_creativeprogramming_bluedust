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
    void drawScene();

    ofImage photo;
    std::vector<Cell> cells;
    std::vector<ofImage> glitter;

    // --- salida (resolución del vídeo, independiente de la ventana) ---
    int outW = 1920;
    int outH = 1080;
    ofFbo fbo;

    int   cellSize = 12;
    float timeNow = 0;
    float fps = 30;
    int   frame = 0;          // contador propio de frames

    // --- calendario ---
    float introTime = 10;     // foto quieta
    float lastStart = 155;    // último inicio posible (160 - fallDur máx)
    float kCurve = 2.0f;      // 1 = ritmo constante, >1 = acelera
    float fallProb = 0.6f;    // probabilidad de caer (resto: desvanece)

    // --- grabación ---
    bool  recording = false;  // true = exporta frames y NO suena la música
    float totalTime = 160;    // duración total (s)

    // --- audio ---
    ofSoundPlayer music;
};