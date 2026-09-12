#include <esp_log.h>
#include <esp_err.h>
#include <nvs.h>
#include <nvs_flash.h>
#include <driver/gpio.h>
#include <esp_event.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "application.h"

#define TAG "main"

extern "C" void app_main(void)
{
    ESP_LOGI(TAG, "==========================================");
    ESP_LOGI(TAG, "KOYODA-XIAO M1 IDLE SHELL");
    ESP_LOGI(TAG, "XiaoZhi core + Waveshare 1.75 native board");
    ESP_LOGI(TAG, "Display target orientation = 270 degrees");
    ESP_LOGI(TAG, "KOYODA idle face enabled only in true IDLE state");
    ESP_LOGI(TAG, "==========================================");
    // Initialize NVS flash for WiFi configuration
    ESP_LOGI(TAG, "M0.2 APP STEP NVS init");
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_LOGW(TAG, "Erasing NVS flash to fix corruption");
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    ESP_LOGI(TAG, "M0.2 APP PASS NVS init");

    // Initialize and run the application
    ESP_LOGI(TAG, "M0.2 APP STEP Application::Initialize()");
    auto& app = Application::GetInstance();
    app.Initialize();
    ESP_LOGI(TAG, "M0.2 APP PASS Application::Initialize()");
    ESP_LOGI(TAG, "M0.2 APP entering Application::Run()");
    app.Run();  // This function runs the main event loop and never returns
}
