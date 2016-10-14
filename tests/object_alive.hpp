#ifndef object_alive_hpp
#define object_alive_hpp

namespace ns_memory {

    class object final {
        bool& alive_;
    public:
         object(bool& alive);
        ~object();

        object(const object&)               = delete;
        object(object&&)                    = delete;
        object& operator=(const object&)    = delete;
        object& operator=(object&&)         = delete;
    };
}

#endif
