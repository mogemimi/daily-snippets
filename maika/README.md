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

#### Arrays

```swift
let arr = [42, 100];
let empty_array = [];
arr[1] = 42;
```

#### Maps

```swift
let m = ["x": 42, "y": 3];
let empty_map = [:];
m["y"] = 42;
```

#### For loops

```swift
for (let i = 0; i < 42; i++) {
    println(i);
}
```

#### For-in loops

```swift
for (let i in arr) {
    println(i);
}
```

#### While loops

```swift
while (vec.x < 0.0) {
    vec.x -= 1.0;
}
```

#### If statements

```swift
if (vec.x < 0.0) {
    vec.x = 0.0;
}
```

#### Tuple

```swift
// Structured binding
let (u, v) = [42, 100];
```

#### Functions

```swift
func min(a : Double, b : Double) -> Double {
    if (a < b) {
        return a;
    }
    return b;
}
```

```swift
func run(f : func(Int)->Int) -> Int {
    return f(42);
}

func main() {
    let f = func(x : Int) -> Int { return x; };
    run(f);
}
```

#### Classes

```swift
class Vector2 {
    let x : Double = 0;
    let y : Double = 0;

    func dot(v : Vector2) -> Double {
        return x * v.x + y * v.y;
    }

    func cross(v : Vector2) -> Double {
        return x * v.y - y * v.x;
    }
}

func main() {
    let vec = Vector2();
    vec.x = 3.141592;
    vec.y = 1.0;
    let d = vec.dot(vec);
}
```
