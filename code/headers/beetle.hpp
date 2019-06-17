#pragma once
#include <base_module.hpp>
#include <hwlib.hpp>
#include <moving_platform.hpp>
#include <qik_2s12v10.hpp>

namespace r2d2::moving_platform {

    class beetle_c : public moving_platform_c {
    private:
        qik_2s12v10_c &qik_2s12v10_motorcontroller;
        hwlib::adc &encode_m0;
        hwlib::adc &encode_m1;

    public:
        /**
         * @brief
         * Constructor beetle_c
         * @param    uart_port: r2d2::uart_ports_c
         * @param    baud_rate: unsigned int
         * @param    reset_pin: hwlib::pin_out &
         * @param    comm:      base_comm_c &
         */
        beetle_c(qik_2s12v10_c &qik_2s12v10_motorcontroller, base_comm_c &comm,
                 hwlib::adc &encode_m0, hwlib::adc &encode_m1);

        /**
         * @brief
         * This function will set the speed between -100 and 100 % speed
         * @detail
         * the speed set must not exceed -100 of 100, if it is, it will set back
         * to 100 or -100
         * @param    int: new speed percentage
         */
        void set_speed(int8_t new_speed) override;

        /**
         * @brief
         * This function will turn the beetle between -90 and 90
         * @detail
         * The degrees set must not exceed -90 of 90, if it is, it will set back
         * to -90 or 90
         * @param    int: new degrees
         */
        void turn(int16_t degrees) override;
    };
} // namespace r2d2::moving_platform
