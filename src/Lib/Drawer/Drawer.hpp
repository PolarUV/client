#ifndef CLIENT_DRAWER_HPP
#define CLIENT_DRAWER_HPP

#include <QPainter>
#include <functional>

namespace lib {
    class Painter {
    private:
        QPainter painter_{};
        size_t width_{}, height_{};
    public:

        inline Painter &SetRenderHint(QPainter::RenderHint hint, bool flag = true) {
            painter_.setRenderHint(hint, flag);
            return *this;
        }

        inline Painter &SetResolution(int width, int height) {
            width_ = width;
            height_ = height;
            return *this;
        }

        template<typename Func, typename ... Args>
        inline Painter &Draw(Func func, Args &&... args) {
            func(painter_, width_, height_, std::forward<Args>(args)...);
            return *this;
        }

        inline Painter &DrawImage(int x, int y, const QImage &img) {
            painter_.drawImage(QPointF(x, y), img);
            return *this;
        }

        inline Painter &DrawImage(int x, int y, const QImage &img, float angle) {
            painter_.rotate(angle);
            painter_.drawImage(QPointF(x, y), img);
            painter_.rotate(-angle);
            return *this;
        }

        inline Painter &DrawImage(int x, int y, const QImage &img, int sx, int sy, int sw, int sh,
                                  Qt::ImageConversionFlags flags = Qt::AutoColor) {
            painter_.drawImage(x, y, img, sx, sy, sw, sh, flags);
            return *this;
        }

        inline Painter &Begin(QPaintDevice *obj) {
            painter_.begin(obj);
            return *this;
        }

        inline void End() {
            painter_.end();
        }
    };
}
#endif