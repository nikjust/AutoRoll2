#include "application.h"

//#include "night_mode.h"
#include "sys_macro.h"
#include "misc/ntp_time.h"




//void Application::load() {
//    //const auto &preset = this->preset();
//}
//
//void Application::update() {
//    config_storage.save();
//
//    load();
//}

void Application::change_state(AppState s) {
    state_change_time = millis();
    state = s;
}

void Application::restart() {
    //if (config_storage.is_pending_commit()) config_storage.force_save();
    ESP.restart();
}

Application::Application(steppers &_stp):stp(_stp) {
    this->stp = _stp;
}

