#pragma once

#define UNITY_CLASS_DECL(MODULE, CLASS_NAME) \
private:\
    inline static constexpr const char* ModuleName = MODULE; \
    inline static constexpr const char* ClassName = CLASS_NAME; \
public: \
    inline static const char* getClassName() { return ClassName; } \
    inline static UnityResolve::Class* getClass() { \
        static UnityResolve::Class* c = nullptr; \
        if (!c) c = app::getClass(MODULE, CLASS_NAME); \
        return c; \
	}

#define UNITY_CLASS_DECL_FROM_FIELD_NAME(MODULE, CONTAINER_CLASS_NAME, FIELD_NAME) \
private: \
    inline static constexpr const char* ModuleName = MODULE; \
    inline static constexpr const char* ContainerClassName = CONTAINER_CLASS_NAME; \
    inline static constexpr const char* FieldName = FIELD_NAME; \
    inline static const char* ClassName; \
public: \
    inline static const char* getClassName() { return ClassName; } \
    inline static UnityResolve::Class* getClass() { \
        static UnityResolve::Class* cachedClass = nullptr; \
        if (!cachedClass) { \
            cachedClass = app::findClassFromField(ModuleName, ContainerClassName, FieldName); \
            ClassName = cachedClass ? cachedClass->name.c_str() : ""; \
        } \
        return cachedClass; \
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

// Resolves a method that comes AFTER a known method in the same class
#define UNITY_METHOD_AFTER(RETURN_TYPE, METHOD_NAME, AFTER_NAME, ...) \
private: \
    inline static UnityResolve::MethodPointer<RETURN_TYPE, __VA_ARGS__> METHOD_NAME##_ptr{}; \
    inline static bool METHOD_NAME##_initialized = false; \
public: \
    inline static UnityResolve::MethodPointer<RETURN_TYPE, __VA_ARGS__> METHOD_NAME() { \
        if (!METHOD_NAME##_initialized) { \
            auto cls = getClass(); \
            auto method = app::findMethodAfter(cls, AFTER_NAME); \
            if (method) { \
                METHOD_NAME##_ptr = method->Cast<RETURN_TYPE, __VA_ARGS__>(); \
            } \
            METHOD_NAME##_initialized = true; \
        } \
        return METHOD_NAME##_ptr; \
    }

// Resolves a method that comes BEFORE a known method in the same class
#define UNITY_METHOD_BEFORE(RETURN_TYPE, METHOD_NAME, BEFORE_NAME, ...) \
private: \
    inline static UnityResolve::MethodPointer<RETURN_TYPE, __VA_ARGS__> METHOD_NAME##_ptr{}; \
    inline static bool METHOD_NAME##_initialized = false; \
public: \
    inline static UnityResolve::MethodPointer<RETURN_TYPE, __VA_ARGS__> METHOD_NAME() { \
        if (!METHOD_NAME##_initialized) { \
            auto cls = getClass(); \
            auto method = app::findMethodBefore(cls, BEFORE_NAME); \
            if (method) { \
                METHOD_NAME##_ptr = method->Cast<RETURN_TYPE, __VA_ARGS__>(); \
            } \
            METHOD_NAME##_initialized = true; \
        } \
        return METHOD_NAME##_ptr; \
    }

// Resolves a method BETWEEN two known method names in the same class
#define UNITY_METHOD_BETWEEN(RETURN_TYPE, METHOD_NAME, AFTER_NAME, BEFORE_NAME, ...) \
private: \
    inline static UnityResolve::MethodPointer<RETURN_TYPE, __VA_ARGS__> METHOD_NAME##_ptr{}; \
    inline static bool METHOD_NAME##_initialized = false; \
public: \
    inline static UnityResolve::MethodPointer<RETURN_TYPE, __VA_ARGS__> METHOD_NAME() { \
        if (!METHOD_NAME##_initialized) { \
            auto cls = getClass(); \
            auto method = app::findMethodBetween(cls, AFTER_NAME, BEFORE_NAME); \
            if (method) { \
                METHOD_NAME##_ptr = method->Cast<RETURN_TYPE, __VA_ARGS__>(); \
            } \
            METHOD_NAME##_initialized = true; \
        } \
        return METHOD_NAME##_ptr; \
    }

// Alternatively, you can call METHOD()(arguments) directly. But it doesn't look as nice.
#define UNITY_CALL(METHOD_ACCESSOR, ...) METHOD_ACCESSOR()(__VA_ARGS__);
