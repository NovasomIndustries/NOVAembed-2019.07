#define dts_header "\n\
/dts-v1/;\n\
#include <dt-bindings/input/input.h>\n\
#include \"imx6ull.dtsi\"\n\
/ {\n\
	model = \"Novasis i.MX6 ULL NOVAsomU based Board\";\n\
	compatible = \"fsl,imx6ull-ddr3-arm2\", \"fsl,imx6ull\";\n\
	chosen {\n\
		stdout-path = &uart1;\n\
	};\n\
	memory {\n\
		reg = <0x80000000 0x10000000>;\n\
	};\n\
	reserved-memory {\n\
		#address-cells = <1>;\n\
		#size-cells = <1>;\n\
		ranges;\n\
		linux,cma {\n\
			compatible = \"shared-dma-pool\";\n\
			reusable;\n\
			size = <0x6000000>;\n\
			linux,cma-default;\n\
		};\n\
	};\n\
	backlight {\n\
		compatible = \"pwm-backlight\";\n\
		pwms = <&pwm1 0 40000>;\n\
		brightness-levels = <0 4 8 16 32 64 128 255>;\n\
		default-brightness-level = <6>;\n\
		status = \"okay\";\n\
	};\n\
	pxp_v4l2 {\n\
		compatible = \"fsl,imx6ul-pxp-v4l2\", \"fsl,imx6sx-pxp-v4l2\", \"fsl,imx6sl-pxp-v4l2\";\n\
		status = \"okay\";\n\
	};\n\
	clocks {\n\
		mclk0: mclk0 {\n\
			compatible = \"fixed-clock\";\n\
			#clock-cells = <0>;\n\
			clock-frequency = <24000000>;\n\
		};\n\
	};\n\
	regulators {\n\
		compatible = \"simple-bus\";\n\
		#address-cells = <1>;\n\
		#size-cells = <0>;\n\
	};\n\
	sound {\n\
		compatible = \"sgtl5000\", \"simple-audio-card\";\n\
		simple-audio-card,name = \"sgtl5000\";\n\
		simple-audio-card,format = \"i2s\";\n\
		simple-audio-card,bitclock-master = <&codec_dai>;\n\
		simple-audio-card,frame-master = <&codec_dai>;\n\
		simple-audio-card,widgets =\n\
			\"Microphone\", \"Mic Jack\",\n\
			\"Line\", \"Line In\",\n\
			\"Line\", \"Line Out\",\n\
			\"Headphone\", \"Headphone Jack\";\n\
		simple-audio-card,routing =\n\
			\"MIC_IN\", \"Mic Jack\",\n\
			\"Mic Jack\", \"Mic Bias\",\n\
			\"Headphone Jack\", \"HP_OUT\";\n\
		cpu_dai: simple-audio-card,cpu {\n\
			sound-dai = <&sai1>;\n\
		};\n\
		codec_dai: simple-audio-card,codec {\n\
			sound-dai = <&sgtl5000>;\n\
		};\n\
	};\n\
};\n\
\n\
&cpu0 {\n\
        operating-points = <\n\
                528000  1175000\n\
                396000  1175000\n\
                198000  1175000\n\
        >;\n\
        fsl,soc-operating-points = <\n\
                528000  1175000\n\
                396000  1175000\n\
                198000  1175000\n\
        >;\n\
        arm-supply = <&sw1c_reg>;\n\
        soc-supply = <&sw1c_reg>;\n\
        fsl,arm-soc-shared = <1>;\n\
};\n\
&clks {\n\
        assigned-clocks = <&clks IMX6UL_CLK_PLL4_AUDIO_DIV>;\n\
        assigned-clock-rates = <786432000>;\n\
};\n\
&fec2 {\n\
	pinctrl-names = \"default\";\n\
	pinctrl-0 = <&pinctrl_enet2>;\n\
	phy-mode = \"rmii\";\n\
	phy-handle = <&ethphy0>;\n\
	phy-supply = <&sw2_reg>;\n\
	status = \"okay\";\n\
	mdio {\n\
		#address-cells = <1>;\n\
		#size-cells = <0>;\n\
		ethphy0: ethernet-phy@1 {\n\
			compatible = \"ethernet-phy-ieee802.3-c22\";\n\
			reg = <1>;\n\
		};\n\
		ethphy1: ethernet-phy@2 {\n\
			compatible = \"ethernet-phy-ieee802.3-c22\";\n\
			reg = <2>;\n\
		};\n\
	};\n\
};\n\
&gpc {\n\
	fsl,cpu_pupscr_sw2iso = <0x1>;\n\
	fsl,cpu_pupscr_sw = <0x0>;\n\
	fsl,cpu_pdnscr_iso2sw = <0x1>;\n\
	fsl,cpu_pdnscr_iso = <0x1>;\n\
	fsl,ldo-bypass = <1>;\n\
};\n\
&i2c1 {\n\
	clock-frequency = <100000>;\n\
	pinctrl-names = \"default\";\n\
	pinctrl-0 = <&pinctrl_i2c1>;\n\
	status = \"okay\";\n\
        pmic: pfuze3000@08 {\n\
                compatible = \"fsl,pfuze3000\";\n\
                reg = <0x08>;\n\
                regulators {\n\
                        sw1a_reg: sw1a {\n\
                                regulator-min-microvolt = <700000>;\n\
                                regulator-max-microvolt = <3300000>;\n\
                                regulator-boot-on;\n\
                                regulator-always-on;\n\
                                regulator-ramp-delay = <6250>;\n\
                        };\n\
                        sw1c_reg: sw1b {\n\
                                regulator-min-microvolt = <700000>;\n\
                                regulator-max-microvolt = <1475000>;\n\
                                regulator-boot-on;\n\
                                regulator-always-on;\n\
                                regulator-ramp-delay = <6250>;\n\
                        };\n\
                        sw2_reg: sw2 {\n\
                                regulator-min-microvolt = <2500000>;\n\
                                regulator-max-microvolt = <3300000>;\n\
                                regulator-boot-on;\n\
                                regulator-always-on;\n\
                        };\n\
                        sw3a_reg: sw3 {\n\
                                regulator-min-microvolt = <900000>;\n\
                                regulator-max-microvolt = <1650000>;\n\
                                regulator-boot-on;\n\
                                regulator-always-on;\n\
                        };\n\
                        swbst_reg: swbst {\n\
                                regulator-min-microvolt = <5000000>;\n\
                                regulator-max-microvolt = <5150000>;\n\
                                regulator-boot-on;\n\
                                regulator-always-on;\n\
                        };\n\
                        snvs_reg: vsnvs {\n\
                                regulator-min-microvolt = <1000000>;\n\
                                regulator-max-microvolt = <3000000>;\n\
                                regulator-boot-on;\n\
                                regulator-always-on;\n\
                        };\n\
                        vref_reg: vrefddr {\n\
                                regulator-boot-on;\n\
                                regulator-always-on;\n\
                        };\n\
                        vgen1_reg: vldo1 {\n\
                                regulator-min-microvolt = <1800000>;\n\
                                regulator-max-microvolt = <3300000>;\n\
                                regulator-boot-on;\n\
                                regulator-always-on;\n\
                        };\n\
                        vgen2_reg: vldo2 {\n\
                                regulator-min-microvolt = <800000>;\n\
                                regulator-max-microvolt = <1550000>;\n\
                                regulator-boot-on;\n\
                                regulator-always-on;\n\
                        };\n\
                        vgen3_reg: vccsd {\n\
                                regulator-min-microvolt = <2850000>;\n\
                                regulator-max-microvolt = <3300000>;\n\
                                regulator-boot-on;\n\
                                regulator-always-on;\n\
                        };\n\
                        vgen4_reg: v33 {\n\
                                regulator-min-microvolt = <2850000>;\n\
                                regulator-max-microvolt = <3300000>;\n\
                                regulator-boot-on;\n\
                                regulator-always-on;\n\
                        };\n\
                        vgen5_reg: vldo3 {\n\
                                regulator-min-microvolt = <1800000>;\n\
                                regulator-max-microvolt = <3300000>;\n\
                                regulator-boot-on;\n\
                                regulator-always-on;\n\
                        };\n\
                        vgen6_reg: vldo4 {\n\
                                regulator-min-microvolt = <1800000>;\n\
                                regulator-max-microvolt = <3300000>;\n\
                                regulator-boot-on;\n\
                                regulator-always-on;\n\
                        };\n\
                };\n\
	};\n\
	sgtl5000: codec@0a {\n\
		compatible = \"fsl,sgtl5000\";\n\
		reg = <0x0a>;\n\
		#sound-dai-cells = <0>;\n\
		clocks = <&mclk0>;\n\
                VDDA-supply = <&vgen2_reg>;\n\
                VDDIO-supply = <&sw2_reg>;\n\
	};\n\
};\n\
\n\
&sai1 {\n\
	pinctrl-names = \"default\";\n\
	pinctrl-0 = <&pinctrl_sai1>;\n\
	status = \"okay\";\n\
};\n\
\n\
&iomuxc_snvs {\n\
        imx6ul-ddr3-arm2 {\n\
                pinctrl_ir: ir_detect {\n\
                        fsl,pins = <\n\
                                MX6ULL_PAD_SNVS_TAMPER2__GPIO5_IO02     0x80000000\n\
                        >;\n\
                };\n\
        };\n\
};\n\
&pwm1 {\n\
	pinctrl-names = \"default\";\n\
	pinctrl-0 = <&pinctrl_pwm1>;\n\
	status = \"okay\";\n\
};\n\
&pxp {\n\
	status = \"okay\";\n\
};\n\
&qspi {\n\
	pinctrl-names = \"default\";\n\
	pinctrl-0 = <&pinctrl_qspi>;\n\
	status = \"okay\";\n\
	ddrsmp=<0>;\n\
	flash0: n25q256a@0 {\n\
		#address-cells = <1>;\n\
		#size-cells = <1>;\n\
		compatible = \"micron,n25q256a\";\n\
		spi-max-frequency = <29000000>;\n\
		spi-nor,ddr-quad-read-dummy = <6>;\n\
		reg = <0>;\n\
	};\n\
};\n\
&uart1 {\n\
	pinctrl-names = \"default\";\n\
	pinctrl-0 = <&pinctrl_uart1>;\n\
	status = \"okay\";\n\
};\n\
&uart2 {\n\
	pinctrl-names = \"default\";\n\
	pinctrl-0 = <&pinctrl_uart2>;\n\
	status = \"okay\";\n\
};\n\
&uart3 {\n\
	pinctrl-names = \"default\";\n\
	pinctrl-0 = <&pinctrl_uart3>;\n\
	fsl,uart-has-rtscts;\n\
	status = \"okay\";\n\
};\n\
&usdhc1 {\n\
	pinctrl-names = \"default\", \"state_100mhz\", \"state_200mhz\";\n\
	pinctrl-0 = <&pinctrl_usdhc1>;\n\
	pinctrl-1 = <&pinctrl_usdhc1_100mhz>;\n\
	pinctrl-2 = <&pinctrl_usdhc1_200mhz>;\n\
	keep-power-in-suspend;\n\
	enable-sdio-wakeup;\n\
	vmmc-supply = <&vgen3_reg>;\n\
        vqmmc-supply = <&vgen3_reg>;\n\
	status = \"okay\";\n\
};\n\
&usbotg1 {\n\
        dr_mode = \"host\";\n\
        disable-over-current;\n\
        status = \"okay\";\n\
};\n\
&usbotg2 {\n\
        dr_mode = \"host\";\n\
        disable-over-current;\n\
        status = \"okay\";\n\
};\n\
&tsc {\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_tsc>;\n\
        xnur-gpio = <&gpio1 3 GPIO_ACTIVE_LOW>;\n\
        measure-delay-time = <0xffff>;\n\
        pre-charge-time = <0xfff>;\n\
        status = \"okay\";\n\
};\n\
&iomuxc {\n\
imx6ul-ddr3-arm2 {\n\
    pinctrl_hog: hoggrp {\
            fsl,pins = <\
                MX6UL_PAD_NAND_DATA07__GPIO4_IO09     0x4001b8b1\
          >;\
        };\
    pinctrl_sai1: sai1grp {\n\
        fsl,pins = <\n\
        MX6UL_PAD_CSI_DATA04__SAI1_TX_SYNC	0x1b0b0\n\
        MX6UL_PAD_CSI_DATA05__SAI1_TX_BCLK	0x1b0b0\n\
        MX6UL_PAD_CSI_DATA06__SAI1_RX_DATA	0x110b0\n\
        MX6UL_PAD_CSI_DATA07__SAI1_TX_DATA	0x1f0b8\n\
        >;\n\
    };\n\
    pinctrl_i2c1: i2c1grp {\n\
        fsl,pins = <\n\
        MX6UL_PAD_UART4_RX_DATA__I2C1_SDA	0x4001b8b1\n\
        MX6UL_PAD_UART4_TX_DATA__I2C1_SCL	0x4001b8b1\n\
        >;\n\
    };\n\
    pinctrl_enet2: enet2grp {\n\
        fsl,pins = <\n\
        MX6UL_PAD_GPIO1_IO07__ENET2_MDC         0x1b098\n\
        MX6UL_PAD_GPIO1_IO06__ENET2_MDIO        0x1b0b0\n\
        MX6UL_PAD_ENET2_TX_DATA0__ENET2_TDATA00 0x1b0a0\n\
        MX6UL_PAD_ENET2_TX_DATA1__ENET2_TDATA01 0x1b0a0\n\
        MX6UL_PAD_ENET2_TX_CLK__ENET2_REF_CLK2  0x4001b031\n\
        MX6UL_PAD_ENET2_TX_EN__ENET2_TX_EN      0x1b0b0\n\
        MX6UL_PAD_ENET2_RX_DATA0__ENET2_RDATA00 0x1b0b0\n\
        MX6UL_PAD_ENET2_RX_DATA1__ENET2_RDATA01 0x1b0b0\n\
        MX6UL_PAD_ENET2_RX_EN__ENET2_RX_EN      0x1b0b0\n\
        MX6UL_PAD_ENET2_RX_ER__ENET2_RX_ER      0x1b0b0\n\
        >;\n\
    };\n\
    pinctrl_esai: esaigrp {\n\
        fsl,pins = <\n\
        MX6UL_PAD_CSI_DATA00__ESAI_TX_HF_CLK     0x1b0b0\n\
        MX6UL_PAD_CSI_DATA01__ESAI_RX_HF_CLK     0x1b0b0\n\
        MX6UL_PAD_CSI_DATA04__ESAI_TX_FS         0x1b0b0\n\
        MX6UL_PAD_CSI_DATA05__ESAI_TX_CLK        0x1b0b0\n\
        MX6UL_PAD_CSI_DATA07__ESAI_T0            0x1b0b0\n\
        MX6UL_PAD_CSI_HSYNC__ESAI_TX1            0x1b0b0\n\
        MX6UL_PAD_CSI_PIXCLK__ESAI_TX2_RX3       0x1b0b0\n\
        MX6UL_PAD_CSI_MCLK__ESAI_TX3_RX2         0x1b0b0\n\
        MX6UL_PAD_CSI_DATA02__ESAI_RX_FS         0x1b0b0\n\
        MX6UL_PAD_CSI_DATA03__ESAI_RX_CLK        0x1b0b0\n\
        MX6UL_PAD_CSI_DATA06__ESAI_TX5_RX0       0x1b0b0\n\
        MX6UL_PAD_CSI_VSYNC__ESAI_TX4_RX1        0x1b0b0\n\
        >;\n\
    };\n\
    pinctrl_pwm1: pmw1grp {\n\
        fsl,pins = <\n\
        MX6UL_PAD_GPIO1_IO08__PWM1_OUT   0x110b0\n\
        >;\n\
    };\n\
    pinctrl_qspi: qspigrp {\n\
        fsl,pins = <\n\
        MX6UL_PAD_NAND_READY_B__QSPI_A_DATA00 0x70a1\n\
        MX6UL_PAD_NAND_CE0_B__QSPI_A_DATA01   0x70a1\n\
        MX6UL_PAD_NAND_CE1_B__QSPI_A_DATA02   0x70a1\n\
        MX6UL_PAD_NAND_CLE__QSPI_A_DATA03     0x70a1\n\
        MX6UL_PAD_NAND_WP_B__QSPI_A_SCLK      0x70a1\n\
        MX6UL_PAD_NAND_DQS__QSPI_A_SS0_B      0x70a1\n\
        >;\n\
    };\n\
    pinctrl_uart1: uart1grp {\n\
        fsl,pins = <\n\
        MX6UL_PAD_UART1_TX_DATA__UART1_DCE_TX 0x1b0b1\n\
        MX6UL_PAD_UART1_RX_DATA__UART1_DCE_RX 0x1b0b1\n\
        >;\n\
    };\n\
    pinctrl_uart2: uart2grp {\n\
        fsl,pins = <\n\
        MX6UL_PAD_UART2_TX_DATA__UART2_DCE_TX 0x1b0b1\n\
        MX6UL_PAD_UART2_RX_DATA__UART2_DCE_RX 0x1b0b1\n\
        >;\n\
    };\n\
    pinctrl_uart3: uart3grp {\n\
        fsl,pins = <\n\
        MX6UL_PAD_UART3_TX_DATA__UART3_DCE_TX 0x1b0b1\n\
        MX6UL_PAD_UART3_RX_DATA__UART3_DCE_RX 0x1b0b1\n\
        MX6UL_PAD_UART3_CTS_B__UART3_DTE_RTS 0x1b0b1\n\
        >;\n\
    };\n\
    pinctrl_usdhc1: usdhc1grp {\n\
        fsl,pins = <\n\
        MX6UL_PAD_SD1_CMD__USDHC1_CMD     0x17059\n\
        MX6UL_PAD_SD1_CLK__USDHC1_CLK     0x10059\n\
        MX6UL_PAD_SD1_DATA0__USDHC1_DATA0 0x17059\n\
        MX6UL_PAD_SD1_DATA1__USDHC1_DATA1 0x17059\n\
        MX6UL_PAD_SD1_DATA2__USDHC1_DATA2 0x17059\n\
        MX6UL_PAD_SD1_DATA3__USDHC1_DATA3 0x17059\n\
        >;\n\
    };\n\
    pinctrl_usdhc1_100mhz: usdhc1grp100mhz {\n\
        fsl,pins = <\n\
        MX6UL_PAD_SD1_CMD__USDHC1_CMD     0x170b9\n\
        MX6UL_PAD_SD1_CLK__USDHC1_CLK     0x100b9\n\
        MX6UL_PAD_SD1_DATA0__USDHC1_DATA0 0x170b9\n\
        MX6UL_PAD_SD1_DATA1__USDHC1_DATA1 0x170b9\n\
        MX6UL_PAD_SD1_DATA2__USDHC1_DATA2 0x170b9\n\
        MX6UL_PAD_SD1_DATA3__USDHC1_DATA3 0x170b9\n\
        >;\n\
    };\n\
    pinctrl_usdhc1_200mhz: usdhc1grp200mhz {\n\
        fsl,pins = <\n\
        MX6UL_PAD_SD1_CMD__USDHC1_CMD     0x170f9\n\
        MX6UL_PAD_SD1_CLK__USDHC1_CLK     0x100f9\n\
        MX6UL_PAD_SD1_DATA0__USDHC1_DATA0 0x170f9\n\
        MX6UL_PAD_SD1_DATA1__USDHC1_DATA1 0x170f9\n\
        MX6UL_PAD_SD1_DATA2__USDHC1_DATA2 0x170f9\n\
        MX6UL_PAD_SD1_DATA3__USDHC1_DATA3 0x170f9\n\
        >;\n\
    };\n\
    pinctrl_tsc: tscgrp {\n\
        fsl,pins = <\n\
        MX6UL_PAD_GPIO1_IO01__GPIO1_IO01        0xb0\n\
        MX6UL_PAD_GPIO1_IO02__GPIO1_IO02        0xb0\n\
        MX6UL_PAD_GPIO1_IO03__GPIO1_IO03        0xb0\n\
        MX6UL_PAD_GPIO1_IO04__GPIO1_IO04        0xb0\n\
        >;\n\
    };\n\
    pinctrl_i2c2: i2c2 {\n\
        fsl,pins = <\n\
        MX6UL_PAD_CSI_HSYNC__I2C2_SCL           0x4001b8b1\n\
        MX6UL_PAD_CSI_VSYNC__I2C2_SDA           0x4001b8b1\n\
        >;\n\
    };\n\
    pinctrl_i2ctouch_irq: i2ctouch_irq {\n\
        fsl,pins = <\n\
        MX6UL_PAD_LCD_RESET__GPIO3_IO04          0x1b0b1\n\
        >;\n\
    };\n\
    pinctrl_tsc2007: tsc2007_irq {\n\
        fsl,pins = <\n\
        MX6UL_PAD_CSI_DATA02__GPIO4_IO23         0x1b0b1\n\
        >;\n\
    };\n\
    pinctrl_lcdif_dat: lcdifdatgrp {\n\
        fsl,pins = <\n\
        MX6UL_PAD_LCD_DATA00__LCDIF_DATA00  0x79\n\
        MX6UL_PAD_LCD_DATA01__LCDIF_DATA01  0x79\n\
        MX6UL_PAD_LCD_DATA02__LCDIF_DATA02  0x79\n\
        MX6UL_PAD_LCD_DATA03__LCDIF_DATA03  0x79\n\
        MX6UL_PAD_LCD_DATA04__LCDIF_DATA04  0x79\n\
        MX6UL_PAD_LCD_DATA05__LCDIF_DATA05  0x79\n\
        MX6UL_PAD_LCD_DATA06__LCDIF_DATA06  0x79\n\
        MX6UL_PAD_LCD_DATA07__LCDIF_DATA07  0x79\n\
        MX6UL_PAD_LCD_DATA08__LCDIF_DATA08  0x79\n\
        MX6UL_PAD_LCD_DATA09__LCDIF_DATA09  0x79\n\
        MX6UL_PAD_LCD_DATA10__LCDIF_DATA10  0x79\n\
        MX6UL_PAD_LCD_DATA11__LCDIF_DATA11  0x79\n\
        MX6UL_PAD_LCD_DATA12__LCDIF_DATA12  0x79\n\
        MX6UL_PAD_LCD_DATA13__LCDIF_DATA13  0x79\n\
        MX6UL_PAD_LCD_DATA14__LCDIF_DATA14  0x79\n\
        MX6UL_PAD_LCD_DATA15__LCDIF_DATA15  0x79\n\
        MX6UL_PAD_LCD_DATA16__LCDIF_DATA16  0x79\n\
        MX6UL_PAD_LCD_DATA17__LCDIF_DATA17  0x79\n\
        MX6UL_PAD_LCD_DATA18__LCDIF_DATA18  0x79\n\
        MX6UL_PAD_LCD_DATA19__LCDIF_DATA19  0x79\n\
        MX6UL_PAD_LCD_DATA20__LCDIF_DATA20  0x79\n\
        MX6UL_PAD_LCD_DATA21__LCDIF_DATA21  0x79\n\
        MX6UL_PAD_LCD_DATA22__LCDIF_DATA22  0x79\n\
        MX6UL_PAD_LCD_DATA23__LCDIF_DATA23  0x79\n\
        >;\n\
    };\n\
    pinctrl_lcdif_ctrl: lcdifctrlgrp {\n\
        fsl,pins = <\n\
        MX6UL_PAD_LCD_CLK__LCDIF_CLK        0x79\n\
        MX6UL_PAD_LCD_ENABLE__LCDIF_ENABLE  0x79\n\
        MX6UL_PAD_LCD_HSYNC__LCDIF_HSYNC    0x79\n\
        MX6UL_PAD_LCD_VSYNC__LCDIF_VSYNC    0x79\n\
        >;\n\
    };\n\
"
#define dts_footer "\n\
};\n\
"
#define i2c2_defs_top "\n\
&i2c2 {\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_i2c2>;\n\
        status = \"okay\";\n\
"

#define i2c2_defs_bottom "\
        polytouch1: eeti@04 {\n\
                compatible = \"eeti,egalax_ts\";\n\
                reg = <0x04>;\n\
                pinctrl-names = \"default\";\n\
                pinctrl-0 = <&pinctrl_i2ctouch_irq>;\n\
                interrupt-parent = <&gpio3>;\n\
                interrupts = <4 0>;\n\
                wakeup-gpios = <&gpio4 31 GPIO_ACTIVE_HIGH>;\n\
                linux,wakeup;\n\
        };\n\
        polytouch2: edt-ft5x06@38 {\n\
                compatible = \"edt,edt-ft5x06\";\n\
                reg = <0x38>;\n\
                pinctrl-names = \"default\";\n\
                pinctrl-0 = <&pinctrl_i2ctouch_irq>;\n\
                interrupt-parent = <&gpio3>;\n\
                interrupts = <4 0>;\n\
                reset-gpios = <&gpio4 30 GPIO_ACTIVE_LOW>;\n\
                wake-gpios = <&gpio4 31 GPIO_ACTIVE_HIGH>;\n\
        };\n\
        polytouch3: gt911@5d {\n\
                compatible = \"goodix,gt911\";\n\
                pinctrl-names = \"default\";\n\
                pinctrl-0 = <&pinctrl_i2ctouch_irq>;\n\
                reg = <0x5d>;\n\
                substitute-i2c-address = <0x2c>;\n\
                esd-recovery-timeout-ms = <2000>;\n\
                interrupt-parent = <&gpio3>;\n\
                interrupts-extended = <&gpio3 4 IRQ_TYPE_LEVEL_HIGH>;\n\
                irq-gpios = <&gpio3 4 GPIO_ACTIVE_HIGH>;\n\
                reset-gpios = <&gpio4 30 GPIO_ACTIVE_LOW>;\n\
        };\n\
        polytouch4: ilitek@41 {\n\
                compatible = \"ilitek_ts\";\n\
                reg = <0x41>;\n\
                pinctrl-names = \"default\";\n\
                pinctrl-0 = <&pinctrl_i2ctouch_irq>;\n\
                interrupt-parent = <&gpio1>;\n\
                interrupts = <6 0>;\n\
                ilitek,irq-gpio = <&gpio1 6 GPIO_ACTIVE_HIGH>;\n\
                ilitek,reset-gpio = <&gpio4 30 GPIO_ACTIVE_LOW>;\n\
        };\n\
        touchscreen: tsc2007@48 {\n\
                compatible = \"ti,tsc2007\";\n\
                reg = <0x48>;\n\
                pinctrl-names = \"default\";\n\
                pinctrl-0 = <&pinctrl_tsc2007>;\n\
                interrupt-parent = <&gpio4>;\n\
                interrupts = <23 0>;\n\
                gpios = <&gpio4 23 GPIO_ACTIVE_LOW>;\n\
                ti,x-plate-ohms = <660>;\n\
                linux,wakeup;\n\
        };\n\
};\n\
"

#define spdif_defs "\
&spdif {\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_spdif>;\n\
        status = \"okay\";\n\
};\n\
"

#define spdif_pins "\
    pinctrl_spdif: spdif {\n\
        fsl,pins = <\n\
        MX6UL_PAD_GPIO1_IO08__SPDIF_OUT        0xb0\n\
        >;\n\
    };\n\
"

#define pwm2_defs "\
&pwm2 {\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_pwm2>;\n\
        status = \"okay\";\n\
};\n\
"
#define pwm2_pins "\
    pinctrl_pwm2: pwm2 {\n\
        fsl,pins = <\n\
        MX6UL_PAD_GPIO1_IO09__PWM2_OUT        0xb0\n\
        >;\n\
    };\n\
"


#define uart6_defs "\
&uart6 {\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_uart6>;\n\
        status = \"okay\";\n\
};\n\
"

#define uart6_pins "\
    pinctrl_uart6: uart6 {\n\
        fsl,pins = <\n\
        MX6UL_PAD_CSI_PIXCLK__UART6_DTE_TX        0xb0\n\
        MX6UL_PAD_CSI_MCLK__UART6_DTE_RX        0xb0\n\
        >;\n\
    };\n\
"

#define ecspi4_defs "\
&ecspi4 {\n\
        fsl,spi-num-chipselects = <1>;\n\
        cs-gpios = <&gpio4 9 0>;\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_ecspi4>;\n\
        status = \"okay\";\n\
};\n\
"
#define ecspi4_dev_4_defs "\
&ecspi4 {\n\
        fsl,spi-num-chipselects = <1>;\n\
        cs-gpios = <&gpio4 9 0>;\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_ecspi4 &pinctrl_ecspi4_cs_1>;\n\
        status = \"okay\";\n\
               spi@0 {\n\
                              reg = <0>;\n\
                              compatible = \"spidev\";\n\
                              spi-max-frequency = <27000000>;\n\
               };\n\
};\n\
"

#define ecspi4_pins "\
    pinctrl_ecspi4: ecspi4 {\n\
        fsl,pins = <\n\
        MX6UL_PAD_NAND_DATA04__ECSPI4_SCLK        0xb0\n\
        MX6UL_PAD_NAND_DATA05__ECSPI4_MOSI        0xb0\n\
        MX6UL_PAD_NAND_DATA06__ECSPI4_MISO        0xb0\n\
        >;\n\
    };\n\
    pinctrl_ecspi4_cs_1: ecspi4_cs_grp-1 {\n\
        fsl,pins = <\n\
        MX6UL_PAD_NAND_DATA07__GPIO4_IO09  0x10b0\n\
        >;\n\
    };\n\
"


#define can1_defs "\
&flexcan1 {\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_flexcan1>;\n\
        status = \"okay\";\n\
};\n\
"
#define can1_pins "\
    pinctrl_flexcan1: can1 {\n\
        fsl,pins = <\n\
        MX6UL_PAD_UART3_CTS_B__FLEXCAN1_TX        0xb0\n\
        MX6UL_PAD_UART3_RTS_B__FLEXCAN1_RX        0xb0\n\
        >;\n\
    };\n\
"

#define lcd_defs "\
&lcdif\n\
{\n\
    pinctrl-names = \"default\";\n\
    pinctrl-0 = <&pinctrl_lcdif_dat\n\
                 &pinctrl_lcdif_ctrl>;\n\
    display = <&display0>;\n\
    status = \"okay\";\n\
    display0: display \n\
    {\n\
        bits-per-pixel = <16>;\n\
        bus-width = <24>;\n\
        display-timings \n\
        {\n\
            native-mode = <&timing0>;\n\
            timing0: timing0 \n\
            {\n\
                clock-frequency = <30000000>;\n\
                hactive = <800>;\n\
                vactive = <480>;\n\
                hback-porch = <64>;\n\
                hfront-porch = <64>;\n\
                vback-porch = <22>;\n\
                vfront-porch = <23>;\n\
                hsync-len = <10>;\n\
                vsync-len = <10>;\n\
                hsync-active = <0>;\n\
                vsync-active = <0>;\n\
                de-active = <1>;\n\
                pixelclk-active = <0>;\n\
            };\n\
        };\n\
    };\n\
};\n\
"



