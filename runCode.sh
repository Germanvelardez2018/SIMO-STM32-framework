echo "compilando ..."
make
echo "programando el dispositivo..."
openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program build/simo.hex verify reset"


# Leer memoria

#read_memory 0xaddress numerodebits(8,16,32) cantidadaleer



#Escribir memoria

# write_memory 0xaddress numerodebits(8,16,32) {datos1,dato2}


