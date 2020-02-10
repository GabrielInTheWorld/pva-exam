#pragma once
template <typename C>
class singleton {
public:
    static C* instance() {
        if ( !_instance ) {
            _instance = new C();
        }
        return _instance;
    }
    virtual ~singleton() {
        if ( _instance ) {
            delete _instance;
        }
        _instance = 0;
    }
protected:
    singleton() {}
private:
    static C* _instance;
};
template <typename C> C* singleton <C>::_instance = 0;
