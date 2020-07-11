#pragma once
#include <atomic>

struct ll_spin{
    std::atomic_flag ll_lock = ATOMIC_FLAG_INIT;

    void lock(){
         while (ll_lock.test_and_set(std::memory_order_acquire));
    }

    void unlock(){
        ll_lock.clear(std::memory_order_release);
    }
};

struct ll_spin_guard{
    ll_spin &spin;

    ll_spin_guard(ll_spin &spin):spin(spin){spin.lock();}
    ~ll_spin_guard(){spin.unlock();}
};