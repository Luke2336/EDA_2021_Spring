Entering testBdd
f: 3 nodes 1 leaves 1 minterms
11  1

g: 3 nodes 1 leaves 3 minterms
0-  1
11  1

f and g are not complementary
f is less than or equal to g
g: 2 nodes 1 leaves 2 minterms
1-  1

h: 2 nodes 1 leaves 2 minterms
-1  1

x + h has 3 nodes
h: 3 nodes 1 leaves 3 minterms
01  1
1-  1

Entering testAdd
r: 6 nodes 3 leaves 3 minterms
01  1
10  1
11  2

s: 4 nodes 2 leaves 1 minterms
11  3

s: 1 nodes 1 leaves 4 minterms
--  inf

p is less than or equal to r
r: 4 nodes 2 leaves 3 minterms
01  1
1-  1

Entering testAdd2
f: 7 nodes 4 leaves 4 minterms
00  0.1
01  0.2
10  0.3
11  0.4

l: 7 nodes 4 leaves 4 minterms
00 -2.30259
01 -1.60944
10 -1.20397
11 -0.916291

r: 7 nodes 4 leaves 4 minterms
00 -0.230259
01 -0.321888
10 -0.361192
11 -0.366516

e: 1 nodes 1 leaves 4 minterms
--  1.84644

Entering testZdd
s: 3 nodes 3 minterms
1- 1
01 1

v is less than s
s: 1 nodes 1 minterms
01 1

Entering testBdd2
f: 7 nodes 1 leaves 7 minterms
01-1  1
101-  1
1101  1
111-  1

Irredundant cover of f:
1-1- 1
-1-1 1

Number of minterms (arbitrary precision): 7
Number of minterms (extended precision):  7.000000e+00Two-literal clauses of f:
 x2 |  x3
 x1 |  x2
 x0 |  x3
 x0 |  x1

vect[0]
1--- 1

vect[1]
0--- 1
-1-- 1

vect[2]
10-- 1
--1- 1

vect[3]
0--- 1
-10- 1
---1 1

digraph "DD" {
size = "7.5,10"
center = true;
edge [dir = none];
{ node [shape = plaintext];
  edge [style = invis];
  "CONST NODES" [style = invis];
" x0 " -> " x1 " -> " x2 " -> " x3 " -> "CONST NODES"; 
}
{ rank = same; node [shape = box]; edge [style = invis];
"  v0  " -> "  v1  " -> "  v2  " -> "  v3  "; }
{ rank = same; " x0 ";
"0x189";
"0x14b";
"0x147";
"0x18c";
}
{ rank = same; " x1 ";
"0x18b";
"0x148";
"0x188";
}
{ rank = same; " x2 ";
"0x18a";
"0x179";
}
{ rank = same; " x3 ";
"0x17a";
}
{ rank = same; "CONST NODES";
{ node [shape = box]; "0x141";
}
}
"  v0  " -> "0x147" [style = solid];
"  v1  " -> "0x14b" [style = solid];
"  v2  " -> "0x189" [style = solid];
"  v3  " -> "0x18c" [style = solid];
"0x189" -> "0x188";
"0x189" -> "0x179" [style = dashed];
"0x14b" -> "0x148";
"0x14b" -> "0x141" [style = dashed];
"0x147" -> "0x141";
"0x147" -> "0x141" [style = dotted];
"0x18c" -> "0x18b";
"0x18c" -> "0x141" [style = dashed];
"0x18b" -> "0x18a";
"0x18b" -> "0x17a" [style = dashed];
"0x148" -> "0x141";
"0x148" -> "0x141" [style = dotted];
"0x188" -> "0x179";
"0x188" -> "0x141" [style = dashed];
"0x18a" -> "0x17a";
"0x18a" -> "0x141" [style = dashed];
"0x179" -> "0x141";
"0x179" -> "0x141" [style = dotted];
"0x17a" -> "0x141";
"0x17a" -> "0x141" [style = dotted];
"0x141" [label = "1"];
}
Entering testBdd3
f: 10 nodes 1 leaves 50 minterms
0-0-0-  1
0-0-10  1
0-100-  1
0-1010  1
0-11--  1
10-00-  1
10-010  1
10-1--  1
11000-  1
110010  1
1101--  1
1110-1  1
111101  1

f1: 5 nodes 1 leaves 36 minterms
0---0-  1
0---10  1
10--0-  1
10--10  1

f1 is less than or equal to f
g: 6 nodes 1 leaves 62 minterms
0-----  1
10----  1
110---  1
1110--  1
11110-  1

h: 8 nodes 1 leaves 51 minterms
0-0-0-  1
0-0-10  1
0-100-  1
0-1010  1
0-11--  1
10-00-  1
10-010  1
10-1--  1
11000-  1
110010  1
1101--  1
111--1  1

g * h == f
Entering testZdd2
p[0]: 3 nodes 1 leaves 64 minterms
----0-0  1
----1-1  1

p[1]: 5 nodes 1 leaves 64 minterms
--0-0-0  1
--0-10-  1
--1-0-1  1
--1-11-  1

p[2]: 7 nodes 1 leaves 64 minterms
0-0-0-0  1
0-0-10-  1
0-10---  1
1-0-0-1  1
1-0-11-  1
1-11---  1

p[3]: 8 nodes 1 leaves 64 minterms
0-0-0-1  1
0-0-11-  1
0-11---  1
11-----  1

digraph "DD" {
size = "7.5,10"
center = true;
edge [dir = none];
{ node [shape = plaintext];
  edge [style = invis];
  "CONST NODES" [style = invis];
" a2 " -> " b2 " -> " a1 " -> " b1 " -> " a0 " -> " b0 " -> " c0 " -> "CONST NODES"; 
}
{ rank = same; node [shape = box]; edge [style = invis];
"  s0  " -> "  s1  " -> "  s2  " -> "  c3  "; }
{ rank = same; " a2 ";
"0x1c3";
"0x1c2";
}
{ rank = same; " b2 ";
"0x148";
}
{ rank = same; " a1 ";
"0x1c1";
"0x1c0";
}
{ rank = same; " b1 ";
"0x17a";
}
{ rank = same; " a0 ";
"0x1bf";
"0x1be";
}
{ rank = same; " b0 ";
"0x199";
}
{ rank = same; " c0 ";
"0x1bd";
}
{ rank = same; "CONST NODES";
{ node [shape = box]; "0x141";
}
}
"  s0  " -> "0x1be" [style = solid];
"  s1  " -> "0x1c0" [style = solid];
"  s2  " -> "0x1c2" [style = solid];
"  c3  " -> "0x1c3" [style = solid];
"0x1c3" -> "0x148";
"0x1c3" -> "0x1c1" [style = dashed];
"0x1c2" -> "0x1c1";
"0x1c2" -> "0x1c1" [style = dotted];
"0x148" -> "0x141";
"0x148" -> "0x141" [style = dotted];
"0x1c1" -> "0x17a";
"0x1c1" -> "0x1bf" [style = dashed];
"0x1c0" -> "0x1bf";
"0x1c0" -> "0x1bf" [style = dotted];
"0x17a" -> "0x141";
"0x17a" -> "0x141" [style = dotted];
"0x1bf" -> "0x199";
"0x1bf" -> "0x1bd" [style = dashed];
"0x1be" -> "0x1bd";
"0x1be" -> "0x1bd" [style = dotted];
"0x199" -> "0x141";
"0x199" -> "0x141" [style = dotted];
"0x1bd" -> "0x141";
"0x1bd" -> "0x141" [style = dotted];
"0x141" [label = "1"];
}
z[0]: 4 nodes 2 minterms
00000000100010 1
00000000010001 1

z[1]: 10 nodes 4 minterms
00001000101000 1
00001000010010 1
00000100100100 1
00000100010001 1

z[2]: 16 nodes 6 minterms
10001010000000 1
10000100101000 1
10000100010010 1
01001001000000 1
01000100100100 1
01000100010001 1

z[3]: 10 nodes 4 minterms
10100000000000 1
01001010000000 1
01000100101000 1
01000100010010 1

z[0]
----1-1 1
----0-0 1
z[0]
----0-0 1
----1-1 1
z[1]
--1-11- 1
--1-0-1 1
--0-10- 1
--0-0-0 1
z[1]
--0-0-0 1
--0-10- 1
--1-0-1 1
--1-11- 1
z[2]
1-11--- 1
1-0-11- 1
1-0-0-1 1
0-10--- 1
0-0-10- 1
0-0-0-0 1
z[2]
0-0-0-0 1
0-0-10- 1
0-10--- 1
1-0-0-1 1
1-0-11- 1
1-11--- 1
z[3]
11----- 1
0-11--- 1
0-0-11- 1
0-0-0-1 1
z[3]
0-0-0-1 1
0-0-11- 1
0-11--- 1
11----- 1
digraph "ZDD" {
size = "7.5,10"
center = true;
edge [dir = none];
{ node [shape = plaintext];
  edge [style = invis];
  "CONST NODES" [style = invis];
" a2+ " -> " a2- " -> " b2+ " -> " a1+ " -> " a1- " -> " b1+ " -> " b1- " -> " a0+ " -> " a0- " -> " b0+ " -> " b0- " -> " c0+ " -> " c0- " -> "CONST NODES"; 
}
{ rank = same; node [shape = box]; edge [style = invis];
"  s0  " -> "  s1  " -> "  s2  " -> "  c3  "; }
{ rank = same; " a2+ ";
"0x184";
"0x17b";
}
{ rank = same; " a2- ";
"0x182";
"0x177";
}
{ rank = same; " b2+ ";
"0x17e";
}
{ rank = same; " a1+ ";
"0x172";
"0x164";
"0x16b";
}
{ rank = same; " a1- ";
"0x162";
"0x170";
}
{ rank = same; " b1+ ";
"0x16c";
}
{ rank = same; " b1- ";
"0x167";
}
{ rank = same; " a0+ ";
"0x15d";
"0x14f";
"0x156";
}
{ rank = same; " a0- ";
"0x15b";
"0x14d";
}
{ rank = same; " b0+ ";
"0x157";
}
{ rank = same; " b0- ";
"0x152";
}
{ rank = same; " c0+ ";
"0x146";
}
{ rank = same; " c0- ";
"0x145";
}
{ rank = same; "CONST NODES";
{ node [shape = box]; "0x142";
"0x141";
}
}
"  s0  " -> "0x14f" [style = solid];
"  s1  " -> "0x164" [style = solid];
"  s2  " -> "0x17b" [style = solid];
"  c3  " -> "0x184" [style = solid];
"0x184" -> "0x17e";
"0x184" -> "0x182" [style = dashed];
"0x17b" -> "0x172";
"0x17b" -> "0x177" [style = dashed];
"0x182" -> "0x172";
"0x182" -> "0x142" [style = dashed];
"0x177" -> "0x16b";
"0x177" -> "0x142" [style = dashed];
"0x17e" -> "0x141";
"0x17e" -> "0x142" [style = dashed];
"0x172" -> "0x16c";
"0x172" -> "0x170" [style = dashed];
"0x164" -> "0x15d";
"0x164" -> "0x162" [style = dashed];
"0x16b" -> "0x167";
"0x16b" -> "0x162" [style = dashed];
"0x162" -> "0x156";
"0x162" -> "0x142" [style = dashed];
"0x170" -> "0x15d";
"0x170" -> "0x142" [style = dashed];
"0x16c" -> "0x141";
"0x16c" -> "0x142" [style = dashed];
"0x167" -> "0x141";
"0x167" -> "0x142" [style = dashed];
"0x15d" -> "0x157";
"0x15d" -> "0x15b" [style = dashed];
"0x14f" -> "0x146";
"0x14f" -> "0x14d" [style = dashed];
"0x156" -> "0x152";
"0x156" -> "0x14d" [style = dashed];
"0x15b" -> "0x146";
"0x15b" -> "0x142" [style = dashed];
"0x14d" -> "0x145";
"0x14d" -> "0x142" [style = dashed];
"0x157" -> "0x141";
"0x157" -> "0x142" [style = dashed];
"0x152" -> "0x141";
"0x152" -> "0x142" [style = dashed];
"0x146" -> "0x141";
"0x146" -> "0x142" [style = dashed];
"0x145" -> "0x141";
"0x145" -> "0x142" [style = dashed];
"0x142" [label = "0"];
"0x141" [label = "1"];
}
Entering testBdd4
f: 5 nodes 1 leaves 3 minterms
000-----------  1
11------------  1

g: 5 nodes 1 leaves 3 minterms
000  1
11-  1

f and h are identical
Entering testBdd5
digraph "DD" {
size = "7.5,10"
center = true;
edge [dir = none];
{ node [shape = plaintext];
  edge [style = invis];
  "CONST NODES" [style = invis];
" a " -> " b " -> " c " -> " d " -> "CONST NODES"; 
}
{ rank = same; node [shape = box]; edge [style = invis];
"  lb  " -> "  ub  " -> "  f  " -> "  primes  " -> "  lprime  "; }
{ rank = same; " a ";
"0x1b5";
}
{ rank = same; " b ";
"0x1ab";
"0x1af";
"0x1b4";
"0x1b6";
}
{ rank = same; " c ";
"0x169";
"0x1ad";
}
{ rank = same; " d ";
"0x17a";
}
{ rank = same; "CONST NODES";
{ node [shape = box]; "0x141";
}
}
"  lb  " -> "0x1b6" [style = dotted];
"  ub  " -> "0x17a" [style = solid];
"  f  " -> "0x1b5" [style = solid];
"  primes  " -> "0x1ab" [style = solid];
"  lprime  " -> "0x1ab" [style = solid];
"0x1b5" -> "0x1af";
"0x1b5" -> "0x1b4" [style = dashed];
"0x1ab" -> "0x17a";
"0x1ab" -> "0x141" [style = dotted];
"0x1af" -> "0x17a";
"0x1af" -> "0x1ad" [style = dotted];
"0x1b4" -> "0x169";
"0x1b4" -> "0x141" [style = dotted];
"0x1b6" -> "0x1ad";
"0x1b6" -> "0x141" [style = dashed];
"0x169" -> "0x17a";
"0x169" -> "0x141" [style = dashed];
"0x1ad" -> "0x141";
"0x1ad" -> "0x17a" [style = dotted];
"0x17a" -> "0x141";
"0x17a" -> "0x141" [style = dotted];
"0x141" [label = "1"];
}
primes(1): 3 nodes 1 leaves 4 minterms
-1-1----------  1

primes(2): is the zero DD
primes(3): 4 nodes 1 leaves 2 minterms
1-01----------  1

primes(4): 6 nodes 1 leaves 5 minterms
-1-1---------- 1
010----------- 1

primes(5): 4 nodes 1 leaves 2 minterms
01-1----------  1

l1: 7 nodes 1 leaves 3 minterms
0111----------  1
111-----------  1

u1: 4 nodes 1 leaves 8 minterms
000-----------  1
011-----------  1
1-1-----------  1

interpolant1: 4 nodes 1 leaves 6 minterms
011-----------  1
1-1-----------  1

l2: 7 nodes 1 leaves 5 minterms
001-----------  1
0110----------  1
101-----------  1

u2: 5 nodes 1 leaves 8 minterms
-000----------  1
-01-----------  1
-110----------  1

interpolant2: 5 nodes 1 leaves 6 minterms
-01-----------  1
-110----------  1

l3: 4 nodes 1 leaves 2 minterms
00-1----------  1

u3: 3 nodes 1 leaves 4 minterms
-0-1----------  1

interpolant3: 3 nodes 1 leaves 4 minterms
-0-1----------  1

Entering testErrorHandling
Oops! Caught: empty DD.
Caught: Invalid argument.
f = var[1] | (var[2] & var[3])
var[0] | var[1] is not a cube
Cudd_Cofactor: Invalid restriction 2
Caught: Invalid argument.
f : 511 nodes 1 leaves 115422332637413376 minterms
g : 511 nodes 1 leaves 115422332637413376 minterms
h Caught: empty DD.
f : 88 nodes 1 leaves 226007109 minterms
g : 91 nodes 1 leaves 3143500301 minterms
h : 142 nodes 1 leaves 2917493192 minterms
Caught: Maximum memory exceeded.
Caught: Timeout expired.  Lag = 119 ms.
**** CUDD modifiable parameters ****
Hard limit for cache size: 2796202
Cache hit threshold for resizing: 30%
Garbage collection enabled: yes
Limit for fast unique table growth: 1677721
Maximum number of variables sifted per reordering: 1000
Maximum number of variable swaps per reordering: 2000000
Maximum growth while sifting a variable: 1.2
Dynamic reordering of BDDs enabled: no
Default BDD reordering method: 4
Dynamic reordering of ZDDs enabled: no
Default ZDD reordering method: 4
Realignment of ZDDs to BDDs enabled: no
Realignment of BDDs to ZDDs enabled: no
Dead nodes counted in triggering reordering: no
Group checking criterion: 7
Recombination threshold: 0
Symmetry violation threshold: 0
Arc violation threshold: 0
GA population size: 0
Number of crossovers for GA: 0
Next reordering threshold: 4004
**** CUDD non-modifiable parameters ****
Memory in use: 146651984
Peak number of nodes: 2044
Peak number of live nodes: 2030
Number of BDD variables: 60
Number of ZDD variables: 14
Number of cache entries: 524288
Number of cache look-ups: 3847
Number of cache hits: 876
Number of cache insertions: 3052
Number of cache collisions: 6
Number of cache deletions: 2294
Cache used slots = 0.17% (expected 0.17%)
Soft limit for cache size: 76800
Number of buckets in unique table: 19200
Used buckets in unique table: 4.22% (expected 4.19%)
Number of BDD and ADD nodes: 2634
Number of ZDD nodes: 14
Number of dead BDD and ADD nodes: 2570
Number of dead ZDD nodes: 0
Total number of nodes allocated: 4857
Total number of nodes reclaimed: 154
Garbage collections so far: 3
Time for garbage collection: 0.00 sec
Reorderings so far: 0
Time for reordering: 0.00 sec
