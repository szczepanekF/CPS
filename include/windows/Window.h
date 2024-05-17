
#pragma once


class Window {
public:
    explicit Window(int m);

    virtual double w(int n) = 0;

    virtual ~Window();

protected:
    int M;
};
