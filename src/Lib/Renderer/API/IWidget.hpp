#ifndef CLIENT_IWIDGET_HPP
#define CLIENT_IWIDGET_HPP

class IWidget {
   public:
    virtual void Draw() = 0;
    virtual ~IWidget() = default;
};

#endif  // CLIENT_IWIDGET_HPP
