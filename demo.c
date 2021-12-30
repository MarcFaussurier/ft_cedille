#import <ç.h>
#import <test>
#import "test.c"

macro int f(int x)
{
	return (x);
}

macro rule (Hello <word>!)
{
	_(Hello dear <word>.)
}

int main(int ac, char **av)
{
	printf ("Hello Doe! ");
	return (0);
}
