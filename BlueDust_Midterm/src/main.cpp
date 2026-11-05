#include "ofMain.h"
#include "ofApp.h"

int main() {
    ofGLWindowSettings settings;
    settings.setSize(1920, 1080);
    settings.windowMode = OF_WINDOW;   // OF_FULLSCREEN para pantalla completa
    settings.setGLVersion(3, 2);       // deja la versión que te generó el Project Generator

    ofCreateWindow(settings);
    ofRunApp(new ofApp());
}