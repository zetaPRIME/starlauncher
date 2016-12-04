#pragma once

namespace starlight {
    template <class T>
    class OptRef {
    private:
        T* ref;
        bool exists;
    public:
        OptRef() : ref(nullptr), exists(false) { }
        OptRef(std::nullptr_t nul) : ref(nullptr), exists(false) { }
        OptRef(const T& ref) : ref(const_cast<T*>(&ref)), exists(true) { } // whatever, const cast, I know what I'm doing
        ~OptRef() { }
        
        const T& get() { return *ref; } // ... I guess :(
        
        explicit operator bool() const { return exists; }
        const T& operator ->() { return *ref; } // meh, technically unsafe but it's not meant to be used without explicit checking
        operator const T&() { return *ref; } // same here
    };
}

