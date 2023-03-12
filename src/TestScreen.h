#pragma once

#include "ScreenManager.h"

class TestScreen : public Screen {
public:
    void init() override;
    void update(float deltaTime) override;
    void render() override;
    void dispose() override;
};
