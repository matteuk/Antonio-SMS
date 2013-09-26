#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"

#include "http.h"
#include "itoa.h"

#define MY_UUID { 0x91, 0x41, 0xB6, 0x28, 0xBC, 0x89, 0x49, 0x8E, 0xB1, 0x47, 0x04, 0x9F, 0x49, 0xC0, 0x99, 0xAD }
PBL_APP_INFO(HTTP_UUID,
    "Antonio SMS", "Antonio Asaro",
    1, 0, /* App version */
    RESOURCE_ID_MENU_ICON,
    APP_INFO_STANDARD_APP);

Window mainWindow;
TextLayer whoLayer, msgLayer, cmdLayer;
#define SMS_SEND_COOKIE   9997

	
void up_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
    text_layer_set_text(&whoLayer, "up_single_click");
    text_layer_set_text(&msgLayer, "");
    text_layer_set_text(&cmdLayer, "");
}

void select_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
    text_layer_set_text(&whoLayer, "");
    text_layer_set_text(&msgLayer, "select_single_click");
    text_layer_set_text(&cmdLayer, "");
}

void select_long_click_handler(ClickRecognizerRef recognizer, Window *window) {
    text_layer_set_text(&whoLayer, "");
    text_layer_set_text(&msgLayer, "select_long_click");
    text_layer_set_text(&cmdLayer, "");
}

void down_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
    text_layer_set_text(&whoLayer, "");
    text_layer_set_text(&msgLayer, "");
    text_layer_set_text(&cmdLayer, "down_single_click");
}

void config_provider(ClickConfig **config, Window *window) {
    // single click / repeat-on-hold config:
    config[BUTTON_ID_SELECT]->click.handler = (ClickHandler) select_single_click_handler;
    config[BUTTON_ID_UP]->click.handler = (ClickHandler) up_single_click_handler;
    config[BUTTON_ID_DOWN]->click.handler = (ClickHandler) down_single_click_handler;
    
    // long click config:
    config[BUTTON_ID_SELECT]->long_click.handler = (ClickHandler) select_long_click_handler;
    config[BUTTON_ID_UP]->click.repeat_interval_ms = 500;
    config[BUTTON_ID_DOWN]->click.repeat_interval_ms = 500;
    config[BUTTON_ID_SELECT]->long_click.delay_ms = 700;
}

void failed(int32_t cookie, int http_status, void *ctx) {
    if (cookie == SMS_SEND_COOKIE) {
    }
}

void success(int32_t cookie, int http_status, DictionaryIterator *dict, void *ctx) {
	if (cookie == SMS_SEND_COOKIE) {
	}
}

void handle_init(AppContextRef ctx) {

    //Main Window init :: BEGIN
    window_init(&mainWindow, "Status");
    window_stack_push(&mainWindow, true /* Animated */);
    
    text_layer_init(&whoLayer, GRect(15, 5, 130, 55));
    layer_add_child(&mainWindow.layer, &whoLayer.layer);
    text_layer_set_font(&whoLayer,fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21));

    text_layer_init(&msgLayer, GRect(15, 55, 130, 105));
    layer_add_child(&mainWindow.layer, &msgLayer.layer);
    text_layer_set_font(&msgLayer, fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21));
    
    text_layer_init(&cmdLayer, GRect(15, 105, 130, 155));
    layer_add_child(&mainWindow.layer, &cmdLayer.layer);
    text_layer_set_font(&cmdLayer, fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21));

    window_set_click_config_provider(&mainWindow, (ClickConfigProvider) config_provider);
    //Main Window init :: END

    http_set_app_id(39152173);
    http_register_callbacks((HTTPCallbacks){
        .success=success,
        .failure=failed
    }, (void*)ctx);

}

void pbl_main(void *params) {
    PebbleAppHandlers handlers = {
        .init_handler = &handle_init,
        .messaging_info = {
            .buffer_sizes = {
                .inbound = 256,
                .outbound = 256,
            }
        },
    };
    app_event_loop(params, &handlers);
}