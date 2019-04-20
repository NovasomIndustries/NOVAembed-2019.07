#define dts_defs_part1_SOLO_DL "\
/dts-v1/;\n\
#include \"imx6dl.dtsi\"\n\
"
#define dts_defs_part1_QUAD "\
/dts-v1/;\n\
#include \"imx6q.dtsi\"\n\
"

#define dts_defs_part2_SOLO_DL "\
/ {\n\
        model = \"Freescale i.MX6 Solo/DualLite NOVAsomP Board\";\n\
        compatible = \"fsl,imx6sdl-novasom\", \"fsl,imx6dl\";\n\
};\n\
&cpu0 {\n\
        arm-supply = <&reg_arm>;\n\
        soc-supply = <&reg_soc>;\n\
};\n\
&gpc {\n\
        fsl,ldo-bypass = <0>;\n\
};\n\
&wdog2 {\n\
        status = \"disabled\";\n\
};\n\
"
#define dts_defs_part2_QUAD "\
/ {\n\
        model = \"Freescale i.MX6 Quad NOVAsomP Board\";\n\
        compatible = \"fsl,imx6q-novasom\", \"fsl,imx6q\";\n\
};\n\
&cpu0 {\n\
        arm-supply = <&reg_arm>;\n\
        soc-supply = <&reg_soc>;\n\
};\n\
&gpc {\n\
        fsl,ldo-bypass = <0>;\n\
};\n\
&wdog2 {\n\
        status = \"disabled\";\n\
};\n\
"

#define dts_defs_sata "\
&sata {\n\
        status = \"okay\";\n\
};\n\
"

#define dtsi_header1_defs "\
/*\n\
* Copyright 2017 Novasis, Inc.\n\
* Copyright 2017 Novasom Industries, Inc.\n\
*\n\
* The code contained herein is licensed under the GNU General Public\n\
* License.\n\
*/\n\
#include <dt-bindings/gpio/gpio.h>\n\
#include <dt-bindings/input/input.h>\n\
/ {\n\
    aliases {\n\
            mxcfb0 = &mxcfb1;\n\
            mxcfb1 = &mxcfb2;\n\
            mxcfb2 = &mxcfb3;\n\
    };\n\
    ir_recv: ir-receiver {\n\
            compatible = \"gpio-ir-receiver\";\n\
            gpios = <&gpio1 2 1>;\n\
            pinctrl-names = \"default\";\n\
            pinctrl-0 = <&pinctrl_novasomp_i_ir>;\n\
    };\n\
    leds {\n\
            compatible = \"gpio-leds\";\n\
            heartbeat-led {\n\
                    gpios = <&gpio3 31 0>;\n\
                    label = \"Heartbeat\";\n\
                    linux,default-trigger = \"heartbeat\";\n\
                pinctrl-names = \"default\";\n\
                pinctrl-0 = <&pinctrl_heartbeat>;\n\
            };\n\
            rc-feedback-led {\n\
                    gpios = <&gpio4 6 0>;\n\
                    label = \"Rc-Feedback\";\n\
                    linux,default-trigger = \"rc-feedback\";\n\
                pinctrl-names = \"default\";\n\
                pinctrl-0 = <&pinctrl_rc_feedback>;\n\
            };\n\
    };\n\
	memory {\n\
		reg = <0x10000000 0x80000000>;\n\
	};\n\
	regulators {\n\
		compatible = \"simple-bus\";\n\
		#address-cells = <1>;\n\
		#size-cells = <0>;\n\
		reg_2p5v: regulator@0 {\n\
			compatible = \"regulator-fixed\";\n\
			reg = <0>;\n\
			regulator-name = \"2P5V\";\n\
			regulator-min-microvolt = <2500000>;\n\
			regulator-max-microvolt = <2500000>;\n\
			regulator-always-on;\n\
		};\n\
		reg_3p3v: regulator@1 {\n\
			compatible = \"regulator-fixed\";\n\
			reg = <1>;\n\
			regulator-name = \"3P3V\";\n\
			regulator-min-microvolt = <3300000>;\n\
			regulator-max-microvolt = <3300000>;\n\
			regulator-always-on;\n\
		};\n\
        reg_usb_h1_vbus: regulator@2 {\n\
                compatible = \"regulator-fixed\";\n\
                reg = <0>;\n\
                regulator-name = \"usb_h1_vbus\";\n\
                regulator-min-microvolt = <5000000>;\n\
                regulator-max-microvolt = <5000000>;\n\
                enable-active-high;\n\
        };\n\
		reg_usb_otg_vbus: regulator@3 {\n\
			compatible = \"regulator-fixed\";\n\
			reg = <2>;\n\
			regulator-name = \"usb_otg_vbus\";\n\
			regulator-min-microvolt = <5000000>;\n\
			regulator-max-microvolt = <5000000>;\n\
			enable-active-high;\n\
		};\n\
        reg_pcie: regulator@4 {\n\
                compatible = \"regulator-fixed\";\n\
                reg = <3>;\n\
                pinctrl-names = \"default\";\n\
                pinctrl-0 = <&pinctrl_pcie_reg>;\n\
                regulator-name = \"MPCIE_3V3\";\n\
                regulator-min-microvolt = <3300000>;\n\
                regulator-max-microvolt = <3300000>;\n\
                gpio = <&gpio2 4 0>;\n\
                enable-active-high;\n\
        };\n\
        lvds_power: lvds_power {\n\
                compatible = \"regulator-fixed\";\n\
                pinctrl-names = \"default\";\n\
                pinctrl-0 = <&lvds_enable_reg>;\n\
                regulator-name = \"lvds_power\";\n\
                regulator-min-microvolt = <3300000>;\n\
                regulator-max-microvolt = <3300000>;\n\
                gpio = <&gpio4 5 0>;\n\
                enable-active-high;\n\
                regulator-always-on;\n\
        };\n\
        lvds_bl_power: lvds_bl_power {\n\
                compatible = \"regulator-fixed\";\n\
                pinctrl-names = \"default\";\n\
                pinctrl-0 = <&lvds_bl_enable_reg>;\n\
                regulator-name = \"lvds_bl_power\";\n\
                regulator-min-microvolt = <5000000>;\n\
                regulator-max-microvolt = <5000000>;\n\
                startup-delay-us = <70000>;\n\
                gpio = <&gpio7 13 0>;\n\
                enable-active-high;\n\
                regulator-always-on;\n\
        };\n\
		snvs_reg: vsnvs {\n\
			regulator-min-microvolt = <1000000>;\n\
			regulator-max-microvolt = <3000000>;\n\
			regulator-boot-on;\n\
			regulator-always-on;\n\
		};\n\
	};\n\
    sound-spdif {\n\
            compatible = \"fsl,imx-audio-spdif\";\n\
            model = \"imx-spdif\";\n\
            spdif-controller = <&spdif>;\n\
            spdif-out;\n\
    };\n\
    sound-hdmi {\n\
            compatible = \"fsl,imx6q-audio-hdmi\",\n\
                         \"fsl,imx-audio-hdmi\";\n\
            model = \"imx-audio-hdmi\";\n\
            hdmi-controller = <&hdmi_audio>;\n\
    };\n\
    backlight {\n\
            compatible = \"pwm-backlight\";\n\
            pwms = <&pwm1 0 5000000>;\n\
            power-supply = <&lvds_bl_power>;\n\
            brightness-levels = <0 4 8 16 32 64 128 255>;\n\
            default-brightness-level = <7>;\n\
            status = \"okay\";\n\
    };\n\
"

#define dtsi_header_hdmivideo1920_mxcfb1_defs "\
    mxcfb1: fb@0 {\n\
            compatible = \"fsl,mxc_sdc_fb\";\n\
            disp_dev = \"hdmi\";\n\
            interface_pix_fmt = \"RGB24\";\n\
            mode_str =\"1920x1080M@60\";\n\
            default_bpp = <24>;\n\
            int_clk = <0>;\n\
            late_init = <0>;\n\
            status = \"okay\";\n\
    };\n\
"
#define dtsi_header_hdmivideo1280_mxcfb1_defs "\
    mxcfb1: fb@0 {\n\
            compatible = \"fsl,mxc_sdc_fb\";\n\
            disp_dev = \"hdmi\";\n\
            interface_pix_fmt = \"RGB24\";\n\
            mode_str =\"1280x720M@60\";\n\
            default_bpp = <24>;\n\
            int_clk = <0>;\n\
            late_init = <0>;\n\
            status = \"okay\";\n\
    };\n\
"

#define dtsi_header_hdmivideo1920_mxcfb2_defs "\
    mxcfb2: fb@1 {\n\
            compatible = \"fsl,mxc_sdc_fb\";\n\
            disp_dev = \"hdmi\";\n\
            interface_pix_fmt = \"RGB24\";\n\
            mode_str =\"1920x1080M@60\";\n\
            default_bpp = <24>;\n\
            int_clk = <0>;\n\
            late_init = <0>;\n\
            status = \"okay\";\n\
    };\n\
"

#define dtsi_header_hdmivideo1280_mxcfb2_defs "\
    mxcfb2: fb@1 {\n\
            compatible = \"fsl,mxc_sdc_fb\";\n\
            disp_dev = \"hdmi\";\n\
            interface_pix_fmt = \"RGB24\";\n\
            mode_str =\"1280x720M@60\";\n\
            default_bpp = <24>;\n\
            int_clk = <0>;\n\
            late_init = <0>;\n\
            status = \"okay\";\n\
    };\n\
"

#define dtsi_header_lvdsvideo_mxcfb1_24_defs "\
    mxcfb1: fb@0 {\n\
            compatible = \"fsl,mxc_sdc_fb\";\n\
            disp_dev = \"ldb\";\n\
            interface_pix_fmt = \"RGB24\";\n\
            default_bpp = <18>;\n\
            int_clk = <0>;\n\
            late_init = <0>;\n\
            status = \"okay\";\n\
    };\n\
"
#define dtsi_header_lvdsvideo_mxcfb1_18_defs "\
    mxcfb1: fb@0 {\n\
            compatible = \"fsl,mxc_sdc_fb\";\n\
            disp_dev = \"ldb\";\n\
            interface_pix_fmt = \"RGB666\";\n\
            default_bpp = <18>;\n\
            int_clk = <0>;\n\
            late_init = <0>;\n\
            status = \"okay\";\n\
    };\n\
"
#define dtsi_header_lvdsvideo_mxcfb2_24_defs "\
    mxcfb2: fb@1 {\n\
            compatible = \"fsl,mxc_sdc_fb\";\n\
            disp_dev = \"ldb\";\n\
            interface_pix_fmt = \"RGB24\";\n\
            default_bpp = <24>;\n\
            int_clk = <0>;\n\
            late_init = <0>;\n\
            status = \"okay\";\n\
    };\n\
"
#define dtsi_header_lvdsvideo_mxcfb2_18_defs "\
    mxcfb2: fb@1 {\n\
            compatible = \"fsl,mxc_sdc_fb\";\n\
            disp_dev = \"ldb\";\n\
            interface_pix_fmt = \"RGB666\";\n\
            default_bpp = <24>;\n\
            int_clk = <0>;\n\
            late_init = <0>;\n\
            status = \"okay\";\n\
    };\n\
"
#define dtsi_header_lvdsvideo_mxcfb3_24_defs "\
    mxcfb3: fb@2 {\n\
            compatible = \"fsl,mxc_sdc_fb\";\n\
            disp_dev = \"ldb\";\n\
            interface_pix_fmt = \"RGB24\";\n\
            default_bpp = <24>;\n\
            int_clk = <0>;\n\
            late_init = <0>;\n\
            status = \"okay\";\n\
    };\n\
"
#define dtsi_header_lvdsvideo_mxcfb3_18_defs "\
    mxcfb3: fb@2 {\n\
            compatible = \"fsl,mxc_sdc_fb\";\n\
            disp_dev = \"ldb\";\n\
            interface_pix_fmt = \"RGB666\";\n\
            default_bpp = <24>;\n\
            int_clk = <0>;\n\
            late_init = <0>;\n\
            status = \"okay\";\n\
    };\n\
"

#define dtsi_footer_video_defs "\
};\n\
"

#define dtsi_header2_defs "\
&fec {\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_enet>;\n\
        phy-mode = \"rmii\";\n\
        phy-supply = <&reg_3p3v>;\n\
        status = \"okay\";\n\
};\n\
&hdmi_core {\n\
        ipu_id = <0>;\n\
        disp_id = <0>;\n\
        status = \"okay\";\n\
};\n\
&hdmi_video {\n\
        fsl,phy_reg_vlev = <0x0294>;\n\
        fsl,phy_reg_cksymtx = <0x800d>;\n\
        status = \"okay\";\n\
};\n\
&hdmi_audio {\n\
        status = \"okay\";\n\
};\n\
&hdmi_cec {\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_hdmi_cec>;\n\
        status = \"okay\";\n\
};\n\
&i2c2 {\n\
        clock-frequency = <100000>;\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_i2c2>;\n\
        status = \"okay\";\n\
        hdmi: edid@50 {\n\
                compatible = \"fsl,imx6-hdmi-i2c\";\n\
                reg = <0x50>;\n\
        };\n\
};\n\
&pwm1 {\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_pwm1>;\n\
        status = \"okay\";\n\
};\n\
&ssi1 {\n\
        fsl,mode = \"i2s-slave\";\n\
        status = \"okay\";\n\
};\n\
&uart3 {\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_uart3>;\n\
        status = \"okay\";\n\
};\n\
&uart5 {\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_uart5>;\n\
        fsl,uart-has-rtscts;\n\
        status = \"okay\";\n\
};\n\
&usbh1 {\n\
        vbus-supply = <&reg_usb_h1_vbus>;\n\
        status = \"okay\";\n\
};\n\
&usbotg {\n\
        vbus-supply = <&reg_usb_otg_vbus>;\n\
        pinctrl-names = \"default\";\n\
        disable-over-current;\n\
        srp-disable;\n\
        hnp-disable;\n\
        adp-disable;\n\
        status = \"okay\";\n\
};\n\
&usdhc1 {\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_usdhc1>;\n\
        cd-gpios = <&gpio1 1 GPIO_ACTIVE_LOW>;\n\
        no-1-8-v;\n\
        keep-power-in-suspend;\n\
        enable-sdio-wakeup;\n\
        status = \"okay\";\n\
};\n\
&usdhc4 {\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_usdhc4>;\n\
        bus-width = <8>;\n\
        vmmc-supply = <&reg_3p3v>;\n\
        status = \"okay\";\n\
};\n\
"

#define ecspi1_4_defs "\
&ecspi1 {\n\
        fsl,spi-num-chipselects = <1>;\n\
        cs-gpios = <&gpio5 17 0>;\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_ecspi1>;\n\
        status = \"okay\";\n\
};\n\
"

#define ecspi1_dev_4_defs "\
&ecspi1 {\n\
        fsl,spi-num-chipselects = <1>;\n\
        cs-gpios = <&gpio5 17 0>;\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_ecspi1>;\n\
        status = \"okay\";\n\
        spi@0 {\n\
            reg = <0>;\n\
            compatible = \"spidev\";\n\
            spi-max-frequency = <54000000>;\n\
        };\n\
};\n\
"

#define ecspi1_5_defs "\
&ecspi1 {\n\
        fsl,spi-num-chipselects = <2>;\n\
        cs-gpios = <&gpio5 17 0> ,  <&gpio5 9 0>;\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_ecspi1>;\n\
        status = \"okay\";\n\
};\n\
"
#define ecspi1_dev_5_defs "\
&ecspi1 {\n\
        fsl,spi-num-chipselects = <2>;\n\
        cs-gpios = <&gpio5 17 0> ,  <&gpio5 9 0>;\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_ecspi1>;\n\
        status = \"okay\";\n\
        spi@0 {\n\
                      reg = <0>;\n\
                      compatible = \"spidev\";\n\
                      spi-max-frequency = <54000000>;\n\
        };\n\
        spi@1 {\n\
                      reg = <1>;\n\
                      compatible = \"spidev\";\n\
                      spi-max-frequency = <54000000>;\n\
        };\n\
};\n\
"

#define ecspi2_4_defs "\
&ecspi2 {\n\
        fsl,spi-num-chipselects = <1>;\n\
        cs-gpios = <&gpio5 12 0>;\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_ecspi2>;\n\
        status = \"okay\";\n\
};\n\
"
#define ecspi2_dev_4_defs "\
&ecspi2 {\n\
        fsl,spi-num-chipselects = <1>;\n\
        cs-gpios = <&gpio5 12 0>;\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_ecspi2>;\n\
        status = \"okay\";\n\
        spi@0 {\n\
                      reg = <0>;\n\
                      compatible = \"spidev\";\n\
                      spi-max-frequency = <54000000>;\n\
        };\n\
};\n\
"

#define ecspi2_5_defs "\
&ecspi2 {\n\
        fsl,spi-num-chipselects = <2>;\n\
        cs-gpios = <&gpio5 12 0> ,  <&gpio5 9 0>;\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_ecspi2>;\n\
        status = \"okay\";\n\
};\n\
"

#define ecspi2_dev_5_defs "\
&ecspi2 {\n\
        fsl,spi-num-chipselects = <2>;\n\
        cs-gpios = <&gpio5 12 0> ,  <&gpio5 9 0>;\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_ecspi2>;\n\
        status = \"okay\";\n\
        spi@0 {\n\
                      reg = <0>;\n\
                      compatible = \"spidev\";\n\
                      spi-max-frequency = <54000000>;\n\
        };\n\
        spi@1 {\n\
                      reg = <1>;\n\
                      compatible = \"spidev\";\n\
                      spi-max-frequency = <54000000>;\n\
        };\n\
};\n\
"

#define ecspi3_4_defs "\
&ecspi3 {\n\
        fsl,spi-num-chipselects = <1>;\n\
        cs-gpios = <&gpio4 24 0>;\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_ecspi3>;\n\
        status = \"okay\";\n\
};\n\
"
#define ecspi3_dev_4_defs "\
&ecspi3 {\n\
        fsl,spi-num-chipselects = <1>;\n\
        cs-gpios = <&gpio4 24 0>;\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_ecspi3>;\n\
        status = \"okay\";\n\
        spi@0 {\n\
                      reg = <0>;\n\
                      compatible = \"spidev\";\n\
                      spi-max-frequency = <54000000>;\n\
        };\n\
};\n\
"

#define ecspi3_5_defs "\
&ecspi3 {\n\
        fsl,spi-num-chipselects = <2>;\n\
        cs-gpios = <&gpio4 24 0> ,  <&gpio4 25 0>;\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_ecspi3>;\n\
        status = \"okay\";\n\
};\n\
"
#define ecspi3_dev_5_defs "\
&ecspi3 {\n\
        fsl,spi-num-chipselects = <2>;\n\
        cs-gpios = <&gpio4 24 0> ,  <&gpio4 25 0>;\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_ecspi3>;\n\
        status = \"okay\";\n\
        spi@0 {\n\
                      reg = <0>;\n\
                      compatible = \"spidev\";\n\
                      spi-max-frequency = <54000000>;\n\
        };\n\
        spi@1 {\n\
                      reg = <1>;\n\
                      compatible = \"spidev\";\n\
                      spi-max-frequency = <54000000>;\n\
        };\n\
};\n\
"

#define ecspi4_4_defs "\
&ecspi4 {\n\
        fsl,spi-num-chipselects = <1>;\n\
        cs-gpios = <&gpio3 29 0>;\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_ecspi4>;\n\
        status = \"okay\";\n\
};\n\
"

#define ecspi4_dev_4_defs "\
&ecspi4 {\n\
        fsl,spi-num-chipselects = <1>;\n\
        cs-gpios = <&gpio3 29 0>;\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_ecspi4>;\n\
        status = \"okay\";\n\
        spi@0 {\n\
                      reg = <0>;\n\
                      compatible = \"spidev\";\n\
                      spi-max-frequency = <54000000>;\n\
        };\n\
};\n\
"

#define audmux4_defs "\
&audmux {\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_audmux4>;\n\
        status = \"okay\";\n\
};\n\
"
#define audmux5_defs "\
&audmux {\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_audmux5>;\n\
        status = \"okay\";\n\
};\n\
"
#define audmux6_defs "\
&audmux {\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_audmux6>;\n\
        status = \"okay\";\n\
};\n\
"
#define can1_defs "\
&can1 {\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_flexcan1>;\n\
        status = \"okay\";\n\
};\n\
"

#define can2_defs "\
&can2 {\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_flexcan2>;\n\
        status = \"okay\";\n\
};\n\
"

#define usdhc3_8_defs "\
&usdhc3 {\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_usdhc3>;\n\
        bus-width = <8>;\n\
        vmmc-supply = <&reg_3p3v>;\n\
        status = \"okay\";\n\
};\n\
"

#define usdhc3_4_defs "\
&usdhc3 {\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_usdhc3>;\n\
        bus-width = <4>;\n\
        vmmc-supply = <&reg_3p3v>;\n\
        status = \"okay\";\n\
};\n\
"

#define i2c1_defs_top "\
&i2c1 {\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_i2c1>;\n\
        status = \"okay\";\n\
"

#define i2c1_defs_bottom "\
};\n\
"

#define i2c3_defs_top "\
&i2c3 {\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_i2c3>;\n\
        status = \"okay\";\n\
"

#define i2c3_defs_bottom "\
        polytouch1: eeti@04 {\n\
                compatible = \"eeti,egalax_ts\";\n\
                reg = <0x04>;\n\
                pinctrl-names = \"default\";\n\
                pinctrl-0 = <&pinctrl_i2ctouch_irq>;\n\
                interrupt-parent = <&gpio1>;\n\
                interrupts = <6 0>;\n\
                wakeup-gpios = <&gpio5 5 GPIO_ACTIVE_HIGH>;\n\
                linux,wakeup;\n\
        };\n\
        polytouch2: edt-ft5x06@38 {\n\
                compatible = \"edt,edt-ft5x06\";\n\
                reg = <0x38>;\n\
                pinctrl-names = \"default\";\n\
                pinctrl-0 = <&pinctrl_i2ctouch_irq>;\n\
                interrupt-parent = <&gpio1>;\n\
                interrupts = <6 0>;\n\
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
                interrupt-parent = <&gpio1>;\n\
                interrupts-extended = <&gpio1 6 IRQ_TYPE_LEVEL_HIGH>;\n\
                irq-gpios = <&gpio1 6 GPIO_ACTIVE_HIGH>;\n\
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
};\n\
"

#define uart1_defs "\
&uart1 {\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_uart1>;\n\
        status = \"okay\";\n\
};\n\
"

#define uart2_4_defs "\
&uart2 {\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_uart2>;\n\
        fsl,uart-has-rtscts;\n\
        status = \"okay\";\n\
};\n\
"
#define uart2_2_defs "\
&uart2 {\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_uart2>;\n\
        status = \"okay\";\n\
};\n\
"

#define uart4_4_defs "\
&uart4 {\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_uart4>;\n\
        fsl,uart-has-rtscts;\n\
        status = \"okay\";\n\
};\n\
"

#define uart4_2_defs "\
&uart4 {\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_uart4>;\n\
        status = \"okay\";\n\
};\n\
"

#define pcie_enabled_defs "\
&pcie {\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_pcie>;\n\
        reset-gpio = <&gpio3 30 0>;\n\
        status = \"okay\";\n\
};\n\
"

#define pcie_disabled_defs "\
&pcie {\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_pcie>;\n\
        reset-gpio = <&gpio3 30 0>;\n\
        status = \"disabled\";\n\
};\n\
"
#define spdif_enabled_defs "\
&spdif {\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pinctrl_spdif>;\n\
        status = \"okay\";\n\
};\n\
"

#define iomux_defs "\
&iomuxc {\n\
    pinctrl-names = \"default\";\n\
    imx6qdl-novasomp {\n\
        pinctrl_enet: enetgrp {\n\
            fsl,pins = <\n\
                MX6QDL_PAD_ENET_MDC__ENET_MDC           0x1b0b0\n\
                MX6QDL_PAD_ENET_MDIO__ENET_MDIO         0x1b0b0\n\
                MX6QDL_PAD_ENET_CRS_DV__ENET_RX_EN      0x1b0b0\n\
                MX6QDL_PAD_ENET_RX_ER__ENET_RX_ER       0x1b0b0\n\
                MX6QDL_PAD_ENET_TX_EN__ENET_TX_EN       0x1b0b0\n\
                MX6QDL_PAD_ENET_RXD0__ENET_RX_DATA0     0x1b0b0\n\
                MX6QDL_PAD_ENET_RXD1__ENET_RX_DATA1     0x1b0b0\n\
                MX6QDL_PAD_ENET_TXD0__ENET_TX_DATA0     0x1b0b0\n\
                MX6QDL_PAD_ENET_TXD1__ENET_TX_DATA1     0x1b0b0\n\
            >;\n\
        };\n\
        pinctrl_hdmi_cec: hdmicecgrp {\n\
            fsl,pins = <\n\
                MX6QDL_PAD_EIM_A25__HDMI_TX_CEC_LINE    0x108b0\n\
            >;\n\
        };\n\
        pinctrl_i2c2: i2c2grp {\n\
            fsl,pins = <\n\
                MX6QDL_PAD_KEY_COL3__I2C2_SCL           0x4001b8b1\n\
                MX6QDL_PAD_KEY_ROW3__I2C2_SDA           0x4001b8b1\n\
            >;\n\
        };\n\
        pinctrl_heartbeat: heartbeatled-grp {\n\
            fsl,pins = <\n\
                MX6QDL_PAD_EIM_D31__GPIO3_IO31          0x17059\n\
            >;\n\
        };\n\
        pinctrl_rc_feedback: rc_feedbackled-grp {\n\
            fsl,pins = <\n\
                MX6QDL_PAD_KEY_COL0__GPIO4_IO06         0x17059\n\
            >;\n\
        };\n\
        pinctrl_novasomp_i_ir: novasomp-i-ir {\n\
            fsl,pins = <\n\
                MX6QDL_PAD_GPIO_2__GPIO1_IO02           0x1b0b1\n\
            >;\n\
        };\n\
        lvds_enable_reg: lvdsgrp {\n\
                fsl,pins = <\n\
                        MX6QDL_PAD_GPIO_18__GPIO7_IO13  0x17059\n\
                >;\n\
        };\n\
        lvds_bl_enable_reg: lvdsblgrp {\n\
                fsl,pins = <\n\
                        MX6QDL_PAD_GPIO_19__GPIO4_IO05  0x17059\n\
                >;\n\
        };\n\
        pinctrl_pcie: pciegrp {\n\
            fsl,pins = <\n\
                MX6QDL_PAD_EIM_D30__GPIO3_IO30          0x17059\n\
            >;\n\
        };\n\
        pinctrl_pcie_reg: pciereggrp {\n\
            fsl,pins = <\n\
                MX6QDL_PAD_NANDF_D4__GPIO2_IO04         0x1b0b0\n\
            >;\n\
        };\n\
        pinctrl_uart3: uart3grp {\n\
            fsl,pins = <\n\
                MX6QDL_PAD_EIM_D24__UART3_TX_DATA       0x1b0b1\n\
                MX6QDL_PAD_EIM_D25__UART3_RX_DATA       0x1b0b1\n\
            >;\n\
        };\n\
        pinctrl_uart5: uart5grp {\n\
            fsl,pins = <\n\
                MX6QDL_PAD_KEY_COL1__UART5_TX_DATA       0x1b0b1\n\
                MX6QDL_PAD_KEY_ROW1__UART5_RX_DATA       0x1b0b1\n\
                MX6QDL_PAD_KEY_ROW4__UART5_CTS_B	     0x1b0b1\n\
            >;\n\
        };\n\
        pinctrl_usdhc1: usdhc1grp {\n\
            fsl,pins = <\n\
                MX6QDL_PAD_SD1_CMD__SD1_CMD             0x17059\n\
                MX6QDL_PAD_SD1_CLK__SD1_CLK             0x10059\n\
                MX6QDL_PAD_GPIO_1__SD1_CD_B 	        0x17059\n\
                MX6QDL_PAD_SD1_DAT0__SD1_DATA0          0x17059\n\
                MX6QDL_PAD_SD1_DAT1__SD1_DATA1          0x17059\n\
                MX6QDL_PAD_SD1_DAT2__SD1_DATA2          0x17059\n\
                MX6QDL_PAD_SD1_DAT3__SD1_DATA3          0x17059\n\
            >;\n\
        };\n\
        pinctrl_usdhc4: usdhc4grp {\n\
            fsl,pins = <\n\
                MX6QDL_PAD_SD4_CMD__SD4_CMD             0x17059\n\
                MX6QDL_PAD_SD4_CLK__SD4_CLK             0x10059\n\
                MX6QDL_PAD_SD4_DAT0__SD4_DATA0          0x17059\n\
                MX6QDL_PAD_SD4_DAT1__SD4_DATA1          0x17059\n\
                MX6QDL_PAD_SD4_DAT2__SD4_DATA2          0x17059\n\
                MX6QDL_PAD_SD4_DAT3__SD4_DATA3          0x17059\n\
                MX6QDL_PAD_SD4_DAT4__SD4_DATA4          0x17059\n\
                MX6QDL_PAD_SD4_DAT5__SD4_DATA5          0x17059\n\
                MX6QDL_PAD_SD4_DAT6__SD4_DATA6          0x17059\n\
                MX6QDL_PAD_SD4_DAT7__SD4_DATA7          0x17059\n\
            >;\n\
        };\n\
        pinctrl_i2ctouch_irq: i2ctouch_irqgrp {\n\
                fsl,pinmux-ids = <\n\
                        MX6QDL_PAD_GPIO_6__GPIO1_IO06 \n\
                >;\n\
        };\n\
        pinctrl_pwm1: pwm1grp {\n\
                fsl,pins = <\n\
                        MX6QDL_PAD_GPIO_9__PWM1_OUT 0x1b0b1\n\
                >;\n\
        };\n\
"

#define dtsi_lvds_header_defs "\
&ldb {\n\
	status = \"okay\";\n\
"

#define dtsi_lvds_footer_defs "\
};\n\
"

