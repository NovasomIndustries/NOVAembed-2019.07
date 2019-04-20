#define dts_header "\n\
/dts-v1/;\n\
#include \"rk3328.dtsi\"\n\
#include <dt-bindings/input/input.h>\n\
/ {\n\
	model = \"Rockchip RK3328 EVB\";\n\
	compatible = \"rockchip,rk3328-evb\", \"rockchip,rk3328\";\n\
\n\
	chosen {\n\
		bootargs = \"earlycon=uart8250,mmio32,0xff130000 swiotlb=1 kpti=0 console=ttyFIQ0\";\n\
	};\n\
\n\
	fiq-debugger {\n\
		compatible = \"rockchip,fiq-debugger\";\n\
		rockchip,serial-id = <2>;\n\
		rockchip,signal-irq = <159>;\n\
		rockchip,wake-irq = <0>;\n\
		rockchip,irq-mode-enable = <0>;\n\
		rockchip,baudrate = <115200>;\n\
		interrupts = <GIC_SPI 127 IRQ_TYPE_LEVEL_LOW>;\n\
		status = \"okay\";\n\
	};\n\
\n\
	gmac_clkin: external-gmac-clock {\n\
		compatible = \"fixed-clock\";\n\
		clock-frequency = <125000000>;\n\
		clock-output-names = \"gmac_clkin\";\n\
		#clock-cells = <0>;\n\
	};\n\
\n\
	sdio_pwrseq: sdio-pwrseq {\n\
		compatible = \"mmc-pwrseq-simple\";\n\
		pinctrl-names = \"default\";\n\
		pinctrl-0 = <&wifi_enable_h>;\n\
		reset-gpios = <&gpio1 18 GPIO_ACTIVE_LOW>;\n\
	};\n\
\n\
	sound {\n\
		compatible = \"simple-audio-card\";\n\
		simple-audio-card,format = \"i2s\";\n\
		simple-audio-card,mclk-fs = <256>;\n\
		simple-audio-card,name = \"rockchip,rk3328\";\n\
		simple-audio-card,cpu {\n\
			sound-dai = <&i2s1>;\n\
		};\n\
		simple-audio-card,codec {\n\
			sound-dai = <&codec>;\n\
		};\n\
	};\n\
\n\
	hdmi-sound {\n\
		compatible = \"simple-audio-card\";\n\
		simple-audio-card,format = \"i2s\";\n\
		simple-audio-card,mclk-fs = <128>;\n\
		simple-audio-card,name = \"rockchip,hdmi\";\n\
		simple-audio-card,cpu {\n\
			sound-dai = <&i2s0>;\n\
		};\n\
		simple-audio-card,codec {\n\
			sound-dai = <&hdmi>;\n\
		};\n\
	};\n\
\n\
	spdif-sound {\n\
		compatible = \"simple-audio-card\";\n\
		simple-audio-card,name = \"rockchip,spdif\";\n\
		simple-audio-card,cpu {\n\
			sound-dai = <&spdif>;\n\
		};\n\
		simple-audio-card,codec {\n\
			sound-dai = <&spdif_out>;\n\
		};\n\
	};\n\
\n\
    spdif_out: spdif-out {\n\
        compatible = \"linux,spdif-dit\";\n\
        #sound-dai-cells = <0>;\n\
    };\n\
\n\
	vcc_host_vbus: host-vbus-regulator {\n\
		compatible = \"regulator-fixed\";\n\
		gpio = <&gpio0 RK_PA0 GPIO_ACTIVE_HIGH>;\n\
		pinctrl-names = \"default\";\n\
		pinctrl-0 = <&host_vbus_drv>;\n\
		regulator-name = \"vcc_host_vbus\";\n\
		regulator-min-microvolt = <5000000>;\n\
		regulator-max-microvolt = <5000000>;\n\
		enable-active-high;\n\
	};\n\
\n\
        vcc_otg_vbus: otg-vbus-regulator {\n\
            compatible = \"regulator-fixed\";\n\
            gpio = <&gpio0 RK_PD3 GPIO_ACTIVE_HIGH>;\n\
            pinctrl-names = \"default\";\n\
            pinctrl-0 = <&otg_vbus_drv>;\n\
            regulator-name = \"vcc_otg_vbus\";\n\
            regulator-min-microvolt = <5000000>;\n\
            regulator-max-microvolt = <5000000>;\n\
            enable-active-high;\n\
        };\n\
        vcc_phy: vcc-phy-regulator {\n\
            compatible = \"regulator-fixed\";\n\
            regulator-name = \"vcc_phy\";\n\
            regulator-always-on;\n\
            regulator-boot-on;\n\
        };\n\
        vcc_sd: sdmmc-regulator {\n\
            compatible = \"regulator-fixed\";\n\
            pinctrl-names = \"default\";\n\
            pinctrl-0 = <&sdmmc0m1_gpio>;\n\
            regulator-name = \"vcc_sd\";\n\
            regulator-min-microvolt = <3300000>;\n\
            regulator-max-microvolt = <3300000>;\n\
            vin-supply = <&vcc_io>;\n\
        };\n\
\n\
        wireless-bluetooth {\n\
            compatible = \"bluetooth-platdata\";\n\
            clocks = <&rk805 1>;\n\
            clock-names = \"ext_clock\";\n\
            uart_rts_gpios = <&gpio1 10 GPIO_ACTIVE_LOW>;\n\
            pinctrl-names = \"default\", \"rts_gpio\";\n\
            pinctrl-0 = <&uart0_rts>;\n\
            pinctrl-1 = <&uart0_gpios>;\n\
            BT,power_gpio = <&gpio1 21 GPIO_ACTIVE_HIGH>;\n\
            BT,wake_host_irq = <&gpio1 26 GPIO_ACTIVE_HIGH>;\n\
            status = \"okay\";\n\
        };\n\
        wireless-wlan {\n\
            compatible = \"wlan-platdata\";\n\
            rockchip,grf = <&grf>;\n\
            wifi_chip_type = \"rtl8723bs\";\n\
            sdio_vref = <3300>;\n\
            WIFI,host_poweren_gpio = <&gpio1 18 GPIO_ACTIVE_HIGH>;\n\
            WIFI,host_wake_irq = <&gpio1 19 GPIO_ACTIVE_HIGH>;\n\
            pinctrl-names = \"default\";\n\
            pinctrl-0 = <&bt_clk>;\n\
            status = \"okay\";\n\
        };\n\
\n\
        ir-receiver {\n\
            compatible = \"gpio-ir-receiver\";\n\
            gpios = <&gpio2 RK_PA2 GPIO_ACTIVE_LOW>;\n\
            pinctrl-names = \"default\";\n\
            pinctrl-0 = <&ir_rx>;\n\
        };\n\
        gpio-leds {\n\
            compatible = \"gpio-leds\";\n\
                rc-feedback  {\n\
                    label = \"gpio-rc-feedback\";\n\
                    gpios = <&gpio2 18 GPIO_ACTIVE_HIGH>;\n\
                    linux,default-trigger = \"gpio-rc-feedback\";\n\
                };\n\
                heartbeat  {\n\
                    label = \"heartbeat\";\n\
                    gpios = <&gpio0 30 GPIO_ACTIVE_HIGH>;\n\
                    linux,default-trigger = \"heartbeat\";\n\
                };\n\
        };\n\
};\n\
&pinctrl {\n\
	ir {\n\
		ir_rx: ir-rx {\n\
			rockchip,pins = <2 RK_PA2 RK_FUNC_1 &pcfg_pull_none>;\n\
		};\n\
	};\n\
\n\
	pmic {\n\
		pmic_int_l: pmic-int-l {\n\
		rockchip,pins =<2 RK_PA6 RK_FUNC_GPIO &pcfg_pull_up>;\n\
		};\n\
	};\n\
\n\
	sdio-pwrseq {\n\
		wifi_enable_h: wifi-enable-h {\n\
		rockchip,pins =<1 18 RK_FUNC_GPIO &pcfg_pull_none>;\n\
		};\n\
	};\n\
\n\
	usb {\n\
		host_vbus_drv: host-vbus-drv {\n\
			rockchip,pins =<0 RK_PA0 RK_FUNC_GPIO &pcfg_pull_none>;\n\
		};\n\
\n\
		otg_vbus_drv: otg-vbus-drv {\n\
			rockchip,pins =<0 RK_PD3 RK_FUNC_GPIO &pcfg_pull_none>;\n\
		};\n\
	};\n\
        wireless-bluetooth {\n\
                uart0_gpios: uart0-gpios {\n\
                rockchip,pins =<1 10 RK_FUNC_GPIO &pcfg_pull_none>;\n\
                };\n\
        };\n\
        clkout32k {\n\
                bt_clk: bt-clk {\n\
                rockchip,pins =<1 RK_PD4 RK_FUNC_1 &pcfg_pull_up>;\n\
                };\n\
        };\n\
};\n\
\
&codec {\n\
	#sound-dai-cells = <0>;\n\
	status = \"okay\";\n\
};\n\
\n\
&cpu0 {\n\
	cpu-supply = <&vdd_arm>;\n\
};\n\
&dmc {\n\
	center-supply = <&vdd_logic>;\n\
	status = \"okay\";\n\
};\n\
\n\
&display_subsystem {\n\
	status = \"okay\";\n\
};\n\
\n\
&emmc {\n\
	bus-width = <8>;\n\
	cap-mmc-highspeed;\n\
	mmc-hs200-1_8v;\n\
	supports-emmc;\n\
	disable-wp;\n\
	non-removable;\n\
	num-slots = <1>;\n\
	pinctrl-names = \"default\";\n\
	pinctrl-0 = <&emmc_clk &emmc_cmd &emmc_bus8>;\n\
	status = \"okay\";\n\
};\n\
\n\
&gmac2io {\n\
	phy-supply = <&vcc_phy>;\n\
	phy-mode = \"rgmii\";\n\
	clock_in_out = \"input\";\n\
	snps,reset-gpio = <&gpio1 RK_PC2 GPIO_ACTIVE_LOW>;\n\
	snps,reset-active-low;\n\
	snps,reset-delays-us = <0 10000 50000>;\n\
	assigned-clocks = <&cru SCLK_MAC2IO>, <&cru SCLK_MAC2IO_EXT>;\n\
	assigned-clock-parents = <&gmac_clkin>, <&gmac_clkin>;\n\
	pinctrl-names = \"default\";\n\
	pinctrl-0 = <&rgmiim1_pins>;\n\
	tx_delay = <0x26>;\n\
	rx_delay = <0x11>;\n\
	status = \"disabled\";\n\
};\n\
\n\
&gmac2phy {\n\
	phy-supply = <&vcc_phy>;\n\
	clock_in_out = \"output\";\n\
	assigned-clocks = <&cru SCLK_MAC2PHY_SRC>;\n\
	assigned-clock-rate = <50000000>;\n\
	assigned-clocks = <&cru SCLK_MAC2PHY>;\n\
	assigned-clock-parents = <&cru SCLK_MAC2PHY_SRC>;\n\
	status = \"okay\";\n\
};\n\
\n\
&gpu {\n\
	status = \"okay\";\n\
	mali-supply = <&vdd_logic>;\n\
};\n\
\n\
&hdmi {\n\
	#sound-dai-cells = <0>;\n\
	ddc-i2c-scl-high-time-ns = <9625>;\n\
	ddc-i2c-scl-low-time-ns = <10000>;\n\
	status = \"okay\";\n\
};\n\
\n\
&hdmiphy {\n\
	status = \"okay\";\n\
};\n\
\n\
&i2c1 {\n\
	status = \"okay\";\n\
	rk805: rk805@18 {\n\
		compatible = \"rockchip,rk805\";\n\
		status = \"okay\";\n\
		reg = <0x18>;\n\
		interrupt-parent = <&gpio2>;\n\
		interrupts = <6 IRQ_TYPE_LEVEL_LOW>;\n\
		pinctrl-names = \"default\";\n\
		pinctrl-0 = <&pmic_int_l> ;\n\
		rockchip,system-power-controller;\n\
		wakeup-source;\n\
		gpio-controller;\n\
		#gpio-cells = <2>;\n\
		#clock-cells = <1>;\n\
		clock-output-names = \"xin32k\", \"rk805-clkout2\";\n\
		rtc {\n\
			status = \"okay\";\n\
		};\n\
\n\
		pwrkey {\n\
			status = \"okay\";\n\
		};\n\
\n\
		gpio {\n\
			status = \"okay\";\n\
		};\n\
\n\
		regulators {\n\
			compatible = \"rk805-regulator\";\n\
			status = \"okay\";\n\
			#address-cells = <1>;\n\
			#size-cells = <0>;\n\
			vdd_logic: RK805_DCDC1 {\n\
				regulator-compatible = \"RK805_DCDC1\";\n\
				regulator-name = \"vdd_logic\";\n\
				regulator-min-microvolt = <712500>;\n\
				regulator-max-microvolt = <1450000>;\n\
				regulator-initial-mode = <0x1>;\n\
				regulator-ramp-delay = <12500>;\n\
				regulator-boot-on;\n\
				regulator-always-on;\n\
				regulator-state-mem {\n\
					regulator-mode = <0x2>;\n\
					regulator-on-in-suspend;\n\
					regulator-suspend-microvolt = <1000000>;\n\
				};\n\
			};\n\
\n\
			vdd_arm: RK805_DCDC2 {\n\
				regulator-compatible = \"RK805_DCDC2\";\n\
				regulator-name = \"vdd_arm\";\n\
				regulator-min-microvolt = <712500>;\n\
				regulator-max-microvolt = <1450000>;\n\
				regulator-initial-mode = <0x1>;\n\
				regulator-ramp-delay = <12500>;\n\
				regulator-boot-on;\n\
				regulator-always-on;\n\
				regulator-state-mem {\n\
					regulator-mode = <0x2>;\n\
					regulator-on-in-suspend;\n\
					regulator-suspend-microvolt = <950000>;\n\
				};\n\
			};\n\
\n\
			vcc_ddr: RK805_DCDC3 {\n\
				regulator-compatible = \"RK805_DCDC3\";\n\
				regulator-name = \"vcc_ddr\";\n\
				regulator-initial-mode = <0x1>;\n\
				regulator-boot-on;\n\
				regulator-always-on;\n\
				regulator-state-mem {\n\
					regulator-mode = <0x2>;\n\
					regulator-on-in-suspend;\n\
				};\n\
			};\n\
\n\
			vcc_io: RK805_DCDC4 {\n\
				regulator-compatible = \"RK805_DCDC4\";\n\
				regulator-name = \"vcc_io\";\n\
				regulator-min-microvolt = <3300000>;\n\
				regulator-max-microvolt = <3300000>;\n\
				regulator-initial-mode = <0x1>;\n\
				regulator-boot-on;\n\
				regulator-always-on;\n\
				regulator-state-mem {\n\
					regulator-mode = <0x2>;\n\
					regulator-on-in-suspend;\n\
					regulator-suspend-microvolt = <3300000>;\n\
				};\n\
			};\n\
\n\
			vdd_18: RK805_LDO1 {\n\
				regulator-compatible = \"RK805_LDO1\";\n\
				regulator-name = \"vdd_18\";\n\
				regulator-min-microvolt = <1800000>;\n\
				regulator-max-microvolt = <1800000>;\n\
				regulator-boot-on;\n\
				regulator-always-on;\n\
				regulator-state-mem {\n\
					regulator-on-in-suspend;\n\
					regulator-suspend-microvolt = <1800000>;\n\
				};\n\
			};\n\
\n\
			vcc_18emmc: RK805_LDO2 {\n\
				regulator-compatible = \"RK805_LDO2\";\n\
				regulator-name = \"vcc_18emmc\";\n\
				regulator-min-microvolt = <1800000>;\n\
				regulator-max-microvolt = <1800000>;\n\
				regulator-boot-on;\n\
				regulator-always-on;\n\
				regulator-state-mem {\n\
					regulator-on-in-suspend;\n\
					regulator-suspend-microvolt = <1800000>;\n\
				};\n\
			};\n\
\n\
			vdd_11: RK805_LDO3 {\n\
				regulator-compatible = \"RK805_LDO3\";\n\
				regulator-name = \"vdd_11\";\n\
				regulator-min-microvolt = <1100000>;\n\
				regulator-max-microvolt = <1100000>;\n\
				regulator-boot-on;\n\
				regulator-always-on;\n\
				regulator-state-mem {\n\
					regulator-on-in-suspend;\n\
					regulator-suspend-microvolt = <1100000>;\n\
				};\n\
			};\n\
		};\n\
	};\n\
};\n\
\n\
&h265e {\n\
	status = \"okay\";\n\
};\n\
\n\
&i2s0 {\n\
	#sound-dai-cells = <0>;\n\
	rockchip,bclk-fs = <128>;\n\
	status = \"okay\";\n\
};\n\
\n\
&i2s1 {\n\
	#sound-dai-cells = <0>;\n\
	status = \"okay\";\n\
};\n\
\n\
&io_domains {\n\
	status = \"okay\";\n\
	vccio1-supply = <&vcc_io>;\n\
	vccio2-supply = <&vcc_18emmc>;\n\
	vccio3-supply = <&vcc_io>;\n\
	vccio4-supply = <&vdd_18>;\n\
	vccio5-supply = <&vcc_io>;\n\
	vccio6-supply = <&vcc_io>;\n\
	pmuio-supply = <&vcc_io>;\n\
};\n\
\n\
\n\
&rkvdec {\n\
	status = \"okay\";\n\
};\n\
\n\
&rockchip_suspend {\n\
	status = \"okay\";\n\
	rockchip,virtual-poweroff = <1>;\n\
};\n\
\n\
&saradc {\n\
	status = \"okay\";\n\
	vref-supply = <&vdd_18>;\n\
};\n\
&uart0 {\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&uart0_xfer &uart0_cts>;\n\
        status = \"okay\";\n\
};\n\
\n\
&uart2 {\n\
        status = \"okay\";\n\
};\n\
\n\
&sdio {\n\
	bus-width = <4>;\n\
	cap-sd-highspeed;\n\
	cap-sdio-irq;\n\
	disable-wp;\n\
	keep-power-in-suspend;\n\
	max-frequency = <150000000>;\n\
	mmc-pwrseq = <&sdio_pwrseq>;\n\
	non-removable;\n\
	num-slots = <1>;\n\
	pinctrl-names = \"default\";\n\
	pinctrl-0 = <&sdmmc1_bus4 &sdmmc1_cmd &sdmmc1_clk>;\n\
	supports-sdio;\n\
	status = \"okay\";\n\
};\n\
\n\
&sdmmc {\n\
	bus-width = <4>;\n\
	cap-mmc-highspeed;\n\
	cap-sd-highspeed;\n\
	disable-wp;\n\
	max-frequency = <150000000>;\n\
	num-slots = <1>;\n\
	pinctrl-names = \"default\";\n\
	pinctrl-0 = <&sdmmc0_clk &sdmmc0_cmd &sdmmc0_dectn &sdmmc0_bus4>;\n\
	supports-sd;\n\
	status = \"okay\";\n\
	vmmc-supply = <&vcc_sd>;\n\
};\n\
\n\
&spdif {\n\
	#sound-dai-cells = <0>;\n\
	status = \"okay\";\n\
};\n\
\n\
&tsadc {\n\
	status = \"okay\";\n\
};\n\
\n\
&u2phy {\n\
	status = \"okay\";\n\
	u2phy_host: host-port {\n\
		status = \"okay\";\n\
	};\n\
	u2phy_otg: otg-port {\n\
		vbus-supply = <&vcc_otg_vbus>;\n\
		status = \"okay\";\n\
	};\n\
};\n\
\n\
&u3phy {\n\
	vbus-supply = <&vcc_host_vbus>;\n\
	status = \"okay\";\n\
};\n\
\n\
&u3phy_utmi {\n\
	status = \"okay\";\n\
};\n\
\n\
&u3phy_pipe {\n\
	status = \"okay\";\n\
};\n\
\n\
&usb20_otg {\n\
	status = \"okay\";\n\
};\n\
\n\
&usb_host0_ehci {\n\
	status = \"okay\";\n\
};\n\
\n\
&usb_host0_ohci {\n\
	status = \"okay\";\n\
};\n\
\n\
&usbdrd3 {\n\
	status = \"okay\";\n\
};\n\
\n\
&usbdrd_dwc3 {\n\
	status = \"okay\";\n\
};\n\
\n\
&vepu {\n\
	status = \"okay\";\n\
};\n\
\n\
&vop {\n\
	status = \"okay\";\n\
};\n\
\n\
&vop_mmu {\n\
	status = \"okay\";\n\
};\n\
\n\
&vpu_service {\n\
	status = \"okay\";\n\
};\n\
"

#define i2c0_defs_top "\n\
&i2c0 {\n\
	status = \"okay\";\n\
"

#define i2c0_footer "\
};\n\
"

#define spi_defs "\n\
&spi0 {\n\
        status = \"okay\";\n\
        max-freq = <48000000>; /* spi internal clk, don't modify */\n\
"

#define spidev_defs "\n\
        spi_dev@0 {\n\
                compatible = \"rockchip,spidev\";\n\
                reg = <0>;\n\
                spi-max-frequency = <12000000>;\n\
                spi-lsb-first;\n\
        };\n\
"
#define spi_footer "\n\
};\n\
"


#define uart1_defs "\n\
&uart1 {\n\
        status = \"okay\";\n\
        pinctrl-names = \"default\";\n\
};\n\
"
#define uart1_4wires_defs "\n\
&uart1 {\n\
        status = \"okay\";\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&uart1_xfer &uart1_cts>;\n\
};\n\
"

#define dts_footer "\n\
};\n\
"
