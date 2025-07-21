#pragma once

#define UNITY_CLASS_DECL(module, className) \
    private:\
    inline static constexpr const char* MODULE_NAME = module; \
    inline static constexpr const char* CLASS_NAME = className; \
    public: \
    inline static UnityResolve::Class* getClass() { \
        static UnityResolve::Class* c = nullptr; \
        if (!c) c = App::getClass(module, className); \
        return c; \
	}

#define UNITY_FIELD(type, name, offset) \
    inline type name() { \
        return *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(this) + offset); \
	} \
	inline void name(type value) const { \
	    *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(this) + offset) = value; \
	}

// Used to initialize a method pointer for a class that's declared with UNITY_CLASS_DECL
#define UNITY_METHOD(returnType, methodName, ...) \
    private: \
    inline static UnityResolve::MethodPointer<returnType, __VA_ARGS__> methodName##_ptr{}; \
    inline static bool methodName##_initialized = false; \
    public: \
    inline static UnityResolve::MethodPointer<returnType, __VA_ARGS__> methodName() { \
        if (!methodName##_initialized) { \
            auto method = App::getMethod(MODULE_NAME, CLASS_NAME, #methodName); \
            if (method) { \
                methodName##_ptr = method->Cast<returnType, __VA_ARGS__>(); \
            } \
            methodName##_initialized = true; \
        } \
        return methodName##_ptr; \
    }

// Lazy initialization macro for methods from a specific module
#define UNITY_METHOD_FROM(module, className, returnType, methodName, ...) \
    inline static UnityResolve::MethodPointer<returnType, __VA_ARGS__> methodName() { \
        static UnityResolve::MethodPointer<returnType, __VA_ARGS__> cached_method{}; \
        static bool initialized = false; \
        if (!initialized) { \
            auto method = App::getMethod(module, className, #methodName); \
            if (method) { \
                cached_method = method->Cast<returnType, __VA_ARGS__>(); \
            } \
            initialized = true; \
        } \
        return cached_method; \
    }
