CC=tcc
ALL=wind

all:V: $ALL

again:
	mk clean && mk

wind:
	$CC -lncurses wind.c -o wind
	
clean:
	rm -r $ALL
