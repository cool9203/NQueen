**NQueen.cpp** : use Hill-Climbing Algorithm for eight queens.  
evaluation function is calculate slope.  
if local optimum than restart.  

| n  | execution time | restart times|one epoch execution time|
|:--:|---------------:|:----:|:----------:|
| 8 |      0.01334s|   1|0.00667s|
| 10|      0.06260s|  17|0.00347s|
| 20|      0.20403s|  19|0.01020s|
| 30|      1.48939s|  45|0.03309s|
| 40|     14.16768s| 146|0.09637s|
| 50|     21.68516s|  80|0.26771s|
|100|    966.15776s| 111|8.62640s|

---

**fast_version.cpp** : use Hill-Climbing Algorithm for eight queens, **but is unstable**, maybe restart many times.  
evaluation function is calculate slope.  
if local optimum than restart.  

| n  | execution time | restart times|one epoch execution time|
|:--:|---------------:|:----:|:----------:|
| 8 |     0.0074s|  30|0.000238s|
| 10|     0.0048s|  21|0.000218s|
| 20|     0.0340s|  79|0.000425s|
| 30|     0.0833s|  79|0.001041s|
| 40|     0.1299s|  70|0.001855s|
| 50|     0.7567s| 376|0.002007s|
|100|    12.0820s| 815|0.014806s|
|200|   238.0028s|2080|0.114369s|

---  
one epoch execution time = execution time / (restart times + 1)
table not so precise.  
have lucky and computer performance affect.   

|   |  test computer  |
|:--:|---------------:|
|cpu|i7-3370 3.40GHz|
|ram|32GB|

use visual studio release to compile.

**`if you need this code, can copy in your code.`**

