openocd -f interface/stlink.cfg -f target/stm32h7x.cfg -c "program build/zephyr/zephyr.elf verify reset exit"