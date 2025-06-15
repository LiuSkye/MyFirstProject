template <class type>
class Foo {
public:
    Foo();
    type val();
    void val(type v);

private:
    type _val;
};
