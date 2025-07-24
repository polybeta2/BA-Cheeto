#pragma once

#define UNITY_CLASS_DECL(MODULE, CLASS_NAME) \
    private:\
    inline static constexpr const char* ModuleName = MODULE; \
    inline static constexpr const char* ClassName = CLASS_NAME; \
    public: \
    inline static UnityResolve::Class* getClass() { \
        static UnityResolve::Class* c = nullptr; \
        if (!c) c = app::getClass(MODULE, CLASS_NAME); \
        return c; \
	}

#define UNITY_FIELD(FIELD_TYPE, FIELD_NAME, FIELD_OFFSET) \
    inline FIELD_TYPE FIELD_NAME() { \
        return *reinterpret_cast<FIELD_TYPE*>(reinterpret_cast<uintptr_t>(this) + FIELD_OFFSET); \
	} \
	inline void FIELD_NAME(FIELD_TYPE value) const { \
	    *reinterpret_cast<FIELD_TYPE*>(reinterpret_cast<uintptr_t>(this) + FIELD_OFFSET) = value; \
	}

// Used to initialize a method pointer for a class that's declared with UNITY_CLASS_DECL
#define UNITY_METHOD(RETURN_TYPE, METHOD_NAME, ...) \
    private: \
    inline static UnityResolve::MethodPointer<RETURN_TYPE, __VA_ARGS__> METHOD_NAME##_ptr{}; \
    inline static bool METHOD_NAME##_initialized = false; \
    public: \
    inline static UnityResolve::MethodPointer<RETURN_TYPE, __VA_ARGS__> METHOD_NAME() { \
        if (!METHOD_NAME##_initialized) { \
            auto method = app::getMethod(ModuleName, ClassName, #METHOD_NAME); \
            if (method) { \
                METHOD_NAME##_ptr = method->Cast<RETURN_TYPE, __VA_ARGS__>(); \
            } \
            METHOD_NAME##_initialized = true; \
        } \
        return METHOD_NAME##_ptr; \
    }

// Lazy initialization macro for methods from a specific module
#define UNITY_METHOD_FROM(MODULE, CLASS_NAME, RETURN_TYPE, METHOD_NAME, ...) \
    inline static UnityResolve::MethodPointer<RETURN_TYPE, __VA_ARGS__> METHOD_NAME() { \
        static UnityResolve::MethodPointer<RETURN_TYPE, __VA_ARGS__> cached_method{}; \
        static bool initialized = false; \
        if (!initialized) { \
            auto method = app::getMethod(MODULE, CLASS_NAME, #METHOD_NAME); \
            if (method) { \
                cached_method = method->Cast<RETURN_TYPE, __VA_ARGS__>(); \
            } \
            initialized = true; \
        } \
        return cached_method; \
    }

// Alternatively, you can call METHOD()(arguments) directly. But it doesn't look as nice.
#define UNITY_CALL(METHOD_ACCESSOR, ...) METHOD_ACCESSOR()(__VA_ARGS__);
