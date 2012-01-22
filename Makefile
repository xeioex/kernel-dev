all:
	cd ./src && make -f ./Makefile && cd ../ && ./update_image.sh

clean:
	cd ./src && make -f ./Makefile clean && cd ../
	

