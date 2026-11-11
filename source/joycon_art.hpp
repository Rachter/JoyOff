#pragma once

// Front-view outline adapted from 0 Noctis 0's Joy-Con illustration (CC BY-SA 4.0).
// See COPYING.ART for the reference, attribution, and adaptation details.
void JoyConOutline(NVGcontext* vg, bool right) {
    nvgSave(vg);
    if (right) { nvgTranslate(vg, 136.512f, 0); nvgScale(vg, -1, 1); }
    nvgBeginPath(vg);
    nvgMoveTo(vg, 136.512f, 3.25f);
    nvgLineTo(vg, 136.512f, 415.937f);
    nvgBezierTo(vg, 136.512f, 416.961f, 136.006f, 417.734f, 134.715f, 417.734f);
    nvgLineTo(vg, 85.075f, 417.734f);
    nvgBezierTo(vg, 33.395f, 417.734f, 0, 372.036f, 0, 332.659f);
    nvgLineTo(vg, 0, 84.719f);
    nvgBezierTo(vg, 0, 26.834f, 56.764f, 0, 84.719f, 0);
    nvgLineTo(vg, 133.509f, 0);
    nvgBezierTo(vg, 135.995f, 0, 136.512f, 1.368f, 136.512f, 3.25f);
    nvgClosePath(vg);
    nvgRestore(vg);
}

NVGcolor ControllerColor(u32 rgba) {
    return nvgRGB(rgba & 0xff, (rgba >> 8) & 0xff, (rgba >> 16) & 0xff);
}

void JoyConIcon(NVGcontext* vg, float x, float y, float scale, bool right,
    bool colorsKnown, u32 bodyColor, u32 buttonsColor) {
    nvgSave(vg);
    nvgTranslate(vg, x, y);
    nvgScale(vg, scale * 0.7f, scale * 0.7f);
    const NVGcolor body = colorsKnown ? ControllerColor(bodyColor) : nvgRGB(76, 88, 96);
    const NVGcolor controls = colorsKnown ? ControllerColor(buttonsColor) : nvgRGB(40, 45, 50);
    const NVGcolor legend = (controls.r * 0.299f + controls.g * 0.587f + controls.b * 0.114f) > 0.55f
        ? nvgRGB(25, 29, 32) : nvgRGB(211, 216, 219);
    // Shoulder cap follows the outer curve, leaving the inner rail edge straight.
    nvgSave(vg);
    if (right) { nvgTranslate(vg, 136.512f, 0); nvgScale(vg, -1, 1); }
    nvgBeginPath(vg);
    nvgMoveTo(vg, 7, 65);
    nvgBezierTo(vg, 11, 22, 47, -7, 86, -7);
    nvgLineTo(vg, 120, -7);
    nvgStrokeColor(vg, controls);
    nvgStrokeWidth(vg, 10);
    nvgLineCap(vg, NVG_ROUND);
    nvgStroke(vg);
    nvgRestore(vg);
    nvgSave(vg);
    nvgTranslate(vg, 3, 5);
    JoyConOutline(vg, right);
    nvgFillColor(vg, nvgRGBA(0, 0, 0, 50));
    nvgFill(vg);
    nvgRestore(vg);
    Rectangle(vg, right ? -3 : 134, 17, 5, 380, nvgRGB(48, 54, 58), 2);
    JoyConOutline(vg, right);
    nvgFillColor(vg, body);
    nvgFill(vg);
    nvgStrokeColor(vg, nvgRGBA(235, 240, 242, 80));
    nvgStrokeWidth(vg, 1.6f);
    nvgStroke(vg);

    const float centerX = right ? 63.94f : 72.33f;
    const float stickY = right ? 221.34f : 108.34f;
    Circle(vg, centerX, stickY, 32.06f, controls);
    Circle(vg, centerX, stickY, 24.7f, nvgLerpRGBA(controls, nvgRGB(255, 255, 255), 0.07f));
    nvgBeginPath(vg);
    nvgCircle(vg, centerX, stickY, 24.7f);
    nvgStrokeColor(vg, nvgLerpRGBA(controls, nvgRGB(255, 255, 255), 0.28f));
    nvgStrokeWidth(vg, 1.5f);
    nvgStroke(vg);

    const float buttonsY = right ? 105.0f : 226.2f;
    const float spacing = 31.31f;
    const float px[] = {centerX, centerX + spacing, centerX, centerX - spacing};
    const float py[] = {buttonsY - spacing, buttonsY, buttonsY + spacing, buttonsY};
    const char* letters[] = {"X", "A", "B", "Y"};
    for (int i = 0; i < 4; ++i) {
        Circle(vg, px[i], py[i], 15.15f, controls);
        if (right) {
            nvgFontFace(vg, "switch-standard");
            nvgFontSize(vg, 14);
            nvgTextAlign(vg, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);
            nvgFillColor(vg, legend);
            nvgText(vg, px[i], py[i], letters[i], nullptr);
        } else {
            nvgSave(vg);
            nvgTranslate(vg, px[i], py[i]);
            nvgRotate(vg, i * 1.570796327f);
            nvgBeginPath(vg);
            nvgMoveTo(vg, 0, -6);
            nvgLineTo(vg, 5, 3);
            nvgLineTo(vg, -5, 3);
            nvgClosePath(vg);
            nvgFillColor(vg, legend);
            nvgFill(vg);
            nvgRestore(vg);
        }
    }
    if (right) {
        Line(vg, 22, 48, 46, 48, controls, 6);
        Line(vg, 34, 36, 34, 60, controls, 6);
        Circle(vg, 41, 300, 17, nvgLerpRGBA(controls, legend, 0.35f));
        Circle(vg, 41, 300, 13.3f, controls);
        nvgBeginPath(vg);
        nvgMoveTo(vg, 33, 300);
        nvgLineTo(vg, 41, 293);
        nvgLineTo(vg, 49, 300);
        nvgLineTo(vg, 47, 300);
        nvgLineTo(vg, 47, 307);
        nvgLineTo(vg, 35, 307);
        nvgLineTo(vg, 35, 300);
        nvgClosePath(vg);
        nvgFillColor(vg, legend);
        nvgFill(vg);
    } else {
        Rectangle(vg, 101, 45, 24, 6, controls, 1);
        Rectangle(vg, 82, 292, 27, 27, controls, 4);
        Circle(vg, 95.5f, 305.5f, 8.5f, legend);
        Circle(vg, 95.5f, 305.5f, 6.2f, controls);
    }
    nvgRestore(vg);
}

// Simplified front view of a Pro Controller, drawn for JoyOff in a 200 x 140 unit box.
constexpr float ProIconWidth = 200, ProIconHeight = 140;

void ProControllerOutline(NVGcontext* vg) {
    nvgBeginPath(vg);
    nvgMoveTo(vg, 60, 8);
    nvgLineTo(vg, 140, 8);
    nvgBezierTo(vg, 170, 8, 188, 18, 194, 44);
    nvgBezierTo(vg, 200, 72, 200, 110, 190, 128);
    nvgBezierTo(vg, 182, 142, 160, 142, 152, 128);
    nvgBezierTo(vg, 144, 114, 136, 100, 120, 100);
    nvgLineTo(vg, 80, 100);
    nvgBezierTo(vg, 64, 100, 56, 114, 48, 128);
    nvgBezierTo(vg, 40, 142, 18, 142, 10, 128);
    nvgBezierTo(vg, 0, 110, 0, 72, 6, 44);
    nvgBezierTo(vg, 12, 18, 30, 8, 60, 8);
    nvgClosePath(vg);
}

void ProControllerIcon(NVGcontext* vg, float x, float y, float scale,
    bool colorsKnown, u32 bodyColor, u32 buttonsColor) {
    nvgSave(vg);
    nvgTranslate(vg, x, y);
    nvgScale(vg, scale, scale);
    const NVGcolor body = colorsKnown ? ControllerColor(bodyColor) : nvgRGB(76, 88, 96);
    const NVGcolor controls = colorsKnown ? ControllerColor(buttonsColor) : nvgRGB(40, 45, 50);
    const NVGcolor legend = (controls.r * 0.299f + controls.g * 0.587f + controls.b * 0.114f) > 0.55f
        ? nvgRGB(25, 29, 32) : nvgRGB(211, 216, 219);
    // Shoulder buttons along the top edge.
    for (int side = 0; side < 2; ++side) {
        nvgSave(vg);
        if (side) { nvgTranslate(vg, ProIconWidth, 0); nvgScale(vg, -1, 1); }
        nvgBeginPath(vg);
        nvgMoveTo(vg, 10, 34);
        nvgBezierTo(vg, 18, 12, 36, 4, 66, 4);
        nvgStrokeColor(vg, nvgLerpRGBA(body, nvgRGB(0, 0, 0), 0.35f));
        nvgStrokeWidth(vg, 7);
        nvgLineCap(vg, NVG_ROUND);
        nvgStroke(vg);
        nvgRestore(vg);
    }
    nvgSave(vg);
    nvgTranslate(vg, 2, 4);
    ProControllerOutline(vg);
    nvgFillColor(vg, nvgRGBA(0, 0, 0, 50));
    nvgFill(vg);
    nvgRestore(vg);
    ProControllerOutline(vg);
    nvgFillColor(vg, body);
    nvgFill(vg);
    nvgStrokeColor(vg, nvgRGBA(235, 240, 242, 80));
    nvgStrokeWidth(vg, 1.4f);
    nvgStroke(vg);

    const auto stick = [&](float cx, float cy) {
        Circle(vg, cx, cy, 15, controls);
        Circle(vg, cx, cy, 11.5f, nvgLerpRGBA(controls, nvgRGB(255, 255, 255), 0.07f));
        nvgBeginPath(vg);
        nvgCircle(vg, cx, cy, 11.5f);
        nvgStrokeColor(vg, nvgLerpRGBA(controls, nvgRGB(255, 255, 255), 0.28f));
        nvgStrokeWidth(vg, 1.2f);
        nvgStroke(vg);
    };
    stick(50, 48);
    stick(124, 78);

    // D-pad.
    Rectangle(vg, 65, 74.5f, 26, 9, controls, 2);
    Rectangle(vg, 73.5f, 66, 9, 26, controls, 2);

    // A/B/X/Y.
    const float bx = 150, by = 48, spacing = 13;
    const float px[] = {bx, bx + spacing, bx, bx - spacing};
    const float py[] = {by - spacing, by, by + spacing, by};
    const char* letters[] = {"X", "A", "B", "Y"};
    for (int i = 0; i < 4; ++i) {
        Circle(vg, px[i], py[i], 7, controls);
        nvgFontFace(vg, "switch-standard");
        nvgFontSize(vg, 8);
        nvgTextAlign(vg, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);
        nvgFillColor(vg, legend);
        nvgText(vg, px[i], py[i] + 0.5f, letters[i], nullptr);
    }

    // Minus / Plus, Capture / Home.
    Line(vg, 80, 28, 88, 28, controls, 3);
    Line(vg, 112, 28, 120, 28, controls, 3);
    Line(vg, 116, 24, 116, 32, controls, 3);
    Rectangle(vg, 86, 40, 9, 9, controls, 2);
    Circle(vg, 90.5f, 44.5f, 2.6f, legend);
    Circle(vg, 109.5f, 44.5f, 5.5f, nvgLerpRGBA(controls, legend, 0.35f));
    Circle(vg, 109.5f, 44.5f, 4.2f, controls);
    nvgRestore(vg);
}
