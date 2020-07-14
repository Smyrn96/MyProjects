all:
	mpicc -o main main.c

run:
	mpirun -np 14 main 10 numservers10_np14.txt

eg:
	mpirun -np 14 --hostfile myhosts.txt main 10 numservers10_np14.txt
	mpirun -np <count> --hostfile <file with hostnames> <executable> <NUM_SERVERS> <testfile>

clean:
	rm main