#import <ç.h>
#import <test>
#import "test.c"

macro int f(int x)
{
	return (x);
}
#import "test.c"
macro rule (Hello <word>!)
{
	return(cat("Hello dear ", word));
}

int main(int ac, char **av)
{
	printf ("Hello Doe!");
	return (0);
}

