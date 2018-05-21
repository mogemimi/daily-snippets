# maika

A experimental type inference as a hobby.

It is distributed under the [MIT License](https://opensource.org/licenses/MIT).

## Build and run

```sh
# Setup build tool
make -C ../maika bootstrap

# Build
make xcode

# Run
./bin/maika -help
```

## Language Specification

```swift
class Vector2 {
    let x : double = 0;
    let y : double = 0;

    func dot(v : Vector2) -> double
    {
        return x * v.x + y * v.y;
    }

    func cross(v : Vector2) -> double
    {
        return x * v.y - y * v.x;
    }
}

func main()
{
    print("hello");

    // Array
    let arr = [42, 100];
    arr[1] = 42;

    // Map
    let m = ["x": 42, "y": 3];
    m["y"] = 42;

    // Empty array and map
    let empty_array = [];
    let empty_map = [:];

    // Class
    let vec = Vector2();
    vec.x = 3.141592;
    vec.y = 1.0;
    let d = vec.dot(vec);

    // Structured binding
    let (u, v) = [42, 100];

    // for
    for (let i = 0; i < 42; i++) {
        println(i);
    }

    // for...in
    for (let i in arr) {
        println(i);
    }

    // while
    while (vec.x < 0.0) {
        vec.x -= 1.0;
    }

    // if
    if (vec.x < 0.0) {
        vec.x = 0.0;
    }
}
```

#### Functions

```swift
func run(f : func(Int)->Int) -> Int
{
    return f(42);
}

func main()
{
    let f = func(x : Int) -> Int { return x; };
    run(f);
}
```
