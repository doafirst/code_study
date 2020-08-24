all:	
	mkdir -p build/
	#mkdir -p build/v30

	#Start to compile dump_snoop_to_lhdc
	#gcc -c dump_hci_src/dump_snoop_to_lhdc.c -o build/dump_snoop_to_lhdc.o
	#gcc build/dump_snoop_to_lhdc.o -o dump_snoop_to_lhdc

	#Start to compile hex_transfer_text
	gcc -c writefifo.c -o build/writefifo.o
	gcc build/writefifo.o -o writefifo
	gcc -c readfifo.c -o build/readfifo.o
	gcc build/readfifo.o -o readfifo
clean:
	rm  -rf out/
	rm *.exe
