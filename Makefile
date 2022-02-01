build:
	cd src/ && g++ main.cpp integration.cpp vector3d.cpp body.cpp -o ../main.out -fopenmp
	mkdir -p build
	mv main.out build/

run:
	build/main.out

build-run: build run

clean:
	rm build/*.out

clean-deep: clean
	rm build/output.csv
