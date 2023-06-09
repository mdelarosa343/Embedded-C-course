#include <stdio.h>
#include <stdint.h>
#include "stm32f746xx.h"
#include "UART.h"
#include "ADC.h"
#include "SYSTICK.h"
#include "TIM.h"


int main(void)
{
	//	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⡤⠖⠒⠲⢤⣤⣤⣤⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
	//	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⠴⠟⠒⠒⠛⠉⠉⠉⠁⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
	//	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠳⡀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
	//	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣄⣀⣄⣠⣤⠠⠤⠞⠛⢯⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀
	//	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣿⠁⢠⣖⣒⡂⠀⠀⠀⠀⠀⣹⣦⡄⠀⠀⠀⠀⠀⠀⠀
	//	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠖⠑⢲⠎⠀⠀⠹⡆⣀⣤⣶⣿⣿⣿⣷⣤⠀⠀⠀⠀⠀⠀
	//	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⠀⠀⢸⠀⠀⠀⠀⢿⣿⣿⣿⠿⠿⢩⣿⣿⠆⠀⠀⠀⠀⠀
	//	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⢀⡀⢸⢀⡀⠀⠀⣼⠋⠉⠀⠀⠀⢈⣭⠋⠀⠀⠀⠀⠀⠀
	//	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣴⣶⡿⣌⢁⣴⢎⡁⠀⢠⠇⠀⠀⠀⠀⠀⣸⠁⠀⠀⠀⠀⠀⠀⠀
	//	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣴⡾⠟⣫⣵⡾⢿⠉⠁⡤⢭⡾⠁⠀⠀⠀⠀⠀⣠⠃⠀⠀⠀⠀⠀⠀⠀⠀
	//	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣤⡾⠟⢋⣥⡶⠟⠛⠁⠀⣾⠀⠀⡇⠀⠹⣆⠀⠀⠀⠀⠀⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀
	//	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡀⠀⠀⠀⠈⠁⠀⠀⠈⠉⠀⠀⠀⠀⠀⣿⠀⠀⠓⠀⠀⠹⡆⠀⠀⠀⢸⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀
	//	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡼⠁⠙⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⡄⠀⠀⠀⠀⠀⢻⣼⡆⢠⡘⣯⠀⠀⠀⠀⠀⠀⠀⠀⠀
	tim3_PB0_output_compare();//⢷⡄⠀⠀⠀⠀⣸⣿⣇⣿⠀⠙⣦⣠⣤⠤⠤⠤⣄⣀⠀
	//	⣠⠴⢾⣍⡒⠶⠤⣤⣤⣤⡤⣿⠀⠀⠙⣦⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢻⣄⣀⣤⠾⢿⣟⣁⣃⢷⡀⠈⢿⣅⠀⠀⠀⢀⣉⣻
	//	⢇⣀⣀⣀⠙⠓⠶⠆⠀⠀⠀⠀⠀⠀⠀⠙⠢⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⣛⣛⣛⣸⣿⣳⣿⣧⣠⠶⠋⠉⠈⣿
	//	⢻⡀⠀⠉⠙⠒⠦⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠳⢤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢉⣩⣽⠟⣻⣿⢹⡿⠛⠛⠉⠀⠀⠀⠸
	//	⠀⠉⠓⠶⠤⠤⡤⠤⠤⠤⠴⠖⠒⢄⠀⠀⠀⠀⠀⠀⠀⠈⠙⠲⠦⣄⠀⠀⠀⠀⠀⠀⣀⣴⠾⠛⠉⣀⣴⣿⢏⣿⣖⠀⠀⠀⠀⠀⠀⠀
	//	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⣦⣀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠈⢀⣠⣴⠾⠛⠉⣀⣤⠾⠻⠍⣿⡿⠋⠉⠙⣧⡄⠀⠀⠀⠀⠀
	//	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠳⣤⠀⠀⠀⠀⠀⣴⡟⠛⠋⠉⣠⣴⠶⠋⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⡿⠶⠶⠶⠶⠶
	//	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠛⠶⣤⡴⠞⠉⠛⠛⠛⠛⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣇⠀⠀⠀⠀⠀
	//THE led blinker WIT NO while loop!
}
