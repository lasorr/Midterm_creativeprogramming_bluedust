#include "ofApp.h"

void ofApp::setup() {
    ofSetFrameRate(fps);
    ofSetRandomSeed(42); // misma secuencia siempre (útil para exportar)

    photo.load("foto.jpg");                       // en bin/data/
    photo.resize(ofGetWidth(), ofGetHeight());

    buildGlitter();

    int cols = ofGetWidth() / cellSize;
    int rows = ofGetHeight() / cellSize;
    float span = lastStart - introTime;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            Cell cell;
            cell.pos = { float(c * cellSize), float(r * cellSize) };
            cell.col = photo.getColor(c * cellSize + cellSize / 2,
                r * cellSize + cellSize / 2);
            float u = ofRandom(1.0f);
            cell.tStart = introTime + span * pow(u, 1.0f / kCurve);
            cell.fallDur = ofRandom(2.5f, 4.5f);
            cell.drift = ofRandom(-30, 30);
            cell.falls = ofRandom(1.0f) < fallProb;
            cell.glitterId = int(ofRandom(glitter.size()));
            cells.push_back(cell);
        }
    }

    // música de fondo
    music.load("cancion.mp3");
    music.setLoop(false);
    music.setVolume(0.8f);
    music.play();
}

void ofApp::buildGlitter() {
    // 6 variantes de tile de purpurina, generadas por código
    for (int v = 0; v < 6; v++) {
        ofPixels pix;
        pix.allocate(cellSize, cellSize, OF_PIXELS_RGBA);
        ofColor base = ofColor::fromHsb(ofRandom(120, 170), 140, 200); // tonos azules
        for (int y = 0; y < cellSize; y++) {
            for (int x = 0; x < cellSize; x++) {
                float n = ofRandom(1.0f);
                ofColor col;
                if (n > 0.94f)  col = ofColor(255, 240, 200);       // destello dorado/blanco
                else            col = base * (0.4f + ofRandom(0.6f));
                col.a = 255;
                pix.setColor(x, y, col);
            }
        }
        ofImage img;
        img.setFromPixels(pix);
        glitter.push_back(img);
    }
}

void ofApp::update() {
    // tiempo por contador de frames: determinista al exportar
    timeNow = ofGetFrameNum() / fps;
}

void ofApp::draw() {
    ofBackground(0);
    float H = ofGetHeight();

    // Pasada 1: huecos (pixel quieto / purpurina / desvanecimiento)
    for (auto& c : cells) {
        float t = timeNow - c.tStart;
        if (t < 0) {
            ofSetColor(c.col);
            ofDrawRectangle(c.pos.x, c.pos.y, cellSize, cellSize);
        }
        else {
            // purpurina que aparece y brilla suavemente
            float fade = ofClamp(t / 0.6f, 0.0f, 1.0f);
            float shimmer = 0.75f + 0.25f * sin(timeNow * 6.0f + c.pos.x * 0.1f + c.pos.y * 0.13f);
            ofSetColor(255, 255 * fade * shimmer);
            glitter[c.glitterId].draw(c.pos.x, c.pos.y);

            // los que no caen: el pixel se desvanece encima
            if (!c.falls && t < 0.5f) {
                ofSetColor(c.col, 255 * (1.0f - t / 0.5f));
                ofDrawRectangle(c.pos.x, c.pos.y, cellSize, cellSize);
            }
        }
    }

    // Pasada 2: pixeles cayendo (encima de todo)
    for (auto& c : cells) {
        float t = timeNow - c.tStart;
        if (c.falls && t >= 0 && t < c.fallDur) {
            // gravedad calibrada: llega al fondo justo en fallDur
            float g = 2.0f * (H + cellSize) / (c.fallDur * c.fallDur);
            float y = c.pos.y + 0.5f * g * t * t;
            float x = c.pos.x + c.drift * t;
            ofSetColor(c.col);
            ofDrawRectangle(x, y, cellSize, cellSize);
        }
    }
}