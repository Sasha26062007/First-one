#include "KeyProcessor.hpp"

Mode KeyProcessor::processKey(int key, Mode currentMode) {
    switch (key) {
        case '1': return Mode::NORMAL;
        case '2': return Mode::INVERT;
        case '3': return Mode::BLUR;
        case '4': return Mode::CANNY;
        default: return currentMode;
    }
}
