echo "compilando ..."
make
echo "programando el dispositivo..."
sudo openocd -f interface/stlink-v2-1.cfg -f target/stm32f1x.cfg -c "program build/NRF24_SIMPLE.hex verify reset"