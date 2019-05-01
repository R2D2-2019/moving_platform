#include <qik_2s12v10.hpp>

namespace r2d2::moving_platform {

    qik_2s12v10_c::qik_2s12v10_c(r2d2::uart_ports_c &uart_port,
                                 unsigned int baud_rate,
                                 hwlib::pin_out &reset_pin)
        : reset_pin(reset_pin), usart_bus(baud_rate, uart_port) {
    }

    void qik_2s12v10_c::set_speed(const int8_t &new_speed) {
        // Todo: depending on the motor configuration, 127 may not be the
        // maximum value
        // Todo: change the speed variable to the actual speed.
        uint8_t speed_byte = 0;
        if (speed >= 0) {
            speed_byte = speed;
            usart_bus << qik_motor_m0_set_forward << speed_byte;
            usart_bus << qik_motor_m1_set_forward << speed_byte;
        } else {
            speed_byte = -1 * speed;
            usart_bus << qik_motor_m0_set_reverse << speed_byte;
            usart_bus << qik_motor_m1_set_reverse << speed_byte;
        }
    }
    void qik_2s12v10_c::set_m0_speed(const int8_t &new_speed) {
        // Todo: depending on the motor configuration, 127 may not be the
        // maximum value
        uint8_t speed_byte = 0;
        if (speed >= 0) {
            speed_byte = speed;
            usart_bus << qik_motor_m0_set_forward << speed_byte;
        } else {
            speed_byte = -1 * speed;
            usart_bus << qik_motor_m0_set_reverse << speed_byte;
        }
    }
    void qik_2s12v10_c::set_m1_speed(const int8_t &new_speed) {
        // Todo: depending on the motor configuration, 127 may not be the
        // maximum value
        uint8_t speed_byte = 0;
        if (speed >= 0) {
            speed_byte = speed;
            usart_bus << qik_motor_m1_set_forward << speed_byte;
        } else {
            speed_byte = -1 * speed;
            usart_bus << qik_motor_m1_set_reverse << speed_byte;
        }
    }

    void qik_2s12v10_c::init() {
        // reset the qik 2s12v10
        reset_pin.write(0);
        hwlib::wait_ms(1);
        reset_pin.write(1);
        hwlib::wait_ms(10);

        // setup the uart communication
        usart_bus << qik_autodetect_baudrate;
    }
    void qik_2s12v10_c::set_m0_brake(const uint8_t &brake) {
    }
    void qik_2s12v10_c::set_m1_brake(const uint8_t &brake) {
    }
    void qik_2s12v10_c::set_brakes(const uint8_t &brake) {
    }

    uint8_t qik_2s12v10_c::get_error() {
        while (usart_bus.available() > 0) {
            usart_bus.receive();
            hwlib::wait_ms(0.05);
        }                           // clear the buffer
        usart_bus << qik_get_error; // send request
        while (!usart_bus.available()) {
            hwlib::wait_ms(0.05);
        }                           // wait for answer
        return usart_bus.receive(); // return answer
    }
    uint8_t qik_2s12v10_c::get_configuration_parameter(const uint8_t &parameter) {
        while (usart_bus.available() > 0) {
            usart_bus.receive();
            hwlib::wait_ms(0.05);
        }                                                   // clear the buffer
        usart_bus << qik_get_config_parameter << parameter; // send request
        while (!usart_bus.available()) {
            hwlib::wait_ms(0.05);
        }                           // wait for answer
        return usart_bus.receive(); // return answer
    }
    void qik_2s12v10_c::set_configuration_parameter(const uint8_t &parameter,
                                                    const uint8_t &value) {
        
    }

    uint8_t qik_2s12v10_c::get_m0_current() {
        return 0;
    }
    uint8_t qik_2s12v10_c::get_m1_current() {
        return 0;
    }
    unsigned int qik_2s12v10_c::get_m0_current_milliamps() {
        return 0;
    }
    unsigned int qik_2s12v10_c::get_m1_current_milliamps() {
        return 0;
    }

} // namespace r2d2::moving_platform
