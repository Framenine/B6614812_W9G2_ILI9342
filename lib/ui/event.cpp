#include <event.h>
#include <Arduino.h>

void event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    int *pLED = (int *)lv_event_get_user_data(e);
    //int *pLED2 = (int *)lv_event_get_user_data(e);
    if (obj == objects.valve_bt && code == LV_EVENT_PRESSED)
    {
        gpio_set_level((gpio_num_t)*pLED, 1);
    }
    else if (obj == objects.valve_bt&& code == LV_EVENT_RELEASED)
    {
        gpio_set_level((gpio_num_t)*pLED, 0);
    }
    else if (obj == objects.sw_pump){
            char buf[32];
            lv_roller_get_selected_str(objects.pwmpercent, buf,sizeof(buf));
            int pwmpercentchoose = String(buf).toInt();
            if (lv_obj_has_state(objects.sw_pump, LV_STATE_CHECKED)){
                int pwmval = pwmpercentchoose * 255/100;
                analogWrite(22, pwmval);
                //gpio_set_level((gpio_num_t)*pLED, pwmval);//ได้เเค่ 0-1
                Serial.print("PWM : ");
                Serial.println(pwmval);

            }
            else
            {
               analogWrite(22, 0);
               //gpio_set_level((gpio_num_t)*pLED, 0);
            }
            
        }
}
void get_sw_state(lv_timer_t *timer)
{   
    int *pSW = (int *)timer->user_data;
    int sw_state = digitalRead(*pSW);

    if (sw_state == LOW)
    {
        lv_led_on(objects.motor_st);
    }
    else
    {
        lv_led_off(objects.motor_st);
    }
}
void update_adc33_val(lv_timer_t * timer){

    LV_UNUSED(timer);
    int adc33_val = analogRead(33);
    int adc33_100 = map(adc33_val,0,4095,0,100);
    lv_meter_set_indicator_value(objects.adc33bar, indicator1,adc33_val);
    lv_label_set_text(objects.adc33val,String(adc33_val).c_str());
    lv_bar_set_value(objects.adc33bar, adc33_100, LV_ANIM_OFF);
}
void update_adc34_val(lv_timer_t * timer){

    LV_UNUSED(timer);
    int adc34_val = analogRead(34);
     int adc34_100 = map(adc34_val,0,4095,0,100);
    lv_meter_set_indicator_value(objects.adc34meter, indicator1,adc34_100);
    lv_label_set_text(objects.adc34val,String(adc34_100).c_str());
}
void update_adc34_meter(lv_timer_t *timer)
{
    LV_UNUSED(timer);
     int adc_val = analogRead(34);
    int adc34_100 = map(adc_val,0,4095,0,100);
    lv_meter_set_indicator_value(objects.adc34val,
                                 indicator1,
                                 adc34_100);
    //lv_label_set_text(objects.adc33val, String(analogRead(34)).c_str());
     lv_label_set_text(objects.adc34val, String(adc34_100).c_str());
}









