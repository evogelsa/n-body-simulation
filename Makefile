build:
	g++ main.cpp integration.cpp vector3d.cpp body.cpp -o main.out -fopenmp

run:
	./main.out

build-run: build run

clean:
	rm *.out

clean-deep: clean
	rm output.csv
