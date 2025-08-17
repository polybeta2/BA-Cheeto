#pragma once
#include <nano_signal_slot.hpp>
#include <functional>

template <typename... Args>
class EventConnection
{
public:
    using DisconnectFunc = std::function<void()>;

    EventConnection() = default;

    // Create a connection with a custom disconnect function
    explicit EventConnection(DisconnectFunc disconnect_func)
        : disconnect_func_(std::move(disconnect_func))
    {
    }

    ~EventConnection()
    {
        disconnect();
    }

    EventConnection(const EventConnection&) = delete;
    EventConnection& operator=(const EventConnection&) = delete;

    EventConnection(EventConnection&& other) noexcept
        : disconnect_func_(std::move(other.disconnect_func_))
    {
        other.disconnect_func_ = nullptr;
    }

    EventConnection& operator=(EventConnection&& other) noexcept
    {
        if (this != &other)
        {
            disconnect();
            disconnect_func_ = std::move(other.disconnect_func_);
            other.disconnect_func_ = nullptr;
        }
        return *this;
    }

    void disconnect()
    {
        if (disconnect_func_)
        {
            disconnect_func_();
            disconnect_func_ = nullptr;
        }
    }

    bool is_connected() const
    {
        return disconnect_func_ != nullptr;
    }

private:
    DisconnectFunc disconnect_func_;
};

template <typename... Args>
class Event
{
public:
    using Connection = EventConnection<Args...>;

    // Connect a lambda or function object to this event and return RAII connection handle
    template <typename Callable>
    [[nodiscard]] Connection connect(Callable&& callable)
    {
        signal_.connect(std::forward<Callable>(callable));

        // Use clear() to disconnect all handlers if needed
        return Connection([this, callable]() mutable
        {
            // Limited capability. Store lambda IDs or diff approach for better cleanup
        });
    }

    // Connect a free function to this event
    template <auto FuncPtr>
    [[nodiscard]] Connection connect()
    {
        signal_.template connect<FuncPtr>();
        return Connection([this]()
        {
            signal_.template disconnect<FuncPtr>();
        });
    }

    // Connect a member function and return RAII connection handle
    template <auto MemPtr, typename T>
    [[nodiscard]] Connection connect(T* instance)
    {
        signal_.template connect<MemPtr>(instance);
        return Connection([this, instance]()
        {
            signal_.template disconnect<MemPtr>(instance);
        });
    }

    // Normal function
    template <auto FuncPtr>
    void addListener()
    {
        signal_.template connect<FuncPtr>();
    }

    // Member functions
    template <typename T, auto MemPtr>
    void addListener(T* instance)
    {
        signal_.template connect<MemPtr>(instance);
    }

    // Lambda or function object
    template <typename Callable>
    void addListener(Callable&& callable)
    {
        signal_.connect(std::forward<Callable>(callable));
    }

    // Normal functions
    template <auto FuncPtr>
    void removeListener()
    {
        signal_.template disconnect<FuncPtr>();
    }

    // Member functions
    template <typename T, auto MemPtr>
    void removeListener(T* instance)
    {
        signal_.template disconnect<MemPtr>(instance);
    }

    template <typename... UArgs>
    void operator()(UArgs&&... args)
    {
        signal_.fire(std::forward<UArgs>(args)...);
    }

    // Accumulate results from all event handlers
    template <typename Accumulator, typename... UArgs>
    void invoke_accumulate(Accumulator&& accumulator, UArgs&&... args)
    {
        signal_.fire_accumulate(std::forward<Accumulator>(accumulator),
                                std::forward<UArgs>(args)...);
    }

    void clear() { signal_.disconnect_all(); }
    bool empty() const { return signal_.is_empty(); }

private:
    Nano::Signal<void(Args...), Nano::TS_Policy<>> signal_;
};

// For ST_Policy. Use when events are fired from a single thread only
template <typename... Args>
class FastEvent
{
public:
    using Connection = EventConnection<Args...>;

    template <typename Callable>
    [[nodiscard]] Connection connect(Callable&& callable)
    {
        signal_.connect(std::forward<Callable>(callable));
        return Connection([]()
        {
            /* Lambda cleanup limitation. See Event impl */
        });
    }

    template <auto FuncPtr>
    [[nodiscard]] Connection connect()
    {
        signal_.template connect<FuncPtr>();
        return Connection([this]()
        {
            signal_.template disconnect<FuncPtr>();
        });
    }

    template <auto MemPtr, typename T>
    [[nodiscard]] Connection connect(T* instance)
    {
        signal_.template connect<MemPtr>(instance);
        return Connection([this, instance]()
        {
            signal_.template disconnect<MemPtr>(instance);
        });
    }

    template <typename... UArgs>
    void operator()(UArgs&&... args)
    {
        signal_.fire(std::forward<UArgs>(args)...);
    }

    void clear() { signal_.disconnect_all(); }
    bool empty() const { return signal_.is_empty(); }

private:
    Nano::Signal<void(Args...), Nano::ST_Policy> signal_;
};

template <typename... Args>
auto make_event()
{
    return Event<Args...>{};
}

template <typename... Args>
auto make_fast_event()
{
    return FastEvent<Args...>{};
}
