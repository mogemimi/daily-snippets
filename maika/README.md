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

#### Basic Types

```swift
let a : Int = 42;
let b : Double = 3.1415926535;
let c : Bool = true;
let d : String = "hello";
```

#### Literals

```swift
// Int
42

// Double
3.1415926535

// Bool
true
false

// String
"hello, world"

// Null
null
```

#### Constants

```swift
const Pi : Double = 3.1415926535;
```

#### `var` and `let`

```swift
var a;
a = 42;

let b = 42;
```

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

#### For Statement

```swift
for (let i = 0; i < 42; i++) {
    println(i);
}
```

#### For-in Statement

```swift
for (let i in arr) {
    println(i);
}
```

#### While Statement

```swift
while (vec.x < 3.141592) {
    vec.x += 0.5;
}
```

#### If Statement

```swift
if (vec.x < 0.0) {
    vec.x = 0.0;
}
```

#### Defer Statement

```swift
func f() {
    defer { print("hello"); }
    print("hi");
}

f();

// Prints "hi"
// Prints "hello"
```

#### Tuple

```swift
// Structured binding
let (u, v) = [42, 100];
```

```swift
let m = ["a": 42, "b": 5];
for (let (k, v) in map) {
    print(k);
    print(v);
}
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
