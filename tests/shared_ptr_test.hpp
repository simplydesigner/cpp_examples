#ifndef memory_test_hpp
#define memory_test_hpp

namespace ns_memory {

    class object final {
    private:
        bool& alive_;
    public:
         object(bool& alive);
        ~object();
    };
}

#endif
