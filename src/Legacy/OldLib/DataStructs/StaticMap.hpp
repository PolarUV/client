#ifndef CLIENT_STATICMAP_HPP
#define CLIENT_STATICMAP_HPP

#include <array>
#include <cstddef>
#include <type_traits>
#include <utility>

namespace lib {
    template<typename Key, typename Value, size_t Size> requires std::is_enum_v<Key>
    class StaticMap {
    public:

        using Key_t = Key;
        using Value_t = Value;
        using Pair_t = std::pair<Key, Value>;

        StaticMap(std::initializer_list<Pair_t> list) {
            for (auto&&[key, value]: list) {
                operator[](key) = value;
            }
        }

        StaticMap() = default;

        const Value &operator[](Key key) const {
            return array_[static_cast<size_t>(key)];
        }

        Value &operator[](Key key) {
            return array_[static_cast<size_t>(key)];
        }

    private:
        std::array<Value, Size> array_{};
    };

}

#endif
