#ifndef DRAWABLE
#define DRAWABLE

class Window;
// Window calls draw(drawable), and drawable calls required window.draw(x)
class Drawable {
    friend Window;

    protected:
    virtual void draw(Window *window) const = 0;
};

#endif