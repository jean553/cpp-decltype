# cpp-decltype

## Simple use case

```cpp
int value {10};

int& get() {
    return value;
}

auto getValue() {
    return get();
}

int main() {

    auto destination = getValue();
    destination += 5;
    std::cout << value << std::endl;

    return EXIT_SUCCESS;
}
```

By running the example above, I want to see `15` displayed in my terminal.
In fact, I want `destination` to be a reference on `value`.

By now, I can see the output `10`; it's normal:
 * `get()` returns a reference to `value`,
 * `getValue()` returns a copy of `get()`, so a new variable equals to `10` and not a reference to `value` anymore; this is due to the following types deduction rule:

```cpp
/* if `param` is a reference, the deduced type does not contain the reference anymore */
template<typename T>
void function(T param);
```

 * `getValue()` returns an `int`, so `destination` is deduced as an `int`.

The value of `destination` is modified but not the value of `value`.
