#ifndef CLIENT_IWIDGET_HPP
#define CLIENT_IWIDGET_HPP

template<typename T>
class IWidget {
public:
    void Draw(){ Derrived().DrawImpl();}

private:
    T& Derrived(){return *reinterpret_cast<T*>(this);}
};

#endif  // CLIENT_IWIDGET_HPP
