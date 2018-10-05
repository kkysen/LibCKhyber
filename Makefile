all:
	cd cmake-build-debug; make Khyber
	cp -p cmake-build-debug/libKhyber.a .

clean:
	cd cmake-build-debug; make clean
	rm -f libKhyber.a
