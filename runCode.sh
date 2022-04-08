echo "compilando ..."
make
echo "programando el dispositivo..."
openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program build/simo.hex verify reset"