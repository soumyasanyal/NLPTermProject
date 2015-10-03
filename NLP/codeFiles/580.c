#include&lt;stdio.h&gt;
typedef struct{
	float i,j,k;
	}Vector;

Vector a = {3, 4, 5},b = {4, 3, 5},c = {-5, -12, -13};

float dotProduct(Vector a, Vector b)
{
	return a.i*b.i+a.j*b.j+a.k*b.k;
}

Vector crossProduct(Vector a,Vector b)
{
	Vector c = {a.j*b.k - a.k*b.j, a.k*b.i - a.i*b.k, a.i*b.j - a.j*b.i};
	
	return c;
}

float scalarTripleProduct(Vector a,Vector b,Vector c)
{
	return dotProduct(a,crossProduct(b,c));
}

Vector vectorTripleProduct(Vector a,Vector b,Vector c)
{
	return crossProduct(a,crossProduct(b,c));
}

void printVector(Vector a)
{
	printf(&quot;( %f, %f, %f)&quot;,a.i,a.j,a.k);
}

int main()
{
	printf(&quot;\n a = &quot;); printVector(a);
	printf(&quot;\n b = &quot;); printVector(b);
	printf(&quot;\n c = &quot;); printVector(c);
	printf(&quot;\n a . b = %f&quot;,dotProduct(a,b));
	printf(&quot;\n a x b = &quot;); printVector(crossProduct(a,b));
	printf(&quot;\n a . (b x c) = %f&quot;,scalarTripleProduct(a,b,c));
	printf(&quot;\n a x (b x c) = &quot;); printVector(vectorTripleProduct(a,b,c));
	
	return 0;
}
