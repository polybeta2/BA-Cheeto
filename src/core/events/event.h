#pragma once
#include <nano_signal_slot.hpp>

template <typename... Args>
class Event
{
public:
    // Normal functions
    template <auto FuncPtr>
    void addListener()
    {
        signal.template connect<FuncPtr>();
    }

    // Member functions
    template <typename T, auto MemPtr>
    void addListener(T* instance)
    {
        signal.template connect<MemPtr>(instance);
    }

    // Lambda functions
    template <typename L>
    void addListener(L&& lambda)
    {
        signal.connect(std::forward<L>(lambda));
    }

    // Normal functions
    template <auto FuncPtr>
    void removeListener()
    {
        signal.template disconnect<FuncPtr>();
    }

    // Member functions
    template <typename T, auto MemPtr>
    void removeListener(T* instance)
    {
        signal.template disconnect<MemPtr>(instance);
    }

    void invoke(Args... args)
    {
        signal.fire(std::forward<Args>(args)...);
    }

    void operator()(Args... args)
    {
        invoke(std::forward<Args>(args)...);
    }

    void clear()
    {
        signal.disconnect_all();
    }

private:
    Nano::Signal<void(Args...), Nano::TS_Policy<>> signal;
};