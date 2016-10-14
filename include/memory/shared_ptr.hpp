#ifndef shared_ptr_hpp
#define shared_ptr_hpp

namespace ns_memory {

    template <typename T>
    class shared_ptr final {
        struct meta_t {
            int count;

            meta_t(const T* cpObject): count(0), object(cpObject) {
            }

            ~meta_t() {
                delete object;
            }
        private:
            const T* object;
        } *meta_;
    public:
        explicit shared_ptr(const T* object = nullptr);
        ~shared_ptr();
        shared_ptr(const shared_ptr& pObject);
        shared_ptr(shared_ptr&& pObject);
        shared_ptr& operator=(const shared_ptr& pObject);
        shared_ptr& operator=(shared_ptr&& pObject);

        void reset();
        void reset(const T *object);
    private:
        void increment();
        void decrement();
    };

    template <typename T>
    void shared_ptr<T>::increment() {
        if (meta_ != nullptr)
            ++meta_->count;
    }

    template <typename T>
    void shared_ptr<T>::decrement() {
        if (meta_ != nullptr && --meta_->count == 0) {
            delete meta_;
            meta_ = nullptr;
        }
    }

    template <typename T>
    shared_ptr<T>::shared_ptr(const T* object) {
        meta_ = object == nullptr
            ? nullptr
            : new meta_t{object};
        increment();
    }

    template <typename T>
    shared_ptr<T>::~shared_ptr() {
        decrement();
    }

    template <typename T>
    shared_ptr<T>::shared_ptr(const shared_ptr& pObject) {
        meta_ = pObject.meta_;
        increment();
    }

    template <typename T>
    shared_ptr<T>::shared_ptr(shared_ptr&& pObject) {
        meta_ = pObject.meta_;
        pObject.meta_ = nullptr;
    }

    template <typename T>
    shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr& pObject) {
        if (&pObject != this) {
            decrement();
            meta_ = pObject.meta_;
            increment();
        }
        return *this;
    }

    template <typename T>
    shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr&& pObject) {
        if (&pObject != this) {
            decrement();
            meta_ = pObject.meta_;
            pObject.meta_ = nullptr;
        }
        return *this;
    }

    template <typename T>
    void shared_ptr<T>::reset() {
        decrement();
    }

    template <typename T>
    void shared_ptr<T>::reset(const T *object) {
        decrement();
        meta_ = object == nullptr
            ? nullptr
            : new meta_t{object};
        increment();
    }
}

#endif
