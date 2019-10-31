/*
AC 0.01s 2.7M SPOJ

algo:
lots of math

lets model the problem

let
H = Hx, Hy == coord of Honda house
K = Kx, Ky == coord of Kagawa house
J = 0,a == coord of Juice
C = b,0 == coord of Chips

the amount travelled will be
f(a,b) = dist(H to J) + dist(J to C) + dist(C to K)

now we want to minimize this function

first of all, there is no need to travel in criss-crossing fashion
it will be inefficient anyway.
so, the illustration in http://www.spoj.com/problems/HONDA shows how the possiblly efficient path works

f(a,b) = sqrt(Hx^2 + (Hy-a)^2) + sqrt((Kx-b)^2 + Ky^2) + sqrt(a^2 + b^2)

This is a two-variable function.
lets perform partial differentiation on f(a,b) on a.

f'a(a,b) = 1/2 * 1/sqrt(Hx^2 + (Hy-a)^2) * (-2(Hy-a)) + 2a / 2 / sqrt(a^2+b^2)
to find the minimum, find the place where f'a(a,b) == 0

1/2 * 1/sqrt(Hx^2 + (Hy-a)^2) * (-2(Hy-a)) + 2a / 2 / sqrt(a^2+b^2) == 0
it can be shown that if a should be a function of b:

a = b*Hy / (Hx+b) or a = -b*Hy / (Hx - b). Choose a = b*Hy / (Hx+b) because the second expression implies that b is negative...
we want b to be positive...

if f(a,b) is geared to minimum.

Interestingly:
when a = b*Hy / (Hx+b), the gradient of line (H -- J) is the same as line (J -- point(-b, 0))

gradient line (H -- J):
m = (Hy - (b*Hy / (Hx+b))) / Hx
m = Hy / (Hx+b)

gradient line (J -- point(-b, 0)):
m = (b*Hy / (Hx+b)) / b
m = Hy / (Hx+b)

This observation allows for the f(a,b) to be simplified to just f(b):
f(b) is thus:

f(b) = sqrt((Hx+b)^2 + Hy^2) + sqrt((Kx-b)^2 + Ky^2)
df(b) / db = (Hx+b) / sqrt((Hx+b)^2 + Hy^2) - (Kx-b) / sqrt((Kx-b)^2 + Ky^2)

set df(b) / db = 0 for minimum b
we get:
(Hx+b) / sqrt((Hx+b)^2 + Hy^2) = (Kx-b) / sqrt((Kx-b)^2 + Ky^2)

square both sides
(Hx+b)^2 / ((Hx+b)^2 + Hy^2) = (Kx-b)^2 / ((Kx-b)^2 + Ky^2)

little algebra and we get:
(Hx+b)^2 * Ky^2 = Hy^2 * (Kx-b)^2

square root both sides and pick the positive one
(Hx+b)*Ky = Hy*(Kx-b)

and finally, 
b = (Hy*Kx - Hx*Ky) / (Ky+Hy)

find b, feed it to the f(b) equation and we're done.

notice that b can be negative.
However, if point H and K is switched, the new b = -b.

But, this is actually not needed because when these two points are inserted to f(b),
both produces exact same result.



*/

#include <stdio.h>
#include <math.h>

int main() {
	int T, c=1;
	scanf("%d", &T);
	while (T--) {
		int Hx, Hy, Kx, Ky;
		
		scanf("%d %d %d %d", &Hx, &Hy, &Kx, &Ky);
		
		double b = (Hy * Kx - Hx * Ky) / ((double)(Ky + Hy));
		
		double r = sqrt((Hx+b)*(Hx+b) + Hy*Hy) + sqrt((Kx-b)*(Kx-b) + Ky*Ky);
		
		printf("Case %d: %.6lf\n", c++, r);
	}
	return 0;
}
