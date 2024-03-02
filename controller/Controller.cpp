/*
* @Author: Qianhua Liu
* @Date: 2024-01-06
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/
#include "controller/Controller.h"

#include <assert.h>

namespace localminmax::controller {

Controller::Controller(const std::string& file_path) : m_file_path(file_path) {}

bool Controller::run()
{
    std::string error_msg = "";
    bool run_status = true;
    
    run_status = parseInputFile(error_msg);
    if (!run_status) {
        // log error
        assert(run_status);
    }

    run_status = runMeasurement(error_msg);
    if (!run_status) {
        // log error
        assert(run_status);
    }

    run_status = runResolver(error_msg);
    if (!run_status) {
        // log error
        assert(run_status);
    }

    return true;
}

bool Controller::runMeasurement(std::string& error_msg)
{    
    if (!createMpMeasurer(error_msg)) {
        // log error
        return false;
    }

    return true;
}

bool Controller::runResolver(std::string& error_msg)
{
    if (!createDefectResolver(error_msg)) {
        // log error
        return false;
    }

    return true;
}

bool Controller::parseInputFile(std::string& error_msg)
{
    m_measure_path1 = std::make_shared<MeasurePath>();
    m_measure_path2 = std::make_shared<MeasurePath>();
    return true;
}

bool Controller::createMpMeasurer(std::string& error_msg)
{
    
    return true;
}

bool Controller::createDefectResolver(std::string& error_msg)
{

    return true;
}

} // localminmax::controller
