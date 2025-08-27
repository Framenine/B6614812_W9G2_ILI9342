#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;
uint32_t active_theme_index = 0;

lv_meter_scale_t * scale0;
lv_meter_indicator_t * indicator1;

void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_tabview_create(parent_obj, LV_DIR_TOP, 32);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 240);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_tabview_add_tab(parent_obj, "Control");
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // pwmpercent
                            lv_obj_t *obj = lv_roller_create(parent_obj);
                            objects.pwmpercent = obj;
                            lv_obj_set_pos(obj, 18, 67);
                            lv_obj_set_size(obj, 130, 100);
                            lv_roller_set_options(obj, "20\n40\n60\n80\n100", LV_ROLLER_MODE_NORMAL);
                        }
                        {
                            // motor_st
                            lv_obj_t *obj = lv_led_create(parent_obj);
                            objects.motor_st = obj;
                            lv_obj_set_pos(obj, 223, 115);
                            lv_obj_set_size(obj, 32, 32);
                            lv_led_set_color(obj, lv_color_hex(0xff0000ff));
                            lv_led_set_brightness(obj, 255);
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 192, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "ValveControl");
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 192, 83);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "Motor Status");
                        }
                        {
                            // valve_bt
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.valve_bt = obj;
                            lv_obj_set_pos(obj, 189, 32);
                            lv_obj_set_size(obj, 100, 35);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Open valve");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 34, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "PWM Control");
                        }
                        {
                            // sw_pump
                            lv_obj_t *obj = lv_switch_create(parent_obj);
                            objects.sw_pump = obj;
                            lv_obj_set_pos(obj, 58, 29);
                            lv_obj_set_size(obj, 50, 25);
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 20, 34);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "OFF");
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 120, 34);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "ON");
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_tabview_add_tab(parent_obj, "Meter");
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // adc34meter
                            lv_obj_t *obj = lv_meter_create(parent_obj);
                            objects.adc34meter = obj;
                            lv_obj_set_pos(obj, 11, 41);
                            lv_obj_set_size(obj, 148, 147);
                            {
                                lv_meter_scale_t *scale = lv_meter_add_scale(obj);
                                scale0 = scale;
                                lv_meter_set_scale_ticks(obj, scale, 41, 1, 5, lv_color_hex(0xffa0a0a0));
                                lv_meter_set_scale_major_ticks(obj, scale, 8, 3, 10, lv_color_hex(0xff000000), 10);
                                lv_meter_set_scale_range(obj, scale, 0, 100, 300, 120);
                                {
                                    lv_meter_indicator_t *indicator = lv_meter_add_needle_line(obj, scale, 3, lv_color_hex(0xff0000ff), -28);
                                    indicator1 = indicator;
                                    lv_meter_set_indicator_value(obj, indicator, 30);
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 11, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "ADC33");
                        }
                        {
                            // adc33bar
                            lv_obj_t *obj = lv_bar_create(parent_obj);
                            objects.adc33bar = obj;
                            lv_obj_set_pos(obj, 72, 3);
                            lv_obj_set_size(obj, 150, 10);
                            lv_bar_set_value(obj, 25, LV_ANIM_OFF);
                        }
                        {
                            // adc33val
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.adc33val = obj;
                            lv_obj_set_pos(obj, 240, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "0");
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 35, 21);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "ADC34 Gauge");
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 176, 91);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "ADC34 Value");
                        }
                        {
                            // adc34val
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.adc34val = obj;
                            lv_obj_set_pos(obj, 176, 115);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "0");
                        }
                    }
                }
            }
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
}



typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_main();
}
