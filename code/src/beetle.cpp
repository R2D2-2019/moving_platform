#include <beetle.hpp>

namespace r2d2::moving_platform {

    beetle_c::beetle_c(r2d2::uart_ports_c &uart_port_one,
             unsigned int baud_rate,
             hwlib::pin_out &reset_pin, 
             base_comm_c &comm):
             moving_platform_c(comm),
             qik_2s12v10_motorcontroller (uart_port_one, baud_rate, reset_pin)
    {
        
        qik_2s12v10_motorcontroller.init();
        qik_2s12v10_motorcontroller.get_configuration_parameter(1);

    }
    void beetle_c::set_speed(const int8_t &new_speed){
        // Todo: depending on the motor configuration, 127 may not be the
        // maximum value
        // Todo: change the speed variable to the actual speed.

        // the speed is given in percentage (-100 (backward) till 100 (foreward))
        speed = new_speed;
        // do not go out of range
        if(speed > 100){
            speed = 100;
        } else if (speed <-100){
            speed = -100;
        } 
        // because of inaccuracies, when not touching the pendals of manual control, a number beween -3 and 8 can be given
        // Just to make sure the robot will not move forward then and not react to quickly, a theshold is made for -10 till 10.
        else if (speed < 10 && speed > -10){
            speed = 0;
            qik_2s12v10_motorcontroller.set_m0_speed(0);
            qik_2s12v10_motorcontroller.set_m1_speed(0);
        }
    }

    void beetle_c::set_steering(const int16_t &degrees){

    }
    void beetle_c::turn(const int16_t &degrees){
        int new_degrees = degrees;
        // because of inaccuracies, when moving forward, the steer of manual control will give a number beween -10 and 10
        // Just to make sure the robot will move forward and not react to quickly, a theshold is made for -15 till 15.
        if(new_degrees < 15 && new_degrees > -15){
            new_degrees = 0;
            
        }
        
        if(speed != 0){
            if(new_degrees == 0){
                qik_2s12v10_motorcontroller.set_m0_speed(speed);
                qik_2s12v10_motorcontroller.set_m1_speed(-speed);
            } else if(new_degrees >0 ){
                // turn left
                qik_2s12v10_motorcontroller.set_m0_speed((speed+new_degrees/4)/3);
                qik_2s12v10_motorcontroller.set_m1_speed(-(speed+new_degrees/4));

            } else{
                // turn right
                qik_2s12v10_motorcontroller.set_m0_speed((speed+new_degrees/4));
                qik_2s12v10_motorcontroller.set_m1_speed(-(speed+new_degrees/4)/3);
            }
        }
        
    }
    void beetle_c::move (const int8_t &distance){

    }
    void beetle_c::move (const int8_t &x, const int8_t &y){

    }
}