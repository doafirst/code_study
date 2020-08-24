all:
	mkdir -p build/
	#Start to compile dump_snoop_to_lhdc
	gcc -c dump_hci_src/dump_snoop_to_lhdc.c -o build/dump_snoop_to_lhdc.o
	gcc build/dump_snoop_to_lhdc.o -o dump_snoop_to_lhdc

	#Start to compile hex_transfer_text
	gcc -c hex_to_text/hex_transfer_text.c -o build/hex_transfer_text.o
	gcc build/hex_transfer_text.o -o hex_transfer_text

clean:
	rm  -rf out/
	rm *.exe