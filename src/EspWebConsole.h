#include "Arduino.h"
#include "ESP8266WebServer.h" 
#include "WebSocketsServer.h"
#include "LittleFS.h"
#include "ArduinoJson.h"

#define SETTINGS_PATH           "/settings.json"
#define DEFAULT_SETTINGS_PATH   "/default_settings.json"


class EspWebConsole{
    public:

        typedef void (*void_function_pointer)();
    
        EspWebConsole() : server(80) {
            LittleFS.begin();
        }
    
        void 
            set_callback(void_function_pointer offline),
            handle(),
            console_print(String output);

        bool
            begin();

        String
            load_setting(String setting);
    
    private:
        ESP8266WebServer server;
        WebSocketsServer websockets_server = WebSocketsServer(81);
        static void_function_pointer _restart;

        int8_t websockets_client = -1; //Current websockets client number connected to (-1 is none)
        File upload_file; //Holds file currently uploading
        
        //settings
        bool settings_page = true;
        bool console_page = true;
        String custom_page_path = "/contacts/";
        String custom_page_name = "Contacts";

        String get_content_type(String filename);
        bool handle_file_read(String path);
        void websockets_event(uint8_t num, WStype_t type, uint8_t * payload, size_t length);
        String text_input_HTML(String id, String val, String type, bool req);
        String multi_input_html(String id, String val, String type, JsonArray opt);
        String input_html(JsonArray settings);
        void handle_settings_get();
        void handle_settings_post();
        void handle_nav();
        bool check_settings_file();
        void handle_file_upload();
};