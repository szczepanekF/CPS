
#pragma once


class Window {
public:
    explicit Window(int m);
    virtual ~Window() = default;
    virtual double w(int n) = 0;

protected:
    int M;
};
