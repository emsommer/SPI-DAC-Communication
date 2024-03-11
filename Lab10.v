	module Lab10(input CLOCK_50, output [2:0]GPIO_1);
	Lab10Nios u0 (
		.clk_clk       (CLOCK_50),       //   clk.clk
		.reset_reset_n (1'b1), // reset.reset_n
		.spi_MISO      (null),      //   spi.MISO
		.spi_MOSI      (GPIO_1[0]),      //      .MOSI
		.spi_SCLK      (GPIO_1[1]),      //      .SCLK
		.spi_SS_n      (GPIO_1[2])       //      .SS_n
	);
endmodule 
