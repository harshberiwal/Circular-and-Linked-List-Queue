
#MakeFile for Assignment_2
#Run Make then run Assignment_2.exe file 

Assignment_2: 
	gcc -o Assignment_2 llfifo.c cbfifo.c llfifo.h cbfifo.h main.c test_llfifo.c test_llfifo.h test_cbfifo.c test_cbfifo.h -Wall -Werror 

