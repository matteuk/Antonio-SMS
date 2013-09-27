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

#define MAIL_TO_SMS_COOKIE   9997
#define TOTAL_WHO 2
#define TOTAL_MSG 3
	
Window mainWindow;
TextLayer whoLayer, msgLayer, cmdLayer;
int who_sel = 0;
int msg_sel = 0;
const char *nam_list[] = {"Antonio",                   "Lori"};
const char *who_list[] = {"4165621384@sms.rogers.com", "4162713650@sms.rogers.com"};
const char *msg_list[] = {"Running%20late", "On%20my%20way%20home", "Busy,%20call%20you%20later"};
const char *tmp_list[] = {"Running late",   "On my way home",       "Busy, call you later"};
static char nam_text[64];
static char msg_text[64];

void request_mail_to_sms() {
    DictionaryIterator *body;
    static char who[64];
    static char msg[64];
    static char url[256];

//    strcpy(url, "http://antonioasaro.site50.net/mail_to_sms.php?cmd=junk");
    strcpy(url, "http://antonioasaro.site50.net/mail_to_sms.php?cmd=send");
    strcpy(who, "&who="); strcat(who, who_list[who_sel]); 
	strcpy(msg, "&msg="); strcat(msg, msg_list[msg_sel]);
	strcat(url, who); strcat(url, msg);
 	if (http_out_get(url, false, MAIL_TO_SMS_COOKIE, &body) != HTTP_OK ||
        http_out_send() != HTTP_OK) {
    }
}

void up_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
	who_sel++; if (who_sel == TOTAL_WHO) who_sel = 0;
	strcpy(nam_text, "To: "); strcat(nam_text, nam_list[who_sel]);
    text_layer_set_text(&whoLayer, nam_text);
}

void select_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
//    text_layer_set_text(&cmdLayer, "select_single_click");
}

void select_long_click_handler(ClickRecognizerRef recognizer, Window *window) {
    text_layer_set_text(&cmdLayer, "Sending ...");
    request_mail_to_sms();
}

void down_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
	msg_sel++; if (msg_sel == TOTAL_MSG) msg_sel = 0;
	strcpy(msg_text, "Msg: "); strcat(msg_text, tmp_list[msg_sel]);
    text_layer_set_text(&msgLayer, msg_text);
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

void failure(int32_t cookie, int http_status, void *ctx) {
    text_layer_set_text(&cmdLayer, "Tried.");
    if (cookie == MAIL_TO_SMS_COOKIE) {
        text_layer_set_text(&cmdLayer, "Failed.");
    }
}

void success(int32_t cookie, int http_status, DictionaryIterator *dict, void *ctx) {
    if (cookie == MAIL_TO_SMS_COOKIE) {
        text_layer_set_text(&cmdLayer, "Success!!");
    }
}

void handle_init(AppContextRef ctx) {

    //Main Window init :: BEGIN
    window_init(&mainWindow, "Status");
    window_stack_push(&mainWindow, true /* Animated */);
    
    text_layer_init(&whoLayer, GRect(5, 10,  135, 30));
    layer_add_child(&mainWindow.layer, &whoLayer.layer);
    text_layer_set_font(&whoLayer,fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));

    text_layer_init(&msgLayer, GRect(5, 40,  135, 60));
    layer_add_child(&mainWindow.layer, &msgLayer.layer);
    text_layer_set_font(&msgLayer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
    
    text_layer_init(&cmdLayer, GRect(5, 110, 135, 40));
    layer_add_child(&mainWindow.layer, &cmdLayer.layer);
    text_layer_set_font(&cmdLayer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));

    window_set_click_config_provider(&mainWindow, (ClickConfigProvider) config_provider);
    //Main Window init :: END

	//Main Window init :: BEGIN
 	strcpy(nam_text, "To: ");  strcat(nam_text, nam_list[who_sel]);
 	strcpy(msg_text, "Msg: "); strcat(msg_text, tmp_list[msg_sel]);
    text_layer_set_text(&whoLayer, nam_text);
    text_layer_set_text(&cmdLayer, "Send. Y/N?");
    text_layer_set_text(&msgLayer, msg_text);

    http_set_app_id(39152173);
    http_register_callbacks((HTTPCallbacks){
        .success=success,
        .failure=failure
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
