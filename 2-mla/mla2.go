package main

import (
    "fmt"
    "math"
)

const EPS float64 = 1e-6
const INF float64 = 9999999999.

// Integral's limits
const L float64 = 0.
const R float64 = 2.5

// The function
func f(x float64) float64 {
    return 1 / math.Sqrt(3*x*x + 4)
}

func main() {
    n := 5.
    prev := INF
    for {
        cur := 0.
        h := (R-L) / n
        for i := 0.; i < n; i++ {
            point := L + h * (i + 0.5)
            cur += f(point)
        }
        cur *= h
        if math.Abs(cur - prev) < EPS {
            fmt.Println("Number of nodes: ", n)
            fmt.Println("Integral: ", cur)
            return
        } else {
            prev = cur
            n *= 2
        }
    }
}
