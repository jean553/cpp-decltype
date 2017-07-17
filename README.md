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

A simple solution consist of getting `getValue()` as a reference:

```cpp
auto& destination = getValue();
```

This does not work. In fact, `getValue()` returned type is `auto` on `get()` that returns `int&`. So once again, `getValue()` returns a new value (`int`) and not a reference (`int&`).

A simple way to fix it is to force `getValue()` to return a reference:

```cpp
auto& getValue() {
    return get();
}
```

`value` is now equal to `15` at the end of the program.

Let's now imagine we want pass parameters to our `get()` method, let's change it to:

```cpp
int& get(int data) {
    return value;
}
```

Note that the `data` parameter is totally useless here. The goal of the example
is simply to update the `get()` function signature.

So we can continue to call it as before, just by updating a little bit the function call:

```cpp
auto& getValue() {
    return get(100);
}
```

Everything still works as expected. `destination` is still a reference to `value`.

We now want to add a new `get()` function, that can handle `float` type:

```cpp
float get(float data) {
    return 1000.f;
}
```

Just by adding this function into our existing code, nothing changes.
In fact, the `float get(float)` function is never called,
as we pass an integer when we call `get(100)`.

Instead of calling `int& get(int)` from `getValue()`, we now want to call `float get(float)`.

We could simply update the code like that:

```cpp
auto& getValue() {
    return get(100.f);
}
```

It does not work. In fact, we try to returns `float&` from `getValue()`
when the `return` statement value is a `float`.
This is due to the following types deduction rule:

```cpp
/* the deduced type for param is a reference */
template<typename T>
void function(T& param);
```

The solution is to update `getValue()` to do not return a reference anymore:

```cpp
auto getValue() {
    return get(100.f);
}
```

Of course, we get exactly the same problem here:

```cpp
auto& destination = getValue();
```

Once again, we have to update `destination` type, which is not a reference anymore.

```cpp
auto destination = getValue();
```

We are now able to handle the `float` type. We now wanna add a parameter
to `getValue()` in order to pass it to `get()`.

So we can simply do:

```cpp
auto getValue(float param) {
    return get(param);
}
```

The new call to `getValue()` is:

```cpp
auto destination = getValue(100.f);
```
