#include <string>
#include "signals/SignalStrategy.h"

class Option {
public:
    Option(SignalStrategy *signalStrategy, const std::string &title);

    std::string title;
    bool visibility{};
    SignalStrategy* signalStrategy{};
};


