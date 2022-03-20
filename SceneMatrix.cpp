#include "SceneMatrix.hpp"

inline SceneMatrix::SceneMatrix() {
#ifdef DEBUG
    std::wcout << L"SceneMatrix()" << std::endl;
#endif // DEBUG
}

inline SceneMatrix::~SceneMatrix() {
#ifdef DEBUG
    std::wcout << L"~SceneMatrix()" << std::endl;
#endif // DEBUG
}

inline void SceneMatrix::run() override {
    for(uint8_t i = 0; i < MATRIX_COUNT; i++)
        matrix_[i].create(context);

    context->create();
    while(context->isActual()) {
        context->autoClock();
        context->autoEvent();

        for(uint8_t i = 0; i < MATRIX_COUNT; i++)
            matrix_[i].update();

        context->window.clear(sf::Color(0, 0, 0, 128));
        for(uint8_t i = 0; i < MATRIX_COUNT; i++)
            matrix_[i].draw();
        context->window.display();
    }
}
