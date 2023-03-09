#ifndef TUPLE
#define TUPLE
template <class A, class B>
class Tuple
{
    private:
        A first;
        B second;
public:
    Tuple() {}

    Tuple(A first, B second) : first(first), second(second) {}

    A getFirst() { return first; }

    B getSecond() { return second; }

    bool operator==(const Tuple<A, B> &other) const
    {
        return (first == other.first && second == other.second);
    }
};
#endif