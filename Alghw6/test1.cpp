#include <math.h>
#include <chplot.h>
int main()
{
int numpoints = 36;
array double x[numpoints],y[numpoints];
lindata(0,360,x,36);
y = sin(x*M_PI/180);
plotxy(x,y,"Ch plot","xlabel","ylabel");
}
