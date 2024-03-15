#include "frontend/Option.h"

Option::Option(SignalStrategy *signalStrategy, const std::string &title) : title(title), signalStrategy(signalStrategy) {
    visibility = false;
}