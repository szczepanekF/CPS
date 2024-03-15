#include <string>
#include "signals/SignalStrategy.h"

class Option {
public:
    Option(SignalStrategy *signalStrategy, const std::string &title);

    virtual ~Option();

    std::string title;
    bool visibility{};
    SignalStrategy* signalStrategy{};
};

