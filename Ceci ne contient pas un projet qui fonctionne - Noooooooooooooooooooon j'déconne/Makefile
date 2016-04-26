# ROLLIN Antoine - PC - Rendu 4 - Version 0123 

CC = gcc -std=gnu99 -O2
OBJ = bin/main.o bin/project.o bin/matrix.o bin/utils.o bin/version.o bin/version0.o bin/version1.o bin/version2.o bin/version3.o bin/region.o bin/argument.o bin/condbarrier.o bin/sembarrier.o

bin/project: $(OBJ)
	@echo " "
	@echo "Building executable..."
	$(CC) -o bin/project $(OBJ) -lm -lpthread
	@echo "==> project"
	@echo " "
	@echo "Cleaning object files..."
	make clean
	@echo " "
	@echo "------------------------------"
	@echo "The progam is ready to be used"
	@echo "------------------------------"
	
bin/main.o: src/main.c src/utils.h src/version0.h src/version1.h src/matrix.h
	@echo "----------------"
	@echo "    MAKEFILE"
	@echo "----------------"
	rm -rf bin
	mkdir bin
	@echo " "
	@echo "Building object files:"
	$(CC) -o bin/main.o -c src/main.c
	@echo "-> main.o"

bin/project.o: src/project.c src/project.h
	$(CC) -o bin/project.o -c src/project.c
	@echo "-> project.o"

bin/matrix.o: src/matrix.c src/matrix.h src/project.h src/utils.h
	$(CC) -o bin/matrix.o -c src/matrix.c
	@echo "-> matrix.o"

bin/utils.o: src/utils.c src/utils.h src/project.h
	$(CC) -o bin/utils.o -c src/utils.c
	@echo "-> utils.o"
	
bin/region.o: src/region.c src/region.h
	$(CC) -o bin/region.o -c src/region.c
	@echo "-> region.o"

bin/argument.o: src/argument.c src/argument.h src/matrix.h src/region.h
	$(CC) -o bin/argument.o -c src/argument.c
	@echo "-> argument.o"
	
bin/condbarrier.o: src/condbarrier.c src/condbarrier.h
	$(CC) -o bin/condbarrier.o -c src/condbarrier.c
	@echo "-> condbarrier.o"

bin/sembarrier.o: src/sembarrier.c src/sembarrier.h
	$(CC) -o bin/sembarrier.o -c src/sembarrier.c
	@echo "-> sembarrier.o"

bin/version.o: src/version.c src/version.h src/matrix.h src/region.h
	$(CC) -o bin/version.o -c src/version.c
	@echo "-> version.o"

bin/version0.o: src/version0.c src/version0.h src/matrix.h src/project.h src/version.h
	$(CC) -o bin/version0.o -c src/version0.c
	@echo "-> version0.o"

bin/version1.o: src/version1.c src/version1.h src/matrix.h src/project.h src/region.h src/argument.h src/version.h
	$(CC) -o bin/version1.o -c src/version1.c
	@echo "-> version1.o"

bin/version2.o: src/version2.c src/version2.h src/matrix.h src/project.h src/region.h src/argument.h src/condbarrier.h src/version.h
	$(CC) -o bin/version2.o -c src/version2.c
	@echo "-> version2.o"
	
bin/version3.o: src/version3.c src/version3.h src/matrix.h src/project.h src/region.h src/argument.h src/sembarrier.h src/version.h
	$(CC) -o bin/version3.o -c src/version3.c
	@echo "-> version3.o"

clean:
	rm -f ./bin/*.o
	@echo "Folder cleaned up from object files"
	@echo ""

